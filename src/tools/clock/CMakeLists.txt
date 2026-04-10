set(CLOCK_SOURCES
    clock_app.cc
)

add_executable(rcli-clock ${CLOCK_SOURCES})

target_link_libraries(
    rcli-clock
    PRIVATE
    core_lib
    rcli_common_includes
)