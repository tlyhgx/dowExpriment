#include "mymodbus.h"

#include <QModbusRtuSerialMaster>
#include <QtMath>

MyModbus::MyModbus()
{

    modbusDevice=new QModbusRtuSerialMaster;

    if(modbusDevice)
    {
        qDebug("create Modbus master success!");
    }
    else
    {
        qDebug("create Modbus Master failse!");
    }



    modbusConnect();

}

MyModbus::MyModbus(const DowInit &dowInit)
{
    //FIXME:如果已存在modbusDevice，则先删除
    modbusDevice=new QModbusRtuSerialMaster;

    if(modbusDevice)
    {
        qDebug("create Modbus master success!");
    }
    else
    {
        qDebug("create Modbus Master failse!");
    }

    m_settings.portName= dowInit.modbusSetting.portName;
    m_settings.baud=dowInit.modbusSetting.baud;
    m_settings.parity=dowInit.modbusSetting.parity;
    m_settings.dataBits=dowInit.modbusSetting.dataBits;
    m_settings.stopBits=dowInit.modbusSetting.stopBits;
    m_settings.responseTime=dowInit.modbusSetting.responseTime;
    m_settings.numberOfRetries=dowInit.modbusSetting.numberOfRetries;

    modbusConnect();

}

MyModbus::~MyModbus()
{
    modbusDisconnect();

}

void MyModbus::modbusConnect()
{
    if(!modbusDevice)return;
    if(modbusDevice->state()!=QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,m_settings.portName);

        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,m_settings.baud);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,m_settings.parity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,m_settings.dataBits);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,m_settings.stopBits);

        modbusDevice->setTimeout(m_settings.responseTime);
        modbusDevice->setNumberOfRetries(m_settings.numberOfRetries);


        if(modbusDevice->connectDevice())
        {
            qDebug("Modbus create success.");
        }else
        {
            qDebug("Modbus create failse.");
        }

    }
}

void MyModbus::modbusDisconnect()
{
    if(modbusDevice)modbusDevice->disconnectDevice();
    delete modbusDevice;
    modbusDevice=nullptr;
}

void MyModbus::modbusRead(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries)
{
    if(!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qDebug("Modbus Device is not connected!");
        return;
    }


    QModbusDataUnit ReadRequest(table, startAddress, numOfEntries);





    if(auto *reply = modbusDevice->sendReadRequest(ReadRequest, serverAddress))
    {
        if(!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, &MyModbus::modbusReadData);
        }
        else{
            delete reply; // broadcast replies return immediately
        }
    }
    else
    {
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }

}

void MyModbus::modbusReadData()
{
    QModbusDataUnit dataUnit;
    auto reply = qobject_cast<QModbusReply *>(sender());
    if(!reply) return;

    if(reply->error() == QModbusDevice::NoError)
    {
        dataUnit = reply->result();
        int res=dataUnit.value(0);

//        qDebug("Items in list: %d", res);
//        for (uint i = 0; i < dataUnit.valueCount(); i++) {//获取每个结果
//                               int res=dataUnit.value(0);
//                                }
        emit modbusReadReady(dataUnit);
    }
    else if(reply->error() == QModbusDevice::ProtocolError)
    {
        modbusMessage(tr("Read response error: %1 (Modbus exception :0x%2)")
                      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1 ,16));
    }
    else
    {
        modbusMessage(tr("Read response: %1 (code :0x%2)")
                      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1 ,16));
    }

    reply->deleteLater();

}

void MyModbus::modbusWrite(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data)
{
    if(!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qDebug("Modbus Device is not connected!");
        return;
    }

    //QModbusDataUnit，是用来处理通过串口一次传输的数据
    QModbusDataUnit dataunit = QModbusDataUnit(table, startAddress, numOfEntries);

    for(uint i = 0; i < dataunit.valueCount(); i++)
    {
        dataunit.setValue( i,  data.at(i));
    }

    if(auto *reply = modbusDevice->sendWriteRequest(dataunit,  serverAddress))
    {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if(reply->error() == QModbusDevice::ProtocolError){
                    modbusMessage(tr("Write response error:%1 (modbus exception:0x%2)")
                                  .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
                }else if (reply->error() != QModbusDevice::NoError) {
                    qDebug()<<tr("Write response error: %1 (code: 0x%2)").
                              arg(reply->errorString()).arg(reply->error(), -1, 16);
                }

                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else{
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }

}
//为适应PLC数据占用两个字节的情况
void MyModbus::modbusWrite_twoBytes(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data)
{
    if(!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qDebug("Modbus Device is not connected!");
        return;
    }

    //QModbusDataUnit，是用来处理通过串口一次传输的数据
    QModbusDataUnit dataunit = QModbusDataUnit(table, startAddress, numOfEntries*2);

    for(uint i = 0; i < dataunit.valueCount(); i++)
    {
        dataunit.setValue(i,data.at(i));
    }

    if(auto *reply = modbusDevice->sendWriteRequest(dataunit,  serverAddress))
    {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if(reply->error() == QModbusDevice::ProtocolError){
                    modbusMessage(tr("Write response error:%1 (modbus exception:0x%2)")
                                  .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
                }else if (reply->error() != QModbusDevice::NoError) {
                    qDebug()<<tr("Write response error: %1 (code: 0x%2)").
                              arg(reply->errorString()).arg(reply->error(), -1, 16);
                }

                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else{
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }
}




//void MyModbus::setSingleCoil(int startAddress, bool state)
//{
//    QModbusDataUnit writeUnit = writeCoilsRequest();
//    writeUnit.setStartAddress(startAddress);
//    writeModel->m_coils.setBit(writeUnit.startAddress(),state);
//    writeUnit.setValue(0, writeModel->m_coils[ writeUnit.startAddress()]);
//    modbusDevice->sendWriteRequest(writeUnit, 1);
//}

//void MyModbus::tc_test()
//{
//    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 44103, 1); // write 1 value in address 40003
//    writeUnit.setValue(0, 0x253);
//    //这里先建好QModbusDataUnit

//    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, 1))
//    //发送写请求
//    {
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, this, [this, reply]()
//            {
//                if (reply->error() != QModbusDevice::NoError)
//                        // error in reply

//                    reply->deleteLater();
//                });
//        }
//        else
//        {
//            if (reply->error() != QModbusDevice::NoError)
//                // error in reply

//            // broadcast replies return immediately
//            reply->deleteLater();
//        }
//    }
//    else
//    {
//        // error in request
//    }
//}

//QModbusDataUnit MyModbus::writeCoilsRequest() const
//{
//    const auto table =
//            static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::Coils);

//    int startAddress = 1;

//    quint16 numberOfEntries = 1;
//    return QModbusDataUnit(table, startAddress, numberOfEntries);
//}

void MyModbus::modbusMessage()
{
    qDebug() << modbusDevice->errorString();
}

void MyModbus::modbusMessage(QString mess)
{
    qDebug() << mess;
}





