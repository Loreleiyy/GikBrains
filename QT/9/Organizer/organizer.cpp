#include "organizer.h"
#include <QFile>
#include <QByteArray>
#include <QDebug>

Organizer::Organizer(QObject *parent)
    : QObject{parent}
{
    fileName = "save";
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)){

        QString str;

        while(!file.atEnd()){
                str = file.readLine();

                QStringList strTask = str.split(' ');
                QString name = strTask[0];
                int dd, MM, yyyy;
                dd = strTask[1].toInt();
                MM = strTask[2].toInt();
                yyyy = strTask[3].toInt();
                QDate date(yyyy, MM, dd);

                int progress = strTask[4].toInt();
                listTask.push_back(Task(name, date, progress));

        }
    }
    for(const Task &task : listTask){
        qDebug() << task.name << ' ' << task.deadline << ' ' << task.progress;
    }
    qDebug() << listTask.size();
}

Organizer::~Organizer()
{
    QFile file(fileName);
    if (file.open(QFile::Append)){
        QString str = "";
        for(const Task &task : newListTask){
            int dd, MM, yyyy;
            dd = task.deadline.day();
            MM = task.deadline.month();
            yyyy = task.deadline.year();
            str += task.name + ' ';
            str += QString::number(dd) + ' ' +
                    QString::number(MM) + ' ' +
                    QString::number(yyyy) + ' ';
            str += QString::number(task.progress) + '\n';
        }
        QByteArray byte = str.toUtf8();
        file.write(byte);

    }
}

void Organizer::setTask(QString newName, QString date, QString prog)
{
    QDate dat = QDate::fromString(date, "dd.MM.yyyy");
    qDebug() << dat;

    int iprog = prog.toInt();
    newListTask.push_back(Task(newName, dat, iprog));
    qDebug() << newListTask[newListTask.size()-1].name;
}



Organizer::Task::Task(QString &newName, QDate &date, int prog) : name(newName),
    deadline(date), progress(prog){

}
