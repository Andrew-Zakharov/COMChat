#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
  portChooser = new PortChooserWidget();
  this->setCentralWidget(portChooser);
  connect(portChooser,SIGNAL(portChoosed()),this,SLOT(changeWidget()));
}

void MainWindow::changeWidget(){
  room = new Room(portChooser->getPort());
  this->setCentralWidget(room);
  this->setWindowTitle(portChooser->getPort()->portName());
  this->resize(500,300);
}

MainWindow::~MainWindow(){

}
