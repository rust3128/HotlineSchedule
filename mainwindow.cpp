#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool isConnect, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    m_isConnectDB=isConnect;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QMainWindow::show();
    if(!m_isConnectDB){
        showOptionsDlg();
    }

}

void MainWindow::showOptionsDlg()
{
    OptionsDialog *optionsDlg = new OptionsDialog(m_isConnectDB);
    optionsDlg->exec();
}
