#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QMenu>
#include <QMap>
#include <QMdiArea>
#include <QTextBlockFormat>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();


protected:



private slots:
    void onSave();

    void onOpen();

    void onReference();

    void openForReading();


    void setDarkTheme();
    void setLightTheme();
    void setEnglish();
    void setRu();
    void print();
    void copyFormat();
    void pasteFormat();
    void newFont();
    void onLeftEdge();
    void onRightEdge();
    void onCenter();
    void dateTime();

private:
    Ui::MainWindow *ui;

    QMdiArea *mid;
    QTranslator *translator;
    void buttonSetText();
    QMenu *menu;
    QMenu *actLanguage;
    QMenu *actTheme;
    QMenu *format;
    QMap<QString, QAction*> action;
    QTextBlockFormat *form;
};
#endif // MAINWINDOW_H
