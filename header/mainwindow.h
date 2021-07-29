#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include <qtmaterialtextfield.h>
#include <qtmaterialtabs.h>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialcircularprogress.h>
#include <qtmaterialsnackbar.h>

#include "tickeradddialog.h"
#include "lotview.h"
#include "ownedlots.h"
#include "soldlots.h"
#include "materialtabs.h"
#include "setkeydialog.h"

#include <math.h>

#define THEME QStringLiteral("#6000e6")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addClicked();
    void newTicker(QString name);
    void bu_ownedClicked();
    void bu_soldClicked();
    void bu_chartClicked();
    void setKey();

    void on_bu_update_clicked();

signals:
    void message(QString);

private:
    Ui::MainWindow *ui;

    TickerAddDialog *m_addTicker;

    ASXcURL *m_globalTickerHandler;

    void setLinesWhite();
};

#endif // MAINWINDOW_H
