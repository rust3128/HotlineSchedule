#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OptionsDialog/optionsdialog.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool isConnect, QWidget *parent = nullptr);
    ~MainWindow();
    void show();
private:
    Ui::MainWindow *ui;
    bool m_isConnectDB;

private:
    void showOptionsDlg();
};

#endif // MAINWINDOW_H
