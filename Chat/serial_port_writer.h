#ifndef SERIAL_PORT_WRITER_H
#define SERIAL_PORT_WRITER_H

#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QCoreApplication>
#include <QTime>
#include <QtGlobal>
#include <QtMath>
#include <QDebug>
#include <QThread>

#define JAM_SIGNAL '&'
#define END_SIGNAL ']'

QT_USE_NAMESPACE

class SerialPortWriter : public QObject
{
    Q_OBJECT

  public:
    SerialPortWriter(QSerialPort* serialPort,QObject* parent = 0);
    ~SerialPortWriter();

    void write(const QByteArray &writeData);

  private:
    QSerialPort* serialPort;
    QByteArray writeData;
    QTextStream standartOutput;
    qint64 bytesWritten;
    QTimer timer;
};

#endif // SERIAL_PORT_WRITER_H
