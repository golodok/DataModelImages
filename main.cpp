#include <QApplication>
#include "connectqmlfrommodel.h"
#include <QListView>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connectQmlFromModel con;

    con.show();
    myModel model;
    QTableView *tableView = new QTableView;
    tableView->setDragDropOverwriteMode(false);
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setDragEnabled(true);
    tableView->setAcceptDrops(true);
    tableView->setDropIndicatorShown(true);
    tableView->setModel(&model);
    tableView->setDefaultDropAction(Qt::MoveAction);
    tableView->show();

    return a.exec();
}
