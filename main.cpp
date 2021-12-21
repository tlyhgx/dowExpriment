
#include "mainbackend.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <hwwalarm.h>

#include <QQmlContext>
#include <mymodbus.h>
#include <QtCore>
#include <realtimecurvebackend.h>
#include <dowdatabase.h>
#include <setparabackend.h>
#include <infolist.h>

#include "getplcval.h"
#include <QtWidgets/QApplication>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

//    QGuiApplication app(argc, argv);





    QApplication app(argc,argv);

    QQmlApplicationEngine engine;



    //设置初始值
    DowInit *dowInit=new DowInit ();

    //实例化modbus
    MyModbus *myModbus=new MyModbus (*dowInit) ;
    GetPlcVal *getPlcVal=new GetPlcVal(dowInit,myModbus);
    DowDataBase::openDB();
//    DowDataBase::createTable();   //NOTE:打开后，会删除所有表格，并重新创建
    //TODO1: 每次脱离test，都要操作一次，能否处理一下
    MainBackend mainBackend(dowInit,getPlcVal);
    RealTimeCurveBackend realTimeCurveBackend(dowInit,getPlcVal);
    SetParaBackend setParaBackend(dowInit,getPlcVal);
    HwwAlarms hwwAlarms(getPlcVal);



    engine.rootContext()->setContextProperty("mainBackend",&mainBackend);
    engine.rootContext()->setContextProperty("realTimeCurveBackend",&realTimeCurveBackend);
    engine.rootContext()->setContextProperty("setParaBackend",&setParaBackend);

    InfoListModel infoListModel;
    mainBackend.setInfoListModel(infoListModel);
    //把报警添加到mainBackend
    HwwAlarms alarmsInfo(getPlcVal);
    mainBackend.setAlarmsInfo(alarmsInfo);

    engine.rootContext()->setContextProperty("infoListModel",&infoListModel);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
