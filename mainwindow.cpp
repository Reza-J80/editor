#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextBlock>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadedFile = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionsave_triggered()
{
    if(!loadedFile){
        QString filename = QFileDialog::getSaveFileName(this,"save file","C:\\");
        QFile file( filename );
        if ( file.open(QIODevice::WriteOnly)){
            QTextStream stream( &file );
            QString text = ui->textEdit->toPlainText();
            stream << text;
            file.close();
        }
    }
    else {
        QFile file( openedFile );
        if ( file.open(QIODevice::WriteOnly)){
            QTextStream stream( &file );
            QString text = ui->textEdit->toPlainText();
            stream << text;
            file.close();
        }
    }

}

void MainWindow::on_actionopen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("open File"),"C:\\" , "Text File (*.txt);;" );
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        ui->textEdit->setText(file.readAll());
        file.close();
    }
    loadedFile = true;
    openedFile = filename;
}
