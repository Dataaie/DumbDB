#!/bin/bash
set -e 
cmake ./
make
test/DumbTests
