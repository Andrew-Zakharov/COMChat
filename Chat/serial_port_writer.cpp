#include "serial_port_writer.h"

QT_USE_NAMESPACE

SerialPortWriter::SerialPortWriter(QSerialPort* serialPort,QObject* parent) : QObject(parent),serialPort(serialPort),standartOutput(stdout),bytesWritten(0){
  timer.setSingleShot(true);
  connect(this->serialPort,&QSerialPort::bytesWritten,this,&SerialPortWriter::handleBytesWritten);
  connect(this->serialPort,static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this,&SerialPortWriter::handleError);
  connect(&timer,&QTimer::timeout,this,&SerialPortWriter::handleTimeout);
}

SerialPortWriter::~SerialPortWriter(){

}

void SerialPortWriter::handleBytesWritten(qint64 bytes){
  bytesWritten += bytes;
  if(bytesWritten == writeData.size()){
    bytesWritten = 0;
    standartOutput << QObject::tr("Data successfully sent to port %1").arg(serialPort->portName()) << endl;
  }
}

void SerialPortWriter::handleTimeout(){
  standartOutput << QObject::tr("Operation timed out for port %1, error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
  //QCoreApplication::exit(1);
}

void SerialPortWriter::handleError(QSerialPort::SerialPortError serialPortError){
  if(serialPortError == QSerialPort::WriteError){
    standartOutput << QObject::tr("An I/O error occured while writing the data to port %1,error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
    QCoreApplication::exit(1);
  }
}

void SerialPortWriter::write(const QByteArray &writeData){
  this->writeData = writeData;

  qint64 bytesWritten = serialPort->write(writeData);

  if(bytesWritten == -1){
    standartOutput << QObject::tr("Failed to write the data to port %1, error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
    QCoreApplication::exit(1);
  }else if(bytesWritten != this->writeData.size()){
    standartOutput << QObject::tr("Failed to write all the data to port %1, error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
    QCoreApplication::exit(1);
  }

  timer.start(5000);
}
