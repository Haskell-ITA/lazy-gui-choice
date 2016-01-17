
#include "todolistmodel.h"


ToDoListModel::ToDoListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    cached_total_estimate = 0;
    cached_total_effort = 0;
}

void ToDoListModel::appendTasks(QList<ToDoItem> &t)
{
    for (int i = 0; i < t.size(); ++i) {
        const ToDoItem ti(t.at(i));
        updateCachedEstimate(true, ti);
        tasks.append(ti);
    }
}

int ToDoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tasks.size();
}

int ToDoListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant ToDoListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= tasks.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        ToDoItem ti(tasks.at(index.row()));

        if (index.column() == 0) {
            return ti.name;
        } else if (index.column() == 1) {
            return QVariant(ti.estimated_minutes);
        } else if (index.column() == 2) {
            return QVariant(ti.was_done);
        }
    }
    return QVariant();
}

QVariant ToDoListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Estimate/Effort");
            case 2:
                return tr("Done");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool ToDoListModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        const ToDoItem ti;
        tasks.insert(position, ti);
        updateCachedEstimate(true, ti);
    }

    endInsertRows();
    return true;
}

bool ToDoListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        const ToDoItem ti = tasks.at(position);
        updateCachedEstimate(false, ti);

        tasks.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool ToDoListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        ToDoItem p = tasks.value(row);

        if (index.column() == 0) {
            p.name = value.toString();
        } else if (index.column() == 1) {

            // NOTE: remove older values
            updateCachedEstimate(false, p);

            p.estimated_minutes = value.toInt();

            updateCachedEstimate(true, p);

        } else if (index.column() == 2) {

            // NOTE: remove older value, because it change state
            updateCachedEstimate(false, p);

            p.was_done = value.toBool();

            updateCachedEstimate(true, p);

        } else return false;

        tasks.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags ToDoListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<ToDoItem> ToDoListModel::getTasks()
{
    return tasks;
}

