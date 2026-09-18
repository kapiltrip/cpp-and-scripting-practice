$ErrorActionPreference = 'Stop'
$cppTopics = @(Get-ChildItem -LiteralPath $PSScriptRoot -Directory |
    Where-Object { Test-Path -LiteralPath (Join-Path $_.FullName 'main.cpp') } |
    Sort-Object Name | Select-Object -ExpandProperty Name)
$cppRepository = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '../../..')).Path
$cppResults = [ordered]@{}
$cppHashes = [ordered]@{}
foreach ($cppTopic in $cppTopics) {
    $cppLines = & (Join-Path $PSScriptRoot 'run.ps1') -Topic $cppTopic
    $cppResults[$cppTopic] = $cppLines -join "`n"
    $cppRelativeSource = "$cppTopic/main.cpp"
    $cppHashPath = Join-Path $PSScriptRoot $cppRelativeSource
    $cppHash = Get-FileHash -LiteralPath $cppHashPath -Algorithm SHA256
    $cppHashes[$cppRelativeSource] = $cppHash.Hash.ToLower()
    Write-Output "${cppTopic}: compiled and ran"
}
$cppHeaderPath = Join-Path $PSScriptRoot 'deep_copy/student.hpp'
$cppHeaderHash = Get-FileHash -LiteralPath $cppHeaderPath -Algorithm SHA256
$cppHashes['deep_copy/student.hpp'] = $cppHeaderHash.Hash.ToLower()
$cppResults['_source_hashes'] = $cppHashes
$cppResultFile = Join-Path $cppRepository 'tmp/cpp-topic-builds/verification.json'
$cppResults | ConvertTo-Json -Depth 5 |
    Set-Content -LiteralPath $cppResultFile -Encoding utf8
Write-Output "Saved verified outputs: $cppResultFile"
Write-Output "Verified $($cppTopics.Count) separate topic programs."
