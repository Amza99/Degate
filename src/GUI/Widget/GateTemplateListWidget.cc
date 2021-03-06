/**
 * This file is part of the IC reverse engineering tool Degate.
 *
 * Copyright 2008, 2009, 2010 by Martin Schobert
 * Copyright 2019-2020 Dorian Bachelot
 *
 * Degate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Degate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with degate. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "GateTemplateListWidget.h"

#include <utility>

namespace degate
{
    GateTemplateListWidget::GateTemplateListWidget(QWidget* parent, Project_shptr project, bool unique_selection)
            : QTableWidget(parent), project(std::move(project))
    {
        setColumnCount(3);
        QStringList list;
        list.append(tr("ID"));
        list.append(tr("Name"));
        list.append(tr("Description"));
        setHorizontalHeaderLabels(list);
        resizeColumnsToContents();
        resizeRowsToContents();
        setSelectionBehavior(SelectRows);

        if (unique_selection)
            setSelectionMode(SelectionMode::SingleSelection);
        else
            setSelectionMode(SelectionMode::MultiSelection);

        update_list();
    }

    std::vector<GateTemplate_shptr> GateTemplateListWidget::get_selected_gates()
    {
        QItemSelectionModel* select = selectionModel();

        if (!select->hasSelection())
            return std::vector<GateTemplate_shptr>(); // Empty vector

        QModelIndexList index = select->selectedRows();
        std::vector<GateTemplate_shptr> res;

        for (auto & sel : index)
        {
            if (sel.isValid())
            {
                res.push_back(project->get_logic_model()->get_gate_library()->get_template(item(sel.row(), 0)->text().toInt()));
            }
        }

        return res;
    }

    GateTemplate_shptr GateTemplateListWidget::get_selected_gate()
    {
        QItemSelectionModel* select = selectionModel();

        if (!select->hasSelection())
            return nullptr;

        QModelIndexList index = select->selectedRows();

        auto sel = index.at(0);

        if (!sel.isValid())
            return nullptr;
        else
            return project->get_logic_model()->get_gate_library()->get_template(item(sel.row(), 0)->text().toInt());
    }

    bool GateTemplateListWidget::has_selection()
    {
        return selectionModel()->hasSelection();
    }

    void GateTemplateListWidget::update_list()
    {
        if (project == nullptr)
            return;

        setRowCount(0);

        GateLibrary_shptr gate_lib = project->get_logic_model()->get_gate_library();
        for (auto iter = gate_lib->begin(); iter != gate_lib->end(); ++iter)
        {
            GateTemplate_shptr gate = (*iter).second;

            insertRow(rowCount());

            // Id
            auto id_item = new QTableWidgetItem(QString::number(gate->get_object_id()));
            id_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            setItem(rowCount() - 1, 0, id_item);

            // Name
            auto name_item = new QTableWidgetItem(QString::fromStdString(gate->get_name()));
            name_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            setItem(rowCount() - 1, 1, name_item);

            // Description
            auto description_item = new QTableWidgetItem(QString::fromStdString(gate->get_description()));
            description_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            setItem(rowCount() - 1, 2, description_item);
        }

        resizeColumnsToContents();
        resizeRowsToContents();
    }
}
