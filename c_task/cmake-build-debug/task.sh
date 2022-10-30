#!/bin/sh
EXEC=./c_task

taskset -c 1 $EXEC > optput
