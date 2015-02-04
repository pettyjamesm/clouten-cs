set(SOURCE_FILES stacks.c system_calls.c value_and_reference.c ../scratch/scratch.c)

set(EXECUTABLE_OUTPUT_PATH bin/)

add_executable(stacks stacks.c)
add_executable(system_calls system_calls.c)
add_executable(value_and_reference value_and_reference.c)