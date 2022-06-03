#ifndef REGISTERS_H
#define REGISTERS_H

typedef enum {
    REG_0,
    REG_1,
    REG_2,
    REG_3,
    REG_4,
    REG_5,
    REG_6,
    REG_7,
    REG_8,
    REG_9,
    REG_10,
    REG_11,
    REG_12,
    REG_13,
    REG_14,
    REG_15,
} Register;

#define REG(v)  vm->registers[v]
#define RTYPE(v) vm->registers[v].type
#define TTS(v) valTypeToStr(vm->registers[v].type)
#define AS_UINT8(v) vm->registers[v].data.unum8
#define AS_UINT16(v) vm->registers[v].data.unum16
#define AS_UINT32(v) vm->registers[v].data.unum32
#define AS_UINT64(v) vm->registers[v].data.unum64
#define AS_INT8(v) vm->registers[v].data.snum8
#define AS_INT16(v) vm->registers[v].data.snum16
#define AS_INT32(v) vm->registers[v].data.snum32
#define AS_INT64(v) vm->registers[v].data.snum64
#define AS_DOUBLE(v) vm->registers[v].data.dnum
#define AS_FLOAT(v) vm->registers[v].data.fnum
#define AS_ADDR(v) vm->registers[v].data.addr
#define AS_BOOL(v) vm->registers[v].data.boolean
#define NZFLAG vm->nzero

const char* regToStr(Register reg);
#endif