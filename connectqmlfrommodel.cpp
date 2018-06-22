#include "connectqmlfrommodel.h"
connectQmlFromModel::connectQmlFromModel(QWidget *parent) : QWidget(parent)
{
    Init();
}

void connectQmlFromModel::Init()
{
    //setObjectName();
    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_model = new myModel();
    QQuickWidget* pQuickWidget = new QQuickWidget(this);
    pQuickWidget->setSource(QUrl("qrc:/main.qml"));
    pQuickWidget->setFixedSize(490,390);
    pQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    pMainLayout->addWidget(pQuickWidget);

    QQmlContext* pcon = pQuickWidget->rootContext();

    pcon->setContextProperty("imgModel",m_model);
    pcon->setContextProperty("myText","Image:");

}
