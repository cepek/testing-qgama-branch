# Qgama interface

The main interface

| Qgama      |     | QGamaControlPanel |
|:------     |:----|:------------------|
| Database   |  Connect to database             | ::on_action_Connect_to_database_triggered() |
|            |* Import Configuration File       | ::on_action_Import_configuration_file_triggered() |
|            |* New Empty Configuration         | ::?? |
|            |* Import Examples                 | ::importExamples()|
|            |  Drop Schema tables              | ::on_action_Drop_schema_Tables_triggered()|
|            |  Delete all Data from the Schema | ::on_action_Delete_all_Data_from_the_Schema_triggered()|
|            |  Delete Network Configuration    | ::on_action_Delete_Network_Configuration_triggered() |
|            |  Exit                            | ::on_action_Exit_triggered() |
| Adjustment |  Network Adjustment              | ::on_action_Network_adjustment_triggered() |
| Tools      |  Adjustment results language     | ::on_action_Adjustment_results_language() |
|            |  Application font                | ::on_action_Application_Font() |
| Help       |  Qgama help                      | ** QGamaHelp::get()->show() |
|            |  About Qgama                     | ::on_action_About_qgama_triggered() |
|            |  About Qt                        | ::on_action_About_qt_triggered()|

\* these functions can be run without connecting to a database first, in such a case implicit
*in memory database* is used and the user is responsible for exporting data if they are
needed (for example export configuration XML input file after editing
the network configuration)

\*\* lambda function
