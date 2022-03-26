#/bin/bash

rm -Rf docs
doxygen Doxyfile

cd docs/latex
make pdf
cd ../..

