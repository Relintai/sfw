# SFW - Simple Framework

Simple c++ app / game framework inspired by the single file c game engines 
and libraries, especially [FWK](https://github.com/r-lyeh/FWK).

It was designed to help with teaching programming, but it turns out it's pretty useful for other projects aswell.

This library / framework is:
- Simple to compile.
- Simple to initialize.
- Simple to use.
- Supports windowing and opengl (ES2).
- Modular (within reason).
- It is desktop only (Windows, Linux, OSX) for now (most code is multiplatform though).

Also:
- The codebase is simple and easy to read.
- Comes with it's own container classes and memory management.
- Comes as 2 (or 3) merged files. (This way it's actually simpler to use and setup compared to if it was single header!)
- It does not use exceptions.

A lite version is also available (sfwl).

## Modules

Currently the framework contains 5 modules, they are additive:

### Core

Has:
- Typedefs
- Math defines, and a class
- Logging, and error macros
- Math helper classes (like Vector2, Vector3, Projection, Transform etc.)
- Containers
- Memory management
- Threading
- Subprocess handling
- Sockets
- Strings
- File and Directory handling

Does not depend on anything.

### Object

Has:
- Object, Reference, Resource classes
- Variant class that can store anything
- Signal class

Depends on Core.

### Render Core

A c++ abstraction over the opengl api.

Has:
- Shaders
- Materials
- Meshes
- Windowing
- Fonts
- Images
- Textures
- FrameBuffers
- Input handling
- An Application and a Scene class for easier development

Depends on Core and Object.

### Render Immediate

Contains a simple immediate renderer class. (called Renderer.)

Depends on Core, Object and Render Core.

### Render Object

Contains a class based renerer api.

Has classes like:
- Camera2D
- Camera3D
- MeshInstance 2D/3D
- Text2D
- TileMap
- Etc.

Depends on Core, Object and Render Core.

## SFWL

The library's lite version.

Same as the normal library except the math helper classes were removed (except for Vector2i, and Rect2i).

It only has 2 modules, Core, and Objects.

## Compilation without the renderer

If you don't need the renderer then everything is extremely simple.

First grab a version that does not have the renderer.

Now you have 2 files: `sfw.h` and `sfw.cpp` or `sfwl.h` and `sfwl.cpp` depending on your choice.

If you use an ide, just add these files to your project (so the .cpp file gets compiled), and you are done.

If you are using a compiler directly, then just add `sfw.cpp` or `sfwl.cpp` to the list of files that you are compiling:

g++ / mingw:

```
g++ -g sfwl.cpp main.cpp -o prog 
```

Note: -g means add debug information to the executable.

MSVC:

```
cl /Zi /EHsc /Feprog-vc.exe sfw.cpp main.cpp
```

Note: /Zi means add debug information to the executable.

If you are creating object files:

g++ / mingw:

```
g++ -g -c sfwl.cpp -o sfwl.o
g++ -g -c main.cpp -o main.o

g++ -g sfwl.o main.o -o prog
```

MSVC:

```
cl /EHsc /Zi /c sfw.cpp /Fo:sfw.obj
cl /EHsc /Zi /c main.cpp /Fo:main.obj

cl /Zi /EHsc /Feprog-vc.exe sfw.obj main.obj
```

Note: You might need to set c++14 level compatibility depending on your compiler. While the codebase is somwhere between 
c++89 and c++11, threads use classes from the std namespace that were added in c++14. Nowadays these are usually available 
without any special setting, but if your compiler is older (or set differently) you might need to add something like: 
`-std=c++14` to your compile commands.

## Compilation with the renderer

If you also want the renderer, first set everything up exactly as in the "Compilation without the renderer" section, 
except you will have 3 files: `sfw.h` and `sfw.cpp`, and `sfw_3rd.m` (this is actually a c header file, it has 
the extencion `.m` to make OSX builds easier).

As a second step we need to tell the linker to link to some of the libraries in the system dynamically in order to
open windows and use opengl.

### MSVC (Windows)

If you are using MSVC you are actually done, no need to do anything else as MSVC has a nice feature where 
this can be done automatically. Search the codebase for `#pragma comment` to see the libraries that get linked.

### MingW

If you are using mingw (If you use the g++ command on windows, that is MingW!), this is how your last (linking) command changes:

```
g++ -g sfwl.cpp main.cpp -lgdi32 -lShlwapi -lws2_32 -o prog 
```

Or

```
g++ -g sfwl.o main.o -lgdi32 -lShlwapi -lws2_32 -o prog
```

Note the position of the `-l` commands, add those after your object (or .cpp) files.

Also, you don't need to add these to the other steps that does not create the final executable.

Note if you use clang, just replacing `g++` to `clang++` or `clang` should work.

### Linux (G++ / clang)

On debian based distributions run the following command to make sure that dependencies are installed:

```
sudo apt-get install libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev
```

Arch based systems should have these by default. For other distros consult the manual and / or the internet
to see which packages are the equivalent of the ones listed above.


This is how your last (linking) command changes:

```
g++ -g sfwl.cpp main.cpp -lX11 -o prog 
```

Or

```
g++ -g sfwl.o main.o -lX11 -o prog
```

Note the position of the `-l` command, add those after your object (or .cpp) files.

Some g++ versions seem a lot more leanient, for example on Manjaro as of this writing 
`g++ -g -lX11 sfwl.o main.o -o prog` works, but on the Raspberry pi (Raspian) it doesn't.

Also, you don't need to add these to the other steps that does not create the final executable.

Note if you use clang, just replacing `g++` to `clang++` or `clang` should work.

### OSX (clang)

If you need the renderer you will need to use clang on OSX.

First we need to setup SDK paths:

```
export SDKROOT=$(xcrun --show-sdk-path)
```

Set up some helper variables: 

```
export cpp_args="-std=c++14 -w -framework cocoa -framework iokit -framework CoreFoundation -framework CoreAudio -framework AudioToolbox "
export m_args="-w -framework cocoa -framework iokit -framework CoreFoundation -framework CoreAudio -framework AudioToolbox "
```

On OSX sfw_3rd.m need to be compiled manually, separately:

(This is a workaround, because Objective-C and C++ code doesn't mix in a single file, but Objective-C and C does.)

```
clang++ -w $m_args -g -c sfw_3rd.m -o sfw_3rd.o
```

Now just compile everything else to objects:

```
clang++ $cpp_args -g -c sfw.cpp -o sfw.o
clang++ $cpp_args -g -c game_scene.cpp -o game_scene.o
clang++ $cpp_args -g -c main.cpp -o main.o
```

Then just link them together:

```
clang++ $cpp_args -g sfw.o sfw_3rd.o game_scene.o main.o -o game 
```

## CompileDB

If you want to edit the split version of the framework in the `sfw` or `sfwl` folder and you
want to generate a compiledb, currently the simples solution that I know of is to install 
the `compiledb` python module and just use it with the makefile in the root of the project.

Create virtual env:

``` python -m venv venv ```

Activate it (This is for bash on linux).

Commands for other shells: https://docs.python.org/3/library/venv.html#how-venvs-work

``` . ./venv/bin/activate ```

Install:

``` pip install compiledb ```

Run compiledb with make to generate compile_commands.json

``` compiledb make ```
