#include "soldlots.h"

SoldLots::SoldLots(QWidget *parent) : LotView(parent)
{
    QVBoxLayout *mainLay = new QVBoxLayout(this);

    m_currentPrice = 0.0;

    m_lotLay = new QVBoxLayout();


    mainLay->addLayout(m_lotLay);


    QSpacerItem *vertSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    this->setLayout(mainLay);

    mainLay->addItem(vertSpacer);

    mainLay->addLayout(addBar());

    auto labels = this->findChildren<QLabel *>();

    for(auto &label:labels){
        label->setMinimumWidth(200);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setFont(QFont(label->font().family(), 14));
        label->setStyleSheet(QStringLiteral("color:#6000e6"));
    }
}

void SoldLots::updateTickerValue(double newPrice)
{
    m_currentPrice = newPrice;

    m_tickerVal->setText(QStringLiteral("$") + QString::number(newPrice));

    auto lots = getLots();

    double value = 0.0;

    for(auto &lot:lots){
        value += (lot->getStat() * lot->getPrice());
    }

    m_tickerMarket->setText(QStringLiteral("$") + QString::number(value));
}

QHBoxLayout *SoldLots::addBar()
{
    QHBoxLayout *addLay             = new QHBoxLayout();
    QSpacerItem *horSpacer          = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

    //THIS BIT MAY CHANGE


    addLay->addWidget(new QLabel(QStringLiteral("Total Returned: ")));
    m_tickerMarket = new QLabel();
    addLay->addWidget(m_tickerMarket);
    addLay->addWidget(new QLabel(QStringLiteral("Ticker Value: ")));
    m_tickerVal = new QLabel();
    addLay->addWidget(m_tickerVal);


    //END

    addLay->addItem(horSpacer);

    return addLay;
}
