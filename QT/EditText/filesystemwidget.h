#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTreeView>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileSystemWidget(QWidget *parent = nullptr);
    QStandardItemModel* getCurrentModel(){
        return model;
    }
    void setNewModel(QStandardItemModel *newMod);
    void rebuildModel(QString str);
private:
    QStandardItemModel *model;
    QTreeView *treeView;
    QGridLayout *layout;
    QComboBox *discs;
    QPushButton *mainPath;
    QString curretnPath;
    QLineEdit *path;

private slots:
    void getDisk(int index);
    void goMainPath();
signals:

};

#endif // FILESYSTEMWIDGET_H
