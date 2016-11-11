#include "port_chooser_widget.h"

PortChooserWidget::PortChooserWidget(QWidget *parent) : QWidget(parent){
  mainLayout = new QVBoxLayout();
  this->setLayout(mainLayout);

  portNameChooser = new QComboBox();
  portNameChooser->addItem("COM1");
  portNameChooser->addItem("COM2");
  portNameChooser->addItem("COM3");

  baudRateChooser = new QComboBox();
  baudRateChooser->addItem("9600");
  baudRateChooser->addItem("19200");
  baudRateChooser->addItem("115200");

  okButton = new QPushButton("Ok");
  connect(okButton,SIGNAL(pressed()),this,SLOT(okButtonPressed()));

  mainLayout->addWidget(portNameChooser);
  mainLayout->addWidget(baudRateChooser);
  mainLayout->addWidget(okButton);
}

QSerialPort* PortChooserWidget::getPort(){
  return port;
}

void PortChooserWidget::okButtonPressed(){
  qDebug() << portNameChooser->currentText() << endl;
  port = new QSerialPort(portNameChooser->currentText());
  port->open(QSerialPort::ReadWrite);
  if(port->isOpen()){
    port->setBaudRate(baudRateChooser->currentText().toInt());
    qDebug() << "Baud rate set to: " << port->baudRate() << endl;
    emit portChoosed();
  }else{
    QMessageBox::critical(this,tr("Port error"),tr("Unable to open the port!"));
  }
}

PortChooserWidget::~PortChooserWidget(){

}
