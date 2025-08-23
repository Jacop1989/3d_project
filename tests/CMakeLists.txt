add_executable(test_model_io test_model_io.c)
target_compile_definitions(test_model_io PRIVATE UNIT_TEST)
add_test(NAME test_model_io COMMAND test_model_io)
