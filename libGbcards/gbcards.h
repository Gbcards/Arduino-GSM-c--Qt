#ifndef GBCARDS_H
#define GBCARDS_H

#include "gbcards_global.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QString>


class GBCARDSSHARED_EXPORT Gbcards : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gbcards(QWidget *parent = 0);
    void ArduinoLeer();
    void sendData(QString Data,QString text);

};

#endif // GBCARDS_H
