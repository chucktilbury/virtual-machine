
#include "valStack.h"
#include "memory.h"

void initValStack(ValStack* store)
{
    store->cap = 0x01 << 1;
    store->len = 0;

    if(store->list != NULL)
        _free(store->list);

    store->list = _alloc_ds_array(Value, store->cap);
}

void uninitValStack(ValStack* store)
{
    if(store->list != NULL)
        _free(store->list);
}

void pushValStack(ValStack* store, Value value)
{
    if(store->cap < store->len+1) {
        store->cap <<= 1;
        store->list = _realloc_ds_array(store->list, Value, store->cap);
    }

    store->list[store->len] = value;
    store->len++;
}

Value peekValStack(ValStack* store, int index)
{
    if(index == 0) {
        // peek the top of the stack
        if(store->len-1 > store->cap) {
            fprintf(stderr, "fatal error: call stack under run\n");
            exit(1);
        }

        return store->list[store->len-1];
    }
    else if(index < 0) {
        // peek a index relative to the TOS. This is an unsigned compare.
        if(index+store->len > store->cap) {
            fprintf(stderr, "fatal error: invalid value stack index\n");
            exit(1);
        }

        return store->list[store->len+index];
    }

    return store->list[0]; // return an error
}

Value popValStack(ValStack* store)
{
    if(store->len-1 > store->cap) {
        fprintf(stderr, "fatal error: call stack under run\n");
        exit(1);
    }

    store->len--;
    return store->list[store->len];
}

uint32_t valStackIndex(ValStack* store)
{
    return store->len;
}