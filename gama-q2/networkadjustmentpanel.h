/*
  GNU Gama Qt based GUI
  Copyright (C) 2013 Ales Cepek <cepek@gnu.org>

  This file is part of GNU Gama.

  GNU Gama is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GNU Gama is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Gama.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NETWORKADJUSTMENTPANEL_H
#define NETWORKADJUSTMENTPANEL_H

#include "adjustment.h"

#include <QMainWindow>

namespace Ui {
    class NetworkAdjustmentPanel;
}

class ParameterEditor;
class PointEditor;
class ObservationEditor;
class NetworkSVG;
class AdjustmentResults;

class NetworkAdjustmentPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetworkAdjustmentPanel(QString connectionName, QWidget *parent = 0);
    ~NetworkAdjustmentPanel();

    void exec();
    bool isValid() const { return valid; }

    static bool        closeAllNetworkAdjustmentPanels;
    static QWidgetList allNetworkAdjustmentPanelsList;

private:
    Ui::NetworkAdjustmentPanel *ui;

    enum {menu_parameters, menu_points, menu_observations };

    Adjustment         adj;
    ParameterEditor   *par;
    PointEditor       *ped;
    ObservationEditor *obs;
    NetworkSVG        *svg;
    AdjustmentResults *res;

    QString connection_name;
    QString configuration_name;
    bool    useTabbedWidgets;
    bool    valid;

    void set_gui_adjustment_functions_status(bool isvalid);

private slots:

    void update_point_editor_table();
    void update_observation_editor_table();

    void getConfigurationName(QString conf, bool tabbed);
    void draw_network_configuration();
    void tabIndexChanged(int n);
    void update_adjustment_results(bool solved=false);
    void status_bar(QString text);
    void save_configuration(QString confname);

    void on_actionSave_XML_adjustment_results_triggered();
    void on_actionSave_adjustment_results_as_plain_text_triggered();
    void on_action_Close_triggered();
    void on_actionSave_as_SQL_file_triggered();
    void on_action_Run_triggered();
    void on_actionSave_network_configuration_outline_triggered();
    void on_actionOutline_draw_triggered();
    void closeEvent(QCloseEvent *event);
    void on_action_Points_changed();
    void on_actionParameters_changed();
    void on_actionObservations_changed();
    void on_action_Save_into_database_triggered();
    void on_actionSave_As_triggered();
    void on_actionPrint_triggered();
    void on_actionPrint_as_PDF_triggered();
    void on_actionSave_adjustment_results_as_HTML_file_triggered();

    void on_actionGama_q2_help_triggered();

signals:

    void networkAdjustmentPanel(bool newPanel);
};

#endif // NETWORKADJUSTMENTPANEL_H
