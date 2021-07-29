#ifndef BUYDIALOG_H
#define BUYDIALOG_H

#include <QDialog>

namespace Ui {
class BuyDialog;
}

class BuyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyDialog(QWidget *parent = nullptr);
    ~BuyDialog();

signals:
    void submitted(uint qty, double price, QString date);

private slots:
    void on_in_qty_textEdited(const QString &arg1);
    void on_in_price_textEdited(const QString &arg1);

    void okClicked();

private:
    Ui::BuyDialog *ui;
};

#endif // BUYDIALOG_H
