#ifndef SERIAL_PORT_READER_H
#define SERIAL_PORT_READER_H

#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QCoreApplication>

QT_USE_NAMESPACE

class SerialPortReader : public QObject
{
    Q_OBJECT

  public:
    SerialPortReader(QSerialPort* serialPort,QObject* parent = 0);
    QString getMessage();
    ~SerialPortReader();

  private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

  signals:
    void messageArrived();

  private:
    QSerialPort* serialPort;
    QByteArray readData;
    QTextStream standartOutput;
    QTimer timer;
};

#endif // SERIAL_PORT_READER_H
