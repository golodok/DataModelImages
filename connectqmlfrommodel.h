#ifndef CONNECTQMLFROMMODEL_H
#define CONNECTQMLFROMMODEL_H

#include <QWidget>
#include "QQuickWidget"
#include <QBoxLayout>
#include "Mymodel.h"
#include <QQmlContext>
#include <QPointer>

class connectQmlFromModel : public QWidget
{
    Q_OBJECT
public:
    explicit connectQmlFromModel(QWidget *parent = nullptr);

signals:

public slots:

private:
    void Init();
    //myTableModel m_spDataModel;

    QPointer<QAbstractItemModel> m_model;
};

#endif // CONNECTQMLFROMMODEL_H
