#include "serial_port_reader.h"

QT_USE_NAMESPACE

SerialPortReader::SerialPortReader(QSerialPort* serialPort,QObject* parent) : QObject(parent),serialPort(serialPort){
    connect(this->serialPort,&QSerialPort::readyRead,this,&SerialPortReader::handleReadyRead);
}

QString SerialPortReader::getMessage(){
    QByteArray message;
    for(int i = 0; i < readData.size(); i++){
        if(readData.at(i + 1) == JAM_SIGNAL){
            i++;
        }else{
            if(readData.at(i) != END_SIGNAL){
                message.push_back(readData.at(i));
            }
        }
    }
    QString newMessage(message);
    readData.clear();
    return newMessage;
}

SerialPortReader::~SerialPortReader(){

}

void SerialPortReader::handleReadyRead(){
    QByteArray byte = serialPort->readAll();

    if(byte.at(byte.size() - 1) == END_SIGNAL){
        readData.push_back(byte);
        qDebug() << "Message: " << readData << endl;
        byte.clear();
        emit messageArrived();
    }
}
