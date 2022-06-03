
#include "system.h"
#include "fileIo.h"

static void initRegisters(VM* vm)
{
    memset(vm->registers, 0, sizeof(vm->registers));
}

static void load_var_store(VarStore* vs, FILE* fp)
{
    fread(&vs->len, sizeof(vs->len), 1, fp);

    vs->cap = 1;
    while(vs->cap <= vs->len)
        vs->cap <<= 1;

    vs->list = _alloc_ds_array(Variable, vs->len);
    fread(vs->list, sizeof(Variable), vs->len, fp);
}

static void load_instr_store(InstrStore* is, FILE* fp)
{
    fread(&is->len, sizeof(is->len), 1, fp);

    is->cap = 1;
    while(is->cap <= is->len)
        is->cap <<= 1;

    is->buffer = _alloc_ds_array(uint8_t, is->len);
    fread(is->buffer, sizeof(char), is->len, fp);
}

static void save_var_store(VarStore* vs, FILE* fp)
{
    fwrite(&vs->len, sizeof(vs->len), 1, fp);
    fwrite(vs->list, sizeof(Variable), vs->len, fp);
}

static void save_instr_store(InstrStore* is, FILE* fp)
{
    fwrite(&is->len, sizeof(is->len), 1, fp);
    fwrite(is->buffer, sizeof(char), is->len, fp);
}

void initVM(VM* vm)
{
    //initInstrStore(&vm->istore);
    initCallStack(&vm->cstack);
    initValStack(&vm->vstack);
    //initVarStore(&vm->vstore);
    initRegisters(vm);
}

void uninitVM(VM* vm)
{
    uninitVarStore(&vm->vstore);
    uninitValStack(&vm->vstack);
    uninitCallStack(&vm->cstack);
    uninitInstrStore(&vm->istore);
}

void loadVM(VM* vm, const char* fname)
{
    FILE* fp = fopen(fname, "r");
    if(fp == NULL) {
        fprintf(stderr, "fatal error: cannot open input file: %s\n", strerror(errno));
        exit(1);
    }

    initVM(vm);
    load_var_store(&vm->vstore, fp);
    load_instr_store(&vm->istore, fp);
    fclose(fp);
}

void saveVM(VM* vm, const char* fname)
{
    FILE* fp = fopen(fname, "w");
    if(fp == NULL) {
        fprintf(stderr, "fatal error: cannot open output file: %s\n", strerror(errno));
        exit(1);
    }

    save_var_store(&vm->vstore, fp);
    save_instr_store(&vm->istore, fp);
    uninitVM(vm);
    fclose(fp);
}


