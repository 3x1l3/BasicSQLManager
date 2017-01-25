#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connection = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_runQueryButton_clicked()
{
    if (!this->connection->open()) {
        ui->statusBar->showMessage("Cannot run query, Not connected!", 5000);

    } else {

        QSqlQuery query(ui->query->toPlainText());

        while (query.next()) {

          qDebug() <<  query.value(0).toString();

        }
    }
}

void MainWindow::on_connectButton_clicked()
{
    this->connection->setHostName(ui->DBHost->text());
    this->connection->setUserName(ui->DBUsername->text());
    this->connection->setPassword(ui->DBPassword->text());
qDebug() << ui->DBHost->text();
    if (this->connection->open()) {
        ui->statusBar->showMessage("Connected!", 5000);

    } else {
        ui->statusBar->showMessage("Error Connecting!",5000);

    }
}
