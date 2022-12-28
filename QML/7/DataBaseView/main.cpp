#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>

#include "qmltablemode.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    QMLTableModel *model = new QMLTableModel();
    model->appendRowElement(*(new QMLTableModel::RowElement{1, "Ivan", "Ivanov",
                                                     {"Sergey Stepanov, Egor Potapov"}}));
    model->appendRowElement(*(new QMLTableModel::RowElement{2, "Egor", "Svistov",
                                                     "Oleg Zarelua, Alexander Zotov, Elena Ivanova"}));
    model->appendRowElement(*(new QMLTableModel::RowElement{3, "Stepan", "Tok",
                                                     "Ivan Ivanov, Alexander Zotov, Elena Ivanova"}));

    engine.rootContext()->setContextProperty("mdl", model);

    engine.load(url);
    qDebug() << engine.offlineStoragePath();

    return app.exec();
}
