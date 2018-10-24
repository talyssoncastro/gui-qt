#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setStyleSheet( " font-size: 22px; " );
    ui->pushButton->setStyleSheet( "color: red;" );

    ui->buttonBox->clear();

    QPushButton* btn1 = ui->buttonBox->addButton( "Teste", QDialogButtonBox::ButtonRole::YesRole );
    QPushButton* btn2 = ui->buttonBox->addButton( "Teste 2", QDialogButtonBox::ButtonRole::NoRole );


    QObject::connect( btn1, &QPushButton::clicked, this, []() {

        QMessageBox msgBox;
        msgBox.setText("The button has been clicked.");
        msgBox.exec();

    } );

    QObject::connect( ui->buttonBox, &QDialogButtonBox::accepted, this, []() {
        QMessageBox msgBox;
        msgBox.setText("Accepted has been clicked.");
        msgBox.exec();
    } );

    QObject::connect( ui->buttonBox, &QDialogButtonBox::rejected, this, []() {
        QMessageBox msgBox;
        msgBox.setText("Rejected has been clicked.");
        msgBox.exec();
    } );

    QObject::connect( ui->buttonBox, &QDialogButtonBox::clicked, this, [=](QAbstractButton* btn) {
        QMessageBox msgBox;
        msgBox.setText("Button " + btn->text());
        msgBox.exec();
    } );

}

MainWindow::~MainWindow()
{
    delete ui;
}