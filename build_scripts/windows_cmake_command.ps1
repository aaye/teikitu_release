# PARAMETER LIST FOR SCRIPT
Param(
# --------------------------------------------------------------------------------------------------------------
    [Parameter(Mandatory=$true, HelpMessage = "Select CMAKE Generator")]
    [ValidateSet("MSVC17", "XCODE", "NINJA", "UNIX")]
    [string]$IDE,

    [Parameter(Mandatory=$true, HelpMessage = "Select compiler")]
    [ValidateSet("CLANG", "MSVC")]
    [string]$COMPILER,

# --------------------------------------------------------------------------------------------------------------
    [Parameter(HelpMessage = "Clean directory")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Run cmake with --fresh")]
    [switch]$FRESH,

    [Parameter(HelpMessage = "Build the target")]
    [switch]$BUILD,

    [Parameter(HelpMessage = "Log Output")]
    [switch]$LOG_STATUS,

    [Parameter(HelpMessage = "CICD Builds - Github Workflows or CircleCI")]
    [switch]$CICD_BUILD,

    [Parameter(HelpMessage = "Disable the use of multi-process")]
    [switch]$NO_PROCESS,

# --------------------------------------------------------------------------------------------------------------

    [Parameter(HelpMessage = "Build only those projects required for Teikitu")]
    [switch]$TEIKITU,

# --------------------------------------------------------------------------------------------------------------
    [Parameter(Mandatory=$true, HelpMessage = "Select target cpu: C11_X64, C11_ARM")]
    [ValidateSet("C17_X64", "C17_ARM")]
    [string]$CPU,

    [Parameter(Mandatory=$true, HelpMessage = "Select target threading library: WIN POSIX")]
    [ValidateSet("WINDOWS", "POSIX")]
    [string]$THREAD,

    [Parameter(Mandatory=$true)]
    [ValidateSet("WINDOWS", "POSIX", "ANDROID")]
    [string]$OS,

    [Parameter(Mandatory=$true, HelpMessage = "Select target device: DESKTOP_X86")]
    [ValidateSet("DESKTOP")]
    [string]$DEVICE,

    [Parameter(HelpMessage = "Select target gpu: REF, DX12")]
    [ValidateSet("NONE", "REF", "DX12", "VULKAN", "METAL")]
    [string]$GPU,

    [Parameter(HelpMessage = "Select target gpu: REF, DX12")]
    [ValidateSet("NONE", "REF", "XAUDIO")]
    [string]$AUDIO,

# --------------------------------------------------------------------------------------------------------------
    [Parameter(Mandatory=$true, HelpMessage = "Select a build type: DEBUG, RELEASE, FINAL, TOOL")]
    [ValidateSet("DEBUG", "RELEASE", "FINAL", "TOOLS")]
    [string]$BUILD_TYPE

# --------------------------------------------------------------------------------------------------------------
)



# Validate that we are working in the correct path

if (-not (Test-Path .\powershell_functions.ps1))
{
    Write-Host -ForegroundColor Red "Powershell Functions script not found."
    Return
}
if (-not (Test-Path ..\teikitu.md))
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



# BUILD PATH

if ($IDE -match "MSVC17")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
elseif ($IDE -match "NINJA")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
elseif ($IDE -match "XCODE")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
elseif ($IDE -match "UNIX")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
$CMAKE_BUILD_PATH += "_" + $COMPILER.ToLower()
$CMAKE_BUILD_PATH += "_" + $CPU.ToLower()
$CMAKE_BUILD_PATH += "_" + $THREAD.ToLower()
$CMAKE_BUILD_PATH += "_" + $OS.ToLower()
$CMAKE_BUILD_PATH += "_" + $DEVICE.ToLower()
If ($GPU)
{
    $CMAKE_BUILD_PATH += "_" + $GPU.ToLower()
}
Else
{
    $CMAKE_BUILD_PATH += "_none"
}
If ($AUDIO)
{
    $CMAKE_BUILD_PATH += "_" + $AUDIO.ToLower()
}
Else
{
    $CMAKE_BUILD_PATH += "_none"
}
if ($IDE -match "NINJA" -or $IDE -match "UNIX")
{
    $CMAKE_BUILD_PATH += "_" + $BUILD_TYPE.ToLower()
}

if ($PSBoundParameters.debug -and $PSBoundParameters.verbose) { Write-Host -fore DarkYellow "BUILD PATH: $CMAKE_BUILD_PATH" }




# Build Directory Validations and Teikitu External
If ($CLEAN -and (Test-Path -Path "..\build\$CMAKE_BUILD_PATH"))
{
    try { remove-item "..\build\$CMAKE_BUILD_PATH" -Recurse -Force -ErrorAction Stop } catch { Write-Host -Fore red "FAILED: CLEAN remove directory and files."; Exit 1 }
}




# BUILD COMMON COMMAND LINE
$CMAKE_BUILD_COMMON_CMD=@() # Empty Array

If ($LOG_STATUS)
{
    $CMAKE_BUILD_COMMON_CMD += "--log-level=STATUS"
}
else
{
    $CMAKE_BUILD_COMMON_CMD += "--log-level=WARNING"
}

If ($FRESH)
{
    $CMAKE_BUILD_COMMON_CMD += "--fresh"
}

if ($IDE -match "MSVC17")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Visual Studio 17 2022"'

    If ($CPU -match "C17_X64")
    {
        $CMAKE_BUILD_COMMON_CMD += "-A x64"
    }

    If ($COMPILER -match "CLANG")
    {
        $CMAKE_BUILD_COMMON_CMD += "-T ClangCL"
    }
}
elseif ($IDE -match "NINJA")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Ninja"'

    if ($COMPILER -match "CLANG")
    {
        $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_C_COMPILER:PATH="C:\Program Files\LLVM\bin\clang.exe"'
        $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER:PATH="C:\Program Files\LLVM\bin\clang++.exe"'
    }
}
elseif ($IDE -match "XCODE")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Xcode"'
}
elseif ($IDE -match "UNIX")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Unix Makefiles"'
}

$CMAKE_BUILD_COMMON_CMD += "-DCMAKE_BUILD_TYPE=" + $BUILD_TYPE.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__TARGET_HARDWARE=" + $CPU.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__THREAD=" + $THREAD.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__OS=" + $OS.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__DEVICE=" + $DEVICE.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__OS_TEXT_WIDE=1"

If ($GPU)
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__GRAPHICS=" + $GPU.ToUpper()
}
else
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__GRAPHICS=NONE"
}

If ($AUDIO)
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__AUDIO=" + $AUDIO.ToUpper()
}
else
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__AUDIO=NONE"
}

if ($CICD_BUILD)
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__AUTOMATION=CICD_BUILD"
    $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__LOG_TO_FILE=0"
}
else
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__AUTOMATION=NONE"
    $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__LOG_TO_FILE=1"
}

if ($CICD_BUILD -or $TEIKITU)
{
    $CMAKE_BUILD_COMMON_CMD += '-DMK_BUILD__LIST="TEIKITU"'
}
else
{
    $CMAKE_BUILD_COMMON_CMD += '-DMK_BUILD__LIST="ALL"'
}

if ($PSBoundParameters.debug -and $PSBoundParameters.verbose) { Write-Host -fore DarkYellow "CMAKE COMMON: $CMAKE_BUILD_COMMON_CMD" }




# BANNER -------------------------------------------------------------------------------------------------------
function Write-HostCenter { param($Message) Write-Host ("{0}{1}" -f (' ' * (([Math]::Max(0, $Host.UI.RawUI.BufferSize.Width / 2) - [Math]::Floor($Message.Length / 2)))), $Message) }

Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)
Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)
Write-Host -ForegroundColor DarkCyan  "----  Target Hardware:" $CPU.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----   Thread Support:" $THREAD.ToUpper()
Write-Host -ForegroundColor DarkCyan  "---- Operating System:" $OS.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----    Target Device:" $DEVICE.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----     Graphics API:" $GPU.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----        Audio API:" $AUDIO.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----       Build Type:" $BUILD_TYPE.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----         Compiler:" $COMPILER.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----    Build Manager:" $IDE.ToUpper()
Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)
Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)

# BUILD TEIKITU EXTERNAL COMMAND LINE --------------------------------------------------------------------------

# CMAKE COMMAND LINE
$CMAKE_BUILD_COMMAND_LINE = [string]::Concat(${CMAKE_BUILD_COMMON_CMD}, ' -S .. -B "..\build\', ${CMAKE_BUILD_PATH}, '"')
if ($PSBoundParameters.debug -or $PSBoundParameters.verbose) { Write-Host -fore cyan "CMAKE PROJECT ARGUMENTS: $CMAKE_BUILD_COMMAND_LINE" }
$CMAKE_COMMAND = "cmake.exe " + ${CMAKE_BUILD_COMMAND_LINE}
Invoke-Expression $CMAKE_COMMAND
if ($LASTEXITCODE -ne 0)
{
    Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build.";
    Exit $LASTEXITCODE
}

# BUILD COMMAND
$CMAKE_BUILD_COMMAND_LINE = [string]::Concat('--build "..\build\', ${CMAKE_BUILD_PATH}, '"', ' --config ', $BUILD_TYPE.ToUpper(), ' --')
if ($IDE -match "MSVC17")
{
    $CMAKE_BUILD_COMMAND_LINE += " /nologo"
    $CMAKE_BUILD_COMMAND_LINE += " /detailedSummary:True" # Show detailed information at the end of the build log about the configurations that were built and how they were scheduled to nodes.
    $CMAKE_BUILD_COMMAND_LINE += " /maxCpuCount" # The default value is 1. If you include this switch without specifying a value, MSBuild will use up to the number of processors.

    If ($PSBoundParameters.verbose)
    {
        $CMAKE_BUILD_COMMAND_LINE += " /verbosity:detailed"
    }
    
    If ($PSBoundParameters.debug)
    {
        $CMAKE_BUILD_COMMAND_LINE += " /bl"
    }    
}
if ($PSBoundParameters.debug -or $PSBoundParameters.verbose) { Write-Host -fore cyan "$CMAKE_BUILD_COMMAND_LINE" }
$CMAKE_COMMAND = "cmake.exe " + ${CMAKE_BUILD_COMMAND_LINE}
Invoke-Expression $CMAKE_COMMAND
if ($LASTEXITCODE -ne 0)
{
    Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build.";
    Exit $LASTEXITCODE
}
