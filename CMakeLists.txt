cmake_minimum_required(VERSION 3.28)

project(main)

set(SOURCES
    ams.c
    amp.c
    frame.c
        audisen_sim.c
        #    usb.c
)

set(HEADERS
        amp.h
        ams.h
        define.h
        frame.h
        audisen_usb.c
        #        usb.h
)

add_executable(main ${HEADERS} ${SOURCES})