#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QMenu>
#include <QMap>
#include <QMdiArea>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

    enum actions{
        save,
        open,
        reference
    };
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

private:
    Ui::MainWindow *ui;

    QMdiArea *mid;
    QTranslator *translator;
    void buttonSetText();
    QMenu *menu;
    QMenu *actLanguage;
    QMenu *actTheme;
    QMap<QString, QAction*> action;
};
#endif // MAINWINDOW_H
