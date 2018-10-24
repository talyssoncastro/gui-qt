#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>

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

    QObject::connect( ui->buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        QMessageBox msgBox;
        msgBox.setText("Accepted has been clicked.");
        msgBox.exec();

        this->openFile();
        this->printFile();

    } );

    QObject::connect( ui->buttonBox, &QDialogButtonBox::rejected, this, [this]() {
        QMessageBox msgBox;
        msgBox.setText("Rejected has been clicked.");
        msgBox.exec();

        this->saveFile();

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

void MainWindow::openFile() {

    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the currentFile name
    currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

    // Close the file
    file.close();

}

void MainWindow::saveFile() {

    // Opens a dialog for saving a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Copy text in the textEdit widget and convert to plain text
    QString text = ui->textEdit->toPlainText();

    // Output to file
    out << text;

    // Close the file
    file.close();

}

void MainWindow::printFile() {

    // Allows for interacting with printer
    QPrinter printer;

    // You'll put your printer name here
    printer.setPrinterName("Printer Name");

    // Create the print dialog and pass the name and parent
    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }

    // Send the text to the printer
    ui->textEdit->print(&printer);

}
