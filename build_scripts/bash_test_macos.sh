#!/bin/sh
# POSIX

die() {
    printf '%s\n' "$1" >&2
    exit 1
}




# INITIALIZE THE PARAMETERS AND ASSIGN THE DEFAULTS

clean=0
fresh=0
build=0
verbose=0
github=0
dev=0
single=0
windows=0
matrix_configuration=




# PARSE PARAMETERS
while :; do
    case $1 in
        --CLEAN)
            clean=1
            ;;
        --FRESH)
            fresh=1
            ;;
        --BUILD)
            build=1
            ;;
        --VERBOSE)
            verbose=1
            ;;
        --GITHUB)
            github=1
            ;;
        --DEV_WORKSPACE)
            dev=1
            ;;
        --SINGLE)
            single=1
            ;;
        --WINDOWS)
            windows=1
            ;;
        --CONFIG)
            if [ "$2" ]; then
                matrix_configuration="$(tr [a-z] [A-Z] <<< "$2")"
                shift
                case $matrix_configuration in
                    APPLE)
                        ;;
                    POSIX)
                        ;;
                    WIN)
                        ;;
                    *)
                        die 'ERROR: Unknown configuration.'
                        ;;
                esac
            else
                die 'ERROR: "--config" requires a non-empty option argument.'
            fi
            ;;
        --) # End of all options.
            shift
            break
            ;;
        -?*)
            printf 'WARN: Unknown option (ignored): %s\n' "$1" >&2
            ;;
        *) # Default case: No more options, so break out of the loop.
            break
    esac

    shift
done

if [ -z "${matrix_configuration}" ]; then
  die 'ERROR: Missing configuration.'
fi




# BUILD COMMON COMMAND LINE
SCRIPT_COMMON_CMD=./bash_cmake_build.sh

if [ ! ${clean} -eq 0 ]; then
    SCRIPT_COMMON_CMD+=" --CLEAN"
fi

if [ ! ${fresh} -eq 0 ]; then
    SCRIPT_COMMON_CMD+=" --FRESH"
fi

if [ ! ${build} -eq 0 ]; then
    SCRIPT_COMMON_CMD+=" --BUILD"
fi

if [ ! ${verbose} -eq 0 ]; then
    SCRIPT_COMMON_CMD+=" --VERBOSE"
fi

if [ ! ${github} -eq 0 ]; then
    SCRIPT_COMMON_CMD+=" --GITHUB"
fi

if [ ! ${windows} -eq 0 ]; then
    SCRIPT_COMMON_CMD+=" --WINDOWS"
fi

if [ ! ${dev} -eq 0 ]; then
  case $matrix_configuration in
    WIN)
      bash ${SCRIPT_COMMON_CMD} --COMPILER MSVC --THREAD WIN --OS WIN --DEVICE DESKTOP --GPU DX12 --AUDIO NONE --CPU C17_X64 --IDE MSVC17 --BUILD_TYPE DEBUG
      ;;
    POSIX)
      ;;
    APPLE)
      bash ${SCRIPT_COMMON_CMD} --COMPILER CLANG --THREAD POSIX --OS POSIX --DEVICE APPLE_MAC --GPU REF --AUDIO NONE --CPU C17_ARM --IDE XCODE --BUILD_TYPE DEBUG
      ;;
    *) # Default case: No more options, so break out of the loop.
      die 'ERROR: configuration script logic error.'
      ;;
  esac
fi




list__compiler=("clang")
case $matrix_configuration in
  WIN)
    list__thread=("win")
    list__os=("win")
    list__device=("desktop")
    list__gpu=("none" "ref" "dx12")
    list__audio=("none")
    list__hardware=("C17_X64")
    ;;
  POSIX)
    list__thread=("posix")
    list__os=("posix")
    list__device=("desktop")
    list__gpu=("none" "ref")
    list__audio=("none")
    list__hardware=("C17_X64")
    ;;
  APPLE)
    list__thread=("posix" "dispatch")
    list__os=("posix")
    list__device=("apple_mac") #("apple_mac" "apple_iphone" "apple_ipad" "apple_tv" "apple_watch")
    list__gpu=("none" "ref")
    list__audio=("none")
    list__hardware=("C17_ARM")
    ;;
  *) # Default case: No more options, so break out of the loop.
    die 'ERROR: configuration script logic error.'
    ;;
esac
list__ide=("ninja")
list__build_type=("debug" "release" "final" "tools")

for build_compiler in "${list__compiler[@]}"
do
  for build_thread in "${list__thread[@]}"
  do
    for build_os in "${list__os[@]}"
    do
      for build_device in "${list__device[@]}"
      do
        for build_gpu in "${list__gpu[@]}"
        do
          for build_audio in "${list__audio[@]}"
          do
            for build_hardware in "${list__hardware[@]}"
            do
              for build_ide in "${list__ide[@]}"
              do
                for build_build_type in "${list__build_type[@]}"
                do
                    if [ ! ${verbose} -eq 0 ]; then
                        echo bash ${SCRIPT_COMMON_CMD} --COMPILER $build_compiler --THREAD $build_thread --OS $build_os --DEVICE $build_device --GPU $build_gpu --AUDIO $build_audio --CPU $build_hardware --IDE $build_ide --BUILD_TYPE $build_build_type
                    fi
                    bash ${SCRIPT_COMMON_CMD} --COMPILER $build_compiler --THREAD $build_thread --OS $build_os --DEVICE $build_device --GPU $build_gpu --AUDIO $build_audio --CPU $build_hardware --IDE $build_ide --BUILD_TYPE $build_build_type
                    if [ ! ${single} -eq 0 ]; then
                        exit 1
                    fi
                done
              done
            done
          done
        done
      done
    done
  done
done
