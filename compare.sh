#!/usr/bin/env bash

cat $1 | grep $2 | sed "s/.*://" | sed "s/[(),]//g" > logClean
cmake-build-debug/p10 | grep $2 | sed "s/.*://" | sed "s/[(),]//g" > mylogClean