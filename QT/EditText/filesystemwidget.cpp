#include "filesystemwidget.h"
#include <QDir>
#include <QLineEdit>

FileSystemWidget::FileSystemWidget(QWidget *parent)
    : QWidget{parent}
{
    model = new QStandardItemModel(this);
    treeView = new QTreeView(this);
    layout = new QGridLayout(this);
    setLayout(layout);
    layout->addWidget(treeView,1,0,10,10);

    if(QSysInfo::productType() == "windows")
    {
    discs = new QComboBox(this);
    QFileInfoList list = QDir::drives();
    QFileInfoList::const_iterator listdisk = list.begin();

    for (; listdisk < list.end(); ++listdisk) {
    discs->addItem(listdisk->path());
    }
    if (list.count() > 0)
    {
    rebuildModel(list.at(0).path());
    }
    layout->addWidget(discs, 0, 0, 1, 2); // координаты
    path = new QLineEdit(this);
    path->setText(curretnPath);
    path->setReadOnly(true);
    layout->addWidget(path, 0,3,1,7);
    connect(discs, SIGNAL(activated(int)), this, SLOT(getDisk(int)));
    } else {
    mainPath = new QPushButton(this);
    mainPath->setText("/");
    layout->addWidget(mainPath, 0, 0, 1, 2);
    connect(mainPath, SIGNAL(clicked()), this, SLOT(goMainPath()));
    rebuildModel("/");
    }

}

void FileSystemWidget::setNewModel(QStandardItemModel *newMod)
{
    treeView->setModel(newMod);
    model = newMod;

}

void FileSystemWidget::rebuildModel(QString str)
{
    curretnPath = str;
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStandardItem*> items;
    items.append(new
    QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon))
    , str));
    model->appendRow(items);
    QDir dir(str);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
    QStringList list = dir.entryList();
    int amount = list.count();
    QList<QStandardItem*>folders;
    for (int i = 0; i < amount; i++)
    {
    QStandardItem* f = new
    QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)),
    list.at(i));
    folders.append(f);
    }
    items.at(0)->appendRows(folders);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
    amount = list.count();
    QList<QStandardItem*>files;
    for (int i = 0; i < amount; i++)
    {
    QStandardItem* f = new
    QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),
    list.at(i));
    files.append(f);
    }

    items.at(0)->appendRows(files);
    setNewModel(model);
}

void FileSystemWidget::getDisk(int index)
{
    QFileInfoList diskList = QDir::drives();
    rebuildModel(diskList.at(index).path());
}

void FileSystemWidget::goMainPath()
{
    rebuildModel("/");
}
