#!/bin/sh
# POSIX

die() {
    printf '%s\n' "$1" >&2
    exit 1
}




# INITIALIZE THE PARAMETERS AND ASSIGN THE DEFAULTS

verbose=0
fresh=0
clean=0
cicd_build=0
teikitu=0




# PARSE PARAMETERS
while :; do
    case $1 in
        --VERBOSE)
            verbose=1
            ;;
        --FRESH)
            fresh=1
            ;;
        --CLEAN)
            clean=1
            ;;
        --CICD_BUILD)
            cicd_build=1
            ;;
        --TEIKITU)
            teikitu=1
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




# BUILD COMMON COMMAND LINE
SCRIPT_COMMON_CMD="./bash_cmake_commands.sh"

if [ ! ${verbose} -eq 0 ]; then
    SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --VERBOSE"
fi

if [ ! ${fresh} -eq 0 ]; then
    SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --FRESH"
fi

if [ ! ${clean} -eq 0 ]; then
    SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --CLEAN"
fi

if [ ! ${cicd_build} -eq 0 ]; then
    SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --CICD_BUILD"
fi

if [ ! ${teikitu} -eq 0 ]; then
    SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --TEIKITU"
fi

SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --IDE XCODE"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --COMPILER XCODE"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --THREAD POSIX"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --OS POSIX"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --DEVICE DESKTOP"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --CPU C17_ARM"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --GPU NONE"
SCRIPT_COMMON_CMD="${SCRIPT_COMMON_CMD} --AUDIO NONE"

list__build_type=("debug" "release" "final" "tools")

for build_build_type in "${list__build_type[@]}"
do
    if [ ! ${verbose} -eq 0 ]; then
        echo bash ${SCRIPT_COMMON_CMD} --BUILD_TYPE ${build_build_type^^}
    fi
    bash ${SCRIPT_COMMON_CMD} --BUILD_TYPE ${build_build_type^^}
done
