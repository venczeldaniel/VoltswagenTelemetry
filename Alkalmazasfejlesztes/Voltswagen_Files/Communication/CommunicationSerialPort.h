#pragma once
#ifndef COMMUNICATIONSERIALPORT_H
#define COMMUNICATIONSERIALPORT_H
#include "Communication.h"
#include <QtSerialPort/QSerialPort>

// http://doc.qt.io/qt-5/qtserialport-index.html
// http://doc.qt.io/qt-5/qserialport.html
// http://doc.qt.io/qt-5/qiodevice.html#readyRead
// http://doc.qt.io/qt-5/qtserialport-examples.html

/**
 * @brief Soros port kommunikáció
 */
class CommunicationSerialPort : public Communication
{
    Q_OBJECT

public:
     /** Konstruktor
      *
      * @param Port címe
      * @param Baudrate
      * @param Adatbitek száma
      * @param Paritás
      * @param Stopbitek
      *
      */
    CommunicationSerialPort(QString portName,
            qint32 baudRate,
            QSerialPort::DataBits dataBits,
            QSerialPort::Parity parity,
            QSerialPort::StopBits stopBits);

     /** Dekonstruktor */
    virtual ~CommunicationSerialPort() = default;

    /** Csatlakozás másik eszközhöz */
    virtual void connect();

     /** Csatlakozás állapota */
    virtual bool isConnected() const override;

protected:
     /** Buffer kiküldése */
    virtual void sendBufferContent() override;

private:
    /** Soros port címe*/
    QSerialPort serialPort;

private slots:
    /** Hibakezelő  */
    void handleError(QSerialPort::SerialPortError error);

};

#endif // COMMUNICATIONSERIALPORT_H
