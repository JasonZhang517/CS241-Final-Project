#include "mainwindow.h"
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QMainWindow>
#include <mainLayout.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   setCentralWidget(new mainLayout());
   resize(1000,1500);
}

MainWindow::~MainWindow()
{
}

