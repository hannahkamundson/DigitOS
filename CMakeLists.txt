cmake_minimum_required(VERSION 3.26)
project(DigitOS C)

set(CMAKE_C_STANDARD 11)

include_directories(project0)
include_directories(project0/tests/test-utils/p2a-ebb)

add_executable(DigitOS
        project0/tests/test-utils/p2a-ebb/alloc.c
        project0/tests/test-utils/p2a-ebb/debug.h
        project0/tests/test-utils/p2a-ebb/other.c
        project0/argprinter.c
        project0/fib.c
        project0/handle.c
        project0/mykill.c
        project0/sig_util.c
        project0/sig_util.h
        project0/utcsh.c
        project0/util.c
        project0/util.h)
