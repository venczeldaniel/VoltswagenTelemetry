#include <QDebug>
#include "RobotState.h"



std::map<int,QString> RobotState::statusNames;
std::map<int,QString> RobotState::patternNames;
//Default konstruktor
RobotState::RobotState()
{
    initStatusNames();
    initPatternNames();
}
//Konstruktor
RobotState::RobotState(Status status, LinePattern pattern, float position)
    : _status(status), _lineposition(position), _pattern(pattern)
{
    initStatusNames();
    initPatternNames();
}
/** statusNames inicializálása*/
void RobotState::initStatusNames()
{
    if (statusNames.empty())
    {
        // Még nincsen inicializálva.
        statusNames[(int)Status::StartState] = QString("StartState");
        statusNames[(int)Status::SlowState] = QString("SlowState");
        statusNames[(int)Status::StartFastState1] = QString("StartFastState1");
        statusNames[(int)Status::StartFastState2] = QString("StartFastState2");
        statusNames[(int)Status::StartFastState3] = QString("StartFastState3");
        statusNames[(int)Status::FastState] = QString("FastState");
        statusNames[(int)Status::SlowingState] = QString("SlowingState");
        statusNames[(int)Status::SlowingState2] = QString("SlowingState2");
        statusNames[(int)Status::StoppedState] = QString("StoppedState");
    }
}

/** patternNames inicializálása*/
void RobotState::initPatternNames()
{
    if (patternNames.empty())
    {
        // Még nincsen inicializálva.
        patternNames[(int)LinePattern::NoLine] = QString("NoLine");
        patternNames[(int)LinePattern::OneLine] = QString("OneLine");
        patternNames[(int)LinePattern::ThreeLine] = QString("ThreeLine");
    }
}

// Státusz kiolvasása
QString RobotState::getStatusName() const
{
    auto it = statusNames.find((int)_status);
    Q_ASSERT(it != statusNames.end());
    return it->second;
}

// Vonalminta kiolvasása
QString RobotState::getPatternName() const
{
    auto it = patternNames.find((int)_pattern);
    Q_ASSERT(it != patternNames.end());
    return it->second;
}

void RobotState::WriteTo(QDataStream& stream) const
{

}
/** Streamen keresztül érkező állapot beolvasása*/
void RobotState::ReadFrom(QDataStream& stream)
{
    quint8 tempQuint8;

    MessageID localID;
    stream >> tempQuint8;
    localID = (MessageID) tempQuint8;
    switch(localID)
    {
        case MessageID::CarState    :
        {
            stream >> tempQuint8;
            _status = (Status) tempQuint8;
            break;
        }
        case MessageID::LinePattern :
        {
            stream >> tempQuint8;
            break;
        }
        case MessageID::LinePosition    :
        {
            stream >> tempQuint8;
            break;
        }
    }
}
// RobotState-ről másolatot visszaadó fv.
void RobotState::CopyFrom(const RobotState &other)
{
    _status = other._status;
    _pattern = other._pattern;
    _lineposition = other._lineposition;
}

QDataStream &operator<<(QDataStream& stream, const RobotState& state)
{
    state.WriteTo(stream);
    return stream;
}

QDataStream &operator>>(QDataStream& stream, RobotState& state)
{
    state.ReadFrom(stream);
    return stream;
}
