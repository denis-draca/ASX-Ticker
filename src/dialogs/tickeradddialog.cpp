#include "tickeradddialog.h"
#include "ui_tickeradddialog.h"

TickerAddDialog::TickerAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TickerAddDialog)
{
    ui->setupUi(this);

    ui->info_progress->setSize(16);
    ui->accepted->setGeometry(ui->bu_check->geometry());
    ui->denied->setGeometry(ui->bu_check->geometry());

    ui->bu_ok->setForegroundColor(QColor(THEME));
    ui->bu_cancel->setForegroundColor(QColor(THEME));
    ui->bu_check->setForegroundColor(QColor(THEME));

    QRegularExpression rx("[a-zA-Z]{0,4}");
    QValidator *only_text = new QRegularExpressionValidator(rx, this);

    ui->in_ticker->setValidator(only_text);

    connect(ui->bu_check, &QAbstractButton::clicked, this, &TickerAddDialog::check_ticker);
    connect(ui->bu_cancel, &QAbstractButton::clicked, this, [this](){this->close();});
    connect(ui->in_ticker, &QtMaterialTextField::textEdited, this, &TickerAddDialog::validate_input);

    connect(ui->bu_ok, &QAbstractButton::clicked, this, &TickerAddDialog::okClicked);

}

TickerAddDialog::~TickerAddDialog()
{
    m_workerThread.quit();
    m_workerThread.wait();
    delete ui;
}

void TickerAddDialog::check_ticker()
{
    ui->stack->setCurrentIndex(1);

    QString name = ui->in_ticker->text();

    ui->Check->setEnabled(false);


    ASXcURL *curl = new ASXcURL();
    curl->setTicker(name);

    curl->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::finished, curl, &QObject::deleteLater);

    connect(this, &TickerAddDialog::execute, curl, &ASXcURL::checkTickerValid);
    connect(curl, &ASXcURL::validTicker, this, &TickerAddDialog::validTicker);
    connect(curl, &ASXcURL::invalidTickker, this, &TickerAddDialog::invalidTicker);


    m_workerThread.start();

    emit execute();
}

void TickerAddDialog::validate_input(const QString &arg1)
{
    Q_UNUSED(arg1);

    ui->stack->setCurrentIndex(0);
    ui->Check->setEnabled(false);
    ui->bu_ok->setEnabled(false);

    auto data = ui->in_ticker->text();

    ui->in_ticker->setText(data.toUpper());

    ui->Check->setEnabled(!data.isEmpty());
}

void TickerAddDialog::validTicker(QString name)
{
    if(name.compare(ui->in_ticker->text()) == 0){
        ui->stack->setCurrentIndex(2);
        ui->bu_ok->setEnabled(true);
    }
}

void TickerAddDialog::invalidTicker()
{
    ui->stack->setCurrentIndex(3);
}

void TickerAddDialog::okClicked()
{
    QString name = ui->in_ticker->text();
    emit acceptedTicker(name);

    close();
}


void TickerAddDialog::cleanup()
{
    ui->stack->setCurrentIndex(0);
    ui->in_ticker->clear();
    ui->Check->setEnabled(false);
    ui->bu_ok->setEnabled(false);
}

void TickerAddDialog::showEvent(QShowEvent *event)
{
    event->accept();
    cleanup();
}
