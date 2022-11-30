#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    void download(const QUrl& url);
    void downloadImg();
    void setRequest(QString &req);

signals:
    void downloadProgress(qint64, qint64);
    void doneFile(const QString&);
    void error();

private:
    QNetworkAccessManager *netManager;
    bool isHTML;
    QString fileStr;                    //  HTML текст
    QString request;                    // запрос
    QList<QUrl*> urlList;


    void parseHtml();
    void done(const QUrl&, const QByteArray&);
private slots:
    void slotFinish(QNetworkReply*);

};

#endif // DOWNLOADER_H
