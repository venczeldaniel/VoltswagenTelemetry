//import QtQuick 2.0
import QtQuick 2.7
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1



Item {
    width: 1200
    height: 640
    id: mainitem
    anchors.fill: parent
    //hozzáférések biztosítása
    property alias setButton: getUserValues
    // Signalok, melyek a kiadott parancsokat jelzik és a nyomógombok
    //  eseménykezelői aktiválják őket.
    signal testCommand;
    signal valueSetCommand;

    // A parancs nyomógombok elemcsoportja
    GroupBox {
        id: commandsGB
        title: "Parancsok"
        // Bal oldalon és fent követi a szülőt. A szélessége fix.
        anchors.left : parent.left
        anchors.top : parent.top
        //anchors.bottom: graphGB.top
        height: 120
        width: 200

        // A nyomógombokat oszlopba rendezzük
        ColumnLayout {
            id: columnLayout1
            // Az oszlop kitölti a szülőt, vagyis a commandsGB-t.
            //anchors.fill: parent
            width: 180
            spacing: 10

            //  Megnyomása esetén (Button.Clicked signal) meghívja a testCommand signalt. (Ez
            //  a signal látható innen, mivel a Button egyik ősében definiáltuk.)
            Button {
                id: testBtn
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Start")
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                width: 150
                onClicked: testCommand()
            }

            //Fényszóró tesztelése
            Button {
                id: lightTest
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Fényszóró")
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                width: 150
                onClicked: robonautlogo.source = '/images/robonautlogo2.png'
            }
        }
    }
    //Beviteli mezők groupboxa
    GroupBox {
        id: adatok
        height: 120
        width: 400
        title: "Adatok"
        anchors.left: commandsGB.right
        anchors.right: currentStateValues.left
        anchors.top: parent.top
        //anchors.bottom: graphGB.top
        anchors.topMargin: 0

         //ColumnLayout{
             //Aktuális szabályozóértékek
            //id:currentControlParam
            //spacing: 10
            //width: 80
           // anchors.left: valuSetCol.right
            //Text{ text: "" + currentState._kappa; }
            //Text{ text: "" + currentState._sebesseg;}
         //}
         //Beállított értékek kiküldése
        Button{
            id: getUserValues
            //anchors.left: currentControlParam.right
            anchors.left: valuSetCol.right
            text: qsTr("Beállít")
            onClicked: valueSetCommand()//currentState. //currentState.setUserValuesCpp("dsd")//
        }
        //egy soron belül több oszlop
        ColumnLayout{
            id:valuSetCol
             spacing:10

            RowLayout{
                id: kappaRow
                Label{
                    id: kappaLabel
                    text: "Kappa:       "
                    font.pixelSize: 12
                    anchors.left: commandsGB.right
                    anchors.topMargin: 5
                }

                TextField{
                    objectName: "kappa"
                    id: kappaField
                    validator: IntValidator {bottom:0}
                    inputMask: "9999"
                    maximumLength: 4
                    anchors.left: kappaLabel.right
                    width: 100
                }
            }

            RowLayout{
                id: sebessegRow
                Label{
                    id: sebesseglabel
                    text: "Sebesség: "
                    font.pixelSize: 12
                    anchors.left: commandsGB.right
                    anchors.topMargin: 5
                }

                TextField{
                    id: sebessegField
                    objectName: "Sebesség"
                    validator: IntValidator {bottom:0}
                    inputMask: "9999"
                    maximumLength: 4
                    textColor: "black"
                    anchors.left: sebessegLabel.right
                    width: 100
                }
            }

               Label{
                    id: sliderLabel
                    text: "Szervóbeállítás (pulzus (ms))"
                    font.pixelSize: 12
                    //anchors.left: currentValuesGB.right
                    anchors.horizontalCenter: valuSetCol.horizontalCenter
                }
                 //szervó szögének beállítása
                Slider{
                    id: servoSlider
                    objectName: "servoSlider"
                    anchors.topMargin: 100
                    maximumValue: 1920
                    minimumValue: 1160
                    stepSize: 1

                }
        }
    }

    // Az állapot lista és a grafikon GroupBoxa.
   GroupBox {
        id: graphGB
        title: qsTr("Csapatlogó")
        // Oldalra és lefelé kitölti a szülőt.
        //anchors.right: parent.right
        width: 660
        height: 660
        anchors.rightMargin: 0
        //anchors.left: parent.left
        anchors.leftMargin: 0
        //anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        // Felfelé a commandsGB és currentValuesGB GroupBoxok közül ahhoz igazodik, aminek lejjebb van az alja.
        //anchors.top: (commandsGB.bottom > currentValuesGB.bottom ? commandsGB.bottom : currentValuesGB.bottom )
        anchors.top: (commandsGB.bottom)
    anchors.topMargin: 0

        Image {
            id: robonautlogo
            source: "/images/robonautlogo.png"
            height: 500
            width: 500
            anchors.left: parent.left
            //anchors.top: parent.top
            anchors.leftMargin: 50
            //anchors.topMargin: 120
            anchors.verticalCenter: parent.verticalCenter


        }
    }

   Component {
       // ID, hogy tudjuk a listánál hivatkozni erre, mint a lista delegatejére.
       id: stateDelegate
       Row {
           // Itt a model az, ami a list egyik eleme. (Bármi is legyen majd az.)
       //Lista kiírásának függvénye
           Text { text: " Állapot: " + model.statusName + "Vonalminta" + model.patternName + "Pozíció" + model.lineposition}
       }
   }

        // Sorban egymás mellett van a lista és a grafikon
        GroupBox {
            anchors.left : graphGB.right
            anchors.top : parent.top
            anchors.right: parent.right
            id: currentStateValues
            title: "Pillanatnyi állapotértékek"
            anchors.rightMargin: 0
            //width:500
            height: 660

            RowLayout {
                // Kitölti a szülőt és nem hagy helyet az elemek között.
                anchors.fill: parent
                spacing: 0
                // A history lista egy scrollozható elemen belül van.
                ScrollView {
                    // A scrollohzató elem igazítása a szölő RowLayouthoz.
                    // Itt a ScrollViewon belül adjuk meg, hogy a RowLayoutban
                    //  mik legyenek a rá (ScrollViewra) vonatkozó méret beállítások,
                    //  mert ezeket a RowLayout kezeli ebben az esetben.
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.minimumWidth: 250
                    Layout.preferredWidth: 250
                    Layout.maximumWidth: 500
                    Layout.minimumHeight: 150
                    // Itt jön a tényleges lista.
                    ListView {
                        id: stateHistoryList
                        // A model az, ahonnan az adatokat vesszük.
                        // A historyModel változót a MainWindowsEventHandling::historyChanged metódus teszi
                        //  elérhetővé a QML oldalon is.
                        //  Típusa QList<QObject*>, a tárolt pointerek valójában RobotState-ekre mutatnak.
                        model: historyModel
                        // A delegate megadása, vagyis hogy egy listaelem hogyan jelenjen meg.
                        //  (Már fentebb definiáltuk.)
                        delegate: stateDelegate

                        // Eseménykezelő, az elemek darabszámának változása esetén a kijelölést
                        //  a legalsó elemre viszi. Ezzel oldja meg, hogy folyamatosan scrollozódjon
                        //  a lista és a legutoló elem mindig látható legyen.
                        onCountChanged: {
                            stateHistoryList.currentIndex = stateHistoryList.count - 1;
                    }
                }
            }
        }
    }
}
