/**
 * @file traps.c
 * @brief Traps are the interface into the outside world. When a trap is
 * executed, there is a trap number that corresponds to the actual function
 * that will be entered when the trap is executed. The parameters of the
 * function can be set up any way that the developer wants, and there are no
 * restrictions on what can be accessed by a trap function. That having been
 * said, there is little error checking on trap calls. If the person writing
 * the assembly does it wrong, bad things are guaranteed to happen. Therefore,
 * traps should be used carefully and mindful of the documentation.
 *
 */
#include "vMachine.h"
#include "traps.h"

static void print_value(VM* vm)
{
    printVal(popValStack(&vm->vstack));
}

static void print_register(VM* vm)
{
// TODO: typecheck this
    //uint8_t reg;
    //READ_VM_OBJ(uint8_t, reg);
    Value val = popValStack(&vm->vstack);
    printVal(vm->registers[val.data.unum8]);
}

static void print_immediate(VM* vm)
{
    Value val;
    READ_VM_OBJ(Value, val);
    printVal(val);
}

void doTrap(VM* vm, TrapNumType tno)
{
    switch(tno) {
        case PRINTV:
            print_value(vm);
            break;
        case PRINTR:
            print_register(vm);
            break;
        case PRINTI:
            print_immediate(vm);
            break;
        default:
            fprintf(stderr, "fatal error: unknown trap number encountered: %d", tno);
            exit(1);
    }
}