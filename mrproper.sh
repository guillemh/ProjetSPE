#!/bin/sh

# Remove files created by qtcreator, Makefiles
# and building directory (release, debug)

rm -f Makefile
rm -f SPH2D.pro.user
rm -f *~

cd core
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..

cd run
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..

cd test
rm -f Makefile Makefile.Release Makefile.Debug
rm -f -r debug
rm -f -r release
rm -f *~
cd ..
