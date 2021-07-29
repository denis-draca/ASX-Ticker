#ifndef SETKEYDIALOG_H
#define SETKEYDIALOG_H

#include <QDialog>

namespace Ui {
class SetKeyDialog;
}

class SetKeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetKeyDialog(QWidget *parent = nullptr);
    ~SetKeyDialog();

signals:
    void submittedKey(QString key);

private slots:
    void on_in_key_textEdited(const QString &arg1);

private:
    Ui::SetKeyDialog *ui;
};

#endif // SETKEYDIALOG_H
