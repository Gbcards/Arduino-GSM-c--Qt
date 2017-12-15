#include "gbcards.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>


QSerialPort *arduino;
static const quint16 arduino_uno_vendor_id = 10755;
static const quint16 arduino_uno_product_id = 67;
QString arduino_port_name;
bool arduino_is_available;

Gbcards::Gbcards(QWidget *parent) :
    QMainWindow(parent)
{

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available)
    {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud19200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else
    {
        QMessageBox::warning(0, "Port error", "Couldn't find the Arduino!");
    }
}

void Gbcards::sendData(QString num,QString text)
{
    QString msgSend = "";
    if(arduino->isWritable()){
        msgSend = "num="+num+"msg="+text;
        arduino->write(msgSend.toUtf8());

    }else{
        qDebug() << "Couldn't write to serial!";
    }
}
