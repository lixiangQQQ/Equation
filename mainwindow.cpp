#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    custom = new Custom(this);
    setCentralWidget(custom);
    custom->show();
    setMinimumSize(1030,391);
}

MainWindow::~MainWindow()
{
    delete ui;
}
