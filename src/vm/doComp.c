
#include "doComp.h"
#include "errors.h"
#include "registers.h"

#define __operation(vm, op, left, right) do { \
        switch(RTYPE(left)) { \
            case UINT8: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_UINT8(left) op AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = ((uint16_t)AS_UINT8(left) op AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = ((uint32_t)AS_UINT8(left) op AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = ((uint64_t)AS_UINT8(left) op AS_UINT64(right)); break; \
                    case INT8: NZFLAG = ((int8_t)AS_UINT8(left) op AS_INT8(right)); break; \
                    case INT16: NZFLAG = ((int16_t)AS_UINT8(left) op AS_INT16(right)); break; \
                    case INT32: NZFLAG = ((int32_t)AS_UINT8(left) op AS_INT32(right)); break; \
                    case INT64: NZFLAG = ((int64_t)AS_UINT8(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_UINT8(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_UINT8(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_UINT8(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_UINT8(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case UINT16: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_UINT16(left) op (uint16_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_UINT16(left) op AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = ((uint32_t)AS_UINT16(left) op AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = ((uint64_t)AS_UINT16(left) op AS_UINT64(right)); break; \
                    case INT8: NZFLAG = ((int16_t)AS_UINT16(left) op (int16_t)AS_INT8(right)); break; \
                    case INT16: NZFLAG = ((int16_t)AS_UINT16(left) op AS_INT16(right)); break; \
                    case INT32: NZFLAG = ((int32_t)AS_UINT16(left) op AS_INT32(right)); break; \
                    case INT64: NZFLAG = ((int64_t)AS_UINT16(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_UINT16(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_UINT16(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_UINT16(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = (AS_UINT16(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case UINT32: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_UINT32(left) op (uint32_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_UINT32(left) op (uint32_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_UINT32(left) op AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = ((uint64_t)AS_UINT32(left) op AS_UINT64(right)); break; \
                    case INT8: NZFLAG = ((int32_t)AS_UINT32(left) op (int32_t)AS_INT8(right)); break; \
                    case INT16: NZFLAG = ((int32_t)AS_UINT32(left) op (int32_t)AS_INT16(right)); break; \
                    case INT32: NZFLAG = ((int32_t)AS_UINT32(left) op AS_INT32(right)); break; \
                    case INT64: NZFLAG = ((int64_t)AS_UINT32(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_UINT32(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_UINT32(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = (AS_UINT32(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_UINT32(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case UINT64: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_UINT64(left) op (uint64_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_UINT64(left) op (uint64_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_UINT64(left) op (uint64_t)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_UINT64(left) op AS_UINT64(right)); break; \
                    case INT8: NZFLAG = ((int64_t)AS_UINT64(left) op (int64_t)AS_INT8(right)); break; \
                    case INT16: NZFLAG = ((int64_t)AS_UINT64(left) op (int64_t)AS_INT16(right)); break; \
                    case INT32: NZFLAG = ((int64_t)AS_UINT64(left) op (int64_t)AS_INT32(right)); break; \
                    case INT64: NZFLAG = ((int64_t)AS_UINT64(left) op (int64_t)AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_UINT64(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_UINT64(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_UINT64(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_UINT64(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case INT8: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_INT8(left) op (int8_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = ((int16_t)AS_INT8(left) op (int16_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = ((int32_t)AS_INT8(left) op (int32_t)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = ((int64_t)AS_INT8(left) op (int64_t)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_INT8(left) op AS_INT8(right)); break; \
                    case INT16: NZFLAG = ((int16_t)AS_INT8(left) op AS_INT16(right)); break; \
                    case INT32: NZFLAG = ((int32_t)AS_INT8(left) op AS_INT32(right)); break; \
                    case INT64: NZFLAG = ((int64_t)AS_INT8(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_INT8(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_INT8(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_INT8(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_INT8(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case INT16: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_INT16(left) op (int16_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_INT16(left) op (int16_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_INT16(left) op (int32_t)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_INT16(left) op (int64_t)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_INT16(left) op AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_INT16(left) op AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_INT16(left) op AS_INT32(right)); break; \
                    case INT64: NZFLAG = (AS_INT16(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_INT16(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_INT16(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_INT16(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_INT16(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case INT32: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_INT32(left) op (int32_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_INT32(left) op (int32_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_INT32(left) op (int32_t)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_INT32(left) op (int32_t)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_INT32(left) op (int32_t)AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_INT32(left) op (int32_t)AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_INT32(left) op AS_INT32(right)); break; \
                    case INT64: NZFLAG = ((int64_t)AS_INT32(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_INT32(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_INT32(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_INT32(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_INT32(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case INT64: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_INT64(left) op (int64_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_INT64(left) op (int64_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_INT64(left) op (int64_t)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_INT64(left) op (int64_t)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_INT64(left) op (int64_t)AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_INT64(left) op (int64_t)AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_INT64(left) op (int64_t)AS_INT32(right)); break; \
                    case INT64: NZFLAG = (AS_INT64(left) op AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = ((float)AS_INT64(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_INT64(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: NZFLAG = ((uint32_t)AS_INT64(left) op AS_ADDR(right)); break; \
                    case BOOL: NZFLAG = ((bool)AS_INT32(left) op AS_BOOL(right)); break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case FLOAT: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_FLOAT(left) op (float)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_FLOAT(left) op (float)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_FLOAT(left) op (float)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_FLOAT(left) op (float)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_FLOAT(left) op (float)AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_FLOAT(left) op (float)AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_FLOAT(left) op (float)AS_INT32(right)); break; \
                    case INT64: NZFLAG = (AS_FLOAT(left) op (float)AS_INT64(right)); break; \
                    case FLOAT: NZFLAG = (AS_FLOAT(left) op AS_FLOAT(right)); break; \
                    case DOUBLE: NZFLAG = ((double)AS_FLOAT(left) op AS_DOUBLE(right)); break; \
                    case ADDRESS: \
                    case BOOL: \
                        runtimeError("comparing %s to %s makes no sense", TTS(left), TTS(right)); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case DOUBLE: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_DOUBLE(left) op (double)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_DOUBLE(left) op (double)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_DOUBLE(left) op (double)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_DOUBLE(left) op (double)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_DOUBLE(left) op (double)AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_DOUBLE(left) op (double)AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_DOUBLE(left) op (double)AS_INT32(right)); break; \
                    case INT64: NZFLAG = (AS_DOUBLE(left) op (double)AS_INT64(right)); break; \
                    case DOUBLE: NZFLAG = (AS_DOUBLE(left) op (double)AS_DOUBLE(right)); break; \
                    case FLOAT: NZFLAG = (AS_DOUBLE(left) op (double)AS_FLOAT(right)); break; \
                    case ADDRESS: \
                    case BOOL: \
                        runtimeError("comparing %s to %s makes no sense", TTS(left), TTS(right)); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case ADDRESS: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_ADDR(left) op AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_ADDR(left) op AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_INT32(right)); break; \
                    case INT64: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_INT64(right)); break; \
                    case ADDRESS: NZFLAG = (AS_ADDR(left) op (uint32_t)AS_ADDR(right)); break; \
                    case FLOAT: \
                    case DOUBLE: \
                    case BOOL: \
                        runtimeError("comparing %s to %s makes no sense", TTS(left), TTS(right)); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case BOOL: \
                switch(RTYPE(right)) { \
                    case UINT8: NZFLAG = (AS_BOOL(left) op (bool)AS_UINT8(right)); break; \
                    case UINT16: NZFLAG = (AS_BOOL(left) op (bool)AS_UINT16(right)); break; \
                    case UINT32: NZFLAG = (AS_BOOL(left) op (bool)AS_UINT32(right)); break; \
                    case UINT64: NZFLAG = (AS_BOOL(left) op (bool)AS_UINT64(right)); break; \
                    case INT8: NZFLAG = (AS_BOOL(left) op (bool)AS_INT8(right)); break; \
                    case INT16: NZFLAG = (AS_BOOL(left) op (bool)AS_INT16(right)); break; \
                    case INT32: NZFLAG = (AS_BOOL(left) op (bool)AS_INT32(right)); break; \
                    case INT64: NZFLAG = (AS_BOOL(left) op (bool)AS_INT64(right)); break; \
                    case FLOAT: \
                    case DOUBLE: \
                    case ADDRESS: \
                    case BOOL: \
                        runtimeError("comparing %s to %s makes no sense", TTS(left), TTS(right)); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("deferred %s operation on right %s", #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                        runtimeError("invalid %s operation on right %s", #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid operand type on right: 0x%0X", RTYPE(right)); \
                } \
                break; \
            case STRING: \
            case DICT: \
            case LIST: \
            case USRTYPE: \
                runtimeWarning("deferred %s operation on left %s", #op, TTS(left)); \
                break; \
            case ERROR: \
            case NOTHING: \
                runtimeError("invalid %s operation on left %s", #op, TTS(left)); \
                break; \
            default: \
                fatalError("invalid operand type on left: 0x%0X", RTYPE(right)); \
        } \
    } while(0)

void doNot(VM* vm, uint8_t regs)
{
    int r = regs & 0x0F;
    switch(RTYPE(r)) {
        case UINT8: NZFLAG = (AS_UINT8(r) != 0); break;
        case UINT16: NZFLAG = (AS_UINT16(r) != 0); break;
        case UINT32: NZFLAG = (AS_UINT32(r) != 0); break;
        case UINT64: NZFLAG = (AS_UINT64(r) != 0); break;
        case INT8: NZFLAG = (AS_INT8(r) != 0); break;
        case INT16: NZFLAG = (AS_INT16(r) != 0); break;
        case INT32: NZFLAG = (AS_INT32(r) != 0); break;
        case INT64: NZFLAG = (AS_INT64(r) != 0); break;
        case FLOAT: NZFLAG = (AS_FLOAT(r) != 0); break;
        case DOUBLE: NZFLAG = (AS_DOUBLE(r) != 0); break;
        case BOOL: NZFLAG = (AS_BOOL(r) != 0); break;
        case ADDRESS: NZFLAG = (AS_ADDR(r) != 0); break;

        case STRING:
        case DICT:
        case LIST:
        case USRTYPE:
            runtimeWarning("deferred boolean operation on %s", TTS(r));
            break;

        case ERROR:
        case NOTHING:
            runtimeError("invalid boolean operation on %s", TTS(r));
            break;

        default:
            fatalError("invalid operand type: 0x%02X", RTYPE(r));
            break;
    }
}

void doEq(VM* vm, uint8_t regs)
{
    int left = (regs >> 4) & 0x0F,
        right = regs & 0x0F;
    __operation(vm, ==, left, right);
}

void doNEq(VM* vm, uint8_t regs)
{
    int left = (regs >> 4) & 0x0F,
        right = regs & 0x0F;
    __operation(vm, !=, left, right);
}

void doLeq(VM* vm, uint8_t regs)
{
    int left = (regs >> 4) & 0x0F,
        right = regs & 0x0F;
    __operation(vm, <=, left, right);
}

void doGeq(VM* vm, uint8_t regs)
{
    int left = (regs >> 4) & 0x0F,
        right = regs & 0x0F;
    __operation(vm, >=, left, right);
}

void doLess(VM* vm, uint8_t regs)
{
    int left = (regs >> 4) & 0x0F,
        right = regs & 0x0F;
    __operation(vm, <, left, right);
}

void doGtr(VM* vm, uint8_t regs)
{
    int left = (regs >> 4) & 0x0F,
        right = regs & 0x0F;
    __operation(vm, >, left, right);
}
