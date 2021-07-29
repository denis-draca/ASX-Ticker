#include "setkeydialog.h"
#include "ui_setkeydialog.h"

SetKeyDialog::SetKeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetKeyDialog)
{
    ui->setupUi(this);

    ui->bu_ok->setEnabled(false);

    connect(ui->bu_cancel, &QAbstractButton::clicked, this, [this](){this->close();});
    connect(ui->bu_ok, &QAbstractButton::clicked, this, [this](){
        emit submittedKey(ui->in_key->text());
        this->close();
    });
}

SetKeyDialog::~SetKeyDialog()
{
    delete ui;
}

void SetKeyDialog::on_in_key_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->bu_ok->setEnabled(false);
    }else{
        ui->bu_ok->setEnabled(true);
    }
}
