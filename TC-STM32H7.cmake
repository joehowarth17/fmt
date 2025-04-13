include(CMakeForceCompiler)
set(CMAKE_SYSTEM_NAME Generic)

#CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)

#CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_FLAGS_INIT "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS_INIT "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -specs=nano.specs -lc -lm -lnosys ")
set(CMAKE_)
