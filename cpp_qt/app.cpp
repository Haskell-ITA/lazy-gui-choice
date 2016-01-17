/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QVariant>
#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "todolistmodel.h"
#include "totalestimatelabel.h"
#include <iostream>

// TODO uso integer editor for estimate
// TODO uso flag true/false for work-done

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ToDoListModel model;

    // Labels with totals

    QLabel * lcEffort = new QLabel;
    TotalEstimateLabel * lEffort = new TotalEstimateLabel;
    lcEffort->setText("Total Effort");
    QObject::connect(&model, SIGNAL(totalEffortChanged(int)),
                     lEffort, SLOT(setTotalEstimate(int)));


    QLabel * lcEstimated = new QLabel();
    TotalEstimateLabel * lEstimated = new TotalEstimateLabel();
    lcEstimated->setText("Estimated Effort");
    QObject::connect(&model, SIGNAL(totalEstimateChanged(int)),
                     lEstimated, SLOT(setTotalEstimate(int)));


    QFormLayout * form1 = new QFormLayout;
    form1->addRow(lcEffort, lEffort);
    form1->addRow(lcEstimated, lEstimated);

    // Table with tasks

    QTableView *table = new QTableView;

    // TODO enable drag and drop for moving cells
    table->setDragEnabled(true);
    table->viewport()->setAcceptDrops(true);
    table->setDropIndicatorShown(true);
    table->setDragDropMode(QAbstractItemView::InternalMove);

    // Init model after the signal is set.

    QList<ToDoItem> tasks;
    for (int row = 0; row < 100; ++row) {
       ToDoItem ti;
       ti.name = QString("Task %0").arg(row + 1);
       ti.estimated_minutes = row + 1;
       ti.was_done = false;
       tasks.append(ti);
    }
    model.appendTasks(tasks);

    // NOTE: add now the model, otherwise the table does not show data.
    table->setModel(&model);

    // Add widgets to the main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(form1);
    layout->addWidget(table);

    // Create main window
    QWidget window;
    window.setLayout(layout);
    window.setWindowTitle("Lazy GUI Chooser - QT");
    window.show();

    return app.exec();
}
