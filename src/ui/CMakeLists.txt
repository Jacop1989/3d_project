add_library(ui
    ui.cpp
    imgui_layer.cpp
    property_panel.cpp
    constraint_panel.cpp
    sketch_view.cpp
    viewport.cpp
)

add_executable(property_panel_example property_panel_example.cpp)
target_link_libraries(property_panel_example ui)
