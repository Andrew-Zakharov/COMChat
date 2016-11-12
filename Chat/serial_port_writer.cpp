#include "serial_port_writer.h"

QT_USE_NAMESPACE

SerialPortWriter::SerialPortWriter(QSerialPort* serialPort,QObject* parent) : QObject(parent),serialPort(serialPort){

}

SerialPortWriter::~SerialPortWriter(){

}

void SerialPortWriter::write(const QByteArray &writeData){    
    QByteArray byte;
    QByteArray end;
    QByteArray jam;

    end.push_back(END_SIGNAL);
    jam.push_back(JAM_SIGNAL);

    qint32 attempt = 0;

    for(qint32 i = 0; i < writeData.size(); i++){
        byte.clear();
        byte.push_back(writeData.at(i));

        serialPort->write(byte);

        while(QTime::currentTime().second() % 2 == 0){
           // qDebug() << "Time=" << QTime::currentTime().toString("hh:mm:ss ");
            serialPort->write(jam);

            srand(QTime::currentTime().msec());
            qint32 delay = qrand() % (qint32)qPow(2,attempt) + 1;
            qDebug() << QString::number(attempt) << "Time=" << QTime::currentTime().toString("hh:mm:ss ") << " Random delay=" << QString::number(delay);

            QThread::msleep(delay);

            serialPort->write(byte);

            attempt++;

            if(attempt == 15){
                break;
            }
        }
        attempt = 0;
    }
    serialPort->write(end);
}
