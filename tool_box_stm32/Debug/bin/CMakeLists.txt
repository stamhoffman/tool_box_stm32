
set(MCU_FAMILY STM32F1xx)
set(MCU_LINE STM32F103xB)
set(MCU_LINKER_SCRIPT arm-gcc-link.ld)
cmake_minimum_required(VERSION 3.6)

project(tool_box_stm32)

add_definitions(-D${MCU_LINE})


file(GLOB_RECURSE USER_SOURCES /stm_lib/src/*.c)
file(GLOB_RECURSE CMSIS_STARTUP /cmsis_boot/startup/startup_stm32f10x_md.c)
file(GLOB_RECURSE CMSIS_BOOT /cmsis_boot/system_stm32f10x.c)

set(SOURCE_FILES ${USER_SOURCES} ${HAL_SOURCES} ${CMSIS_BOOT} ${CMSIS_STARTUP} ${MCU_LINKER_SCRIPT})

include_directories(/cmsis/)
include_directories(/cmsis_boot/)
include_directories(/stm_lib/inc)

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} mthumb -g -nostartfiles -Wl -o0,-Map=${PROJECT_NAME}.map")
set(HEX_FILE ${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
