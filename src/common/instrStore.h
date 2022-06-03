#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "system.h"
#include "values.h"

typedef struct {
    unsigned char* buffer;
    unsigned long cap;
    unsigned long len;
    unsigned long index;
} InstrStore;

void initInstrStore(InstrStore* store);
void uninitInstrStore(InstrStore* store);

/*
void write_u8(InstrStore* store, uint8_t val);
void write_u16(InstrStore* store, uint16_t val);
void write_u32(InstrStore* store, uint32_t val);
void write_u64(InstrStore* store, uint64_t val);

void write_s8(InstrStore* store, int8_t val);
void write_s16(InstrStore* store, int16_t val);
void write_s32(InstrStore* store, int32_t val);
void write_s64(InstrStore* store, int64_t val);

void write_value(InstrStore* store, Value val);
void write_idx(InstrStore* store, VarIdx idx);

uint8_t read_u8(InstrStore* store);
uint16_t read_u16(InstrStore* store);
uint32_t read_u32(InstrStore* store);
uint64_t read_u64(InstrStore* store);

int8_t read_s8(InstrStore* store);
int16_t read_s16(InstrStore* store);
int32_t read_s32(InstrStore* store);
int64_t read_s64(InstrStore* store);

Value read_value(InstrStore* store);
VarIdx read_idx(InstrStore* store);
*/

unsigned long getInstrIndex(InstrStore* store);
unsigned long getInstrLen(InstrStore* store);
void setInstrIndex(InstrStore* store, unsigned long idx);
void incInstrIndex(InstrStore* store, int idx);
bool isInstrEnded(InstrStore* store);

#define WRITE(s, t, v) do { \
        while(s.cap < s.len + sizeof(t)) { \
            s.cap <<= 1; \
            s.buffer = _realloc(s.buffer, s.cap); \
        } \
        *((t*)&s.buffer[s.len]) = v; \
        s.len += sizeof(t); \
    } while(0)

#define READ(s, t, v) do { \
        v = *((t*)&s.buffer[s.index]); \
        s.index += sizeof(t); \
    } while(0)

#define WRITE_VM_OBJ(t, v) WRITE(vm->istore, t, v)
#define READ_VM_OBJ(t, v) READ(vm->istore, t, v)

#endif