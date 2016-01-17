#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QVariant>
#include <QList>

class ToDoItem {
  public:

    ToDoItem() {
        name = "";
        estimated_minutes = 0;
        was_done = false;
    }

    QString name;

    int estimated_minutes;

    bool was_done;
};

/**
 * A ToDoList model, with an incremental caching of the total of minutes.
 * NOTE: I was not able to extend (safely) QStandardTableModel with this feature,
 * because the slots and signals have no info about the old changed value,
 * so I start "from scratch" with a complete model implementation.
 */
class ToDoListModel : public QAbstractTableModel {
    Q_OBJECT

    public:

        ToDoListModel(QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
        int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
        QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
        Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;

        QList<ToDoItem> getTasks();

        virtual void appendTasks(QList<ToDoItem> &tasks);

        int getTotalEstimate()
        {
          return cached_total_estimate;
        }

        int getTotalEffort()
        {
            return cached_total_effort;
        }

    signals:

      void totalEstimateChanged(int newValue);

      void totalEffortChanged(int newValue);

    protected:

      void updateCachedEstimate(bool isInsert, const ToDoItem &ti) {
          int toAdd;

          if (isInsert) {
              toAdd = ti.estimated_minutes;
          } else {
              // NOTE: in case of remove, remove the value from the cache instead
              toAdd = - ti.estimated_minutes;
          }

          if (ti.was_done) {
              cached_total_effort += toAdd;
              emit totalEffortChanged(cached_total_effort);
          } else {
              cached_total_estimate += toAdd;
              emit totalEstimateChanged(cached_total_estimate);
          }
      }

    private:

       QList<ToDoItem> tasks;

       int cached_total_estimate;

       int cached_total_effort;

};



#endif // TODOLISTMODEL_H

