cmake_minimum_required(VERSION 3.16)

# ----- Project: C only -----
project(3d_project LANGUAGES C)

# C dialect & extensions
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON) # allow gnu17 when toolchain prefers

# Default build type if not provided
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ----- Compile warnings (per compiler) -----
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    -Wall -Wextra -Wshadow -Wconversion -Wpedantic
    -Wno-unused-parameter
  )
elseif (MSVC)
  add_compile_options(/W4 /permissive-)
endif()

# ----- Optimizations / Debug flags -----
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-O0 -g)
  elseif (MSVC)
    add_compile_options(/Od /Zi)
  endif()

  # Optional sanitizers (GNU/Clang only; may be unavailable on some MinGW)
  include(CheckCCompilerFlag)
  check_c_compiler_flag("-fsanitize=address" HAS_ASAN)
  check_c_compiler_flag("-fsanitize=undefined" HAS_UBSAN)
  if (HAS_ASAN AND HAS_UBSAN AND (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"))
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
  endif()
else() # Release & others
  if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-O2 -DNDEBUG)
  elseif (MSVC)
    add_compile_options(/O2 /DNDEBUG)
  endif()
endif()

# ----- Sources -----
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/*.c"
  "${CMAKE_SOURCE_DIR}/3d_*.c"
)

# Executable (main app)
add_executable(3d_project ${SRC})

# Include paths (public first, then internal)
target_include_directories(3d_project PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/src/app"
  "${CMAKE_SOURCE_DIR}/src/math"
  "${CMAKE_SOURCE_DIR}/src/render"
  "${CMAKE_SOURCE_DIR}/src/platform"
  "${CMAKE_SOURCE_DIR}/src/sketch"
  "${CMAKE_SOURCE_DIR}/src/core"
)

# Win32 / X11 system libs + Win32 lightweight headers
if (WIN32)
  target_compile_definitions(3d_project PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
  target_link_libraries(3d_project PRIVATE gdi32 user32 kernel32)
else()
  target_link_libraries(3d_project PRIVATE X11 m)
endif()

# ----- Test runner (no main.c) -----
set(SRC_NO_MAIN ${SRC})
list(REMOVE_ITEM SRC_NO_MAIN "${CMAKE_SOURCE_DIR}/src/app/main.c")

add_executable(test_runner
  "${CMAKE_SOURCE_DIR}/tests/test_runner.c"
  ${SRC_NO_MAIN}
)

target_include_directories(test_runner PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/src/app"
  "${CMAKE_SOURCE_DIR}/src/math"
  "${CMAKE_SOURCE_DIR}/src/render"
  "${CMAKE_SOURCE_DIR}/src/platform"
  "${CMAKE_SOURCE_DIR}/src/sketch"
  "${CMAKE_SOURCE_DIR}/src/core"
)

if (WIN32)
  target_compile_definitions(test_runner PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
  target_link_libraries(test_runner PRIVATE gdi32 user32 kernel32)
else()
  target_link_libraries(test_runner PRIVATE X11 m)
endif()
