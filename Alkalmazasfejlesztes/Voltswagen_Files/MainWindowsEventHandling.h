#pragma once
#ifndef MAINWINDOWSEVENTHANDLING_H
#define MAINWINDOWSEVENTHANDLING_H
#include <QObject>
#include <QDebug>

class RobotProxy;
class QQmlContext;
class RobotStateHistory;

class QQuickItem;
class QQmlApplicationEngine;

/**
 * @brief Ez az osztály tartalmazza a felhasználó felület (GUI) eseménykezelőit.
 *
 * A függőségeit a konstruktoron kereszül kapja meg és kapcsolódik a GUI
 * signaljaihoz.
 *
 */
class MainWindowsEventHandling : public QObject
{
    Q_OBJECT

public:
    /** Konstruktor
     *
     * @param robot A robot proxy példány
     * @param qmlContext    A QML context objektum
     * @param history   A használt RobotStateHistory objektum.
     */
    MainWindowsEventHandling(RobotProxy& robot, QQmlContext &qmlContext, RobotStateHistory &history);
    /** Dekonstruktor */
    ~MainWindowsEventHandling() = default;

    /** Beállítja az osztály változóját az
     *
     * @param root A QML gyökérelem.
     *
     * @sa StvApplication::StvApplication (int argc, char *argv[])
     */
    void setRootObject(QObject *root);

public slots:
    /** A GUI beivteli mezői gombjának eseménykezelője. */
    void valueSetCommand();
    /** A tesztszekvencia indításának eseménykezelője*/
    void testCommand();

    /** Azt jelzi, hogy változott az állapot history. (Tipikusan mert új állapot érkezett a robottól.)
     * Frissíti a QML számára elérhetővé tett, C++ oldali változókat (propertyket) és
     * kiváltja a historyContextUpdated() signalt.
    */
    void historyChanged();

signals:
    /** Jelzi, hogy változott a megjelenítés számára az adatmodell.
     * Ilyenkor az érintett QML elemek (a grafikon) újrarajzolják magukat.
     */
    void historyContextUpdated();

private:
    /** A használt robot proxy. */
    RobotProxy& robot;

    /** \addtogroup Hivatkozások adatkötéshez
     *  @{
     */
    /** QML context a robot adatok frissítéséhez. */
    QQmlContext &qmlContext;
    /** A history objektum. */
    RobotStateHistory &history;
    /** @}*/
    QObject *rootObject;
    /** Segédfüggvény QML elemek rekurzív megkeresésére.
     * @param rootObject A QML gyökérelem, amivel a keresést kezdjük.
     * @param name Az objectName (QML elemek tulajdonsága), amit keresünk.
     */
    static QQuickItem* FindItemByName(QObject *rootObject, const QString& name);

    /** Segédfüggvény QML elemek rekurzív megkeresésére.
     * A FindItemByName(QObject *rootObject, const QString& name) használja.
     * @param nodes Azon node-ok listája, melyekben (rekurzívan) az adott nevű elemet keressük.
     * @param name  Az objectName (QML elemek tulajdonsága), amit keresünk.
     */
    static QQuickItem* FindItemByName(QList<QObject*> nodes, const QString& name);
};

#endif // MAINWINDOWSEVENTHANDLING_H
