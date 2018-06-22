#include "mymodel.h"

myModel::myModel(QObject *parent)
    : QAbstractListModel(parent)
{
    setDir("C:/image");
    setMask("*.jpg *.png");
    m_qlpixList = getIcon(QDir(m_ptxDir));
}

QVariant myModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return "Image";
}

int myModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid())
        return 0;
    return m_qlpixList.size();


}

QVariant myModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role) {
    case Qt::DecorationRole:{
        QPixmap pix(m_qlpixList.at(index.row()));
        return pix;
    }
    case pathToImg:{
            return "file:///./image/"+ m_qstrlPath.at(index.row());
        }
    default:
        return QVariant();
        return QVariant();
    }
}

bool myModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

             m_qlpixList.replace(index.row(), value.value<QPixmap>());
             emit dataChanged(index, index);
             return true;
         }
         return false;
}

Qt::ItemFlags myModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QHash<int, QByteArray> myModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames ();;
    roles[pathToImg] = "pathToImg";
    return roles;
}

bool myModel::insertRows(int position, int rows, const QModelIndex &index)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_qlpixList.insert(position,QPixmap());
    }

    endInsertRows();
    return true;
}

bool myModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_qlpixList.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QStringList myModel::mimeTypes() const
{
    QStringList types;
    types << "image/jpeg";
    return types;
}

QMimeData *myModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QPixmap pix = data(index, Qt::DecorationRole).value<QPixmap>() ;
            stream << pix;
        }
    }

    mimeData->setData("image/jpeg", encodedData);
    return mimeData;
}

bool myModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << action;
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("image/jpeg"))
        return false;

    if (column > 0)
        return false;
    int beginRow;

    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());
    QByteArray encodedData = data->data("image/jpeg");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QList<QPixmap> newItems;
    int rows = 0;

    while (!stream.atEnd()) {
        QPixmap pix;
        stream >> pix;
        newItems.push_back(pix);
        ++rows;
    }
    insertRows(beginRow, rows, QModelIndex());
    foreach (const QPixmap &pix, newItems) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, pix);
        beginRow++;
    }

    return true;
}

Qt::DropActions myModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}


QList<QPixmap> myModel::getIcon(const QDir &dir)
{
    QList<QPixmap> tmpqlpixList;
    QStringList listFiles = QDir(m_ptxDir).entryList(m_ptxMask.split(" "),QDir::Files);
    m_qstrlPath = listFiles;
    foreach(QString file,listFiles){
        tmpqlpixList.push_back(QPixmap(QDir(m_ptxDir).absoluteFilePath(file)));
    }
    return tmpqlpixList;
}


