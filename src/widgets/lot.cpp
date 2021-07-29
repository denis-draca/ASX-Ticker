#include "lot.h"

Lot::Lot(QWidget *parent, bool allowSale) : QWidget(parent), m_allowSale(allowSale)
{
    auto *widgeLayout = new QHBoxLayout(this);

    widgeLayout->setContentsMargins(0,0,0,0);
    widgeLayout->setMargin(0);

    this->setLayout(widgeLayout);

    m_lot       = new QLabel(this);
    m_total     = new QLabel(this);
    m_status    = new QLabel(this);
    m_date      = new QLabel(this);
    m_price     = new QLabel(this);
    m_invested  = new QLabel(this);

    m_allowSale = true;

    auto labels = this->findChildren<QLabel *>();

    for(auto &label:labels){
        label->setMinimumWidth(150);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setFont(QFont(label->font().family(), 14));
        label->setStyleSheet(QStringLiteral("color:#6000e6;border: 1px solid black;"));
    }

    QtMaterialFlatButton *bu_delete = new QtMaterialFlatButton(this);
    QtMaterialFlatButton *bu_sale = new QtMaterialFlatButton(this);

    bu_delete->setForegroundColor(QColor(QStringLiteral("#ed0909")));
    bu_sale->setForegroundColor(QColor(QStringLiteral("#09e8e1")));

    QPixmap del(":/icons/Icons/delete_black_24dp.svg");
    QIcon delIcon(del);

    QPixmap sel(":/icons/Icons/attach_money_black_24dp.svg");
    QIcon selIcon(sel);

    bu_delete->setIcon(delIcon);
    bu_delete->setIconSize(del.rect().size());

    bu_sale->setIcon(selIcon);
    bu_sale->setIconSize(sel.rect().size());

    widgeLayout->addWidget(m_lot);
    widgeLayout->addWidget(m_total);
    widgeLayout->addWidget(m_status);
    widgeLayout->addWidget(m_date);
    widgeLayout->addWidget(m_price);
    widgeLayout->addWidget(m_invested);
    widgeLayout->addWidget(bu_delete);
    widgeLayout->addWidget(bu_sale);

    if(!allowSale){
//        bu_sale->hide();
        bu_sale->setEnabled(false);
        bu_sale->setForegroundColor(QColor(QStringLiteral("#ffffff")));
    }

    connect(bu_delete, &QPushButton::clicked, this, [this](){this->deleteLater();});
    connect(bu_sale, &QPushButton::clicked, this, &Lot::sellClicked);
}

void Lot::setStatus(size_t status)
{
    m_statusVal = status;
    m_status->setText(QString::number(status));
}

void Lot::setLot(size_t lot)
{
    m_LotVal = lot;
    m_lot->setText(QString::number(lot));
}

void Lot::setTotal(size_t total)
{
    m_totalVal = total;
    m_total->setText(QString::number(total));

    m_invested->setText(QStringLiteral("$") + QString::number(static_cast<double>(total) * m_priceVal));
}

void Lot::setDate(QString &date)
{
    m_dateVal = date;
    m_date->setText(date);
}

void Lot::setPrice(double price)
{
    m_priceVal = price;
    m_price->setText(QStringLiteral("$") + QString::number(price));

    m_invested->setText(QStringLiteral("$") + QString::number(static_cast<double>(m_totalVal) * m_priceVal));
}

void Lot::sellClicked()
{
    if(m_statusVal == 0){
        return;
    }

    auto *sell = new SellDialog(parentWidget());

    sell->setMaxQty(static_cast<int>(m_statusVal));

    connect(sell, &SellDialog::submitSale, this, &Lot::sold);

    sell->exec();
}

void Lot::sold(uint qty, double price, QString date)
{
    this->setStatus(m_statusVal - qty);

    emit saleSubmitted(m_LotVal, m_totalVal, qty, date, price);
}

