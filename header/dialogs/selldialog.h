#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>

namespace Ui {
class SellDialog;
}

class SellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SellDialog(QWidget *parent = nullptr);
    ~SellDialog();

    void setMaxQty(int qty);

signals:
    void submitSale(uint qty, double price, QString date);

private slots:
    void on_in_qty_textEdited(const QString &arg1);

    void on_in_price_textEdited(const QString &arg1);
    void submitClicked();

private:
    Ui::SellDialog *ui;
};

#endif // SELLDIALOG_H
