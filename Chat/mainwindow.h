#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <port_chooser_widget.h>
#include <room.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void changeWidget();

  private:
    PortChooserWidget* portChooser;
    Room* room;
};

#endif // MAINWINDOW_H
