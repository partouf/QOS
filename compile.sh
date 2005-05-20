#!/bin/sh

echo Standard prefixed parts
nasm Src/boot.asm -o Output/boot.prt
nasm Src/vdir.asm -o Output/vdir.prt
nasm Src/root.asm -o Output/root.prt

echo Directories
nasm Src/bindir.asm -o Output/bindir.prt
nasm Src/moddir.asm -o Output/moddir.prt

echo Core
nasm Src/corefile.asm -o Output/corefile.prt


echo Combine parts
cd Output
cat boot.prt vdir.prt root.prt bindir.prt moddir.prt corefile.prt > qos.img
cd ..
