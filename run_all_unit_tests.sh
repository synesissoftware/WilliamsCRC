#! /bin/bash

ScriptPath=$0
Dir=$(cd $(dirname "$ScriptPath"); pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=$Dir/_build


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --help)

      cat << EOF
WilliamsCRC is a port/wrapper of Ross Williams' CRC library
Copyright (c) 2019-2024, Matthew Wilson and Synesis Information Systems
Copyright (c) 2010-2019, Matthew Wilson and Synesis Software
Copyright (c) 1993, Ross Williams
Runs all (matching) component-test and unit-test programs

$ScriptPath [ ... flags/options ... ]

Flags/options:

    behaviour:


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

echo "Executing make and then running all test programs"

status=0

if make; then

  for f in $(find $Dir -type f -perm +111 '(' -name 'test_unit*' -o -name 'test.unit.*' ')') $(find $Dir -type f -perm +111 '(' -name 'test_component*' -o -name 'test.component.*' ')')
  do

    echo
    echo "executing $f:"

    if ! $f; then

      status=$?

      break 1
    fi
  done
else

  status=$?
fi

cd ->/dev/null

exit $status


# ############################## end of file ############################# #

