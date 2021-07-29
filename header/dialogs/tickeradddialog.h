#ifndef TICKERADDDIALOG_H
#define TICKERADDDIALOG_H

#include <QDialog>
#include <QShowEvent>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QThread>
#include <QString>

#include "asxcurl.h"

#define THEME QStringLiteral("#6000e6")


namespace Ui {
class TickerAddDialog;
}

class TickerAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TickerAddDialog(QWidget *parent = nullptr);
    ~TickerAddDialog();

private slots:
    void check_ticker();
    void validate_input(const QString &arg1);

    void validTicker(QString name);
    void invalidTicker();
    void okClicked();

signals:
    void execute();
    void acceptedTicker(QString name);

private:
    Ui::TickerAddDialog *ui;

    QThread m_workerThread;

private:

    void cleanup();

    void showEvent( QShowEvent* event );
};

#endif // TICKERADDDIALOG_H
