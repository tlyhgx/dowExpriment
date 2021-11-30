#ifndef DOWINIT_H
#define DOWINIT_H

#include <QObject>

class DowInit : public QObject
{
    Q_OBJECT
public:
    explicit DowInit(QObject *parent = nullptr);
public:
    struct PlcMemoryAddress{
        int signal=2060;   //信号地址,M地址，PLC集中在一起另外配置
        int signalNum=8;   //信号个数
    };

     PlcMemoryAddress plcMemoryAddress;

     struct ModbusSetting{
         QString portName="COM1";
     };
     ModbusSetting modbusSetting;


signals:

};

#endif // DOWINIT_H
