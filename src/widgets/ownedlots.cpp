#include "ownedlots.h"

OwnedLots::OwnedLots(QWidget *parent) : LotView(parent)
{
    QVBoxLayout *mainLay = new QVBoxLayout(this);

    m_currentPrice = 0.0;

    m_lotLay = new QVBoxLayout();

    m_lotLay->setMargin(0);
    m_lotLay->setContentsMargins(0,0,0,0);

    mainLay->addLayout(m_lotLay);


    QSpacerItem *vertSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    this->setLayout(mainLay);

    mainLay->addItem(vertSpacer);

    mainLay->addLayout(addBar());

    auto labels = this->findChildren<QLabel *>();

    for(auto &label:labels){
        label->setMinimumWidth(150);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setFont(QFont(label->font().family(), 14));
        label->setStyleSheet(QStringLiteral("color:#6000e6"));
    }
}

QHBoxLayout *OwnedLots::addBar()
{
    QHBoxLayout *addLay             = new QHBoxLayout();
    QSpacerItem *horSpacer          = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

    //THIS BIT MAY CHANGE


    addLay->addWidget(new QLabel(QStringLiteral("Ticker Market Value: ")));
    m_tickerMarket = new QLabel();
    addLay->addWidget(m_tickerMarket);
    addLay->addWidget(new QLabel(QStringLiteral("Ticker Value: ")));
    m_tickerVal = new QLabel();
    addLay->addWidget(m_tickerVal);


    //END

    addLay->addItem(horSpacer);

    QtMaterialFlatButton *addBut    = new QtMaterialFlatButton(this);
    addLay->addWidget(addBut);

    QPixmap addPixmap(":/icons/Icons/add_black_48dp.svg");

    QIcon addIcon(addPixmap);

    addBut->setIcon(addIcon);
    addBut->setIconSize(addPixmap.rect().size());
    addBut->setForegroundColor(QColor(QStringLiteral("#09ed09")));

    connect(addBut, &QtMaterialFlatButton::clicked, this, &OwnedLots::addClicked);

    return addLay;
}
