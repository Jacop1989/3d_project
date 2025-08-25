add_library(platform)

target_include_directories(platform PUBLIC ${CMAKE_SOURCE_DIR}/include)

if (WIN32)
    target_sources(platform PRIVATE win32_platform.c)
else()
    find_package(X11 REQUIRED)
    target_sources(platform PRIVATE x11_platform.c)
    target_link_libraries(platform PUBLIC X11::X11)
endif()
