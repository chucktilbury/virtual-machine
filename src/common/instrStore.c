/**
 * @file instrStore.c
 * @brief This is the instruction store of the virtual machine. It is
 * basically a buffer of unsigned characters that can be written and read
 * as different sized objects.
 */
#include "memory.h"
#include "instrStore.h"

/*
static void expand(InstrStore* store, unsigned long size)
{
    while(store->cap < store->len+size) {
        store->cap <<= 1;
        store->buffer = _realloc(store->buffer, store->cap);
    }
}
*/

void initInstrStore(InstrStore* store)
{
    if(store->buffer != NULL)
        _free(store->buffer);

    store->len = 0;
    store->index = 0;
    store->cap = 0x01 << 3;

    store->buffer = _alloc(store->cap);
}

void uninitInstrStore(InstrStore* store)
{
    if(store->buffer != NULL)
        _free(store->buffer);
}

/*
void write_u8(InstrStore* store, uint8_t val)
{
    expand(store, sizeof(uint8_t));
    *((uint8_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(uint8_t);
}

void write_u16(InstrStore* store, uint16_t val)
{
    expand(store, sizeof(uint16_t));
    *((uint16_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(uint16_t);
}

void write_u32(InstrStore* store, uint32_t val)
{
    expand(store, sizeof(uint32_t));
    *((uint32_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(uint32_t);
}

void write_u64(InstrStore* store, uint64_t val)
{
    expand(store, sizeof(uint64_t));
    *((uint64_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(uint64_t);
}

void write_s8(InstrStore* store, int8_t val)
{
    expand(store, sizeof(uint8_t));
    *((int8_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(int8_t);
}

void write_s16(InstrStore* store, int16_t val)
{
    expand(store, sizeof(uint16_t));
    *((int16_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(int16_t);
}

void write_s32(InstrStore* store, int32_t val)
{
    expand(store, sizeof(uint32_t));
    *((int32_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(int32_t);
}

void write_s64(InstrStore* store, int64_t val)
{
    expand(store, sizeof(uint64_t));
    *((int64_t*)&store->buffer[store->len]) = val;
    store->len += sizeof(int64_t);
}

void write_value(InstrStore* store, Value val)
{
    expand(store, sizeof(Value));
    *((Value*)&store->buffer[store->len]) = val;
    store->len += sizeof(Value);
}

void write_idx(InstrStore* store, VarIdx idx)
{
    expand(store, sizeof(VarIdx));
    *((VarIdx*)&store->buffer[store->len]) = idx;
    store->len += sizeof(VarIdx);
}

uint8_t read_u8(InstrStore* store)
{
    uint8_t val = *((uint8_t*)&store->buffer[store->index]);
    store->index += sizeof(uint8_t);
    return val;
}

uint16_t read_u16(InstrStore* store)
{
    uint16_t val = *((uint16_t*)&store->buffer[store->index]);
    store->index += sizeof(uint16_t);
    return val;
}

uint32_t read_u32(InstrStore* store)
{
    uint32_t val = *((uint32_t*)&store->buffer[store->index]);
    store->index += sizeof(uint32_t);
    return val;
}

uint64_t read_u64(InstrStore* store)
{
    uint64_t val = *((uint64_t*)&store->buffer[store->index]);
    store->index += sizeof(uint64_t);
    return val;
}

int8_t read_s8(InstrStore* store)
{
    int8_t val = *((int8_t*)&store->buffer[store->index]);
    store->index += sizeof(int8_t);
    return val;
}

int16_t read_s16(InstrStore* store)
{
    int16_t val = *((int16_t*)&store->buffer[store->index]);
    store->index += sizeof(int16_t);
    return val;
}

int32_t read_s32(InstrStore* store)
{
    int32_t val = *((int32_t*)&store->buffer[store->index]);
    store->index += sizeof(int32_t);
    return val;
}

int64_t read_s64(InstrStore* store)
{
    int64_t val = *((int64_t*)&store->buffer[store->index]);
    store->index += sizeof(int64_t);
    return val;
}

Value read_value(InstrStore* store)
{
    Value val = *((Value*)&store->buffer[store->index]);
    store->index += sizeof(Value);
    return val;
}
*/

unsigned long getInstrIndex(InstrStore* store)
{
    return store->index;
}

unsigned long getInstrLen(InstrStore* store)
{
    return store->len;
}

void setInstrIndex(InstrStore* store, unsigned long idx)
{
    store->index = idx;
}

void incInstrIndex(InstrStore* store, int idx)
{
    store->index += idx;
}

bool isInstrEnded(InstrStore* store)
{
    return (store->index > store->len);
}
