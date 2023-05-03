# DeMage - Engine

DeMage is ECS based engine for making 2D games, written in C++, with support of SDL2 library.

*Engine based and inspired by: https://github.com/sobajic/MATFGame*

## Development status:
Development is in progress. 
Idea is enable simple use engine for people to learn about ECS based systems and to have fun making own games. 

## Setup

### Cmake Setup

After cloning repository, run update of submodules
```bash
  git submodule init
  git submodule update
```
After this, `vcpkg` manager will be added to dependencies folder.

### 1. Windows - Visual Studio

If you are using `Visual Studio`, you can open folded using it.
Before building, regenerate `CMake` cache, by going to `Project/Configure Demage`.

After all packages are downloaded, built, and build files are generated, you can  choose target build (`Debug, Release`) and executable to run.

### 2. Unix - console 

Just run in root folder.
```bash
cmake .
```
 After generation of build files, run command to build engine
 ```bash
make
```

### 3. Setup for VSCode 

WIP

### Install troubleshoots
- If for some reason you get error that `vcpkg` is not installed, go to `dependencies/vcpkg` and run manualy `bootstrap-vcpkg.[bat/sh]`.