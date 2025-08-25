# 3D Project

Minimal software-rendered demo in pure C with Win32/X11 platform layer.

## Build & Run

### Windows (MSYS2 MinGW64)
```sh
pacman -S --needed mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb
cmake -S . -B build
cmake --build build
build/3d_project.exe
```

### Linux
```sh
sudo apt-get install -y build-essential libx11-dev
cmake -S . -B build
cmake --build build
./build/3d_project
```
