#Build tool_box_stm32

include (CMakeForceCompiler)
set(CMAKE_SYSTEM_NAME Generic)

SET(CMAKE_SYSTEM_VERSION 1)

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

SET(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/arm-gcc-link.ld)
SET(COMMON_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -ffunction-sections -g2 -O0 -c -DSTM32F103RB  -DUSE_STDPERIPH_DRIVER -D__ASSEMBLY__")
SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl, -gc-sections -specs=nosys.specs -specs=nano.specs -T ${LINKER_SCRIPT}")
