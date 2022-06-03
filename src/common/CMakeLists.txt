
project(vm)

add_library(${PROJECT_NAME} STATIC
    memory.c
    opcodes.c
    values.c
    instrStore.c
    varStore.c
    callStack.c
    valStack.c
    traps.c
    fileIo.c
    registers.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}/../common
)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra" "-g" "-DTRACE")
