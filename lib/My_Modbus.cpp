//
// Created by tangl on 2021-11-19.
//

#include "My_Modbus.h"
#include "qdebug.h"


My_Modbus::My_Modbus() {
    modbusDevice = new QModbusRtuSerialMaster(nullptr);
    connect(modbusDevice, SIGNAL(errorOccurred()), this, SLOT(modbusMessage()));

    if (modbusDevice) {
        qDebug("创建Modbus Master 成功!");
        modbusMessage("创建Modbus Master 成功!");
        connect(modbusDevice,&QModbusClient::stateChanged,this,&My_Modbus::modbusStateChanged);
    }else{
        qDebug("创建Modbus Master 失败!");
        modbusMessage("创建Modbus Master 失败!");
    }
}

My_Modbus::~My_Modbus() {
    delete modbusDevice;
}

void My_Modbus::modbusConnect() {
    if (!modbusDevice) {
        return;
    }

    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,m_settings.portName);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,m_settings.baud);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,m_settings.parity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,m_settings.dataBits);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,m_settings.stopBits);
        modbusDevice->setTimeout(m_settings.responseTime);
        modbusDevice->setNumberOfRetries(m_settings.numOfRetries);
    }

    if(modbusDevice->connectDevice())
    {
        QString info="Modbus连接成功!";
        qDebug()<<info;
        modbusMessage(info);
    }else
    {
        QString info="Modbus 连接失败!";
        qDebug()<<info;
        modbusMessage(info);
    }
}

void My_Modbus::modbusDisconnect() {
    if(modbusDevice)  modbusDevice->disconnectDevice();
    delete modbusDevice;
    modbusDevice=nullptr;
}

void My_Modbus::modbusRead(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries) {
    if (!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug("Modbus Device is not connected!");
        return;
    }

    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numOfEntries);

    if (auto *reply = modbusDevice->sendReadRequest(dataUnit, serverAddress)) {
        if (reply->isFinished()) {
            connect(reply,&QModbusReply::finished,this,&My_Modbus::modbusReadData);
        }

    } else{
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }
}

void My_Modbus::modbusWrite(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries,
                            QVector<quint16> data) {
    if (!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug("Modbus Device is not connected!");
        return;
    }

    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numOfEntries);
    for (int i = 0; i < dataUnit.valueCount(); ++i) {
        dataUnit.setValue(i, data.at(i));
    }

    if (auto *reply = modbusDevice->sendWriteRequest(dataUnit, serverAddress)) {
        connect(reply,&QModbusReply::finished,this,[this,reply](){
            if (reply->error() == QModbusDevice::ProtocolError) {
                modbusMessage(tr("Write response error:%1 (modbus exception:0x%2) ")
                .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(),-1,16));
            } else{
                modbusMessage(tr("Write response:%1 (code:0x%2")
                                      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
            }
            reply->deleteLater();
        });
    }
    else{
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }

}

void My_Modbus::modbusStateChanged(int state) {
    if (state == QModbusDevice::UnconnectedState) {
        qDebug("Modbus 已断开！");
    } else if (state == QModbusDevice::ConnectedState) {
        qDebug("Modbus 已连接！");
    }
}

void My_Modbus::modbusMessage(void) {
    QString info=modbusDevice->errorString();
    qDebug()<<info;
    modbusInfo=info.toStdString();
}

void My_Modbus::modbusMessage(QString mess) {

    qDebug()<<mess;
    modbusInfo=mess.toStdString();
}

void My_Modbus::modbusReadData(void) {
    QModbusDataUnit dataUnit;
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply) {
        return;
    }
    if (reply->error() == QModbusDevice::NoError) {
        dataUnit=reply->result();
        emit(modbusReadReady(dataUnit));
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        modbusMessage(tr("Read response error:%1 (Modbus expection :0x%2)")
                              .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
    }else{
        modbusMessage(tr("Read response: %1(code :0x%2")
                              .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
    }
    reply->deleteLater();
}
