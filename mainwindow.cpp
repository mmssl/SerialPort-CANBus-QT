#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadPorts();

    comport = new QSerialPort();
    comport->setPortName(canPortname);
    comport->setBaudRate(QSerialPort::BaudRate::Baud57600);
    comport->setDataBits(QSerialPort::DataBits::Data8);
    comport->setStopBits(QSerialPort::StopBits::OneStop);
    comport->setParity(QSerialPort::NoParity);
    comport->open(QSerialPort::ReadWrite);
    frame.setFrameId(8);
    QByteArray payload = this->ui->lineEdit_transmit->text().toUtf8();
    frame.setPayload(payload);

    QCanBusFrame frame(QCanBusFrame::DataFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{

}

void MainWindow::on_pushButton_connect_clicked()
{
    device->connectDevice();

    // can connect
    if (device->connectDevice())
    {
        qDebug() << "connected state is:" << device->state();
    }
    else
    {
        qDebug() << "connection failed" << device->errorString();
    }


    // serial communication
    if (comport->isOpen())
    {
        qDebug() << "SerialPort is open";
        // frame = candevice->readFrame();

        //
        QMessageBox::information(this, "Port", "Serial Port is open");
    }
    else
    {
        QMessageBox::warning(this, "Port", "Serial Port is not open");
    }

}


void MainWindow::on_pushButton_send_clicked()
{
    // CAN write frame
    if(device->writeFrame(frame))
    {
        qDebug() << "Wrote frame state is" << device->state();
    }
    else
    {
        qDebug() << "Write failed error is:" << device->errorString();
    }

    // Serial port
    if (comport->isOpen())
    {
        // canframe = "test";
        comport->write(this->ui->lineEdit_transmit->text().toLatin1());
        qDebug() << "frame" << this->ui->lineEdit_transmit->text().toLatin1();

    }
}

void MainWindow::loadPorts()
{
    foreach (auto &port, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_port->addItem(port.portName());

    }
    canPortname = ui->comboBox_port->currentText();
    qDebug() << "Port Name:" << canPortname;
}


void MainWindow::on_pushButton_close_clicked()
{
    comport->close();
    device->disconnectDevice();
    QMessageBox::information(this, "Port", "Serial Port is closed");
}


void MainWindow::on_pushButton_read_clicked()
{
    QList<QCanBusFrame> _canData = device->readAllFrames();
    QByteArray bytedata;
    for (const QCanBusFrame& frame : _canData)
    {
        bytedata.append(frame.payload());
    }
    // QByteArray _data = comport->readAll();
    ui->label_received->setText(bytedata);
    qDebug() << "Can frame data:" << bytedata;
}


