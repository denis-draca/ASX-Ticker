#include "selldialog.h"
#include "ui_selldialog.h"

SellDialog::SellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellDialog)
{
    ui->setupUi(this);

    QValidator *onlyDouble = new QDoubleValidator(0, INT32_MAX, 2, this);

    ui->in_price->setValidator(onlyDouble);

    ui->bu_ok->setEnabled(false);

    ui->in_date->setDate(QDate::currentDate());

    connect(ui->bu_cancel, &QAbstractButton::clicked, this, [this](){this->close();});
    connect(ui->bu_ok, &QAbstractButton::clicked, this, &SellDialog::submitClicked);
}

SellDialog::~SellDialog()
{
    delete ui;
}

void SellDialog::setMaxQty(int qty)
{
    QValidator *onlyInt = new QIntValidator(0, qty, this);

    ui->in_qty->setValidator(onlyInt);
    ui->in_qty->setPlaceholderText(QStringLiteral("Available: ") + QString::number(qty));
}

void SellDialog::on_in_qty_textEdited(const QString &arg1)
{
    uint max = ui->in_qty->placeholderText().replace(QStringLiteral("Available: "), QStringLiteral("")).toUInt();

    if(arg1.toUInt() > max){
        ui->in_qty->setText(QString::number(max));
    }

    if(arg1.isEmpty()){
        ui->bu_ok->setEnabled(false);
        return;
    }

    if(!ui->in_price->text().isEmpty()){
        ui->bu_ok->setEnabled(true);
    }
}

void SellDialog::on_in_price_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->bu_ok->setEnabled(false);
        return;
    }

    if(!ui->in_qty->text().isEmpty()){
        ui->bu_ok->setEnabled(true);
    }
}

void SellDialog::submitClicked()
{
    uint qty = ui->in_qty->text().toUInt();
    double price = ui->in_price->text().toDouble();
    QString date = ui->in_date->text();

    emit submitSale(qty, price, date);

    close();
}
