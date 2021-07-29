#ifndef SOLDLOTS_H
#define SOLDLOTS_H

#include <QWidget>

#include "lotview.h"

class SoldLots : public LotView
{
    Q_OBJECT
public:
    explicit SoldLots(QWidget *parent = nullptr);

public slots:
    void updateTickerValue(double newPrice);

private:
    QHBoxLayout* addBar();
};

#endif // SOLDLOTS_H
