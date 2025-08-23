set(CMAKE_CXX_STANDARD 17)

add_executable(test_model_io test_model_io.c)
target_compile_definitions(test_model_io PRIVATE UNIT_TEST)
add_test(NAME test_model_io COMMAND test_model_io)

add_executable(test_obj_parser
    test_obj_parser.c
    ../src/io/obj_parser.c
    ../src/kernel/mesh.c)
add_test(NAME test_obj_parser COMMAND test_obj_parser)

add_executable(test_stl_parser
    test_stl_parser.c
    ../src/io/stl_parser.c
    ../src/kernel/mesh.c)
add_test(NAME test_stl_parser COMMAND test_stl_parser)

add_executable(test_step_parser
    test_step_parser.c
    ../src/io/step_parser.c
    ../src/kernel/mesh.c)
add_test(NAME test_step_parser COMMAND test_step_parser)

add_executable(test_mesh_builder
    test_mesh_builder.cpp
    ../src/kernel/mesh_builder.cpp
    ../src/kernel/mesh.c)
add_test(NAME test_mesh_builder COMMAND test_mesh_builder)

add_executable(test_constraints
    test_constraints.cpp
    ../src/sketch/sketch.cpp
    ../src/sketch/constraint_manager.cpp
    ../src/sketch/entity_line.cpp
    ../src/sketch/entity_circle.cpp)
add_test(NAME test_constraints COMMAND test_constraints)

add_executable(test_features
    test_features.cpp
    ../src/model/feature.cpp
    ../src/model/history_tree.cpp
    ../src/kernel/mesh.c
    ../src/kernel/boolean.cpp)
add_test(NAME test_features COMMAND test_features)

add_executable(test_kernel
    kernel/test_kernel.cpp
    ../src/kernel/boolean.cpp
    ../src/kernel/mesh.c)
add_test(NAME test_kernel COMMAND test_kernel)

add_executable(test_assembly
    test_assembly.cpp
    ../src/assembly/Assembly.cpp
    ../src/assembly/Component.cpp
    ../src/assembly/Mate.cpp)
add_test(NAME test_assembly COMMAND test_assembly)
