#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeySequence>
#include <serial_port_reader.h>
#include <serial_port_writer.h>
#include <QTime>
#include <QtGlobal>
#include <QtMath>
#include <QDebug>

#define JAM_SIGNAL "Collision"

class Room : public QWidget
{
    Q_OBJECT
  public:
    explicit Room(QSerialPort* port,QWidget *parent = 0);

  private slots:
    void sendButtonPressed();
    void addMessage();

  private:
    QString* portName;
    QVBoxLayout* mainLayout;
    QHBoxLayout* messageLayout;
    QTextEdit* history;
    QLineEdit* message;
    QPushButton* sendButton;
    SerialPortReader* reader;
    SerialPortWriter* writer;
    QTextStream output;
};

#endif // ROOM_H
