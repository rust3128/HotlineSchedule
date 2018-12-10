#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QAbstractButton>
#include <QSettings>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(bool isConnect, QWidget *parent = nullptr);
    ~OptionsDialog();
    bool isOptionChanged();
private slots:
    void optionChanged();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::OptionsDialog *ui;
    bool m_connected;
    QSettings *settings;
    bool changedOptions = false;
private:
    void createUI();
    void saveOptions();
};

#endif // OPTIONSDIALOG_H
