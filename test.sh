#!/bin/bash
make
export LD_LIBRARY_PATH=$(pwd)/release/dev/lib:$LD_LIBRARY_PATH; ./bin/TestGame