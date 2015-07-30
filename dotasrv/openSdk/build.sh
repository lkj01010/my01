#!/bin/bash
find ./package/ -name *.tar.gz | xargs -IX tar -zxvf X -C package_compile/
make config
make outlib
make example
