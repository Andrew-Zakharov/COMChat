#include "room.h"

Room::Room(QSerialPort* port, QWidget *parent) : QWidget(parent),output(stdout){
    portName = new QString(port->portName());

    reader = new SerialPortReader(port);
    writer = new SerialPortWriter(port);

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    history = new QTextEdit();
    history->setReadOnly(true);
    history->append("Connected to " + port->portName() + "\n");

    message = new QLineEdit();
    message->setPlaceholderText("Enter your message...");

    sendButton = new QPushButton("Send");
    connect(sendButton,SIGNAL(released()),this,SLOT(sendButtonPressed()));
    connect(message,SIGNAL(returnPressed()),this,SLOT(sendButtonPressed()));

    messageLayout = new QHBoxLayout();
    messageLayout->addWidget(message);
    messageLayout->addWidget(sendButton);

    mainLayout->addWidget(history);
    mainLayout->addLayout(messageLayout);
    connect(reader,SIGNAL(messageArrived()),this,SLOT(addMessage()));
}

void Room::addMessage(){
    history->append("Message: " + reader->getMessage());
}

void Room::sendButtonPressed(){
    if(message->text().contains(QRegExp("\\S"))){
        sendButton->setEnabled(false);
        message->setReadOnly(true);

        writer->write(message->text().toLatin1());

        history->append("You: " + message->text() + "\n");
        message->clear();

        message->setReadOnly(false);
        sendButton->setEnabled(true);
    }
}
