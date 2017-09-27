@echo off

mkdir ..\..\build
pushd ..\..\build
cl -Zi ..\DungeonCrawl\code\DungeonCrawl.cpp /EHsc user32.lib
popd