#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QObject>
#include <QDate>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

class Organizer : public QObject
{
    Q_OBJECT
private:
    class Task{
    public:
        Task(QString &newName, QDate &date, int prog);
        QString name;
        QDate deadline;
        int progress;

    };

    bool createConnectionDB();
    bool createTable();
    bool insertRecord(QString newName, int day, int mounth, int year, int prog);

    //QList<Task> listTask;
    //QList<Task> newListTask;
    //QString fileName;
    QSqlDatabase db;
    QSqlQueryModel *model;
    QTableView *view;

public:
    explicit Organizer(QObject *parent = nullptr);
    ~Organizer();
    Q_INVOKABLE void setTask(QString newName, QString date, QString prog);
    Q_INVOKABLE int getTaskCount();
    Q_INVOKABLE void getTable();
signals:
    void noValid();
};

#endif // ORGANIZER_H
