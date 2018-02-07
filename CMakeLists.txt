set(MCU_FAMILY STM32F1xx)
set(MCU_LINE STM32F103xB)
set(LINKER_SCRIPT STM32F103RBTx_FLASH.ld)
#add_definitions(DSTM32F10X_MD)

cmake_minimum_required(VERSION 3.5.0)
project(tool_box_stm32 C ASM)
include(stm32f103rbt6.cmake)

#set(CMAKE_VERBOSE_M‌​AKEFILE ON)

file(GLOB_RECURSE SRC stm_lib/src/*.c)
file(GLOB_RECURSE MAIN main.c)

include_directories(stm_lib/inc)
include_directories(cmsis)
include_directories(cmsis_boot)

add_library(CMSIS cmsis_boot/system_stm32f10x.c cmsis_boot/startup/startup_stm32f10x_md.c)

add_executable(${PROJECT_NAME}.elf ${SRC} ${MAIN} ${LINKER_SCRIPT})

target_link_libraries(${PROJECT_NAME}.elf CMSIS)


set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
         COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
         COMMAND ${CMAKE_OBJCOPY} -Obinaty <$TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
         COMMENT "BUILD ${HEX_FILE} \n BUILDding ${BIN_FILE}")
