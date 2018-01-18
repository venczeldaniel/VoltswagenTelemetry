#include "RobotProxy.h"
#include "RobotStateHistory.h"
#include "Communication/Communication.h"
#include "RobotState.h"

RobotProxy::RobotProxy(RobotStateHistory& history, Communication &communication)
    : history(history), communication(communication)
{
    // Jelzést kérünk, ha új robot állapot (RobotState) érkezik.
    QObject::connect(&communication, SIGNAL(dataReady(QDataStream&)), this, SLOT(dataReady(QDataStream&)));
}

void RobotProxy::dataReady(QDataStream &stream)
{
    // Új robot állapto érkezett, elmentjük a historyba.
    //  (Onnan vesszük majd azt is, hogy mi az aktuális állapot.)
    RobotState state;
    stream >> state;
    history.Add(state);

}
//String kiküldése az adott kommunikációs csatornán
void RobotProxy::sendString(QString str)
{
    communication.send(str);
}



