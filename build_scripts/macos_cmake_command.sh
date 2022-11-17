#!/bin/sh
# Universal bash build script
#  Linux - use directly with bash
#  MacOS - use directly with bash
#  Windows - use with WSL (Linux Subsystem) for the prepartion step, and then use the generated ps1 files for the actual build.


die() {
    printf '%s\n' "$1" >&2
    exit 1
}




# INITIALIZE THE PARAMETERS AND ASSIGN THE DEFAULTS
# - Listed in the same order and default as the windows script

ide=NINJA
compiler=CLANG

clean=0
fresh=0
build=0
log_status=0
os_wide=0
cicd_build=0
no_process=0
parallel=0

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
                ide="$(tr [a-z] [A-Z] <<< "$2")"
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
                compiler="$(tr [a-z] [A-Z] <<< "$2")"
                shift
                case $compiler in
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
        --BUILD)
            build=1
            ;;
        --LOG_STATUS)
            log_status=1
            ;;
        --OS_WIDE)
            os_wide=1
            ;;
        --CICD_BUILD)
            cicd_build=1
            ;;
        --NO_PROCESS)
            no_process=1
            ;;
        --PARALLEL)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                parallel="$(tr [0-9] [0-9] <<< "$2")"
                shift
            else
                die 'ERROR: "--build_type" requires a non-empty option argument.'
            fi
            ;;
        --CPU)       # Takes an option argument; ensure it has been specified.
            if [ "$2" ]; then
                cpu="$(tr [a-z] [A-Z] <<< "$2")"
                shift
                case $cpu in
                    C17_ARM)
                        ;;
                    C17_X64)
                        ;;
                    INTEL_X64)
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
                thread="$(tr [a-z] [A-Z] <<< "$2")"
                shift
                case $thread in
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
                os="$(tr [a-z] [A-Z] <<< "$2")"
                shift
                case $os in
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
                device="$(tr [a-z] [A-Z] <<< "$2")"
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
                gpu="$(tr [a-z] [A-Z] <<< "$2")"
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
                audio="$(tr [a-z] [A-Z] <<< "$2")"
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
                build_type="$(tr [a-z] [A-Z] <<< "$2")"
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
CMAKE_BUILD_PATH="../build/"
echo

CMAKE_BUILD_PATH+="$(tr [A-Z] [a-z] <<< $ide)"
CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $compiler)"
CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $cpu)"
CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $thread)"
CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $os)"
if [ ! $os_wide -eq 0 ]; then
    CMAKE_BUILD_PATH+="_wc"
fi
CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $device)"
if [ ! -z "${gpu}" ]; then
  CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $gpu)"
else
  CMAKE_BUILD_PATH+="_none"
fi
if [ ! -z "${audio}" ]; then
  CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $audio)"
else
  CMAKE_BUILD_PATH+="_none"
fi
if [ ! ${ide} = XCODE ]; then
  CMAKE_BUILD_PATH+="_$(tr [A-Z] [a-z] <<< $build_type)"
fi

if [ ! ${log_status} -eq 0 ]; then
  echo CMAKE BUILD PATH: $CMAKE_BUILD_PATH
fi




# BUILD COMMON COMMAND LINE
CMAKE_BUILD_COMMON_CMD= # Empty Array

if [ ! ${log_status} -eq 0 ]; then
    CMAKE_BUILD_COMMON_CMD+=" --log-level=STATUS"
fi

if [ ! ${fresh} -eq 0 ]; then
    CMAKE_BUILD_COMMON_CMD+=" --fresh"
fi

case $ide in
  UNIX)
    CMAKE_BUILD_COMMON_CMD+=' -G "Unix Makefiles"'
    ;;
  NINJA)
    CMAKE_BUILD_COMMON_CMD+=' -G Ninja'
    if [ ${compiler} = CLANG ]; then
      CMAKE_BUILD_COMMON_CMD+=' -DCMAKE_C_COMPILER=/usr/bin/clang'
      CMAKE_BUILD_COMMON_CMD+=' -DCMAKE_CXX_COMPILER=/usr/bin/clang++'
    fi
    ;;
  XCODE)
    CMAKE_BUILD_COMMON_CMD+=' -G Xcode'
    CMAKE_BUILD_COMMON_CMD+=' -DCMAKE_C_COMPILER=/usr/bin/clang'
    CMAKE_BUILD_COMMON_CMD+=' -DCMAKE_CXX_COMPILER=/usr/bin/clang++'
    ;;
  *)
    die 'Script logic failure'
    ;;
esac
CMAKE_BUILD_COMMON_CMD+=" -DCMAKE_BUILD_TYPE=${build_type}"
CMAKE_BUILD_COMMON_CMD+=" -DMK_BUILD__TARGET_HARDWARE=${cpu}"
CMAKE_BUILD_COMMON_CMD+=" -DMK_BUILD__THREAD=${thread}"
CMAKE_BUILD_COMMON_CMD+=" -DMK_BUILD__OS=${os}"
CMAKE_BUILD_COMMON_CMD+=" -DMK_BUILD__DEVICE=${device}"
if [ ! ${os_wide} -eq 0 ]; then
    CMAKE_BUILD_COMMON_CMD+=" -DMK_COMPILE_PLATFORM_TEXT__WIDE=1"
fi
CMAKE_BUILD_COMMON_CMD+=" -DMK_FEATURE__GRAPHICS=${gpu}"
CMAKE_BUILD_COMMON_CMD+=" -DMK_FEATURE__AUDIO=${audio}"

if [ ! ${log_status} -eq 0 ]; then
  echo CMAKE COMMAND LINE OPTIONS: $CMAKE_BUILD_COMMON_CMD
fi

if [ ${cicd_build} -eq 0 ]; then
    CMAKE_BUILD_COMMON_CMD+=" -DMK_BUILD__LIST=\"ALL\""
else
    CMAKE_BUILD_COMMON_CMD+=" -DMK_BUILD__LIST=\"TEIKITU\""
fi



# CLEAN OPTION

if [ ${clean} -ne 0 ]; then
  if [ ! ${verbose} -eq 0 ]; then
    echo CLEANING BUILD DIRECTORY: ${CMAKE_BUILD_PATH}
  fi
  rm -rfd ${CMAKE_BUILD_PATH}
fi




# BANNER -------------------------------------------------------------------------------------------------------

if [ ! ${log_status} -eq 0 ]; then
  printf "SCRIPT COMMAND LINE CONFIGURATION\n"
  printf "CPU: ${cpu}\n"
  printf "THREAD: ${thread}\n"
  printf "OS: ${os}\n"
  printf "DEVICE: ${device}\n"
  printf "GPU: ${gpu}\n"
  printf "AUDIO: ${audio}\n"
  printf "BUILD_TYPE: ${build_type}\n"
  printf "IDE: ${ide}\n"
  printf "COMPILER: ${compiler}\n\n"
fi

# BUILD TEIKITU EXTERNAL COMMAND LINE --------------------------------------------------------------------------

# CMAKE COMMAND LINE
if [ ! ${log_status} -eq 0 ]; then
  echo CMAKE COMMAND: cmake ${CMAKE_BUILD_COMMON_CMD} -S .. -B ./${CMAKE_BUILD_PATH}
  cmake ${CMAKE_BUILD_COMMON_CMD} -S .. -B "./${CMAKE_BUILD_PATH}"
else
  cmake ${CMAKE_BUILD_COMMON_CMD} -S .. -B "./${CMAKE_BUILD_PATH}" 1> /dev/null
fi

# BUILD COMMAND
if [ ${build} -ne 0 ]; then
  if [ ${log_status} -ne 0 ]; then
    echo CMAKE BUILD COMMAND: cmake --build ./${CMAKE_BUILD_PATH}/
    cmake --build "./${CMAKE_BUILD_PATH}" --config ${build_type}
  else
    cmake --build "./${CMAKE_BUILD_PATH}" --config ${build_type}  1> /dev/null
  fi
fi
