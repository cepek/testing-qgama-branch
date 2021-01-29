# Changelog

All notable changes to gama-q2 project are documented in this file.

## gama-q2-1-04

Build on Ubuntu 20.04.1 LTS (qtcreator and cmake -GNinja)

* removed warnings from Clang-tidy and Clazy static analysis
  Affected files:
  * gama-q2/adjustment.h/cpp
  * gama-q2/dbconnectdialog.h/cpp
  * gama-q2/dbfunctions.cpp
	* gama-q2/drawsettings.cpp
  * gama-q2/importconfiguration.h/cpp


* fixed compile warnings "c++11 range-loop might detach Qt container"
  Affected files:
  * gamaq2controlpanel.cpp

* git checkout  HEAD^ CMakeLists.txt

* fixed compile error: no member named 'SkipEmptyParts' in namespace 'Qt',
  example code: split(QRegExp(";[\\s+"),Qt::SkipEmptyParts);

  Qt::SkipEmptyParts renamed to QString::SkipEmptyParts which fixed
  the problem, but according to the documentation the code was correct.

  Affected files:
  * networkadjustmentpanel.cpp
  * gamaq2controlpanel.cpp

* explicit name for QString::fromUtf8 at networkadjustmentpanel.cpp:717

* fixed warning Don't call QList::operator[]() on temporary
  fileName = fileDialog.selectedFiles()[0];
  fixed several times in networkadjustmentpanel.cpp

* several warnings in networkadjustmmentpane.cpp  class with destructor
  marked 'final' cannot be inherited from observation.h

  fixed in GNU gama file gama/lib/gnu_gama/local/observation.h

* fixed warnings c++11 range-loop might detach Qt container

## gama-q2-1-03

* introduced new version format of git labels, corresponging tar
  name for this version is qt-gama-q2-1-03.tar.gz

## gama-qt-1-02

## gama-qt-1-01

## gama-qt-1-00
