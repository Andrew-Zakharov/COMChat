#include "serial_port_reader.h"

QT_USE_NAMESPACE

SerialPortReader::SerialPortReader(QSerialPort* serialPort,QObject* parent) : QObject(parent),serialPort(serialPort),standartOutput(stdout){
  connect(this->serialPort,&QSerialPort::readyRead,this,&SerialPortReader::handleReadyRead);
  connect(this->serialPort,static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this,&SerialPortReader::handleError);
  connect(&timer,&QTimer::timeout,this,&SerialPortReader::handleTimeout);
  timer.start(5000);
}

QString SerialPortReader::getMessage(){
  QString newMessage(readData);
  return newMessage;
}

SerialPortReader::~SerialPortReader(){

}

void SerialPortReader::handleReadyRead(){
  readData.clear();
  readData.append(serialPort->readAll());
  emit messageArrived();
  if(!timer.isActive()){
    timer.start(5000);
  }
}

void SerialPortReader::handleTimeout(){
  if(readData.isEmpty()){
    standartOutput << QObject::tr("No data was currently available for reading from port %1, error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
  }else{
    standartOutput << QObject::tr("Data successfully received from port %1").arg(serialPort->portName()) << endl;
    standartOutput << readData << endl;
  }
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError){
  if(serialPortError == QSerialPort::ReadError){
    standartOutput << QObject::tr("An I/O error occured while reading the data from port %1, error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
    QCoreApplication::exit(1);
  }
}
