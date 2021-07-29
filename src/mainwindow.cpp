#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progress->setSize(16);
    ui->progress->setMaximumHeight(ui->bu_update->height());
    ui->progress->setMaximumWidth(25);

    ui->progress->hide();

    QPixmap upArrow(":/icons/Icons/arrow_circle_up_black_24dp.svg");
    QPixmap downArrow(":/icons/Icons/arrow_circle_down_black_24dp.svg");

    QIcon upIcon(upArrow);
    QIcon downIcon(downArrow);

    ui->bu_import->setIcon(upIcon);
    ui->bu_import->setIconSize(upArrow.rect().size());

    ui->bu_export->setIcon(downIcon);
    ui->bu_export->setIconSize(downArrow.rect().size());

    QList<QtMaterialFlatButton *> flatButs      = this->findChildren<QtMaterialFlatButton *>();
    QList<QtMaterialRaisedButton *> raisedButs  = this->findChildren<QtMaterialRaisedButton *>();

    for(auto &flat:flatButs){flat->setForegroundColor(QColor(QStringLiteral("#6000e6")));}

    for(auto &raised:raisedButs){
        raised->setBackgroundColor(QColor(QStringLiteral("#6000e6")));
        raised->setForegroundColor(QColor(QStringLiteral("#ffffff")));
    }

    ui->bu_addTicker->setHaloVisible(false);
    ui->bu_import->setHaloVisible(false);
    ui->bu_export->setHaloVisible(false);

    QtMaterialSnackbar *snack = new QtMaterialSnackbar(this);

    m_globalTickerHandler = new ASXcURL(this);


    //    ui->progress->setSize(14);


//    LotView *view = new LotView(ui->pg_owned);

//    ui->pg_owned->layout()->addWidget(view);

    //connections

    connect(ui->bu_addTicker, &QPushButton::clicked, this, &MainWindow::addClicked);
    connect(this, &MainWindow::message, snack, &QtMaterialSnackbar::addMessage);

    connect(ui->bu_showOwned, &QtMaterialFlatButton::clicked, this, &MainWindow::bu_ownedClicked);
    connect(ui->bu_showSold, &QtMaterialFlatButton::clicked, this, &MainWindow::bu_soldClicked);
    connect(ui->bu_showGraph, &QtMaterialFlatButton::clicked, this, &MainWindow::bu_chartClicked);
    connect(ui->lst_tickers, &QListWidget::currentRowChanged, ui->stack_owned, &QStackedWidget::setCurrentIndex);
    connect(ui->lst_tickers, &QListWidget::currentRowChanged, ui->stack_sold, &QStackedWidget::setCurrentIndex);
//    connect(ui->lst_tickers, &QListWidget::currentRowChanged, ui->stack_chart, &QStackedWidget::setCurrentIndex);

    connect(m_globalTickerHandler, &ASXcURL::updateComplete, this, [this](){ui->progress->hide();});
    connect(ui->bu_update, &QAbstractButton::clicked, this, [this](){ui->progress->show();});
    connect(ui->actionSet_Key, &QAction::triggered, this, &MainWindow::setKey);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addClicked()
{
    newTicker("VAS");//temp  code
    newTicker("VETH");
    return;
    TickerAddDialog diag;

    connect(&diag, &TickerAddDialog::acceptedTicker, this, &MainWindow::newTicker);

    diag.exec();
}

void MainWindow::newTicker(QString name)
{
    emit message(QStringLiteral("Ticker added ") + name);

    ui->lst_tickers->addItem(name);

    m_globalTickerHandler->registerTicker(name);

    auto *ownPg     = new QWidget();
    auto *ownLay    = new QVBoxLayout(ownPg);

    OwnedLots *ownView = new OwnedLots(ownPg);

    ASXcURL *tickerhandler = new ASXcURL(ownView);
    tickerhandler->setTicker(name);

    ownLay->addWidget(ownView);

    ui->stack_owned->addWidget(ownPg);

    auto *soldPg     = new QWidget();
    auto *soldLay    = new QVBoxLayout(soldPg);

    SoldLots *soldView = new SoldLots(soldPg);
    soldView->setSisterView(ownView);

    soldLay->addWidget(soldView);

    ui->stack_sold->addWidget(soldPg);

    connect(ownView, &OwnedLots::saleSubmitted, soldView, &SoldLots::addFormedLot);
    connect(m_globalTickerHandler, &ASXcURL::rawResult, tickerhandler, &ASXcURL::getTickerValue);
    connect(tickerhandler, &ASXcURL::tickerMarketValue, ownView, &OwnedLots::updateTickerValue);

}

void MainWindow::bu_ownedClicked()
{
    setLinesWhite();
    ui->ownedLine->setStyleSheet(QString::fromUtf8("color: #6000e6"));
    ui->stack->setCurrentIndex(0);
}

void MainWindow::bu_soldClicked()
{
    setLinesWhite();
    ui->soldLine->setStyleSheet(QString::fromUtf8("color: #6000e6"));
    ui->stack->setCurrentIndex(1);
}

void MainWindow::bu_chartClicked()
{
    setLinesWhite();
    ui->chartLine->setStyleSheet(QString::fromUtf8("color: #6000e6"));
    ui->stack->setCurrentIndex(2);
}

void MainWindow::setKey()
{
    SetKeyDialog *set = new SetKeyDialog(this);

    connect(set, &SetKeyDialog::submittedKey, m_globalTickerHandler, &ASXcURL::setApiKey);

    set->exec();
}

void MainWindow::setLinesWhite()
{
    ui->soldLine->setStyleSheet(QString::fromUtf8("color: #ffffff"));
    ui->ownedLine->setStyleSheet(QString::fromUtf8("color: #ffffff"));
    ui->chartLine->setStyleSheet(QString::fromUtf8("color: #ffffff"));
}

void MainWindow::on_bu_update_clicked()
{
    m_globalTickerHandler->update();
}
