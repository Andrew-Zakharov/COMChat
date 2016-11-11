#ifndef PORTCHOOSERWIDGET_H
#define PORTCHOOSERWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSerialPort>

class PortChooserWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit PortChooserWidget(QWidget *parent = 0);
    QSerialPort* getPort();
    ~PortChooserWidget();

  private slots:
    void okButtonPressed();

  signals:
    void portChoosed();

  private:
    QSerialPort* port;
    QVBoxLayout* mainLayout;
    QComboBox* portNameChooser;
    QComboBox* baudRateChooser;
    QPushButton* okButton;
};

#endif // PORTCHOOSERWIDGET_H
