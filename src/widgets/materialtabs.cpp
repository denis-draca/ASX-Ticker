#include "materialtabs.h"

MaterialTabs::MaterialTabs(QWidget *parent) : QWidget(parent)
{
    m_tabCount = 0;

    auto *widgeLayout = new QVBoxLayout(this);

    m_bar = new QHBoxLayout(this);

    widgeLayout->addLayout(m_bar);

    this->setLayout(widgeLayout);
}

void MaterialTabs::addTab(QString name)
{
    auto *tabLayout     = new QVBoxLayout(this);

    auto bu_tab         = new QtMaterialFlatButton(this);
    auto bu_tabBelow    = new QtMaterialFlatButton(this);

    bu_tab->setForegroundColor(QColor(QStringLiteral("#6000e6")));
    bu_tab->setText(name);
    bu_tab->setHaloVisible(false);
    bu_tab->setRippleStyle(Material::NoRipple);

    bu_tabBelow->setHaloVisible(false);
    bu_tabBelow->setRippleStyle(Material::NoRipple);
    bu_tabBelow->setMaximumHeight(2);

    m_strips.push_back(bu_tabBelow);

    tabLayout->addWidget(bu_tab);
    tabLayout->addWidget(bu_tabBelow);

    connect(bu_tab, &QtMaterialFlatButton::clicked, [&, this](){
        for(auto &pt:m_strips){
            pt->setBackgroundColor(QColor(QStringLiteral("#ffffff")));
        }
        bu_tab->setBackgroundColor(QColor(QStringLiteral("#6000e6")));
    });

    m_bar->addLayout(tabLayout);
}
