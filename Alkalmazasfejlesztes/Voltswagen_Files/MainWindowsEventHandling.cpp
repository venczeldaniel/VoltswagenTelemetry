#include "MainWindowsEventHandling.h"
#include "RobotProxy.h"
#include <QQmlContext>
#include "RobotStateHistory.h"

#include <QQuickItem>
#include <QQmlApplicationEngine>

//Konstruktor
MainWindowsEventHandling::MainWindowsEventHandling(
        RobotProxy &robot, QQmlContext& qmlContext, RobotStateHistory& history)
    : robot(robot), qmlContext(qmlContext), history(history), rootObject(NULL)
{
    QObject::connect(&history, SIGNAL(historyChanged()), this, SLOT(historyChanged()));
}
//rootObject beállítása a GUI-val történő adatcseréhez
void MainWindowsEventHandling::setRootObject(QObject *root)
{
 rootObject = root;
}
//GUI-ról jövő signal slot-ja, a beállított paraméterek kiküldése
void MainWindowsEventHandling::valueSetCommand()
{

    QString command;
    QString kP_s, kD_s, servo_s;
    QObject *kPValue = rootObject->findChild<QObject*>("kPValue");
    if (kPValue)
       kP_s =  kPValue->property("text").toString();

    QObject *kDValue = rootObject->findChild<QObject*>("kDValue");
    if (kDValue)
       kD_s =  kDValue->property("text").toString();

    QObject *servoSlider = rootObject->findChild<QObject*>("servoSlider");
    if (servoSlider)
       servo_s =  servoSlider->property("value").toString();

    qDebug() << kP_s;
    qDebug() << kD_s;
    qDebug() << servo_s;

    command = "2:" + kP_s + " " + kD_s + " " + servo_s +  " ;";
    robot.sendString(command);
}
//Tesztparancs kiküldése gombnyomásra
void MainWindowsEventHandling::testCommand()
{
    robot.sendString("!");
}



void MainWindowsEventHandling::historyChanged()
{
    // Ahhoz, hogy frissüljenek a QML oldali adatok, frissíteni kell a változók összekapcsolását.
    qmlContext.setContextProperty(QStringLiteral("historyModel"), QVariant::fromValue(history.stateList));
    qmlContext.setContextProperty(QStringLiteral("currentState"), QVariant::fromValue(history.currentState));

    // Jelzünk a QML controloknak, hogy újrarajzolhatják magukat, beállítottuk az új értékeket.
    emit historyContextUpdated();
}

QQuickItem* MainWindowsEventHandling::FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = FindItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}
//rootobject-ből kiindulva megkeresi a name nevű leszármazottat
QQuickItem* MainWindowsEventHandling::FindItemByName(QObject *rootObject, const QString& name)
{
    return FindItemByName(rootObject->children(), name);
}

