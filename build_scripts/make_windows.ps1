# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "Clean the intermediate and target directories")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Run cmake with --fresh")]
    [switch]$FRESH,

    [Parameter(HelpMessage = "GPU")]
    [string]$GPU,

    [Parameter(HelpMessage = "CICD Builds - Github Workflows or CircleCI")]
    [switch]$CICD_BUILD,

    [Parameter(HelpMessage = "Build only those projects required for Teikitu")]
    [switch]$TEIKITU
)


# Validate that we are working in the correct path

if (-not (Test-Path .\powershell_functions.ps1 -PathType Leaf))
{
    Write-Host -ForegroundColor Red "Powershell Functions script not found."
    Return
}
if (-not (Test-Path .\windows_cmake_command.ps1 -PathType Leaf))
{
    Write-Host -ForegroundColor Red "Windows Terminal build script for cmake not found."
    Return
}
if (-not (Test-Path ..\teikitu.md -PathType Leaf))
{
    Write-Host -ForegroundColor Red "Teikitu Markdown file marking the depot root not found."
    Return
}
$depotHash = Get-FileHash ..\teikitu.md
if ($depotHash.Hash -ne "50963478609E0FF498436B81E4BBF9E7A7DCD5C517A83E49E34FD856E519D8EF")
{
    Write-Host -ForegroundColor Red "Teikitu Markdown file hash not as expected."
    Return
}



. $PSScriptRoot\powershell_functions.ps1



# START PROCESS ARGUMENT PARAMETER

$START_PROCESS_ARGUMENT_COMMON=@("$PSScriptRoot\windows_cmake_command.ps1")

If ($PSBoundParameters.verbose)
{
    $START_PROCESS_ARGUMENT_COMMON += "-VERBOSE"
}

If ($PSBoundParameters.debug)
{
    $START_PROCESS_ARGUMENT_COMMON += "-DEBUG"
    $START_PROCESS_ARGUMENT_COMMON += "-LOG_STATUS"
}

If ($CLEAN -or $FRESH)
{
    $START_PROCESS_ARGUMENT_COMMON += "-FRESH"
}

If ($CLEAN)
{
    $START_PROCESS_ARGUMENT_COMMON += "-CLEAN"
}

If ($GPU)
{
    $START_PROCESS_ARGUMENT_COMMON += "-GPU:$GPU"
}

If ($CICD_BUILD)
{
    $START_PROCESS_ARGUMENT_COMMON += "-CICD_BUILD"
}

If ($TEIKITU)
{
    $START_PROCESS_ARGUMENT_COMMON += "-TEIKITU"
}

$START_PROCESS_ARGUMENT_COMMON += "-THREAD:WINDOWS"
$START_PROCESS_ARGUMENT_COMMON += "-OS:WINDOWS"
$START_PROCESS_ARGUMENT_COMMON += "-DEVICE:DESKTOP"
$START_PROCESS_ARGUMENT_COMMON += "-CPU:C17_X64"



@('DEBUG','RELEASE') | ForEach-Object {
    $BUILD_TYPE = $_

    $SCRIPT_COMMAND_LINE = [string]::Concat($START_PROCESS_ARGUMENT_COMMON, " -IDE:NINJA", " -COMPILER:CLANG", " -BUILD_TYPE:$BUILD_TYPE")
    if ($PSBoundParameters.debug) { Write-Host -fore cyan "SCRIPT ARGUMENTS: $SCRIPT_COMMAND_LINE" }
    Invoke-Expression $SCRIPT_COMMAND_LINE
    if ($LASTEXITCODE -ne 0) { Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build."; Exit $LASTEXITCODE }

    $SCRIPT_COMMAND_LINE = [string]::Concat($START_PROCESS_ARGUMENT_COMMON, " -IDE:MSVC17", " -COMPILER:MSVC", " -BUILD_TYPE:$BUILD_TYPE")
    if ($PSBoundParameters.debug) { Write-Host -fore cyan "SCRIPT ARGUMENTS: $SCRIPT_COMMAND_LINE" }
    Invoke-Expression $SCRIPT_COMMAND_LINE
    if ($LASTEXITCODE -ne 0) { Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build."; Exit $LASTEXITCODE }
}

Exit 0
