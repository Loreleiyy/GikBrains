#include "organizer.h"
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QWindow>
#include <QSqlRecord>


bool Organizer::createConnectionDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("save.db");
    return db.open();
}

bool Organizer::createTable()
{
    QSqlQuery que;
    QString str = "CREATE TABLE save ("
            "id	INTEGER NOT NULL,"
            "name	TEXT,"
            "day	INTEGER,"
            "mounth	INTEGER,"
            "year INTEGER,"
            "progress	INTEGER,"
                  "PRIMARY KEY(id)"
                  ")";
    qDebug() << str;
    return que.exec(str);
}

bool Organizer::insertRecord(QString newName, int day, int mounth, int year, int prog)
{
    QSqlQuery que;
    QString str = "INSERT INTO save(name, day, mounth, year, progress) "
            "VALUES('%1', '%2', '%3', '%4', '%5')";
    QString s = str.arg(newName).arg(day).arg(mounth).arg(year).arg(prog);
    return que.exec(s);
}

Organizer::Organizer(QObject *parent)
    : QObject{parent}
{

    view = new QTableView();



    model = new QSqlQueryModel(this);


    if (!createConnectionDB()){
        qDebug() << "no connection DB";
        return;
    }
//    if(!createTable()){
//        qDebug() << "no create table";
//        return;
//    }

}

Organizer::~Organizer()
{

}

void Organizer::setTask(QString newName, QString date, QString prog)
{

    QDate dat = QDate::fromString(date, "dd.MM.yyyy");
    qDebug() << dat;
    int dd, MM, yyyy;
    dd = dat.day();
    MM = dat.month();
    yyyy = dat.year();

    int iprog = prog.toInt();
    if(newName.isEmpty() || (!dat.isValid()) || !(iprog >= 0 && iprog <= 10)){
        emit noValid();
        return;
    }

    if(!insertRecord(newName, dd, MM, yyyy, iprog)){
        qDebug() << "no record";
    }
//    newListTask.push_back(Task(newName, dat, iprog));
}

int Organizer::getTaskCount()
{
    QString str = "SELECT COUNT(*) FROM save";
    QSqlQuery que;
    que.exec(str);
    que.first();
    return que.value(0).toInt();
}

void Organizer::getTable()
{
    model->setQuery("SELECT * FROM save");
    view->setModel(model);
    view->resize(800,600);
    view->show();
}



Organizer::Task::Task(QString &newName, QDate &date, int prog) : name(newName),
    deadline(date), progress(prog){

}
