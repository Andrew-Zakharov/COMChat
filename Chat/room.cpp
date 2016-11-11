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
    history->append(reader->getMessage());
}

void Room::sendButtonPressed(){
    if(message->text().contains(QRegExp("\\S"))){
        sendButton->setEnabled(false);
        message->setReadOnly(true);

        QByteArray writeData = message->text().toLatin1();

        qint32 k = 1;
        QTime time;

        while(time.currentTime().second() % 2 == 0){
            history->append("Transmitter detected the collision.Sending jam signal...\n");
            writer->write(JAM_SIGNAL);
            history->append("Jam signal sent.\n");

            srand(QTime::currentTime().msec());
            qint32 r = qrand() % (qint32)qPow(2,k);

            for(qint32 i = 0; i < r; i++);

            k++;

            if(k == 10){
                break;
            }
        }

        if(k != 10){
            history->append("You: " + message->text() + "\n");
            writer->write(writeData);
            message->clear();
        }
    }

    message->setReadOnly(false);
    sendButton->setEnabled(true);
}
