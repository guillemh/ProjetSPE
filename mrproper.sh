#!/bin/sh

# Remove files created by qtcreator, Makefiles
# and building directory (release, debug)

rm Makefile
rm SPH2D.pro.user

cd core
rm Makefile Makefile.Release Makefile.Debug
rm -r debug
rm -r release
cd ..

cd run
rm Makefile Makefile.Release Makefile.Debug
rm -r debug
rm -r release
cd ..

cd test
rm Makefile Makefile.Release Makefile.Debug
rm -r debug
rm -r release
cd ..
