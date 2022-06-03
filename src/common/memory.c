/**
 * @file memory.c
 * @brief The purpose of this module is to track memory to facilitate
 * serializations and garbage collection. This is not a classic heap
 * where a contiguous memory zone is allocated and then parceled out upon
 * request. Pointers are allocated in such a way as to allow the allocations
 * be added to a double-linked list for ease of removal. The new pointers are
 * always added to the end of the list. The user will access memory in the
 * normal way and pointers are returned as (void*) as one would normally
 * expect. Trying to free memory memory that was allocated by this library
 * with the system free() function will result in a memory exception.
 *
 * It is expected that the user will use the macro interface rather than to
 * use these functions directly, however, if a separate set of allocations is
 * desired then the functions can be used directly or through another macro
 * wrapper.
 */
#include "memory.h"

MemoryT* global_memory_ptr = NULL;

/**
 * @brief Simple wrapper around the system allocation routine that aborts the
 * program if the memory allocation fails.
 *
 * @param size
 * @return void*
 */
static inline void* allocate(SizeT size)
{
    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "memory allocation error: Cannot allocate %lu bytes\n", size);
        exit(1);
    }
    memset(ptr, 0, size);
    return ptr;
}

/**
 * @brief Simple wrapper around the system allocation routines that aborts the
 * program if a memory reallocation fails.
 *
 * @param optr
 * @param size
 * @return void*
 */
static inline void* reallocate(void* optr, SizeT size)
{
    void* nptr = realloc(optr, size);
    if(nptr == NULL) {
        fprintf(stderr, "memory allocation error: Cannot reallocate %lu bytes\n", size);
        exit(1);
    }
    return nptr;
}

/**
 * @brief Convert an allocated pointer to an internal allocation structure.
 *
 * @param ptr
 * @return struct alloc_block*
 */
static inline struct alloc_block* void_to_block(void* ptr)
{
    struct alloc_block* block = (struct alloc_block*)(((char*)ptr) - sizeof(struct alloc_block));
    if(block->magic != MAGIC_NUMBER) {
        fprintf(stderr, "memory allocation error: attempt to use a corrupt memory block\n");
        exit(1);
    }

    return block;
}

/**
 * @brief Convert an internal allocation block pointer to an output pointer.
 *
 * @param ptr
 * @return void*
 */
static inline void* block_to_void(struct alloc_block* ptr)
{
    return (void*)&ptr->data[0];
}

/**
 * @brief Add the size of the management struct to the allocated size.
 *
 * @param size
 * @return SizeT
 */
static inline SizeT void_size_to_alloc_size(SizeT size)
{
    return size + sizeof(struct alloc_block);
}

/**
 * @brief Create a alloc block object.
 *
 * @param size
 * @return struct alloc_block*
 */
static inline struct alloc_block* create_alloc_block(SizeT size)
{
    return allocate(void_size_to_alloc_size(size));
}

/**
 * @brief Create the data structures for the memory management.
 *
 * @return MemoryT*
 */
MemoryT* initMem()
{
    return (MemoryT*)allocate(sizeof(MemoryT));
}

/**
 * @brief Destroy the data structures for memory management.
 *
 * @param mem
 */
void uninitMem(MemoryT* mem)
{
    struct alloc_block* ptr;
    struct alloc_block* next;

    if(mem != NULL) {
        for(ptr = mem->root; ptr != NULL; ptr = next) {
            next = ptr->next;
            free(ptr);
        }
        free(mem);
    }
}

/**
 * @brief Allocate new memory and add it to the list.
 *
 * @param mem
 * @param size
 * @return void*
 */
void* allocMem(MemoryT* mem, SizeT size)
{
    struct alloc_block* block = create_alloc_block(size);
    block->size = size;
    block->magic = MAGIC_NUMBER;

    if(mem->root != NULL) {
        mem->last->next = block;
        block->prev = mem->last;
        mem->last = block;
    }
    else {
        mem->root = block;
        mem->last = block;
    }

    mem->tot_alloc += size;
    mem->crnt_alloc += size;
    mem->crnt_items ++;
    mem->tot_items ++;

    return block_to_void(block);
}

/**
 * @brief Change the size of an allocated block. If the pointer is not in
 * management then abort the program for a developer error.
 *
 * @param mem
 * @param ptr
 * @param size
 * @return void*
 */
void* reallocMem(MemoryT* mem, void* ptr, SizeT size)
{
    if(size == 0 && ptr != NULL) {
        freeMem(mem, ptr);
    }
    else if(ptr == NULL)
        return allocMem(mem, size);

    struct alloc_block* block = void_to_block(ptr);
    if(block->magic != MAGIC_NUMBER) {
        fprintf(stderr, "memory allocation error: attempt to reallocate a block that has not been allocated\n");
        exit(1);
    }
    else {
        SizeT osize = block->size;
        block->size = size;
        mem->crnt_alloc -= osize;
        mem->crnt_alloc += size;
        mem->tot_alloc += size-osize; // could be negative

        block = reallocate(block, void_size_to_alloc_size(size));

        return block_to_void(block);
    }

    return NULL; // never happens
}

/**
 * @brief Allocate a new string.
 *
 * @param mem
 * @param str
 * @return char*
 */
char* strdupMem(MemoryT* mem, const char* str)
{
    SizeT len = strlen(str)+1;
    char* sbuf = memdupMem(mem, (void*)str, len);
    return sbuf;
}

/**
 * @brief Duplicate a memory buffer. This is generally intended to allocate
 * locally defined data structures.
 *
 * @param mem
 * @param ptr
 * @param size
 * @return void*
 */
void* memdupMem(MemoryT* mem, void* ptr, SizeT size)
{
    void* nptr = allocMem(mem, size);
    memcpy(nptr, ptr, size);
    return nptr;
}

/**
 * @brief Free a block of memory that was previously allocated by this library
 * and abort the application if an attempt is made to free a corrupt memory
 * block.
 *
 * @param mem
 * @param ptr
 */
void freeMem(MemoryT* mem, void* ptr)
{
    if(ptr != NULL) {
        struct alloc_block* block = void_to_block(ptr);

        if(block == mem->root) {
            mem->root = mem->root->next;
            if(mem->root != NULL)
                mem->root->prev = NULL;
        }
        else if(block == mem->last) {
            mem->last = mem->last->prev;
            if(mem->last != NULL)
                mem->last->next = NULL;
        }
        else {
            if(block->next != NULL)
                block->next->prev = block->prev;
            if(block->prev != NULL)
                block->prev->next = block->next;
        }

        mem->tot_free += block->size;
        mem->crnt_alloc -= block->size;
        mem->crnt_items --;

        free(block);
    }
}

/**
 * @brief Print out basic information about the data that is currently allocated.
 *
 * @param mem
 */
void dumpMem(MemoryT* mem)
{
    struct alloc_block* crnt;
    struct alloc_block* next;
    int count = 0;

    printf("\n-----Dump Memory-----\n");
    for(crnt = mem->root; crnt != NULL; crnt = next)     {
        next = crnt->next;
        printf("%5d. ", count++);
        printf("ptr = %p ", crnt);
        printf("ret = %p ", &crnt->data[0]);
        printf("size = %lu ", crnt->size);
        printf("magic = 0x%08X ", crnt->magic);
        printf("next = %p ", crnt->next);
        printf("prev = %p\n", crnt->prev);
    }
    printf("\n");
    printf("   tot_alloc = %lu\n", mem->tot_alloc);
    printf("   tot_free = %lu\n", mem->tot_free);
    printf("   tot_items = %lu\n", mem->tot_items);
    printf("   crnt_alloc = %lu\n", mem->crnt_alloc);
    printf("   crnt_items = %lu\n", mem->crnt_items);
    printf("-------End Dump------\n\n");

}
