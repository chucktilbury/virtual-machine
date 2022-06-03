#ifndef MEMORY_H
#define MEMORY_H

#include "system.h"

typedef unsigned long SizeT;
#define MAGIC_NUMBER    0xDEADBEEF

typedef struct __attribute__((packed)) alloc_block {
    unsigned int magic; // magic number
    SizeT size;     // Size of the original requested allocation.
    struct alloc_block* next;   // Next block in the chain.
    struct alloc_block* prev;   // Previous block in the chain.
    unsigned char data[0];      // First byte of allocated data.
}  alloc_block_t;

typedef struct {
    alloc_block_t* root;   // First allocation unit.
    alloc_block_t* last;   // Pointer to the last free block.
    SizeT tot_alloc;    // Bytes allocated for entire run
    SizeT tot_free;     // Bytes that have been freed during entire run.
    SizeT tot_items;    // Number of items that have been allocated
    SizeT crnt_alloc;   // Bytes that are currently allocated.
    SizeT crnt_items;   // Number of items that are currently allocated.
} MemoryT;

MemoryT* initMem();
void uninitMem(MemoryT* mem);

/*
 * These are not normally called directly, but through the macros given below.
 */
void* allocMem(MemoryT* mem, SizeT size);
void* reallocMem(MemoryT* mem, void* ptr, SizeT size);
char* strdupMem(MemoryT* mem, const char* str);
void* memdupMem(MemoryT* mem, void* ptr, SizeT size);
void freeMem(MemoryT* mem, void* ptr);
void dumpMem(MemoryT* mem);

extern MemoryT* global_memory_ptr;

/*
 * This is the normal interface.
 */
#define _initMemory()   do { global_memory_ptr = initMem(); } while(0)
#define _destroyMemory()  do{ uninitMem(global_memory_ptr); } while(0)
#define _dumpMemory() do { dumpMem(global_memory_ptr); } while(0)

#define _alloc(s)   allocMem(global_memory_ptr, (s))
#define _alloc_ds(t) (t*)allocMem(global_memory_ptr, sizeof(t))
#define _alloc_ds_array(t, n) (t*)allocMem(global_memory_ptr, sizeof(t)*(n))

#define _alloc_str(s) strdupMem(global_memory_ptr, (s))

#define _realloc(p, s) reallocMem(global_memory_ptr, (p), (s))
#define _realloc_ds(p, t) (t*)reallocMem(global_memory_ptr, (p), sizeof(t))
#define _realloc_ds_array(p, t, n) (t*)reallocMem(global_memory_ptr, (p), sizeof(t)*(n))

#define _memdup(p, s) memdupMem(global_memory_ptr, (p), (s))
#define _memdup_ds(p, t) (t*)memdupMem(global_memory_ptr, (p), sizeof(t))
#define _memdup_ds_array(p, t, n) (t*)memdupMem(global_memory_ptr, (p), sizeof(t)*(n))

#define _free(p) freeMem(global_memory_ptr, (p))

#endif