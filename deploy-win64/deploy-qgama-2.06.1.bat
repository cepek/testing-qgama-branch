:: 
:: run this file from build directory after
::
:: cmake ..
:: cmake --build . --config Release
::
:: *** update release dir, version and windeployqt.exe path
::
set rel=""
set ver="2.06"

md   qgama-%ver%
md   qgama-%ver%\bin

copy %rel%*.exe qgama-%ver%
copy gama\%rel%*.exe qgama-%ver%\bin

C:\Qt\6.2.2\msvc2019_64\bin\windeployqt.exe qgama-%ver%\qgama.exe
