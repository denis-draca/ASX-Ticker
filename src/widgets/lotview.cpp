#include "lotview.h"

LotView::LotView(QWidget *parent) : QWidget(parent), m_sisterView(nullptr)
{

}

void LotView::addLot(size_t num, size_t qty, QString date, double price)
{
    Lot *lot = new Lot(this);

    lot->setLot(num);
    lot->setDate(date);
    lot->setPrice(price);
    lot->setTotal(qty);
    lot->setStatus(qty);

    m_lotLay->addWidget(lot);

    connect(lot, &Lot::saleSubmitted, this, &LotView::passOnSale);

    lot->show();
}

void LotView::addFormedLot(size_t lotnum, size_t originalQty, uint qty, QString Date, double price)
{
    Lot *lot = new Lot(this);

    lot->setLot(lotnum);
    lot->setDate(Date);
    lot->setPrice(price);
    lot->setTotal(originalQty);
    lot->setStatus(qty);

    m_lotLay->addWidget(lot);

    connect(lot, &Lot::saleSubmitted, this, &LotView::passOnSale);

    lot->show();
}

void LotView::updateTickerValue(double newPrice)
{
    m_currentPrice = newPrice;

    m_tickerVal->setText(QStringLiteral("$") + QString::number(newPrice));

    auto lots = getLots();

    double value = 0.0;

    for(auto &lot:lots){
        value += (lot->getStat() * newPrice);
    }

    m_tickerMarket->setText(QStringLiteral("$") + QString::number(value));
}

void LotView::passOnSale(size_t lot, size_t originalQty, uint qty, QString Date, double price)
{
    updateTickerValue(m_currentPrice);

    emit saleSubmitted(lot, originalQty, qty, Date, price);
}

QList<Lot *> LotView::getLots()
{
    auto lots = this->findChildren<Lot *>();

    return lots;
}

void LotView::addClicked()
{
    auto buy = new BuyDialog(this);

    connect(buy, &BuyDialog::submitted, this, &LotView::submitted);

    buy->exec();
}

void LotView::submitted(uint qty, double price, QString date)
{
    auto lots = this->findChildren<Lot *>();

    size_t maxLot = 0;

    for(auto &lot:lots){
        if(lot->getLot() > maxLot){
            maxLot = lot->getLot();
        }
    }

    maxLot++;

    addLot(maxLot, qty, date, price);

    updateTickerValue(m_currentPrice);
}

QHBoxLayout *LotView::heading()
{
    QHBoxLayout *headingLay = new QHBoxLayout();

    QLabel *lot     = new QLabel(QStringLiteral("Lot Num"));
    QLabel *total   = new QLabel(QStringLiteral("Total Owned"));//total owned
    QLabel *status  = new QLabel(QStringLiteral("Transacted")); //total remaining or total sold
    QLabel *date    = new QLabel(QStringLiteral("Date"));
    QLabel *price   = new QLabel(QStringLiteral("Price Each")); //price bought or sold
    QLabel *invest  = new QLabel(QStringLiteral("Invested")); //price bought or sold

    headingLay->addWidget(lot);
    headingLay->addWidget(total);
    headingLay->addWidget(status);
    headingLay->addWidget(date);
    headingLay->addWidget(price);
    headingLay->addWidget(invest);


    QtMaterialFlatButton *bu_delete = new QtMaterialFlatButton(this);

    bu_delete->setForegroundColor(QColor(QStringLiteral("#ffffff")));

    QPixmap del(":/icons/Icons/delete_black_24dp.svg");
    QIcon delIcon(del);

    bu_delete->setIcon(delIcon);
    bu_delete->setIconSize(del.rect().size());

    bu_delete->setRippleStyle(Material::NoRipple);
    bu_delete->setHaloVisible(false);


    headingLay->addWidget(bu_delete);

    headingLay->setMargin(10);

    return headingLay;
}
