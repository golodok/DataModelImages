#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QPixmap>
#include <QMimeData>
#include <QDebug>

class myModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ModelRoles
    {
        pathToImg
    };

    explicit myModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                          int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setDir(const QString &dir){ m_ptxDir = dir;}
    void  setMask(const QString &mask){ m_ptxMask = mask; }
    QHash<int, QByteArray> roleNames() const;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);


    Qt::DropActions supportedDropActions() const;

private:
    QList<QPixmap>  getIcon(const QDir &dir);
    QStringList getFileInDir(const QDir &dir);
    QString m_ptxMask;
    QString  m_ptxDir;
    QList<QPixmap> m_qlpixList;
};

#endif // MYMODEL_H
