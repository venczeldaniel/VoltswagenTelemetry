#include "StvApplication.h"

StvApplication::StvApplication(int argc, char *argv[])
    : QApplication(argc, argv), engine(), history(), serialPort(QString("COM3"),115200,QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop),
      robot(history, serialPort), handler(robot, *engine.rootContext(), history)
{

    serialPort.connect();
    // Szimulálunk egy history változást, mert attól kezdve léteznek a QML oldalon
    //  a C++ oldalról származó változók. (Különben referencia hibákat kapnánk a QML oldalon
    //  egészen addig, amíg az első üzenet meg nem jönne a szimulátortól.
    handler.historyChanged();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // A QML gyökérelemre szükségünk van ahhoz, hogy tudjunk hivatkozni a QML-es elemekre.
    auto rootObjects = engine.rootObjects();
    if (rootObjects.size() == 0)
    {
        qDebug() << "HIBA: Nem sikerült létrehozni a QML környezetet.";
        return;
    }
    // A QML környezet is felállt, bekötjük a signalokat a QML és C++ oldal között.
    QObject *rootObject = rootObjects[0];
    // A handler beköti a saját signaljait.
    //handler.ConnectQmlSignals(rootObject);
    handler.setRootObject(rootObject);
    // Bekötjük a nyomógombok signaljait.
    QObject::connect(rootObject, SIGNAL(valueSetCommandCpp()),
                     &handler, SLOT(valueSetCommand()));
    QObject::connect(rootObject, SIGNAL(testCommandCpp()),
                     &handler, SLOT(testCommand()));
}

