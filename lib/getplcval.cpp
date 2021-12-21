#include "getplcval.h"



GetPlcVal::GetPlcVal(DowInit *dowInit, MyModbus *mymodbus, QObject *parent)
{
    Q_UNUSED(parent);
    this->dowInit=dowInit;
    myModbus=mymodbus;

    connect(myModbus,&MyModbus::modbusReadReady,
            this,&GetPlcVal::recieveReply);

    QTimer *timer500=new QTimer;
    connect(timer500,&QTimer::timeout,this,&GetPlcVal::askOtherSignalVals);
    connect(timer500,&QTimer::timeout,this,&GetPlcVal::askTempSignalVals);
    connect(timer500,&QTimer::timeout,this,&GetPlcVal::ask_alarm_from_plc);

    timer500->start(dowInit->getAskPlc_cycle_ms());
}

void GetPlcVal::recieveReply(QModbusDataUnit dataUnit)
{
    //FIXME:此处可以考虑用switch
//    qDebug()<<dataUnit.startAddress();
    if (dataUnit.startAddress()==dowInit->plcMemoryAddress.other_signal){
        QVariantList signalVals;
        int x_high,x_low;
        float res_parse;
        for(uint i=0;i<(dataUnit.valueCount());i++)
        {
            if(i%2==0){
                x_high=dataUnit.values()[i+1];
                x_low=dataUnit.values()[i];
                res_parse=parseInt2Float(x_high,x_low);
                signalVals<<res_parse;
            }
        }

        emit otherSignalValChanged(signalVals);
        m_signalVals= signalVals;
    }

    else if (dataUnit.startAddress()==dowInit->plcMemoryAddress.temp_signal){
        QVariantList tempSignalVals;
        for(uint i=0;i<(dataUnit.valueCount());i++)
        {
            tempSignalVals<< dataUnit.values()[i]*0.1;
        }
        emit tempSignalValChanged(tempSignalVals);
        m_tempSignalVals=tempSignalVals;
    }
    else if(dataUnit.startAddress()==dowInit->plcMemoryAddress.para_to_plc){
        QVariantList paraVals;
        int x_high,x_low;
        float res_parse;
        for(uint i=0;i<(dataUnit.valueCount());i++)
        {

            if(i>=0 && i<=3){
                if(i%2==0){
                    paraVals<<dataUnit.values()[i]*0.1;
                }
            }else if(i>3 && i<6){
                if(i%2==0){
                    paraVals<<dataUnit.values()[i];
                }
            }else if(i>=6 &&i<=13)
            {
                if(i%2==0){
                    x_high=dataUnit.values()[i+1];
                    x_low=dataUnit.values()[i];
                    res_parse=parseInt2Float(x_high,x_low);
                    paraVals<<res_parse;
                }
            }else if(i>=14 && i<=15)
            {
                if(i%2==0){
                    paraVals<<dataUnit.values()[i]*0.1;
                }
            }

        }
        emit paraValsChanged(paraVals);
        m_paraVals=paraVals;
    }
    else if(dataUnit.startAddress()==dowInit->plcMemoryAddress.alarm){
        int just_alarm_from_plc=dataUnit.values()[0];
        if(m_alarms!=just_alarm_from_plc){
            emit alarmsChanged(m_alarms,just_alarm_from_plc);
            m_alarms=just_alarm_from_plc;
        }

    }
}



void GetPlcVal::askOtherSignalVals()
{
    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
                         dowInit->plcMemoryAddress.other_signal,dowInit->getSignalValsNum()*2);
}

void GetPlcVal::askTempSignalVals()
{
    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
                         dowInit->plcMemoryAddress.temp_signal,dowInit->getTempSignalValsNum());
}

int GetPlcVal::getAlarms() const
{
    return m_alarms;
}

QVariantList GetPlcVal::getParaVals() const
{
    return m_paraVals;
}

QVariantList GetPlcVal::getSignalVals() const
{
    return m_signalVals;
}

QVariantList GetPlcVal::getTempSignalVals() const
{
    return m_tempSignalVals;
}

void GetPlcVal::setPara_to_plc(int startAddress, QList<Para_with_plc> paras)
{
    QVector<quint16>data;
    for(int i=0;i<paras.size();i++)
    {
        data<<paras[i].getResVal_DWORD()[0]<<paras[i].getResVal_DWORD()[1];
    }
    myModbus->modbusWrite_twoBytes(1,QModbusDataUnit::HoldingRegisters,startAddress,
                                   paras.size(),data);
}



void GetPlcVal::askPara_from_plc(int startAddress, QList<Para_with_plc> paras)
{
    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
                         startAddress,paras.size()*2);

}

void GetPlcVal::ask_alarm_from_plc()
{

    myModbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,
                         dowInit->plcMemoryAddress.alarm,1);
}

void GetPlcVal::startSys()
{  //TODO1:
    QVector<quint16> data;
    data<<1;
    myModbus->modbusWrite(1,QModbusDataUnit::HoldingRegisters,dowInit->plcMemoryAddress.startCommand,
                          1,data);
}

void GetPlcVal::stopSys()
{
    QVector<quint16> data;
    data<<0;
    myModbus->modbusWrite(1,QModbusDataUnit::HoldingRegisters,dowInit->plcMemoryAddress.startCommand,
                          1,data);
}



/**ModbusRTU格式的2个32位整数转浮点数，高位为x1,低位为x2
  * @brief MyModbus::parseInt2Float
  * @param x1
  * @param x2
  * @return
  * QModbusTcpClient接收数据处理的时候，一般方法是

const QModbusDataUnit unit = reply->result();

unit.value(0) 的值默认是无符号整数quint16，如果要取得浮点数，用上面函数如下操作：

     float t1 = parseInt2Float(unit.value(1),unit.value(0));

     //第二个字节在前

     float t1 = parseInt2Float(14969,62470);
  * https://blog.csdn.net/ydyuse/article/details/108951509
  */
float GetPlcVal:: parseInt2Float(int x1, int x2) {

    int f, fRest, exponent, exponentRest;

    float value, weishu;

    f = x1 / 32768;

    fRest = x1 % 32768;

    exponent = fRest / 128;

    exponentRest = fRest % 128;

    weishu = (float)(exponentRest * 65536 + x2) / 8388608;

    value = (float)qPow(-1, f) * (float)qPow(2, exponent - 127) * (weishu + 1);

    return value;

}
///把浮点数转换为2个word
/// \brief GetPlcVal::parseFloat2Int
/// \param input_float
/// \return
///https://blog.csdn.net/qq_45086135/article/details/120099693
vector<int16_t> GetPlcVal::parseFloat2Int(float input_float)
{

    vector<int16_t> res_dword;
    /*拆分 */
    int16_t *pa1=(int16_t *)(&input_float);
    int16_t *pa2=pa1+1;

    //    //定义一个同类型对象，用来接收组合后的结果
    //    float b=0.0;
    //    int16_t *pb1=(int16_t *)(&b);
    //    int16_t *pb2=pb1+1;

    //    //组合
    //    *pb1=*pa1;
    //    *pb2=*pa2;


    res_dword.push_back(*pa1);
    res_dword.push_back(*pa2);
    return res_dword;

}
