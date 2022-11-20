#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "specialchar.h"


#include <QDebug>
#include <QTableWidget>

#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QStringList list = {"C++", "Python", "Java", "C#", "PHP", "JavaScript"};
    model = new QStandardItemModel(list.size(), 1, this);


    ui->listProgram->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);

    for (int i = 0; i < model->rowCount(); ++i){
        QString str = list[i];
        QModelIndex index = model->index(i, 0);
        model->setData(index, str, Qt::DisplayRole);

        model->setData(index, QIcon("./icon/" + str + ".svg"), Qt::DecorationRole);
    }

    ui->listProgram->setViewMode(QListView::ListMode);
    ui->listProgram->setMovement(QListView::Free);
    ui->listProgram->setModel(model);
    ui->listProgram->setDragDropMode(QAbstractItemView::InternalMove);




    QStringList table = {"№", "Имя компьютера", "IP адрес", "MAC адрес"};
    int row = 4;
    int col = 4;
    ui->tableComp->setRowCount(row);
    ui->tableComp->setColumnCount(col);
    ui->tableComp->setHorizontalHeaderLabels(table);
    ui->tableComp->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableComp->setColumnWidth(3,140);


    for(int i = 0; i < row; ++i){
        QString str = QString::number(i+1);
        QTableWidgetItem *item = new QTableWidgetItem(str);
        ui->tableComp->setItem(i, 0, item);
        str = "comp_" + QString::number(i+1);
        QTableWidgetItem *item2 = new QTableWidgetItem(str);
        ui->tableComp->setItem(i,1, item2);
        str = QString("192.168.%1.%2").arg(i).arg(i+1);

        QTableWidgetItem *item3 = new QTableWidgetItem(str);
        ui->tableComp->setItem(i,2, item3);
        str = QString("00-17-ab-be-28-%1c").arg(i);
        QTableWidgetItem *item4 = new QTableWidgetItem(str);
        ui->tableComp->setItem(i,3, item4);
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TextSpecChar_textChanged()
{
    QString txt = ui->TextSpecChar->toPlainText();
    qint32 pos = 0;
    while(true) {
        qint32 fnd = txt.indexOf("<#", pos);
        if (fnd == -1)return;
        pos = fnd +1;
        int r = txt.indexOf(">", fnd);
        int space = txt.indexOf(" ", fnd);

        if((r < space || space == -1) && r != -1){
            SpecialChar specialChar(txt.mid(fnd+2, r - fnd -2));
            QTextCursor cursor = ui->TextSpecChar->textCursor();

            txt.insert(r+1, specialChar.parse());
            txt.remove(fnd, r - fnd+1);
            ui->TextSpecChar->setPlainText(txt);
            ui->TextSpecChar->setTextCursor(cursor);
        }
    }
}


void MainWindow::on_Button2Add_clicked()
{
    int count = model->rowCount();
    model->insertRow(count);
    QModelIndex index = model->index(count, 0);

    model->setData(index, "NewProg", Qt::DisplayRole);
    model->setData(index, QIcon("./icon/comp"), Qt::DecorationRole);
}


void MainWindow::on_Button2Delete_clicked()
{
    int row = ui->listProgram->currentIndex().row();
    model->takeRow(row);
}


void MainWindow::on_checkIcon_stateChanged(int arg1)
{
    if (arg1) {
        ui->listProgram->setViewMode(QListView::IconMode);
    }
    else {
        ui->listProgram->setViewMode(QListView::ListMode);
    }
}


void MainWindow::on_Button3Color_clicked()
{
    QList<QTableWidgetItem *> item = ui->tableComp->selectedItems();

    for (auto &i : item) {

        i->setBackground(QBrush(Qt::green, Qt::SolidPattern));
    }
}





