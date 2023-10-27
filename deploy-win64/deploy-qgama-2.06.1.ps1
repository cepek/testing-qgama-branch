#
# run this file from the qgama build directory
#

if ($args.Count -ne 0)
{
    Write-Host "`nUsage:" $MyInvocation.InvocationName "`n"
    Write-Host "   edit version, optional release directory, windeployqt path"
    Write-Host "   and run from the release directory`n"
    exit
}

$ver="2.06.X"     # release version
#$rel=""          # optional release directory
$windeployqt="C:\Qt\6.2.2\msvc2019_64\bin\windeployqt.exe"

Write-Host

$errs=0
if (-Not (Test-Path -Path $windeployqt)) {
    Write-Host "Program " $windeployqt.ToString() " not found"
    $errs+=1
}

if (Test-Path -Path qgama-$ver) {
    Write-Host "Directory qgama-$ver already exists"
    $errs+=1
}

if (Test-Path -Path qgama-$ver.zip) {
    Write-Host "File qgama-$ver.zip already exists"
    $errs+=1
}

if ($errs) {
    Write-Host "`nNothing was done`n"
    exit
}

New-Item -ItemType Directory -Path qgama-$ver      | Out-Null
New-Item -ItemType Directory -Path qgama-$ver/bin  | Out-Null

Copy-Item qgama.exe      -Destination  qgama-$ver
Copy-Item gama$rel\*.exe -Destination  qgama-$ver/bin

Invoke-Expression "$windeployqt qgama-$ver\qgama.exe"
Compress-Archive  -Path qgama-$ver qgama-$ver.zip

# pick your choice
Get-FileHash -Algorithm sha256 qgama-$ver.zip | Out-File .\qgama-$ver.sha256
Get-FileHash -Algorithm md5    qgama-$ver.zip | Out-File .\qgama-$ver.md5
