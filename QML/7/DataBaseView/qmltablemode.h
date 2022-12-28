#pragma once

#include <QAbstractTableModel>
#include <QObject>
#include <vector>


class QMLTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QMLTableModel(QObject *parent = nullptr);

    struct RowElement{
        int id;
        QString name;
        QString surname;
        QString friends;
    };



    enum QMLTableModelRoles{
        IdRole = Qt::UserRole + 1,
        NameRole,
        SurnameRole,
        FriendsRole
    };

    Q_INVOKABLE int rowCount(const QModelIndex& index) const override;
    Q_INVOKABLE int columnCount(const QModelIndex& index) const override;
    Q_INVOKABLE QVariant data(const QModelIndex& index, int role)const override;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const override;

    void appendRowElement(const RowElement& element);
private:
    std::vector<RowElement> m_data;
};


