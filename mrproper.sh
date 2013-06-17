#!/bin/sh

# Remove files created by qtcreator, Makefiles
# and building directory (release, debug)

make clean
rm -f SPH2D.pro.user
rm -f *~

cd core
make clean
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..

cd run
make clean
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..

cd test
make clean
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..

cd g3d
make clean
rm test_*
rm -f Makefile
rm -f *~
cd ..

cd cascade
make clean
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..

