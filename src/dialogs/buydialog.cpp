#include "buydialog.h"
#include "ui_buydialog.h"

BuyDialog::BuyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyDialog)
{
    ui->setupUi(this);

    ui->in_date->setDate(QDate::currentDate());

    QList<QtMaterialFlatButton *> flatButs = this->findChildren<QtMaterialFlatButton *>();
    for(auto &flat:flatButs){flat->setForegroundColor(QColor(QStringLiteral("#6000e6")));}

    QValidator *onlyInt = new QIntValidator(0, INT32_MAX, this);
    QValidator *onlyDouble = new QDoubleValidator(0, INT32_MAX, 2, this);

    ui->in_qty->setValidator(onlyInt);
    ui->in_price->setValidator(onlyDouble);

    ui->bu_ok->setEnabled(false);

    connect(ui->bu_cancel, &QtMaterialFlatButton::clicked, this, [this](){this->close();});
    connect(ui->bu_ok, &QtMaterialFlatButton::clicked, this, &BuyDialog::okClicked);
}

BuyDialog::~BuyDialog()
{
    delete ui;
}

void BuyDialog::on_in_qty_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->bu_ok->setEnabled(false);
        return;
    }

    if(!ui->in_price->text().isEmpty()){
        ui->bu_ok->setEnabled(true);
    }
}

void BuyDialog::on_in_price_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->bu_ok->setEnabled(false);
        return;
    }

    if(!ui->in_qty->text().isEmpty()){
        ui->bu_ok->setEnabled(true);
    }
}

void BuyDialog::okClicked()
{
    uint qty = ui->in_qty->text().toUInt();
    double price = ui->in_price->text().toDouble();
    QString date = ui->in_date->text();

    emit submitted(qty, price, date);

    close();
}
