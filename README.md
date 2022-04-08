# QGama

```GNU Gama``` is a project dedicated to adjustment of geodetic networks.
It is intended for use with traditional geodetic surveying which are
still used and needed in special measurements (e.g., underground
or high precision engineering measurements). ```QGama``` is a Qt based user
interface for GNU Gama adjustment of geodetic networks in which XML
input is complemented with a database. The most simple case is Sqlite3
file database, which does not need any special knowledge from the user.

http://www.gnu.org/software/gama/qgama

The distribution package QGama comes also with several command line programs
stored in the subdirectory ```bin```. QGama is not dependent on these programs,
which on the other hand must be run from a terminal (for example Gnome terminal
in GNU/Linux or PowerShell in Windows).

## GNU Gama command line programs

### gama-local

The main program of the GNU Gama project, solves adjustment of
local geodetic network with input in XML. Run ```gama-local --help``` 
to see description of its options.

    Adjustment of local geodetic network        version: 2.17.2 / GNU C/C++ 11.2
    ************************************
    https://www.gnu.org/software/gama/

    Usage: gama-local  [--input-xml] input.xml  [options]

    Options:

    --algorithm  gso | svd | cholesky | envelope
    --language   en | ca | cz | du | es | fi | fr | hu | ru | ua | zh
    --encoding   utf-8 | iso-8859-2 | iso-8859-2-flat | cp-1250 | cp-1251
    --angular    400 | 360
    --latitude   <latitude>
    --ellipsoid  <ellipsoid name>
    --text       adjustment_results.txt
    --html       adjustment_results.html
    --xml        adjustment_results.xml
    --octave     adjustment_results.m
    --svg        network_configuration.svg
    --cov-band   covariance matrix of adjusted parameters in XML output
                 n  = -1  for full covariance matrix (implicit value)
                 n >=  0  covariances are computed only for bandwidth n
    --iterations maximum number of iterations allowed in the linearized
                 least squares algorithm (implicit value is 5)
    --export     updated input data based on adjustment results
    --verbose    [yes | no]
    --version
    --help

    Report bugs to: <bug-gama@gnu.org>
    GNU gama home page: <https://www.gnu.org/software/gama/>
    General help using GNU software: <https://www.gnu.org/gethelp/>

### gama-g3

Gama-g3 is a program for adjustment of 3D networks on ellipsoid, currently is
limited to adjuste coordinates, vector and spatial distances.

    Usage:  gama-g3  [ options ] input  [ output ]

     input      xml data file name
     output     optional output data file name

     --algorithm  envelope | gso | svd | cholesky
     --project-equations file     optional output of project equations in XML

     -h         help (this text)

### gama-local-gkf2yaml, gama-local-yaml2gkf

Conversion program between gama-local XML input and yaml language.

    gama-local-gkf2yaml input.gkf  [output.yaml]
    gama-local-yaml2gkf input.yaml [output.gkf]

### krumm2gkf

Conversion from data format used in Geodetic Network Adjustment Examples
by Friedhelm Krumm to XML input format of gama-local (GNU Gama)

https://www.gis.uni-stuttgart.de/lehre/campus-docs/adjustment_examples.pdf

    krumm2gkf  input_file  [ output_file  ]
    krumm2gkf < std_input  [ > std_output ]

    Options:
    -h, --help      this text
    -v, --version   print program version
    -e, --examples  add the following comment to the generated XML file

         This example is based on published material Geodetic Network Adjustment
         Examples by Friedhelm Krumm, Geodätisches Institut Universität Stuttgart,
         Rev. 3.5, January 20, 2020
