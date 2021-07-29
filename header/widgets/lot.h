#ifndef LOT_H
#define LOT_H

#include <QWidget>
#include <QLabel>
#include <QLayout>

#include <qtmaterialflatbutton.h>

#include "selldialog.h"

class Lot : public QWidget
{
    Q_OBJECT
public:
    explicit Lot(QWidget *parent = nullptr, bool allowSale = true);

signals:
    void saleSubmitted(size_t lot, size_t originalQty, uint qty, QString Date, double price);

public slots:
    void setStatus(size_t status);
    void setLot(size_t lot);
    void setTotal(size_t total);
    void setDate(QString &date);
    void setPrice(double price);

private slots:
    void sellClicked();
    void sold(uint qty, double price, QString date);

public:
    size_t getLot(){return m_LotVal;}
    size_t getStat(){return m_statusVal;}
    double getPrice(){return  m_priceVal;}

private:
    size_t m_statusVal;
    size_t m_LotVal;
    size_t m_totalVal;

    double m_priceVal;

    QString m_dateVal;

    bool m_allowSale;

    //owned widgets

    QLabel *m_lot;
    QLabel *m_total;//total owned
    QLabel *m_status; //total remaining or total sold
    QLabel *m_date;
    QLabel *m_price; //price bought or sold
    QLabel *m_invested;
};

#endif // LOT_H
