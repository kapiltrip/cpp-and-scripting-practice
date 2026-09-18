param(
    [ValidatePattern('^[a-z][a-z0-9_]*$')]
    [string]$Topic = 'practice',
    [switch]$List
)
$ErrorActionPreference = 'Stop'
$cppRepository = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '../../..')).Path
$cppTopics = @(Get-ChildItem -LiteralPath $PSScriptRoot -Directory |
    Where-Object { Test-Path -LiteralPath (Join-Path $_.FullName 'main.cpp') } |
    Sort-Object Name | Select-Object -ExpandProperty Name)
if ($List) {
    foreach ($cppName in @('practice') + $cppTopics) {
        Write-Output "& ./Projects/CppOOP/code/run.ps1 -Topic $cppName"
    }
    return
}
if ($Topic -eq 'practice') {
    $cppSource = Join-Path $PSScriptRoot '../practice.cpp'
} elseif ($Topic -in $cppTopics) {
    $cppSource = Join-Path $PSScriptRoot "$Topic/main.cpp"
} else {
    throw "Unknown topic '$Topic'. Use -List to see the available commands."
}
$cppBuildFolder = Join-Path $cppRepository "tmp/cpp-topic-builds/$Topic"
New-Item -ItemType Directory -Path $cppBuildFolder -Force | Out-Null
$cppExecutable = Join-Path $cppBuildFolder 'lesson.exe'
$cppObject = Join-Path $cppBuildFolder 'lesson.obj'
$cppVcvars = 'C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat'
if (-not (Test-Path -LiteralPath $cppVcvars)) {
    throw 'The configured Visual Studio 2022 C++ compiler was not found.'
}
# Build one entry point at a time; the installed compiler's stable mode is C++20.
$cppCompile = 'cl /nologo /std:c++20 /EHsc /W4 /WX /permissive- /utf-8 ' +
    '"' + $cppSource + '" /Fe:"' + $cppExecutable + '" /Fo:"' + $cppObject + '"'
& cmd.exe /d /c ('call "' + $cppVcvars + '" >nul && ' + $cppCompile)
if ($LASTEXITCODE -ne 0) { throw "Compilation failed for $Topic." }
& $cppExecutable
if ($LASTEXITCODE -ne 0) { throw "The $Topic example failed." }
