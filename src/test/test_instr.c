
// build string:
// gcc -Wall -Wextra -I../include -I../lib -g -o ti test_instr.c ../lib/instructions.c ../lib/memory.c
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "memory.h"

enum {
    BYTE = sizeof(uint8_t),
    SHORT = sizeof(uint16_t),
    INT = sizeof(uint32_t),
    LONG = sizeof(uint64_t),
    SIGNED,
    UNSIGNED,
    STOP,
};

int size_list[] = {
    BYTE, SHORT, SHORT, INT, INT, LONG,
    BYTE, BYTE, BYTE, SHORT, SHORT, INT,
    INT, LONG, LONG, LONG,
    STOP
};

int type_list[] = {
    UNSIGNED, UNSIGNED, SIGNED, SIGNED, UNSIGNED, UNSIGNED,
    UNSIGNED, UNSIGNED, SIGNED, SIGNED, SIGNED, SIGNED,
    UNSIGNED, UNSIGNED, SIGNED, SIGNED,
    STOP
};

int main() {

    _initMemory();
    init_instructions();

    write_u8(0xFF);
    write_u16(0x9988);
    write_s16(-279);
    write_s32(12345);
    write_u32(0x12345678);
    write_u64(0xFEDCBA9876543210);

    write_u8(0xA5);
    write_u8(0x5A);
    write_s8(-3);
    write_s16(0xde);
    write_s16(279);
    write_s32(-12345);

    write_u32(0x12345678);
    write_u64(0xFEDCBA9876543210);
    write_s64(1098787654);
    write_s64(-1098787654);
printf("here\n");
    for(int idx = 0; size_list[idx] != STOP; idx++) {
        switch(size_list[idx]) {
            case BYTE:
                switch(type_list[idx]) {
                    case SIGNED:
                        printf("signed byte: %d\n", read_s8());
                        break;
                    case UNSIGNED:
                        printf("unsigned byte: 0x%02X\n", read_u8());
                        break;
                    default:
                        fprintf(stderr, "error 2\n");
                        exit(1);
                }
                break;
            case SHORT:
                switch(type_list[idx]) {
                    case SIGNED:
                        printf("signed short: %d\n", read_s16());
                        break;
                    case UNSIGNED:
                        printf("unsigned short: 0x%04X\n", read_u16());
                        break;
                    default:
                        fprintf(stderr, "error 2\n");
                        exit(1);
                }
                break;
            case INT:
                switch(type_list[idx]) {
                    case SIGNED:
                        printf("signed int: %d\n", read_s32());
                        break;
                    case UNSIGNED:
                        printf("unsigned int: 0x%08X\n", read_u32());
                        break;
                    default:
                        fprintf(stderr, "error 2\n");
                        exit(1);
                }
                break;
            case LONG:
                switch(type_list[idx]) {
                    case SIGNED:
                        printf("signed long: %ld\n", read_s64());
                        break;
                    case UNSIGNED:
                        printf("unsigned long: 0x%16lX\n", read_u64());
                        break;
                    default:
                        fprintf(stderr, "error 2\n");
                        exit(1);
                }
                break;
            default:
                fprintf(stderr, "error\n");
                exit(1);

        }
    }
}

