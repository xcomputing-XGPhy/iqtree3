:: @echo off
setlocal enabledelayedexpansion

:: Build the DLL file and the DEF file
g++ -shared -o iqtree3.dll %1 -Wl,--output-def,iqtree3.def -liqtree3 -L. -lws2_32 -lz -lpthread

:: Create the LIB file
lib /def:iqtree3.def
