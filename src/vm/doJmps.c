
#include "doJmps.h"
#include "errors.h"

/**
 * @brief A call has stack elements expected. The address is delivered in
 * various ways, given by the instruction type, but in addition to that, the
 * function parameters are required to execute a call. The TOS will be the
 * number of function args that are on the stack. That number is then used to
 * allocate the array of elements, which is then popped and store in the
 * array. When the code that has been called is entered, the stack is neutral
 * with no data that is relevant to the call.
 *
 * @param vm
 * @param val
 */
void doCall(VM* vm, Value val)
{
    int idx;

    switch(val.type) {
        case ADDRESS:   idx = (int)val.data.addr;   break;

        case UINT8:
        case UINT16:
        case UINT32:
        case UINT64:
        case INT8:
        case INT16:
        case INT32:
        case INT64:
        case ERROR:
        case NOTHING:
        case FLOAT:
        case DOUBLE:
        case BOOL:
        case STRING:
        case DICT:
        case LIST:
        case USRTYPE:
            runtimeError("cannot use type %s as a call address", valTypeToStr(val.type));
            break;
        default:
            fatalError("invalid address type encountered: 0x%02X", val.type);
    }

    CallStackElem call;
    call.ret_addr = getInstrIndex(&vm->istore);
    call.arity = popValStack(&vm->vstack);

    if(call.arity.type != UINT8)
        fatalError("invalid call arity type: %s", valTypeToStr(call.arity.type));

    uint8_t num = call.arity.data.unum8;
    call.parameters = _alloc_ds_array(Value, num);
    for(int i = 0; i < (int)num; i++) {
        call.parameters[i] = popValStack(&vm->vstack);
    }

    pushCallStack(&vm->cstack, call);
    setInstrIndex(&vm->istore, idx);
}

void doRCall(VM* vm, Value val)
{
    int idx;

    switch(val.type) {
        case UINT8:     idx = (int)val.data.unum8;  break;
        case UINT16:    idx = (int)val.data.unum16; break;
        case UINT32:    idx = (int)val.data.unum32; break;
        case UINT64:    idx = (int)val.data.unum64; break;
        case INT8:      idx = (int)val.data.snum8;  break;
        case INT16:     idx = (int)val.data.snum16; break;
        case INT32:     idx = (int)val.data.snum32; break;
        case INT64:     idx = (int)val.data.snum64; break;
        case ADDRESS:   idx = (int)val.data.addr;   break;

        case ERROR:
        case NOTHING:
        case FLOAT:
        case DOUBLE:
        case BOOL:
        case STRING:
        case DICT:
        case LIST:
        case USRTYPE:
            runtimeError("cannot use type %s as a call address offset", valTypeToStr(val.type));
            break;
        default:
            fatalError("invalid address type encountered: 0x%02X", val.type);
    }

    CallStackElem call;
    call.ret_addr = getInstrIndex(&vm->istore);
    call.arity = popValStack(&vm->vstack);

    if(call.arity.type != UINT8)
        fatalError("invalid call arity type: %s", valTypeToStr(call.arity.type));

    uint8_t num = call.arity.data.unum8;
    call.parameters = _alloc_ds_array(Value, num);
    for(int i = 0; i < (int)num; i++) {
        call.parameters[i] = popValStack(&vm->vstack);
    }

    pushCallStack(&vm->cstack, call);
    incInstrIndex(&vm->istore, idx);
}

void doJmp(VM* vm, Value val)
{
    int idx;

    switch(val.type) {
        case ADDRESS:   idx = (int)val.data.addr;   break;

        case UINT8:
        case UINT16:
        case UINT32:
        case UINT64:
        case INT8:
        case INT16:
        case INT32:
        case INT64:
        case ERROR:
        case NOTHING:
        case FLOAT:
        case DOUBLE:
        case BOOL:
        case STRING:
        case DICT:
        case LIST:
        case USRTYPE:
            runtimeError("cannot use type %s as a jmp address", valTypeToStr(val.type));
            break;
        default:
            fatalError("invalid address type encountered: 0x%02X", val.type);
    }

    setInstrIndex(&vm->istore, idx);
}

void doRJmp(VM* vm, Value val)
{
    int idx;

    switch(val.type) {
        case UINT8:     idx = (int)val.data.unum8;  break;
        case UINT16:    idx = (int)val.data.unum16; break;
        case UINT32:    idx = (int)val.data.unum32; break;
        case UINT64:    idx = (int)val.data.unum64; break;
        case INT8:      idx = (int)val.data.snum8;  break;
        case INT16:     idx = (int)val.data.snum16; break;
        case INT32:     idx = (int)val.data.snum32; break;
        case INT64:     idx = (int)val.data.snum64; break;
        case ADDRESS:   idx = (int)val.data.addr;   break;

        case ERROR:
        case NOTHING:
        case FLOAT:
        case DOUBLE:
        case BOOL:
        case STRING:
        case DICT:
        case LIST:
        case USRTYPE:
            runtimeError("cannot use type %s as a call address offset", valTypeToStr(val.type));
            break;
        default:
            fatalError("invalid address type encountered: 0x%02X", val.type);
    }

    incInstrIndex(&vm->istore, idx);
}

void doBr(VM* vm, Value val)
{
    if(vm->nzero) {
        int idx;

        switch(val.type) {
            case ADDRESS:   idx = (int)val.data.addr;   break;

            case UINT8:
            case UINT16:
            case UINT32:
            case UINT64:
            case INT8:
            case INT16:
            case INT32:
            case INT64:
            case ERROR:
            case NOTHING:
            case FLOAT:
            case DOUBLE:
            case BOOL:
            case STRING:
            case DICT:
            case LIST:
            case USRTYPE:
                runtimeError("cannot use type %s as a jmp address", valTypeToStr(val.type));
                break;
            default:
                fatalError("invalid address type encountered: 0x%02X", val.type);
        }

        setInstrIndex(&vm->istore, idx);
    }
}

void doRBr(VM* vm, Value val)
{
    if(vm->nzero) {
        int idx;

        switch(val.type) {
            case UINT8:     idx = (int)val.data.unum8;  break;
            case UINT16:    idx = (int)val.data.unum16; break;
            case UINT32:    idx = (int)val.data.unum32; break;
            case UINT64:    idx = (int)val.data.unum64; break;
            case INT8:      idx = (int)val.data.snum8;  break;
            case INT16:     idx = (int)val.data.snum16; break;
            case INT32:     idx = (int)val.data.snum32; break;
            case INT64:     idx = (int)val.data.snum64; break;
            case ADDRESS:   idx = (int)val.data.addr;   break;

            case ERROR:
            case NOTHING:
            case FLOAT:
            case DOUBLE:
            case BOOL:
            case STRING:
            case DICT:
            case LIST:
            case USRTYPE:
                runtimeError("cannot use type %s as a call address offset", valTypeToStr(val.type));
                break;
            default:
                fatalError("invalid address type encountered: 0x%02X", val.type);
        }

        incInstrIndex(&vm->istore, idx);
    }
}

void doReturn(VM* vm)
{
    CallStackElem cse = popCallStack(&vm->cstack);
    _free(cse.parameters);
    setInstrIndex(&vm->istore, cse.ret_addr);
}

