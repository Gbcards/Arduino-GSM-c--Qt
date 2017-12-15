#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <gbcards.h>

QGridLayout *gridLayout_C;
QLabel *label_C;
QLabel *label_2_C;
QLineEdit *lineEdit_C;
QPlainTextEdit *plainTextEdit_C;
QPushButton *pushButton_C;
QPushButton *pushButton_2_C;
Gbcards *gb;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gridLayout_C = new QGridLayout();
    gridLayout_C->setMargin(11);
    gridLayout_C->setSpacing(11);

    label_C = new QLabel();
    label_C->setObjectName(QStringLiteral("label_C"));
    label_C->setText("Número");

    gridLayout_C->addWidget(label_C, 0, 0, 1, 1);

    label_2_C = new QLabel();
    label_C->setObjectName(QStringLiteral("label_2_C"));
    label_2_C->setText("Mensaje");

    gridLayout_C->addWidget(label_2_C, 1, 0, 1, 1);

    lineEdit_C = new QLineEdit();
    lineEdit_C->setObjectName(QStringLiteral("lineEdit_C"));

    gridLayout_C->addWidget(lineEdit_C, 0, 1, 1, 2);

    plainTextEdit_C = new QPlainTextEdit(ui->centralWidget);
    plainTextEdit_C->setObjectName(QStringLiteral("plainTextEdit_C"));

    gridLayout_C->addWidget(plainTextEdit_C, 1, 1, 1, 2);

    pushButton_C = new QPushButton(ui->centralWidget);
    pushButton_C->setObjectName(QStringLiteral("pushButton_C"));
    pushButton_C->setText("Enviar Mensaje");
    connect(pushButton_C,SIGNAL(clicked()),this,SLOT(SendData()));

    gridLayout_C->addWidget(pushButton_C, 2, 1, 1, 1);

    pushButton_2_C = new QPushButton(ui->centralWidget);
    pushButton_2_C->setObjectName(QStringLiteral("pushButton_2_C"));
    pushButton_2_C->setText("Llamar");
    connect(pushButton_2_C,SIGNAL(clicked()),this,SLOT(Call()));

    gridLayout_C->addWidget(pushButton_2_C, 2, 2, 1, 1 );

    ui->widget->setLayout(gridLayout_C);

    lineEdit_C->setFocus();

    gb = new Gbcards();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendData()
{
    QMessageBox *mb = new QMessageBox();
    if(lineEdit_C->text().length()<=8)
    {
        mb->setIcon(QMessageBox::Critical);
        mb->setText("Aviso");
        mb->setInformativeText("Es necesario ingresar 9 digitos.");
        mb->exec();
    }
    else if(plainTextEdit_C->toPlainText().length()<1)
    {
        mb->setIcon(QMessageBox::Critical);
        mb->setText("Aviso");
        mb->setInformativeText("No se ha escrito un mensaje a enviar.");
        mb->exec();
    }
    else
    {
        gb->sendData("m"+lineEdit_C->text(),plainTextEdit_C->toPlainText());
        mb->setIcon(QMessageBox::Information);
        mb->setText("Aviso");
        mb->setInformativeText("Mensaje Enviado.");
        mb->exec();
        plainTextEdit_C->setPlainText("");
    }
    delete mb;
}

void MainWindow::Call()
{
    QMessageBox *mb = new QMessageBox();
    if(lineEdit_C->text().length()<=8)
    {
        mb->setIcon(QMessageBox::Critical);
        mb->setText("Aviso");
        mb->setInformativeText("Es necesario ingresar 9 digitos.");
        mb->exec();
    }
    else
    {
        gb->sendData("l"+lineEdit_C->text(),plainTextEdit_C->toPlainText());
        mb->setIcon(QMessageBox::Information);
        mb->setText("Aviso");
        mb->setInformativeText("Llamando.");
        mb->exec();
        plainTextEdit_C->setPlainText("");
    }
    delete mb;
}

