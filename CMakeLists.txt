cmake_minimum_required(VERSION 3.28)

project(audisen)

set(SOURCES
        src/ams.c
        src/amp.c
        src/frame.c
        src/utils.c
    #    usb.c
)

set(HEADERS
        include/amp.h
        include/ams.h
        include/define.h
        include/frame.h
        include/utils.h
    #        usb.h
)

add_executable(autotests ${SOURCES} ${HEADERS}
        include/autotests.h
        src/autotests.c
        test/test_unitaire.c
)

add_executable(simulation ${SOURCES} ${HEADERS}
        src/audisen_sim.c
)

add_executable(usb ${SOURCES} ${HEADERS}
        src/usb.c
        include/usb.h
        src/audisen_usb.c
)

#relative path for the .lib
target_link_libraries(usb ${CMAKE_SOURCE_DIR}/ftd2xxDriver/amd64/ftd2xx.lib)
