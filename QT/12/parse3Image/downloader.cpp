#include "downloader.h"
#include <QFile>

Downloader::Downloader(QObject *parent)
    : QObject{parent}
{
    netManager = new QNetworkAccessManager(this);
    connect(netManager, &QNetworkAccessManager::finished, this, &Downloader::slotFinish);


}

void Downloader::download(const QUrl &url)
{
    qDebug() << url.toString();

    QNetworkRequest request(url);
    QNetworkReply *reply = netManager->get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &Downloader::downloadProgress);

}

void Downloader::downloadImg()
{
    isHTML = false;
    for(const QUrl* i : urlList){
        download(*i);
    }
}

void Downloader::setRequest(QString &req)
{
    urlList.clear();
    request = req;
    QUrl url("https://yandex.ru/images/search?text=" + request);
    isHTML = true;
    download(url);


}

void Downloader::parseHtml()
{


    QFile file("save.html");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "file no open";
        return;
    }
    QByteArray byte = file.readAll();
    fileStr = byte;
    int pos = 0;
    int lpos, rpos;
    QString str;
    for (int i = 0; i < 3; ++i){
        int sumSim = 0;
        pos = fileStr.indexOf("img_href\":\"" , pos);
        lpos = fileStr.indexOf("http", pos);
        rpos = fileStr.indexOf('"', lpos+2);
        sumSim = rpos - lpos;
        str = fileStr.mid(lpos, sumSim);
        pos = rpos;
        qDebug() << str;
        urlList.push_back(new QUrl(str));
    }
    for (const QUrl *i : urlList){
        qDebug() << i->toString();
    }
}

void Downloader::done(const QUrl &url, const QByteArray &byte)
{
    QFile file;

    if(isHTML){
        file.setFileName("save.html");
    }
    else{
        file.setFileName(url.path().section('/', -1));
    }

    if(file.open(QIODevice::WriteOnly)){
        file.write(byte);
        if(isHTML){
            parseHtml();
            downloadImg();
        }
        else{
            emit doneFile(file.fileName());
        }
    }
    file.close();
}


void Downloader::slotFinish(QNetworkReply *reply)
{

    if(reply->error() != QNetworkReply::NetworkError::NoError){
        qDebug() << reply->error();
        emit error();
    }
    else{
        done(reply->url(), reply->readAll());
    }
    reply->deleteLater();
}
