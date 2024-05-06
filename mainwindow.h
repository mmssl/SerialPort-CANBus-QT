#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCanBus>
#include <QtSerialBus>
#include <QSerialPort>
#include <QLabel>
#include <QMessageBox>
#include <QCanBusFrame>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);


    void on_pushButton_connect_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_read_clicked();

private:
    Ui::MainWindow *ui;
    QCanBus *canbus;
    QCanBusDevice *candevice;
    QSerialPort *comport;
    QLabel *canreceived;
    QString canPortname;
    QString canframe;
    QCanBusDevice *device = QCanBus::instance()->createDevice("socketcan", "vcan0");
    QCanBusFrame frame;

private:

    void loadPorts();



};
#endif // MAINWINDOW_H
