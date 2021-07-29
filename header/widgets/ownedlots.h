#ifndef OWNEDLOTS_H
#define OWNEDLOTS_H

#include <QWidget>

#include "lotview.h"

class OwnedLots : public LotView
{
    Q_OBJECT
public:
    explicit OwnedLots(QWidget *parent = nullptr);

private:
    QHBoxLayout* addBar();
};

#endif // OWNEDLOTS_H
