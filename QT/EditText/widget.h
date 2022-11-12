#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTranslator>
#include "filesystemwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


protected:
     void keyPressEvent(QKeyEvent *event)override;

private slots:
    void on_ButtonSave_clicked();

    void on_ButtonOpen_clicked();

    void on_ButtonReference_clicked();

    void openForReading();

    void changeLang();
    void setDarkTheme();
    void setLightTheme();

private:
    Ui::Widget *ui;
    QTranslator *translator;
    void buttonSetText();
    FileSystemWidget *fileWidget;
};
#endif // WIDGET_H
