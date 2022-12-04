#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

// Task HTML Parese

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileStr = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть", QDir::current().path(), "HTML(*.html)");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)){
        QByteArray byte = file.readAll();
        fileStr = byte;
        ui->plainTextEdit->setPlainText(fileStr);
    }
}


void MainWindow::on_ButtonGet_clicked()   // get data
{
    if (fileStr.isEmpty()){
        ui->plainTextEdit->setPlainText("не выбран файл");
        return;
    }
    int pos = 0;
    int lPos, rPos, nymSym;
    QString str;
    for (int i = 0; i < 2; ++i){
        pos = fileStr.indexOf("<div class=\"rate__currency svelte-ov6yem\"", pos);
        lPos = fileStr.indexOf(">", ++pos);
        rPos = fileStr.indexOf("</div>", lPos);
        nymSym = rPos-lPos;
        str = fileStr.mid(lPos+1, nymSym-1);
        if(i == 0){
            ui->lineUSD->setText(str);          // USD
        } else{
            ui->lineEURO->setText(str);         // EURO
        }
    }

    pos = fileStr.indexOf("data-testid=\"weather-temp\"");          // the weather is now
    lPos = fileStr.indexOf(">", pos);
    rPos = fileStr.indexOf("</span>", lPos);
    nymSym = rPos - lPos;
    str = fileStr.mid(lPos+1, nymSym-1);
    pos = 0;

    for (int i = 0; i < 2; ++i){
        pos = fileStr.indexOf("weather__future svelte-dp8sbw\"", pos);  // future weather
        lPos = fileStr.indexOf(">", ++pos);
        rPos = fileStr.indexOf("</div>", lPos);
        nymSym = rPos - lPos;
        str += '\n' + fileStr.mid(lPos+1, nymSym-1);
    }


    ui->textBrowser->setText(str);
}

