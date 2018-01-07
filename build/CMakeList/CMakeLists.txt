    
include(CMakeForceCompiler)


set(MCU_LINKER_SCRIPT arm-gcc-link.ld)
set(MCU_ARCH cortex-m3)
set(MCU_FLOAT_ABI soft)
set(MCU_FPU fpv4-sp-d16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GCC)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GCC)

set(COMMON_FLAGS "-mcpu=${MCU_ARCH} -Wall -mthumb -ffunction-sections -fdata-sections -g  -o0 -c -fno-common DUSE_STDPERIPH_DRIVER -D__ASSEMBLY__")
# -mcpu=cortex-m3 -mthumb -Wall -ffunction-sections -g -O0 -c -DSTM32F103RB -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -D__ASSEMBLY__

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -T ${CMAKE_SOURCE_DIR}/${MCU_LINKER_SCRIPT}")
