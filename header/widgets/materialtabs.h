#ifndef MATERIALTABS_H
#define MATERIALTABS_H

#include <QWidget>
#include <QLayout>
#include <vector>
#include <QScrollArea>

#include <qtmaterialflatbutton.h>

class MaterialTabs : public QWidget
{
    Q_OBJECT
public:
    explicit MaterialTabs(QWidget *parent = nullptr);

signals:

public slots:
    void addTab(QString name);

private:
    QHBoxLayout *m_bar;

    size_t m_tabCount;

    std::vector<QtMaterialFlatButton *> m_strips;
};

#endif // MATERIALTABS_H
