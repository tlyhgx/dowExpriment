#include "easytablemodel.h"
#include "mainbackend.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sortfilterproxymodel.h>
#include <QQmlContext>
#include <mymodbus.h>
#include <QtCore>
#include <realtimecurvebackend.h>
#include <dowdatabase.h>
#include <setparabackend.h>

#include "getplcval.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

//    QGuiApplication app(argc, argv);
    QApplication app(argc,argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<EasyTableModel>("EasyModel", 1, 0, "EasyTableModel");

    //设置初始值
    DowInit *dowInit=new DowInit ();
    dowInit->modbusSetting.portName="COM1";
    //实例化modbus
    MyModbus *myModbus=new MyModbus (*dowInit) ;

    DowDataBase::openDB();
//    DowDataBase::createTable();   //NOTE:打开后，会删除所有表格，并重新创建
    MainBackend mainBackend(dowInit,myModbus);
    RealTimeCurveBackend realTimeCurveBackend(dowInit,myModbus);
    SetParaBackend setParaBackend;
    GetPlcVal getPlcVal(dowInit,myModbus);
//TODO:初始化的参数，部分要从数据库读取

    engine.rootContext()->setContextProperty("mainBackend",&mainBackend);
    engine.rootContext()->setContextProperty("realTimeCurveBackend",&realTimeCurveBackend);
    engine.rootContext()->setContextProperty("setParaBackend",&setParaBackend);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
