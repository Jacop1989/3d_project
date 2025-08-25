add_library(render tri.c zbuf.c)
target_include_directories(render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
