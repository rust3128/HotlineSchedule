#include "usersdialog.h"
#include "ui_usersdialog.h"
#include "checkboxdelegate.h"
#include <QSqlRelationalDelegate>
#include <QCheckBox>

UsersDialog::UsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);

    createModel();
    createUI();

}

UsersDialog::~UsersDialog()
{
    delete ui;
}

void UsersDialog::createModel()
{
    modelUsers = new QSqlRelationalTableModel();
    modelUsers->setTable("users");
    modelUsers->setRelation(8, QSqlRelation("userrole","role_ID","rolename"));
    modelUsers->select();

}

void UsersDialog::createUI()
{
    ui->tableView->setModel(modelUsers);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    for( int i=0; i<modelUsers->rowCount(); i++ )
        {
            QWidget *widget = new QWidget();
            QCheckBox *chBox = new QCheckBox();
            QHBoxLayout *layout = new QHBoxLayout;
            layout->setMargin(0);
            layout->setSpacing(0);
            layout->addWidget(chBox);
            layout->setAlignment( Qt::AlignCenter );
            widget->setLayout( layout );
            ui->tableView->setIndexWidget( modelUsers->index(i, 9), widget );

            if( modelUsers->data( modelUsers->index(i, 9) ).toBool() )
                chBox->setChecked( true );
            else
                chBox->setChecked( false );

            connect( chBox, SIGNAL(clicked(bool)), this, SLOT(onCheckBoxChecked(bool)) );
        }
    ui->tableView->setItemDelegateForColumn(9,new CheckBoxDelegate);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();

}

void UsersDialog::onCheckBoxChecked(bool isChecked)
{
    QCheckBox *widget = qobject_cast<QCheckBox*>(sender());

    for( int i=0; i<modelUsers->rowCount(); i++ )
    {
        if( ui->tableView->indexWidget(modelUsers->index(i, 9)) !=  nullptr )
        {
            QWidget *cellWidget = qobject_cast<QWidget*>(ui->tableView->indexWidget(modelUsers->index(i, 9)))->layout()->itemAt(0)->widget();

            if( widget == qobject_cast<QCheckBox*>(cellWidget) )
            {
                if( isChecked )
                    modelUsers->setData( modelUsers->index(i, 9), true );
                else
                    modelUsers->setData( modelUsers->index(i, 9), false );

                modelUsers->submitAll();
            }
        }
    }

}

void UsersDialog::on_pushButtonAdd_clicked()
{
    modelUsers->insertRow(modelUsers->rowCount());
    for( int i=0; i<modelUsers->rowCount(); i++ )
        ui->tableView->indexWidget( modelUsers->index(i,9) )->deleteLater();

    for( int i=0; i<modelUsers->rowCount(); i++ )
        {
            QWidget *widget = new QWidget();
            QCheckBox *chBox = new QCheckBox();
            QHBoxLayout *layout = new QHBoxLayout;
            layout->setMargin(0);
            layout->setSpacing(0);
            layout->addWidget(chBox);
            layout->setAlignment( Qt::AlignCenter );
            widget->setLayout( layout );
            ui->tableView->setIndexWidget( modelUsers->index(i, 9), widget );

            if( modelUsers->data( modelUsers->index(i, 9) ).toBool() )
                chBox->setChecked( true );
            else
                chBox->setChecked( false );

            connect( chBox, SIGNAL(clicked(bool)), this, SLOT(onCheckBoxChecked(bool)) );
        }
    modelUsers->submitAll();
}
