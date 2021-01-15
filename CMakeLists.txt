cmake_minimum_required(VERSION 3.17)
project(C_Practices C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Practices
        Chapter-01/hello.c
        Chapter-01/temperature.c
        Chapter-01/main.c
        Chapter-01/filecopying.c
        Chapter-01/char_count.c
        Chapter-01/line_count.c Chapter-01/word_count.c Chapter-01/arrays.c Chapter-01/power.c Chapter-01/input_line.c Chapter-01/external.c Chapter-02/types.c Chapter-03/binSearch.c Chapter-03/switches.c Chapter-03/atoi.c Chapter-03/shelsort.c Chapter-03/reverse.c Chapter-03/itoa.c Chapter-03/trim.c Chapter-04/patterns.c)
