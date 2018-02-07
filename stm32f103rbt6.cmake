#include(CMakeForceCompiler)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)
#set(LINKER_LANGUAGE C ASM)

# Find the cross compiler
find_program(ARM_CC arm-none-eabi-gcc ${TOOLCHAIN_DIR}/bin)
find_program(ARM_CXX arm-none-eabi-g++ ${TOOLCHAIN_DIR}/bin)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy ${TOOLCHAIN_DIR}/bin)
find_program(ARM_SIZE_TOOL arm-none-eabi-size  ${TOOLCHAIN_DIR}/bin)
find_program(ARM_AS arm-none-eabi-as ${TOOLCHAIN_DIR}/bin)


set(CMAKE_C_COMPILER ${ARM_CC})
set(CMAKE_CXX_COMPILER ${ARM_CXX})

set(COMMON_FLAGS "-mcpu=${CMAKE_SYSTEM_PROCESSOR} -mthumb -ffunction-sections -fdata-sections -g -fno-common -fmessage-length=0")

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-m3 -DSTM32F103RB -DSTM32F10X_MD -mthumb")

if (CMAKE_SYSTEM_PROCESSOR STREQUAL cortex-m3)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
else (message(WARNING Processor not recognised in toolchain file, compiler flags not configured))
endif ()

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/STM32F103RBTx_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m3 -fno-exceptions -fno-rtti -DSTM32F103RB -DSTM32F10X_MD D -DUSE_STDPERIPH_DRIVER -D__ASSEMBLY__ -mthumb -g2 -O0 -Wl,-gc-sections -T ${LINKER_SCRIPT}")
