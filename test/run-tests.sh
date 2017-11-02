#!/bin/bash

EXEC_PATH=$(which ${1})

echo "Running system tests:"
cd system-tests
./run-system-tests.sh $EXEC_PATH
cd ..
