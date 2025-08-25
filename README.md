# 3D Project

Minimal software renderer in pure C17 using only operating system APIs (Win32/X11). No third‑party libraries are required.

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug   # or Release
cmake --build build
```
Debug builds use `-O0 -g` and enable sanitizers when available. Release builds use `-O2 -DNDEBUG`.

## Run

```
./build/3d_project
```

## Tests

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target test_runner
./build/test_runner
```

## Error handling

All runtime functions return `err_t` codes and log messages instead of aborting. Allocation failures during initialization are reported as `ERR_OOM` and the application exits cleanly. Bad inputs are clipped or ignored safely.
