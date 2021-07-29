#include "portfolio_handler.h"

PortfolioHandler::PortfolioHandler(QObject *parent) : QObject(parent)
{
    m_portfolio_loc = QStringLiteral("portfolio2.xml");
}

void PortfolioHandler::lock_approved()
{
    if(!m_portfolio_exists){
        return;
    }

    QFile file(m_portfolio_loc);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }

    uint lot_max = 0;

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == QStringLiteral("tickers")){

            while(reader.readNextStartElement()){
                if(reader.name() == QStringLiteral("ticker")){
                    m_ready_ticker.lots_owned.clear();
                    while(reader.readNextStartElement()){
                        if(reader.name() == QStringLiteral("name")){

                            QString s = reader.readElementText();
                            m_ready_ticker.name = s;

                        }
                        if(reader.name() == QStringLiteral("value")){
                            QString s = reader.readElementText();
                            auto price  = s.toDouble();

                            m_ready_ticker.price_dollars = std::floor(price);
                            m_ready_ticker.price_cents   = std::floor(((price - static_cast<double>(m_ready_ticker.price_dollars)) * 100.0) + 0.1);


                        }
                        if(reader.name() == QStringLiteral("lots")){
                            while(reader.readNextStartElement()){
                                asx::LOT lot;
                                if(reader.name() == QStringLiteral("lot")){
                                    while(reader.readNextStartElement()){

                                        if(reader.name() == QStringLiteral("date")){
                                            QString s = reader.readElementText();
                                            lot.date = s;
                                        }

                                        if(reader.name() == QStringLiteral("number")){
                                            QString s = reader.readElementText();
                                            lot.lot_number = s.toUInt();

                                            if(lot.lot_number > lot_max){
                                                lot_max = lot.lot_number;
                                            }
                                        }

                                        if(reader.name() == QStringLiteral("qty")){
                                            QString s = reader.readElementText();
                                            lot.qty = s.toUInt();
                                        }
                                        if(reader.name() == QStringLiteral("purchase")){
                                            QString s = reader.readElementText();
                                            auto price  = s.toDouble();

                                            lot.price_dollars = std::floor(price);
                                            lot.price_cents   = std::floor(((price - static_cast<double>(lot.price_dollars)) * 100.0) + 0.1);
                                        }
                                    }

                                    m_ready_ticker.lots_owned.push_back(lot);
                                }
                            }
                        }
                    }

                    emit new_ticker();
                }
            }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
    }

    emit lot_counter(lot_max);
    emit done();

}

void PortfolioHandler::creation_approved()
{
    QFile file(m_portfolio_loc);

    file.open(QIODevice::WriteOnly|QIODevice::Text);

    m_portfolio_exists = true;
}

void PortfolioHandler::load_portfolio()
{
    QFileInfo check_file(m_portfolio_loc);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        m_portfolio_exists = true;
    } else {
        m_portfolio_exists = false;
        emit request_creation();
        return;
    }

    emit request_lock();
}

asx::TICKER PortfolioHandler::get_ready_ticker()
{
    return m_ready_ticker;
}

void PortfolioHandler::save(std::vector<asx::TICKER> &tickers)
{
    QFile file(m_portfolio_loc);

    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("tickers");

    for(auto &ticker:tickers){
        xmlWriter.writeStartElement("ticker");

        xmlWriter.writeTextElement("name", ticker.name);
        xmlWriter.writeTextElement("value", QString("%1.%2").arg(ticker.price_dollars).arg(ticker.price_cents));

        xmlWriter.writeStartElement("lots");

        for(auto &lot:ticker.lots_owned){
            xmlWriter.writeStartElement("lot");
            xmlWriter.writeTextElement("date", lot.date);
            xmlWriter.writeTextElement("qty", QString::number(lot.qty));
            xmlWriter.writeTextElement("number", QString::number(lot.lot_number));
            xmlWriter.writeTextElement("purchase", QString("%1.%2").arg(lot.price_dollars).arg(lot.price_cents));
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
}
