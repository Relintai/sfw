@echo off

rem TODO this needs to be updated,
rem sdl setup used to be not that trivial on windows, there are likely better ways now

if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
)

rem debug: /Zi (== -g)

cl /EHsc /Zi /c sfw.cpp /Fo:sfw.obj
cl /EHsc /Zi /c game_scene.cpp /Fo:game_scene.obj
cl /EHsc /Zi /c main.cpp /Fo:main.obj

cl /Zi /EHsc /Fegame-vc.exe ^
		sfw.obj game_scene.obj main.obj ^
		/SUBSYSTEM:CONSOLE
