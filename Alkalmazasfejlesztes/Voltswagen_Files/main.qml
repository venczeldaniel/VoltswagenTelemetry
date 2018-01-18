import QtQuick 2.4
import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import QtQuick 2.0
import QtQuick 2.7
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

// Ez lesz az alkalmazás főablaka
ApplicationWindow {
    id: mainwindow
    title: qsTr("VoltsWagen")
    width: 1200
    height: 640
    property alias mainFormControl: mainFormControl
    visible: true
    Component.onCompleted: {
       // Megnyíló ablak középre igazítása
            setX(Screen.width / 2 - width / 2);
            setY(Screen.height / 2 - height / 2);
    }
    // Signalok, melyeket a C++ oldalon fogunk C++ slotokhoz kötni
    //  az StvApplication osztály konstruktorában.
    signal testCommandCpp()
    signal valueSetCommandCpp()




    // Az ablak menuBar tulajdonságának értékül adunk egy MenuBar példányt, amit itt rakunk össze.
    menuBar: MenuBar {
        // A MenuBar-on belül vannak a menük, Menu példányok formájában. Most csak egy "Exit" menünk van,
        //  benne egyetlen menüponttal.

        Menu {
            // A menünek a title tulajdonsága egyúttal az & jellel megadja a billentyű parancsot is: Alt-x
            title: qsTr("&Exit")
            // Az egyetlen menüpont
            MenuItem {
                text: qsTr("E&xit")
                // A menüpont Triggered signaljához kapcsolunk eseménykezelőt
                //  úgy, hogy értéket adunk az onTriggered tulajdonságnak. Az eseménykezelőt
                //  JavaScript nyelven írjuk meg.
                 shortcut: qsTr("Ctrl+Q")
                onTriggered: Qt.quit();
            }
        }
    }

    /* Instantiating the MainForm control which contains everything in the main form,
        except the menu. */
    // A MainForm elem példányosítása. Itt adjuk meg az ID-ját, a helyét (anchors),
    //  valamint a signaljainak az eseménykezelőit.
    MainForm {
        id: mainFormControl
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 2
        anchors.fill: parent

        // Az eseménykezelőkben tovább hívjuk az itteni signalokat a C++ oldal felé.
        onTestCommand: {
            testCommandCpp();
        }
        onValueSetCommand: {
            valueSetCommandCpp();

        }
    }
}
