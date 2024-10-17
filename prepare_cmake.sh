#! /bin/bash

ScriptPath=$0
Dir=$(cd $(dirname "$ScriptPath"); pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
MakeCmd=${SIS_CMAKE_COMMAND:-make}

CMakeVerboseMakefile=0
Configuration=Release
RunMake=0


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    -v|--cmake-verbose-makefile)

      CMakeVerboseMakefile=1
      ;;
    -d|--debug-configuration)

      Configuration=Debug
      ;;
    -m|--run-make)

      RunMake=1
      ;;
    -s|--stlsoft-root-dir)

      shift
      STLSoftDirGiven=$1
      ;;
    --help)

      cat << EOF
WilliamsCRC is a port/wrapper of Ross Williams CRC library
Copyright (c) 2019-2024, Matthew Wilson and Synesis Information Systems
Copyright (c) 2010-2019, Matthew Wilson and Synesis Software
Copyright (c) 1993, Ross Williams
Creates/reinitialises the CMake build script(s)

$ScriptPath [ ... flags/options ... ]

Flags/options:

    behaviour:

    -v
    --cmake-verbose-makefile
        configures CMake to run verbosely (by setting CMAKE_VERBOSE_MAKEFILE
        to be ON)

    -d
    --debug-configuration
        use Debug configuration (by setting CMAKE_BUILD_TYPE=Debug). Default
        is to use Release

    -m
    --run-make
        executes make after a successful running of CMake

    -s <dir>
    --stlsoft-root-dir <dir>
        specifies the STLSoft root-directory, which will be passed to CMake
        as the variable STLSOFT, and which will override the environment
        variable STLSOFT (if present)

    standard flags:

    --help
        displays this help and terminates

EOF

      exit 0
      ;;
    *)
      >&2 echo "$ScriptPath: unrecognised argument '$1'; use --help for usage"

      exit 1
      ;;
  esac

  shift
done


# ##########################################################
# main()

mkdir -p $CMakeDir || exit 1

cd $CMakeDir

echo "Executing CMake"

if [ $CMakeVerboseMakefile -eq 0 ]; then CMakeVerboseMakefileFlag="OFF" ; else CMakeVerboseMakefileFlag="ON" ; fi

if [ -z $STLSoftDirGiven ]; then CMakeSTLSoftVariable="" ; else CMakeSTLSoftVariable="-DSTLSOFT=$STLSoftDirGiven/" ; fi

cmake \
  $CMakeSTLSoftVariable \
  -DCMAKE_BUILD_TYPE=$Configuration \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=$CMakeVerboseMakefileFlag \
  .. || (cd ->/dev/null ; exit 1)

status=0

if [ $RunMake -ne 0 ]; then

  echo "Executing $MakeCmd"

  $MakeCmd
  status=$?
fi

cd ->/dev/null

if [ $CMakeVerboseMakefile -ne 0 ]; then

  echo -e "contents of $CMakeDir:"
  ls -al $CMakeDir
fi

exit $status


# ############################## end of file ############################# #

