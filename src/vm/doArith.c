
#include <math.h>
#include "doArith.h"
#include "errors.h"
#include "registers.h"

#define _verify(v) do { \
    switch(RTYPE(v)) { \
        case UINT8: \
            if(AS_UINT8(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case UINT16: \
            if(AS_UINT16(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case UINT32: \
            if(AS_UINT32(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case UINT64: \
            if(AS_UINT64(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case INT8: \
            if(AS_INT8(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case INT16: \
            if(AS_INT16(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case INT32: \
            if(AS_INT32(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case INT64: \
            if(AS_INT64(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case FLOAT: \
            if(AS_FLOAT(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        case DOUBLE: \
            if(AS_DOUBLE(v) == 0) \
                runtimeError("divide by zero error"); \
            break; \
        default: \
            break; \
    } \
} while(0)

//static inline void operation(VM* vm, const char* op, uint8_t dest, uint8_t left, uint8_t right)
#define _operation(vm, op, dest, left, right) do { \
    switch(RTYPE(left)) { \
        case UINT8: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = UINT8; \
                        AS_UINT8(dest) = AS_UINT8(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = UINT16; \
                        AS_UINT16(dest) = AS_UINT8(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = UINT32; \
                        AS_UINT32(dest) = AS_UINT8(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT8(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT8; \
                        AS_INT8(dest) = AS_UINT8(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_UINT8(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_UINT8(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT8(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_UINT8(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_UINT8(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_UINT8(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case UINT16: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = UINT16; \
                        AS_UINT16(dest) = AS_UINT16(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = UINT16; \
                        AS_UINT16(dest) = AS_UINT16(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = UINT32; \
                        AS_UINT32(dest) = AS_UINT16(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT16(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_UINT16(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_UINT16(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_UINT16(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT16(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_UINT16(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_UINT16(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_UINT8(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case UINT32: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = UINT32; \
                        AS_UINT32(dest) = AS_UINT32(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = UINT32; \
                        AS_UINT32(dest) = AS_UINT32(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = UINT32; \
                        AS_UINT32(dest) = AS_UINT32(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT32(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_UINT32(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_UINT32(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_UINT32(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT32(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_UINT32(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_UINT32(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_UINT32(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case UINT64: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT64(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT64(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT64(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = UINT64; \
                        AS_UINT64(dest) = AS_UINT64(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT64(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT64(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT64(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_UINT64(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_UINT64(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_UINT64(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_UINT64(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case INT8: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = INT8; \
                        AS_INT8(dest) = AS_INT8(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT8(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT8(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT8(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT8; \
                        AS_INT8(dest) = AS_INT8(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT8(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT8(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT8(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_INT8(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_INT8(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_INT8(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case INT16: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT16(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT16(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT16(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT16(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT16(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT16(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT16(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT16(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_INT16(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_INT16(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_INT16(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case INT32: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT32(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT32(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT32(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT32(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT8; \
                        AS_INT8(dest) = AS_INT32(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT16; \
                        AS_INT16(dest) = AS_INT32(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT32; \
                        AS_INT32(dest) = AS_INT32(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT32(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_INT32(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_INT32(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_INT32(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case INT64: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = INT64; \
                        AS_INT64(dest) = AS_INT64(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_INT64(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_INT64(left) op AS_DOUBLE(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_INT64(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case FLOAT: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = FLOAT; \
                        AS_FLOAT(dest) = AS_FLOAT(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_FLOAT(left) op AS_DOUBLE(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ADDRESS: \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case DOUBLE: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_INT64(right); \
                        break; \
                    case FLOAT: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_DOUBLE(left) op AS_FLOAT(right); \
                        break; \
                    case DOUBLE: \
                        RTYPE(dest) = DOUBLE; \
                        AS_DOUBLE(dest) = AS_UINT8(left) op AS_DOUBLE(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case ADDRESS: \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case ADDRESS: { \
                switch(RTYPE(right)) { \
                    case UINT8: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_UINT8(right); \
                        break; \
                    case UINT16: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_UINT16(right); \
                        break; \
                    case UINT32: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_UINT32(right); \
                        break; \
                    case UINT64: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_UINT64(right); \
                        break; \
                    case INT8: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_INT8(right); \
                        break; \
                    case INT16: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_INT16(right); \
                        break; \
                    case INT32: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_INT32(right); \
                        break; \
                    case INT64: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_INT64(right); \
                        break; \
                    case ADDRESS: \
                        RTYPE(dest) = ADDRESS; \
                        AS_ADDR(dest) = AS_ADDR(left) op AS_ADDR(right); \
                        break; \
                    case STRING: \
                    case DICT: \
                    case LIST: \
                    case USRTYPE: \
                        runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
                        break; \
                    case FLOAT: \
                    case DOUBLE: \
                    case ERROR: \
                    case NOTHING: \
                    case BOOL: \
                        runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
                        break; \
                    default: \
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
                        break; \
                } \
            } \
            break; \
        case STRING: \
        case DICT: \
        case LIST: \
        case USRTYPE: \
            runtimeWarning("defer operation for %s %s %s\n", TTS(left), #op, TTS(right)); \
            break; \
        case ERROR: \
        case NOTHING: \
        case BOOL: \
            runtimeError("operation on %s %s %s is invalid\n", TTS(left), #op, TTS(right)); \
            break; \
        default: \
            fatalError("invalid right hand type: 0x%02X", RTYPE(right)); \
            break; \
    } \
} while(0)

void doNeg(VM* vm, uint8_t regs)
{
    int dest = (regs >> 4) & 0x0F,
        src = regs & 0x0F;

    switch(RTYPE(src)) {
        case UINT8:
            RTYPE(dest) = INT8;
            AS_INT8(dest) = - AS_UINT8(src);
            break;
        case UINT16:
            RTYPE(dest) = INT16;
            AS_INT16(dest) = - AS_UINT16(src);
            break;
        case UINT32:
            RTYPE(dest) = INT32;
            AS_INT32(dest) = - AS_UINT32(src);
            break;
        case UINT64:
            RTYPE(dest) = INT64;
            AS_INT64(dest) = - AS_UINT64(src);
            break;
        case INT8:
            RTYPE(dest) = INT8;
            AS_INT8(dest) = - AS_INT8(src);
            break;
        case INT16:
            RTYPE(dest) = INT16;
            AS_INT16(dest) = - AS_INT16(src);
            break;
        case INT32:
            RTYPE(dest) = INT32;
            AS_INT32(dest) = - AS_INT32(src);
            break;
        case INT64:
            RTYPE(dest) = INT64;
            AS_INT64(dest) = - AS_INT64(src);
            break;
        case FLOAT:
            RTYPE(dest) = FLOAT;
            AS_FLOAT(dest) = - AS_FLOAT(src);
            break;
        case DOUBLE:
            RTYPE(dest) = DOUBLE;
            AS_DOUBLE(dest) = - AS_DOUBLE(src);
            break;
        case BOOL:
            RTYPE(dest) = BOOL;
            AS_BOOL(dest) = AS_BOOL(src)? false: true;
            break;
        case DICT:
        case LIST:
        case USRTYPE:
        case ERROR:
        case NOTHING:
        case STRING:
        case ADDRESS:
            break;
        default:
            break;
    }
}

void doAdd(VM* vm, uint16_t regs)
{
    int dest = (regs >> 8) & 0x0F,
        left = (regs >> 4) & 0x0F,
        right = regs & 0x0f;

    _operation(vm, +, dest, left, right);
}

void doSub(VM* vm, uint16_t regs)
{
    int dest = (regs >> 8) & 0x0F,
        left = (regs >> 4) & 0x0F,
        right = regs & 0x0f;

    _operation(vm, -, dest, left, right);
}

void doMul(VM* vm, uint16_t regs)
{
    int dest = (regs >> 8) & 0x0F,
        left = (regs >> 4) & 0x0F,
        right = regs & 0x0f;

    _operation(vm, *, dest, left, right);
}

void doDiv(VM* vm, uint16_t regs)
{
    int dest = (regs >> 8) & 0x0F,
        left = (regs >> 4) & 0x0F,
        right = regs & 0x0f;

    _verify(right);
    _operation(vm, /, dest, left, right);
}

void doMod(VM* vm, uint16_t regs)
{
    int dest = (regs >> 8) & 0x0F,
        left = (regs >> 4) & 0x0F,
        right = regs & 0x0f;

    _verify(right);

    switch(RTYPE(left)) {
        case UINT8: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = UINT8;
                        AS_UINT8(dest) = AS_UINT8(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = UINT16;
                        AS_UINT16(dest) = AS_UINT8(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = UINT32;
                        AS_UINT32(dest) = AS_UINT8(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT8(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT8;
                        AS_INT8(dest) = AS_UINT8(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_UINT8(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_UINT8(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT8(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_UINT8(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_UINT8(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_UINT8(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case UINT16: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = UINT16;
                        AS_UINT16(dest) = AS_UINT16(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = UINT16;
                        AS_UINT16(dest) = AS_UINT16(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = UINT32;
                        AS_UINT32(dest) = AS_UINT16(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT16(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_UINT16(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_UINT16(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_UINT16(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT16(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_UINT16(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_UINT16(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_UINT8(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case UINT32: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = UINT32;
                        AS_UINT32(dest) = AS_UINT32(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = UINT32;
                        AS_UINT32(dest) = AS_UINT32(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = UINT32;
                        AS_UINT32(dest) = AS_UINT32(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT32(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_UINT32(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_UINT32(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_UINT32(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT32(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_UINT32(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_UINT32(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_UINT32(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case UINT64: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT64(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT64(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT64(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = UINT64;
                        AS_UINT64(dest) = AS_UINT64(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT64(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT64(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT64(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_UINT64(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_UINT64(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_UINT64(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_UINT64(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case INT8: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = INT8;
                        AS_INT8(dest) = AS_INT8(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT8(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT8(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT8(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT8;
                        AS_INT8(dest) = AS_INT8(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT8(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT8(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT8(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_INT8(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_INT8(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_INT8(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case INT16: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT16(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT16(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT16(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT16(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT16(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT16(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT16(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT16(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_INT16(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_INT16(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_INT16(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case INT32: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT32(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT32(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT32(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT32(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT8;
                        AS_INT8(dest) = AS_INT32(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT16;
                        AS_INT16(dest) = AS_INT32(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT32;
                        AS_INT32(dest) = AS_INT32(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT32(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_INT32(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_INT32(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_INT32(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case INT64: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = INT64;
                        AS_INT64(dest) = AS_INT64(left) % AS_INT64(right);
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_INT64(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_INT64(left), AS_DOUBLE(right));
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_INT64(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case FLOAT: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_UINT8(right));
                        break;
                    case UINT16:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_UINT16(right));
                        break;
                    case UINT32:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_UINT32(right));
                        break;
                    case UINT64:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_UINT64(right));
                        break;
                    case INT8:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_INT8(right));
                        break;
                    case INT16:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_INT16(right));
                        break;
                    case INT32:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_INT32(right));
                        break;
                    case INT64:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_INT64(right));
                        break;
                    case FLOAT:
                        RTYPE(dest) = FLOAT;
                        AS_FLOAT(dest) = fmodf((float)AS_FLOAT(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmodf((float)AS_FLOAT(left), AS_DOUBLE(right));
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ADDRESS:
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case DOUBLE: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_UINT8(right));
                        break;
                    case UINT16:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_UINT16(right));
                        break;
                    case UINT32:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_UINT32(right));
                        break;
                    case UINT64:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_UINT64(right));
                        break;
                    case INT8:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_INT8(right));
                        break;
                    case INT16:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_INT16(right));
                        break;
                    case INT32:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_INT32(right));
                        break;
                    case INT64:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_INT64(right));
                        break;
                    case FLOAT:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_DOUBLE(left), AS_FLOAT(right));
                        break;
                    case DOUBLE:
                        RTYPE(dest) = DOUBLE;
                        AS_DOUBLE(dest) = fmod((double)AS_UINT8(left), AS_DOUBLE(right));
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case ADDRESS:
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case ADDRESS: {
                switch(RTYPE(right)) {
                    case UINT8:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_UINT8(right);
                        break;
                    case UINT16:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_UINT16(right);
                        break;
                    case UINT32:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_UINT32(right);
                        break;
                    case UINT64:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_UINT64(right);
                        break;
                    case INT8:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_INT8(right);
                        break;
                    case INT16:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_INT16(right);
                        break;
                    case INT32:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_INT32(right);
                        break;
                    case INT64:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_INT64(right);
                        break;
                    case ADDRESS:
                        RTYPE(dest) = ADDRESS;
                        AS_ADDR(dest) = AS_ADDR(left) % AS_ADDR(right);
                        break;
                    case STRING:
                    case DICT:
                    case LIST:
                    case USRTYPE:
                        runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
                        break;
                    case FLOAT:
                    case DOUBLE:
                    case ERROR:
                    case NOTHING:
                    case BOOL:
                        runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
                        break;
                    default:
                        fatalError("invalid right hand type: 0x%02X", RTYPE(right));
                        break;
                }
            }
            break;
        case STRING:
        case DICT:
        case LIST:
        case USRTYPE:
            runtimeWarning("defer operation for %s %% %s\n", TTS(left), TTS(right));
            break;
        case ERROR:
        case NOTHING:
        case BOOL:
            runtimeError("operation on %s %% %s is invalid\n", TTS(left), TTS(right));
            break;
        default:
            fatalError("invalid right hand type: 0x%02X", RTYPE(right));
            break;
    }
}
