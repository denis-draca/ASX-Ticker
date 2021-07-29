#ifndef LOTVIEW_H
#define LOTVIEW_H

#include <QWidget>

#include <QLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QScrollArea>
#include <QPair>

#include <qtmaterialflatbutton.h>

#include "lot.h"
#include "buydialog.h"

#include <vector>

class LotView : public QWidget
{
    Q_OBJECT
public:
    explicit LotView(QWidget *parent = nullptr);

signals:
    void saleSubmitted(size_t lot, size_t originalQty, uint qty, QString Date, double price);

public slots:
    void updateTickerValue(double newPrice);
    void addFormedLot(size_t lotnum, size_t originalQty, uint qty, QString Date, double price);

public:
    QList<Lot *> getLots();

    void setSisterView(LotView *sister){m_sisterView = sister;}

private slots:
    void submitted(uint qty, double price, QString date);
    void passOnSale(size_t lot, size_t originalQty, uint qty, QString Date, double price);


protected slots:
    void addClicked();
    void addLot(size_t num, size_t qty, QString date, double price);


protected:
    QLabel *m_tickerVal;
    QLabel *m_tickerMarket;
    double m_currentPrice;
    QVBoxLayout *m_lotLay;

private:
    std::vector<Lot *> m_lots;

    QHBoxLayout* heading();

    LotView *m_sisterView;

    virtual QHBoxLayout* addBar() = 0;
};

#endif // LOTVIEW_H
