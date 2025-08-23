set(CMAKE_CXX_STANDARD 17)

add_executable(test_model_io test_model_io.c)
target_compile_definitions(test_model_io PRIVATE UNIT_TEST)
add_test(NAME test_model_io COMMAND test_model_io)

add_executable(test_step_parser
    test_step_parser.c
    ../src/io/step_parser.c
    ../src/mesh.c)
add_test(NAME test_step_parser COMMAND test_step_parser)

add_executable(test_mesh_builder
    test_mesh_builder.cpp
    ../src/kernel/mesh_builder.cpp)
add_test(NAME test_mesh_builder COMMAND test_mesh_builder)

add_executable(test_constraints
    test_constraints.cpp
    ../src/sketch/sketch.cpp
    ../src/sketch/constraint_manager.cpp
    ../src/sketch/entity_line.cpp
    ../src/sketch/entity_circle.cpp)
add_test(NAME test_constraints COMMAND test_constraints)
