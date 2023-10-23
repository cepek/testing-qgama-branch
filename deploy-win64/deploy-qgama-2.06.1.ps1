#  
# run this file from the build directory
#
# cmake ..
# cmake --build . --config Release
#

if ($args.Count -ne 0)
{
    Write-Host "`nUsage:" $MyInvocation.InvocationName "`n"
    Write-Host "   edit version, optional release directory, windeployqt path"
    Write-Host "   and run from the release directory`n"
    exit
}

$ver="2.06.1"     # release version
$rel=""           # optional release directory  
$windeployqt="C:\Qt\6.2.2\msvc2019_64\bin\windeployqt.exe"

$errs=0
if (-Not (Test-Path -Path $windeployqt)) {
    Write-Host "`nProgram " $windeployqt.ToString() " not found" 
    $errs+=1
}

if (Test-Path -Path qgama-$ver) {
    Write-Host "`nDirectory qgama-$ver already exists"
    $errs+=1
}

if (Test-Path -Path qgama-$ver.zip) {
    Write-Host "`nFile qgama-$ver.zip already exists"
    $errs+=1
}

if ($errs) {
    Write-Host "`n"
    exit
}

New-Item -ItemType Directory -Path qgama-$ver
New-Item -ItemType Directory -Path qgama-$ver/bin

Copy-Item qgama.exe      -Destination  qgama-$ver
Copy-Item gama$rel\*.exe -Destination  qgama-$ver/bin

Invoke-Expression "$windeployqt qgama-$ver\qgama.exe"
Compress-Archive  -Path qgama-$ver qgama-$ver.zip
