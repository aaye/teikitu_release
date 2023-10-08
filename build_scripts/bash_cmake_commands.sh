#!/bin/sh
# Universal bash build script
#  Linux - use directly with bash
#  MacOS - use directly with bash
#  Windows - use with WSL (Linux Subsystem) for the prepartion step, and then use the generated ps1 files for the actual build.


die() {
    printf '%s\n' "$1" >&2
    exit 1
}

# General Formatting
#define GEN_FORMAT_RESET                "0"
#define GEN_FORMAT_BRIGHT               "1"
#define GEN_FORMAT_DIM                  "2"
#define GEN_FORMAT_UNDERSCORE           "3"
#define GEN_FORMAT_BLINK                "4"
#define GEN_FORMAT_REVERSE              "5"
#define GEN_FORMAT_HIDDEN               "6"

# Foreground Colors
#define FOREGROUND_COL_BLACK            "30"
#define FOREGROUND_COL_RED              "31"
#define FOREGROUND_COL_GREEN            "32"
#define FOREGROUND_COL_YELLOW           "33"
#define FOREGROUND_COL_BLUE             "34"
#define FOREGROUND_COL_MAGENTA          "35"
#define FOREGROUND_COL_CYAN             "36"
#define FOREGROUND_COL_WHITE            "37"

# Background Colors
#define BACKGROUND_COL_BLACK            "40"
#define BACKGROUND_COL_RED              "41"
#define BACKGROUND_COL_GREEN            "42"
#define BACKGROUND_COL_YELLOW           "43"
#define BACKGROUND_COL_BLUE             "44"
#define BACKGROUND_COL_MAGENTA          "45"
#define BACKGROUND_COL_CYAN             "46"
#define BACKGROUND_COL_WHITE            "47"

#define SHELL_COLOR_ESCAPE_SEQ(X) "\x1b["X"m"
#define SHELL_FORMAT_RESET  ANSI_COLOR_ESCAPE_SEQ(GEN_FORMAT_RESET)


# INITIALIZE THE PARAMETERS AND ASSIGN THE DEFAULTS
# - Listed in the same order and default as the windows script

ide=NINJA
compiler=CLANG

clean=0
fresh=0
build=0
log_status=0
verbose=0
cicd_build=0
teikitu=0

cpu=
thread=
os=
device=
gpu=NONE
audio=NONE

build_type=




# SHOULD VALIDATE HASH AND PATH




# PARSE PARAMETERS
# - This is done automatically by powershell

while :; do
    case $1 in
        -h|-\?|--help)
            show_help    # Display a usage synopsis.
            exit
            ;;
        --IDE)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                ide="$2"
                shift
                case $ide in
                    UNIX)
                        ;;
                    NINJA)
                        ;;
                    XCODE)
                        ;;
                    *)
                        die 'ERROR: Unknown IDE parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--ide" requires a non-empty option argument.'
            fi
            ;;
        --COMPILER)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                compiler="$2"
                shift
                case $compiler in
                    CLANG)
                        ;;
                    XCODE)
                        ;;
                    *)
                        die 'ERROR: Unknown COMPILER parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--compiler" requires a non-empty option argument.'
            fi
            ;;
        --CLEAN)
            clean=1
            ;;
        --FRESH)
            fresh=1
            ;;
        --LOG_STATUS)
            log_status=1
            ;;
        --VERBOSE)
            verbose=1
            ;;
        --CICD_BUILD)
            cicd_build=1
            ;;
        --TEIKITU)
            teikitu=1
            ;;
        --PARALLEL)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                parallel="$2"
                shift
            else
                die 'ERROR: "--build_type" requires a non-empty option argument.'
            fi
            ;;
        --CPU)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                cpu="$2"
                shift
                case $cpu in
                    C17_ARM)
                        ;;
                    C17_X64)
                        ;;
                    *)
                        die 'ERROR: Unknown CPU parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--cpu" requires a non-empty option argument.'
            fi
            ;;
        --THREAD)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                thread="$2"
                shift
                case $thread in
                    AND)
                        ;;
                    POSIX)
                        ;;
                    WIN)
                        ;;
                    *)
                        die 'ERROR: Unknown THREAD parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--thread" requires a non-empty option argument.'
            fi
            ;;
        --OS)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                os="$2"
                shift
                case $os in
                    AND)
                        ;;
                    POSIX)
                        ;;
                    WIN)
                        ;;
                    *)
                        die 'ERROR: Unknown OS parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--os" requires a non-empty option argument.'
            fi
            ;;
        --DEVICE)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                device="$2"
                shift
                case $device in
                    DESKTOP)
                        ;;
                    APPLE_MAC)
                        ;;
                    APPLE_IPHONE)
                        ;;
                    APPLE_IPAD)
                        ;;
                    APPLE_TV)
                        ;;
                    APPLE_WATCH)
                        ;;
                    *)
                        die 'ERROR: Unknown DEVICE parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--device" requires a non-empty option argument.'
            fi
            ;;
        --GPU)
            if [ "$2" ]; then
                gpu="$2"
                shift
                case $gpu in
                    NONE)
                        ;;
                    REF)
                        ;;
                    DX12)
                        ;;
                    *)
                        die 'ERROR: Unknown GPU parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--gpu" requires a non-empty option argument.'
            fi
            ;;
        --AUDIO)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                audio="$2"
                shift
                case $audio in
                    NONE)
                        ;;
                    REF)
                        ;;
                    XAUDIO)
                        ;;
                    *)
                        die 'ERROR: Unknown AUDIO parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--audio" requires a non-empty option argument.'
            fi
            ;;
        --BUILD_TYPE)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                build_type="$2"
                shift
                case $build_type in
                    DEBUG)
                        ;;
                    RELEASE)
                        ;;
                    FINAL)
                        ;;
                    TOOLS)
                        ;;
                    *)
                        die 'ERROR: Unknown BUILD_TYPE parameter.'
                        ;;
                esac
            else
                die 'ERROR: "--build_type" requires a non-empty option argument.'
            fi
            ;;
        --)
            shift
            break
            ;;
        -?*)
            printf 'WARN: Unknown option (ignored): %s\n' "$1" >&2
            ;;
        *)
            break
    esac

    shift
done

# VALIDATION - ENFORCE PARAMETER REQUIREMENT
if [ ! -z "${cpu}" -a ! -z "${thread}" -a ! -z "${os}" -a ! -z "${device}" -a ! -z "${gpu}" -a ! -z "${audio}" -a ! -z "${build_type}" -a ! -z "${ide}" -a ! -z "${compiler}" ]; then
  :
else
  die 'Incomplete Command Line'
fi




# BUILD PATH
CMAKE_BUILD_PATH="${ide,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${compiler,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${cpu,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${thread,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${os,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${device,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${gpu,,}"
CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${audio,,}"
if [ ${ide^^} != XCODE ]; then
  CMAKE_BUILD_PATH="${CMAKE_BUILD_PATH}_${build_type,,}"
fi

if [ ! ${verbose} -eq 0 ]; then
  printf '\033[33;1m'
  printf "CMAKE BUILD PATH: %s\n" ${CMAKE_BUILD_PATH}
  printf '\033[0m'
fi




# BUILD COMMON COMMAND LINE
declare -a CMAKE_BUILD_COMMON_CMD # Empty Array

if [ ! ${log_status} -eq 0 ]; then
    CMAKE_BUILD_COMMON_CMD+=(--log-level=STATUS)
fi

if [ ! ${fresh} -eq 0 ]; then
    CMAKE_BUILD_COMMON_CMD+=(--fresh)
fi

case $ide in
  UNIX)
    CMAKE_BUILD_IDE="Unix Makefiles"
    CMAKE_BUILD_COMMON_CMD+=(${CMAKE_BUILD_IDE:+-G "$CMAKE_BUILD_IDE"})
    CMAKE_BUILD_POST_CMD=(-k -j)
    ;;
  NINJA)
    CMAKE_BUILD_COMMON_CMD+=(-G Ninja)
    CMAKE_BUILD_POST_CMD=
    ;;
  XCODE)
    CMAKE_BUILD_COMMON_CMD+=(-G Xcode)
    CMAKE_BUILD_POST_CMD=
    ;;
  *)
    die "Script logic failure"
    ;;
esac
if [ ${compiler^^} = CLANG ]; then
  CMAKE_BUILD_COMMON_CMD+=(-DCMAKE_C_COMPILER=/usr/bin/clang-16)
  CMAKE_BUILD_COMMON_CMD+=(-DCMAKE_CXX_COMPILER=/usr/bin/clang++-16)
fi
CMAKE_BUILD_COMMON_CMD+=(-DCMAKE_BUILD_TYPE=${build_type^^})
CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__TARGET_HARDWARE=${cpu^^})
CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__THREAD=${thread^^})
CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__OS=${os^^})
CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__DEVICE=${device^^})
CMAKE_BUILD_COMMON_CMD+=(-DMK_FEATURE__GRAPHICS=${gpu^^})
CMAKE_BUILD_COMMON_CMD+=(-DMK_FEATURE__AUDIO=${audio^^})

if [ ! ${cicd_build} -eq 0 ]; then
{
    CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__AUTOMATION=CICD_BUILD)
    CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__LOG_TO_FILE=0)
}
else
{
    CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__AUTOMATION=NONE)
    CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__LOG_TO_FILE=1)
}
fi

if [ ! ${cicd_build} -eq 0 ] || [ ! ${teikitu} -eq 0 ]; then
{
    CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__LIST="TEIKITU")
}
else
{
    CMAKE_BUILD_COMMON_CMD+=(-DMK_BUILD__LIST="ALL")
}
fi
CMAKE_BUILD_COMMON_CMD+=(-S ..)
CMAKE_BUILD_COMMON_CMD+=(${CMAKE_BUILD_PATH:+-B "../build/${CMAKE_BUILD_PATH,,}"})

if [ ! ${verbose} -eq 0 ]; then
  printf '\033[33;1m'
  printf "CMAKE COMMON: ${CMAKE_BUILD_COMMON_CMD[@]}\n"
  printf '\033[0m'
fi




# CLEAN OPTION

if [ ${clean} -ne 0 ]; then
  if [ ! ${verbose} -eq 0 ]; then
    echo CLEANING BUILD DIRECTORY: ${CMAKE_BUILD_PATH,,}
  fi
  rm -rfd ${CMAKE_BUILD_PATH}
fi




# BANNER -------------------------------------------------------------------------------------------------------

printf '\033[36;1m'
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
printf '%s\n' "----  Target Hardware: ${cpu^^}"
printf '%s\n' "----   Thread Support: ${thread^^}"
printf '%s\n' "---- Operating System: ${os^^}"
printf '%s\n' "----    Target Device: ${device^^}"
printf '%s\n' "----     Graphics API: ${gpu^^}"
printf '%s\n' "----        Audio API: ${audio^^}"
printf '%s\n' "----       Build Type: ${build_type^^}"
printf '%s\n' "----         Compiler: ${compiler^^}"
printf '%s\n' "----    Build Manager: ${ide^^}"
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
printf '\033[0m'




# BUILD TEIKITU EXTERNAL COMMAND LINE --------------------------------------------------------------------------

# trap 'printf %s\\n "$BASH_COMMAND" >&2' DEBUG

# CMAKE COMMAND LINE
if [ ! ${verbose} -eq 0 ]; then
  printf '\033[36;1m%s\033[0m\n' "CMAKE COMMAND: cmake ${CMAKE_BUILD_COMMON_CMD[@]}"
  echo cmake "${CMAKE_BUILD_COMMON_CMD[@]}"
  cmake "${CMAKE_BUILD_COMMON_CMD[@]}"
else
  cmake "${CMAKE_BUILD_COMMON_CMD[@]}" 1> /dev/null
fi

# BUILD COMMAND
CMAKE_BUILD_COMMON_CMD=(${CMAKE_BUILD_PATH:+--build "../build/${CMAKE_BUILD_PATH,,}"})
CMAKE_BUILD_COMMON_CMD+=(--config ${build_type^^})
CMAKE_BUILD_COMMON_CMD+=(-- ${CMAKE_BUILD_POST_CMD[@]})
if [ ! ${verbose} -eq 0 ]; then
  printf '\033[36;1m%s\033[0m\n' "CMAKE COMMAND: cmake  ${CMAKE_BUILD_COMMON_CMD[@]}"
  echo cmake "${CMAKE_BUILD_COMMON_CMD[@]}"
  cmake "${CMAKE_BUILD_COMMON_CMD[@]}"
else
  cmake "${CMAKE_BUILD_COMMON_CMD[@]}" 1> /dev/null
fi

# BUILD TAG
if [ ! ${cicd_build} -eq 0 ]; then
  git tag -d build__hlnx_${CMAKE_BUILD_PATH,,}
  git tag build__hlnx_${CMAKE_BUILD_PATH,,} -m "Success" --no-edit -s
fi

