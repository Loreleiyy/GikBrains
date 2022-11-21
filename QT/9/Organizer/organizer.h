#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QObject>
#include <QDate>
#include <QList>

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

    QList<Task> listTask;
    QList<Task> newListTask;
    QString fileName;
public:
    explicit Organizer(QObject *parent = nullptr);
    ~Organizer();
    Q_INVOKABLE void setTask(QString newName, QString date, QString prog);
signals:

};

#endif // ORGANIZER_H
