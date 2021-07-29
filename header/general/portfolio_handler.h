#ifndef PortfolioHandler_H
#define PortfolioHandler_H

#include <QObject>

#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QFileInfo>

#include <math.h>


namespace asx {
struct LOT
{
    LOT() {}

    uint qty             = 0;
    uint price_dollars   = 0;
    uint price_cents     = 0;

    uint lot_number      = 0;

    QString date;
};

struct TICKER
{
    TICKER() {}

    QString name;

    std::vector<LOT> lots_owned;
    std::vector<LOT> lots_sold;

    int price_dollars   = 0;
    int price_cents     = 0;
};

}

class PortfolioHandler : public QObject
{
    Q_OBJECT
public:
    explicit PortfolioHandler(QObject *parent = nullptr);

public slots:
    void lock_approved();
    void creation_approved();

signals:
    void new_ticker();

    void request_creation();
    void request_lock();
    void done();

    void lot_counter(uint lot);


public:
    void load_portfolio();

    asx::TICKER get_ready_ticker();

    void save(std::vector<asx::TICKER> &tickers);

private:
    bool m_portfolio_exists = false;

    asx::TICKER m_ready_ticker;

    QString m_portfolio_loc;
};

#endif // PortfolioHandler_H
