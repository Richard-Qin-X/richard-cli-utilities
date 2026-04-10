set(CORE_SOURCES
    license.cc
    terminal.cc
    logger.cc
    signals.cc
    keyboard.cc
    utils.cc
)

add_library(core_lib STATIC ${CORE_SOURCES})

target_link_libraries(core_lib PUBLIC rcli_common_includes)