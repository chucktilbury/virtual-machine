
#include "vMachine.h"
#include "memory.h"
#include "opcodes.h"
#include "runLoop.h"
#include "traps.h"
#include "fileIo.h"


int main() {

    _initMemory();

    VM* vm = _alloc_ds(VM);
    initVM(vm);

    vm->registers[0].type = UINT32;
    vm->registers[0].data.unum32 = 0xdeadbeef;

    Value val;
    val.type = UINT8;
    val.data.unum8 = 0;
    pushValStack(&vm->vstack, val);

    WRITE_VM_OBJ(uint8_t, OP_TRAP);
    WRITE_VM_OBJ(TrapNumType, PRINTR); // trap number
    WRITE_VM_OBJ(uint8_t, OP_EXIT);

    runLoop(vm);

    uninitVM(vm);
    _free(vm);

    _destroyMemory();

    return 0;
}