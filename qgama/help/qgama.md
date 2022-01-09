# Qgama

Qgama is a <a href="http://qt.io/">Qt</a> application for
adjustment of geodetic networks with database support, where the
database can be a simple SQLite3 flat file, used for storing geodetic
network data, or any full-featured relational DBMS
with <a href="http://doc.qt.io/qt-5/sql-driver.html">Qt driver</a>
available, like PostgreSQL or MySQL. It is build on the
<a href="http://www.gnu.org/software/gama/">GNU gama</a> adjustment
library

Qgama Graphical User Interface (GUI) has two main panels. One
*Main Control Panel* that is open on the application startup
and *Network Adjustment Panel* open for a selected network
configuration. More than one network adjustment panels can be opened
simultaneously.

## Quick Start

Start the program and select from the *Main Control Panel* menu

* Database => Connect to Database => OK
* Database => Import Examples => OK
* Adjustment => Network Adjustment => *select an example* => OK
* Adjustment => Run

and start experimenting with the adjustment. Enjoy!

## Main Control Panel

*Main Control Menu* has four menus and a bottom status bar
temporarily displaying program's messages. This panel is displayed at
program startup and the user typically starts with connection to a
database.

| Qgama      |  Main Control Panel    |
|:------     |:----|
| Database   |  Connect to database             |
|            |* Import Configuration File       |
|            |* Import Examples                 |
|            |  Drop Schema tables              |
|            |  Delete all Data from the Schema |
|            |  Delete Network Configuration    |
|            |  Exit                            |
| Adjustment |  Network Adjustment              |
| Tools      |  Adjustment results language     |
|            |  Application font                |
| Help       |  Qgama help                      |
|            |  About Qgama                     |
|            |  About Qt                        |

> Functions marked \* can be run without connecting to a database first,
> in such a case ??> implicit *in memory database* is used and the user is
> responsible for exporting data if they are needed (for example export
> configuration XML input file after editing the network configuration).



### Database menu

* Connect to database

    starts up a dialog for connecting to a database. Until the
    connection is established, some program functions are blocked. To open
    database connection the user must select *Database Drive* which
    implicitly set to *QSQLITE*. For Sqlite the database file must be
    selecte in *Open File dialog*, for new database you must check
    the *Create a New Sqlite Database* check box. Alternatively you
    can work with temporary database *:memory:* (implicit database
    name), but its content is lost when the program is closed.

    If you select another *Database Driver* in the top combo-box
    (for example to *QPSQL*) dialog changes and input fields
    for *Database Name, Username, Passwords, Hostname and Port* are
    displayed (depending on your system only some of the attributes need
    to be entered).

* Import Configuration File

    XML input adjustment data (*Configuration File*) contains
    information on points, observations and other adjustment parameters,
    for details see GNU gama
    <a href="http://www.gnu.org/software/gama/manual/index.html">documentation</a>.
    After selection the file (with .xml or .gkf extension), the dialog
    displays *existing configuration names* and user can either
    replace selected existing configuration or create a *new
    configuration name*. The configuration name can be arbitrary, but
    *white spaces* are removed by the application.

* Drop Schema Tables, Delete All Data from the Schema, Delete Network Configuration

    are corresponding administrative database operations.

* Import Examples

    Imports a set of example networks distributed with the application to the
    opened database.

* Plugins ...

    if plugins are available, they are listed here.

* Exit

    The program stops when all panels are closed. You can even
    close *Main Control Panel* and have one or more *Network
    Adjustment Panels* open and continue work. In situations like this
    the exit dialog asks if you want to exit just the *Main Control
    Panel* (yes) or all other opened panels as well (yes to all).

### Adjustment menu

* Network Adjustment

    Opens dialog for selecting *network configuration* stored
    in the database. If the configuration is selected, a new *Network
    Adjustment Panel* is created.



### Tools Menu

* Adjustement results language

* Enables to select a language for the adjustment results text.

* Help menu

### Qgama help

* this text.

### About Qgama

* Basic information about Qgama, its version, GNU gama build
  version and the GPL licence.

### About Qt

* Qt version, licencing and basic information on Qt C++ cross-platform.

## Network Adjustment Panel

### File menu

* Save
* Save network data into database.
* Save As ...

    Save copy of network data into database under a new name.

* Export as XML in input file

    Export information from Parameters, Points and Observations
    editors to an XML configuration file (gkf). This file contains all
    information needed for the adjustment and can be used by qgama or
    gama-local.

* Export as XML SQL file

    Similar to the previous function, adjustment information is
    stored in SQL format which can be imported to a database.

* Print

    Print adjustment results.

* Export adjustment results as

    > * XML adjustment results
    > * HTML file
    > * Plaint text file
    > * Octave matrix file

* Save network configuration outline

    > Save configuration sketch in SVG format.

* Close

    > Close current *Network Adjustment Panel* (or all opened panels).

### Adjustment menu

* Run

    > Start adjustment of the network.


### Edit Menu

* Parameters
* Points
* Observations

    > Implicitly editing of network adjustment parameters, points'
    > data and observations are disabled. In the *Edit menu* users can
    > enable/disable one or all three editors.

### Settings

* Outline draw

    > Opens dialog for changing parameters of the network outline draw.

### Help

* Qgama help

    > this text.

## Editors and adjustment results

*Network Adjustment Results* has three editor panels for
adjustment paramater, points and observations and two output panels,
the *outline draw* and the adjustment results text output. These
five panels can be organized as tabbed or docked (as indicated by the
user on opening a new adjustment configuration).

Adjustment parameters editor is strightforward, the meaning of
individual parameters is described in GNU gama
<a href="http://www.gnu.org/software/gama/manual/index.html">documentation</a>.
Points' editor is also simple, attributes *Txx* and *Tz*
define how the role of the point coordinates in the adjustment:

* fixed

    > given coordinates

* free

    > adjusted coordinates (ie. unknown adjustment parameter)

* constrained
    > adjusted coordinates that are subject to a second adjustment
    > constraint (the sum of squares of constrained coordinates is
    > minimal)

All other points/coordinates (not explicitly specified) are unused in the
adjustment.
