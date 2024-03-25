cmake_minimum_required(VERSION 3.28)

project(main)

set(SOURCES
    ams.c
    amp.c
    frame.c
    #    usb.c
)

set(HEADERS
    amp.h
    ams.h
    define.h
    frame.h
    #        usb.h
)

add_executable(autotests ${SOURCES} ${HEADERS}
    autotest/autotests.h
    autotest/autotests.c
    test_unitaire.c
)

add_executable(simulation ${SOURCES} ${HEADERS}
    audisen_sim.c
)

add_executable(usb ${SOURCES} ${HEADERS}
    usb.c
    usb.h
    audisen_usb.c
)