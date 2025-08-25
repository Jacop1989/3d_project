add_subdirectory(kernel)
add_subdirectory(sketch)
add_subdirectory(model)
add_subdirectory(assembly)
add_subdirectory(io)
add_subdirectory(ui)
add_subdirectory(platform)
add_subdirectory(render)

add_executable(three_d_app app/main.c)
target_link_libraries(three_d_app
    kernel
    sketch
    model
    assembly
    io
    ui
    platform
    render
)
