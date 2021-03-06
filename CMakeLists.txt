cmake_minimum_required(VERSION 2.8)

set(ARCH i686)
set(PLATFORM pc)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${ARCH})
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_C_COMPILER_WORKS 1) # Les test compilateur de CMake utilisent un flag, -rdynamic pas disponible sur le cross compiler qu'on a
set(CMAKE_CXX_COMPILER_WORKS 1)

project(LudOS)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(profile_detection)

LOAD_PROFILE("${ARCH}" "${PLATFORM}")

add_definitions("-DARCH_${ARCH} -DLUDOS_ARCH=\"${ARCH}\"")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_COMPILER "/usr/bin/nasm")
enable_language(ASM_NASM)

file(GLOB_RECURSE KERN_BASE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "kern/*.cpp" "kern/*.c")
file(GLOB_RECURSE ACPICA_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/acpica/*.c")
file(GLOB_RECURSE ACPICA_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/acpica/*.h")
file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "kern/cpp_runtime/*.cpp")
file(GLOB_RECURSE LIBK_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "libc/*.c" "libc/*.cpp" "libc/*.asm")
file(GLOB_RECURSE LIBK_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "libc/*.h" "libc/*.hpp")
file(GLOB_RECURSE LIBKPP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "libk++/*.cpp" "libk++/*.c")
file(GLOB_RECURSE LIBKPP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "libk++/*.hpp" "libk++/*.tpp" "libk++/*.h")
file(GLOB_RECURSE LIBCPP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libc++/*.cpp" "external/libc++/*.c")
file(GLOB_RECURSE LIBCPP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libc++/*.hpp" "external/libc++/*.tpp" "external/libc++/*.h")
file(GLOB_RECURSE LIBCXXABI_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libcxxabi/*.cpp" "external/libcxxabi/*.c")
file(GLOB_RECURSE LIBCXXABI_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libcxxabi/*.hpp" "external/libcxxabi/*.h")
file(GLOB_RECURSE LIBX86EMU_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libx86emu/*.c")
file(GLOB_RECURSE LIBX86EMU_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libx86emu/include/*.h")
file(GLOB_RECURSE LIBDISASM_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libdisasm/*.c")
file(GLOB_RECURSE LIBDISASM_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/libdisasm/*.h")
file(GLOB_RECURSE STB_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/stb/*.h")
file(GLOB_RECURSE STB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "external/stb/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "kern/*.hpp" "kern/*.h" "kern/*.def" "kern/*.tpp")
file(GLOB_RECURSE LD_SCRIPTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.ld")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/kern")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/kern/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/kern/external")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libk++/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/libc++")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/acpica")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/libcxxabi")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/libx86emu/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/libdisasm")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/libunwind")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/libunwind/src")

option(WITH_SSE "Compiles with gcc sse support" ON)
option(WITH_SSE2 "Compiles with gcc sse2 support" OFF)
option(WITH_ARCH_NATIVE "Compiles with -march=native" OFF)
option(WITH_UBSAN "Compiles with undefined behavior sanitization" OFF)
option(WITH_ASAN "Compiles with address sanitization" OFF)
option(USE_CLANG_TIDY "Run clang-tidy on build" OFF)
option(WITH_ACPICA "Compiles libacpica" OFF)

if (WITH_SSE)
    set(SIMD_OPTIONS "-mmmx -msse -mno-sse2 -ftree-vectorize")
elseif (WITH_SSE2)
    set(SIMD_OPTIONS "-mmmx -msse -msse2 -mssse3 -ftree-vectorize")
else()
    set(SIMD_OPTIONS "-mno-mmx -mno-sse -mno-sse2")
endif()

set(ARCH_OPTIONS "")
if (WITH_ARCH_NATIVE)
    set(ARCH_OPTIONS "${ARCH_OPTIONS} -march=native")
else()
endif()

set(SANITIZER_OPTIONS "")
if (WITH_UBSAN)
    set(SANITIZER_OPTIONS "${SANITIZER_OPTIONS} -fsanitize=undefined")
endif()
if(WITH_ASAN)
    set(SANITIZER_OPTIONS "${SANITIZER_OPTIONS} -fsanitize=address")
endif()

# Compilation options
set(KERNEL_VIRTUAL_BASE 0xC0000000 CACHE STRING "")
set(CURRENT_YEAR 2017)
if (WITH_ACPICA)
    set(USES_ACPICA 1)
else()
    set(USES_ACPICA 0)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/kern/utils/defs.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/kern/utils/defs.hpp")

set(GENERIC_SRCS ${CPP_SOURCES} ${KERN_BASE_SOURCES} ${STB_SOURCES})

if (NOT WITH_ACPICA)
    list(FILTER GENERIC_SRCS EXCLUDE REGEX "acpi/.*")
endif()

add_executable(${PROJECT_NAME} ${PLATFORM_SRCS} ${ISA_SRCS} ${GENERIC_SRCS} ${HEADERS} ${STB_HEADERS} ${LD_SCRIPTS})

target_compile_definitions(${PROJECT_NAME} PUBLIC "-D__LUDOS__")

set(CMAKE_C_FLAGS "${ISA_C_FLAGS} ${PLATFORM_C_FLAGS} -Os -fno-strict-aliasing -fstack-protector -m32 ${SIMD_OPTIONS} ${ARCH_OPTIONS} -Wwrite-strings -ffast-math ${SANITIZER_OPTIONS} -std=c11 -Wall -Wextra -Wconversion -Wcast-qual -Wmisleading-indentation -Wno-unused-parameter -Wno-implicit-int -Wnull-dereference -lgcc -static-libgcc -ffreestanding -fno-builtin -nostdlib -fno-omit-frame-pointer -Werror=implicit-function-declaration -lgcc")
set(CMAKE_CXX_FLAGS "${ISA_CXX_FLAGS} ${PLATFORM_CXX_FLAGS} -Os -fno-exceptions -fno-strict-aliasing -m32 ${SIMD_OPTIONS} ${ARCH_OPTIONS} -Wwrite-strings -Wsuggest-final-types -Wsuggest-final-methods -Wconversion -Woverloaded-virtual -ffast-math ${SANITIZER_OPTIONS} -fstack-protector -std=c++17 -Wall -Wextra -Wlogical-op -Wrestrict -Wnull-dereference -Wno-cast-qual -Wdouble-promotion -Wno-unused-parameter -Wno-format -Wno-switch -Wno-packed-bitfield-compat -Wno-reorder -Wno-trigraphs -Wmisleading-indentation -Wnull-dereference -lgcc -static-libgcc -ffreestanding -fno-builtin -nostdlib -fno-omit-frame-pointer -Werror=implicit-function-declaration -lgcc")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
  "-T ${PLATFORM_LAYOUT} ${ISA_LINKER_FLAGS} ${PLATFORM_LINKER_FLAGS} -lgcc -Xlinker -Map=ld.map ")
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".bin")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${ARCH}-elf-gcc -T ${PLATFORM_LAYOUT} ${ISA_LINKER_FLAGS} --no-ld-generated-unwind-info ${PLATFORM_LINKER_FLAGS} <OBJECTS> -o <TARGET>.bin")

add_library(libk ${LIBK_SOURCES} ${LIBK_HEADERS})
target_compile_definitions(libk
    PUBLIC __is_libk)
#set_target_properties(libk PROPERTIES COMPILE_FLAGS "-w")
target_compile_options(libk PUBLIC $<$<NOT:$<COMPILE_LANGUAGE:ASM_NASM>>:-w>)

add_library(libcxxabi ${LIBCXXABI_SOURCES} ${LIBCXXABI_HEADERS})
set_target_properties(libcxxabi PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(libcxxabi PROPERTIES COMPILE_FLAGS "-w")
target_compile_definitions(libcxxabi PUBLIC "-D__LUDOS__")
target_link_libraries(libcxxabi)

add_library(libcpp ${LIBCPP_SOURCES} ${LIBCPP_HEADERS})
set_target_properties(libcpp PROPERTIES COMPILE_FLAGS "-w")
target_link_libraries(libcpp libcxxabi)
target_compile_definitions(libcpp PUBLIC "-D__LUDOS__")

add_library(libk++ ${LIBKPP_SOURCES} ${LIBKPP_HEADERS})
set_target_properties(libk++ PROPERTIES COMPILE_FLAGS "-w")
target_compile_definitions(libk++ PUBLIC "-D__LUDOS__")

add_library(libx86emu ${LIBX86EMU_SOURCES} ${LIBX86EMU_HEADERS})
set_target_properties(libx86emu PROPERTIES LINKER_LANGUAGE C)
set_target_properties(libx86emu PROPERTIES COMPILE_FLAGS "-w")
target_link_libraries(libx86emu libk)

add_library(libdisasm ${LIBDISASM_SOURCES} ${LIBDISASM_HEADERS})
set_target_properties(libdisasm PROPERTIES LINKER_LANGUAGE C)
set_target_properties(libdisasm PROPERTIES COMPILE_FLAGS "-w")
target_link_libraries(libdisasm libk)
target_compile_definitions(libdisasm PUBLIC "-D__LUDOS__")

if (WITH_ACPICA)
    add_library(acpica ${ACPICA_SOURCES} ${ACPICA_HEADERS})
    set_target_properties(acpica PROPERTIES LINKER_LANGUAGE C)
    set_target_properties(acpica PROPERTIES COMPILE_FLAGS "-w")
    target_link_libraries(acpica libk)
    target_compile_definitions(acpica PUBLIC "-D__LUDOS__")
endif()

include(ExternalProject)

add_subdirectory(userland)

target_link_libraries(${PROJECT_NAME} libk libk++ libcpp libcxxabi libx86emu libdisasm)
if (WITH_ACPICA)
    target_link_libraries(${PROJECT_NAME} acpica)
endif()
target_link_libraries(libx86emu libk)

set(CMAKE_CXX_LINK_EXECUTABLE "/usr/local/cross/bin/${ARCH}-elf-ld --build-id=none -T ${PLATFORM_LAYOUT} ${ISA_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>-L/usr/tooLargeForHome/cross_src/build-gcc/i686-elf/libgcc/ -lgcc")

if (USE_CLANG_TIDY)
    set(DO_CLANG_TIDY "clang-tidy" "-checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*,cppcoreguidelines-*")
    set_target_properties(
      ${PROJECT_NAME} PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "./multiboot-check.sh" $<TARGET_FILE:${PROJECT_NAME}>
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tools")
