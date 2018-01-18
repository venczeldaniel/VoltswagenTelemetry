#pragma once
#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H
#include <QDataStream>
#include <QString>

/**
 * @brief A robot teljes állapotleírása le egy adott időpillanatban.
 *
 * A kommunikáció során ilyen objektumokat küldünk át a robot és a kliens között.
 * A robottól érkezve az aktuális állapotot képviseli, míg az ellenkező irányba küldve
 *  parancsként a kívánt állapotot írja le.
 *
 * A history ilyen objektumok sorozata.
 */
class RobotState : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief A robot állapota
     */
    enum class Status
    {
        /** . A robot áll. */
        StartState = 0,
        /** . Lassan megy. */
        SlowState = 1,
        /** . Gyorsuló átmeneti1. */
        StartFastState1= 2,
        /** . Gyorsuló átmeneti2. */
        StartFastState2 =3,
        /** . Gyorsuló átmeneti3. */
        StartFastState3=4,
        /** . Gyors . */
        FastState =5,
        /** . Lassuló átmenet1 . */
        SlowingState = 6,
        /** . Lassuló átmenet2 . */
        SlowingState2 = 7,
        /** . Álló . */
        StoppedState = 8
    };
    /**
     *  @brief Üzenet azonosító
     */
    enum class MessageID
    {
        CarState,
        LinePosition,
        LinePattern
    };

    /**
     *  @brief Vonaltípus
     */
    enum class LinePattern
    {
        OneLine,
        ThreeLine,
        NoLine
    };

    /**
     * @brief Konstruktor
     */
    RobotState();

    /**
     * @brief Konstruktor adott értékekkel.
     * @param status    Robot állapot
     *
     */
    RobotState(Status status, LinePattern _pattern, float _lineposition);

    ~RobotState() = default;

    // A NOTIFY signalokat nem implementáljuk, mert nincs rájuk szükség.

    /** Állapot (vagy parancs) */
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    Status status() const { return _status; }
    void setStatus(const Status status) { _status = status; }

    /** Vonalminta */
    Q_PROPERTY(LinePattern pattern READ pattern WRITE setPattern NOTIFY patternChanged)
    LinePattern pattern() const { return _pattern; }
    void setPattern(const LinePattern pattern) { _pattern = pattern; }

    /** Vonalpozíció */
    Q_PROPERTY(float lineposition READ lineposition WRITE setPosition NOTIFY linePositionChanged)
    float lineposition() const { return _lineposition; }
    void setPosition(const float lineposition) { _lineposition = lineposition; }

    /** Az aktuális állapot QStringként. */
    // In QML, it will be accessible as model.statusName
    Q_PROPERTY(QString statusName READ getStatusName NOTIFY statusChanged)

    /** Az aktuális vonalminta QStringként. */
    // In QML, it will be accessible as model.patternName
    Q_PROPERTY(QString patternName READ getPatternName NOTIFY patternChanged)

    /** Sorosítja az objektumot a megadott streambe. */
    void WriteTo(QDataStream& stream) const;

    /** Beolvassa az objektumot a streamből. */
    void ReadFrom(QDataStream& stream);

    /** Másolat készítés. */
    // Erre azért van szükség, mert a QObject-ek másolására speciális szabályok vonatkoznak.
    void CopyFrom(const RobotState& other);

    /** Olvaható formában visszaadja az állapotot. */
    QString getStatusName() const;

    /** Olvaható formában visszaadja a vonalmintát. */
    QString getPatternName() const;

signals:
    // Nem használt signal-ok */
    void statusChanged();
    void patternChanged();
    void linePositionChanged();

private:
    Status _status;
    float _lineposition;
    LinePattern _pattern;

    /** Az állapotok és szöveges verziójuk közti megfeleltetés.
     * A getStatusName() használja. */
    static std::map<int,QString> statusNames;

    /** A vonalminták és szöveges verziójuk közti megfeleltetés.
     * A getPatternName() használja. */
    static std::map<int,QString> patternNames;

    /** Beállítja a statusNames értékeit. A konstruktor hívja. */
    void initStatusNames();

    /** Beállítja a patternNames értékeit. A konstruktor hívja. */
    void initPatternNames();
};

/** Beburkolja a RobotState.WriteTo metódust. */
QDataStream &operator<<(QDataStream &, const RobotState &);

/** Beburkolja a RobotState.ReadFrom metódust. */
QDataStream &operator>>(QDataStream &, RobotState &);

#endif // ROBOTSTATE_H
