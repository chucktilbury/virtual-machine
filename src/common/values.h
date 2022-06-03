#ifndef VALUES_H
#define VALUES_H

#include "system.h"

typedef enum {
    ERROR,      // union data is undefined
    NOTHING,    // union data is undefined
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT,
    DOUBLE,
    BOOL,
    ADDRESS,
    STRING,
    DICT,
    LIST,
    USRTYPE,
    DEFER, // used in the tables to mark deferred transformations
    EXTERN, // external function defined in external code
} ValType;

// use shallow copy, rather than heap allocation
typedef struct {
    ValType type;
    bool isConst;
    union {
        uint8_t unum8;
        uint16_t unum16;
        uint32_t unum32;
        uint64_t unum64;
        int8_t snum8;
        int16_t snum16;
        int32_t snum32;
        int64_t snum64;
        float fnum;
        double dnum;
        bool boolean;
        uint32_t addr;
        // these are indexes into their respective stores...
        int str;
        int dict;
        int list;
        int usrtype;
    } data;
} __attribute__((packed)) Value;


// Convert the type to a string for debugging and error generation.
const char* valTypeToStr(ValType type);
void printVal(Value val);

#endif

#if 0
// These getters and setters are not strictly required
void setValType(Value value, ValType type);
ValType getValType(Value value);

void setValConst(Value value, bool state);
bool getValConst(Value value);


void setValUnum8(Value value, uint8_t val);
void setValUnum16(Value value, uint16_t val);
void setValUnum32(Value value, uint32_t val);
void setValUnum64(Value value, uint64_t val);
void setValSnum8(Value value, int8_t val);
void setValSnum16(Value value, int16_t val);
void setValSnum32(Value value, int32_t val);
void setValSnum64(Value value, int64_t val);
void setValFnum(Value value, float val);
void setValDnum(Value value, double val);
void setValBool(Value value, bool val);
void setValAddr(Value value, uint32_t val);
void setValStr(Value value, int val);
void setValDict(Value value, int val);
void setValList(Value value, int val);
void setValUsrtype(Value value, int val);

uint8_t getValUnum8(Value value);
uint16_t getValUnum16(Value value);
uint32_t getValUnum32(Value value);
uint64_t getValUnum64(Value value);
int8_t getValSnum8(Value value);
int16_t getValSnum16(Value value);
int32_t getValSnum32(Value value);
int64_t getValSnum64(Value value);
float getValFnum(Value value);
double getValDnum(Value value);
bool getValBool(Value value);
uint32_t getValAddr(Value value);
int getValStr(Value value);
int getValDict(Value value);
int getValList(Value value);
int getValUsrtype(Value value);

// Tables that help detect errors and implement type rule system.
ValType getPromotionResult(ValType to, ValType from);
ValType getArithResultType(ValType left, ValType right);
ValType getCompResultType(ValType left, ValType right);


// Arithmetic and comparison factory macros.
#define PromoteValue(dest, to, from) do { \
    } while(0)

#define ArithValue(dest, left, right, oper) do { \
    } while(0)

#define CompValue(dest, left, right, oper) do { \
    } while(0)
#endif

