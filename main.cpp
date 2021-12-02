#include "easytablemodel.h"
#include "mainbackend.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sortfilterproxymodel.h>
#include <QQmlContext>
#include <mymodbus.h>





int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<EasyTableModel>("EasyModel", 1, 0, "EasyTableModel");

    //设置初始值
    DowInit *dowInit=new DowInit ();

//    qmlRegisterType<MainBackend>("MainBackendClass", 1, 0, "MainBackend");



    dowInit->modbusSetting.portName="COM1";
    //实例化modbus
    MyModbus *myModbus=new MyModbus () ;

    MainBackend mainBackend(dowInit,myModbus);

//    mainBackend.setDowInit(dowInit);
//    mainBackend.setMyModbus(myModbus);
    engine.rootContext()->setContextProperty("mainBackend",&mainBackend);







    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
