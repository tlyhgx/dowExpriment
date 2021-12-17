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
    timer500->start(dowInit->getAskPlc_cycle_ms());
}

void GetPlcVal::recieveReply(QModbusDataUnit dataUnit)
{
    //FIXME:此处可以考虑用switch
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

QVariantList GetPlcVal::getSignalVals() const
{
    return m_signalVals;
}

QVariantList GetPlcVal::getTempSignalVals() const
{
    return m_tempSignalVals;
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
