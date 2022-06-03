
#include "varStore.h"
#include "memory.h"

static VarIdx find_slot(VarStore* store)
{
    if(store->free_slots > 0) {
        for(VarIdx idx = 0; idx < store->len; idx++) {
            if(store->list[idx].status == DELETED) {
                store->free_slots--;
                store->list[idx].status = ACTIVE;
                return idx;
            }
        }
        return 0; // error
    }

    if(store->cap < store->len-1)
        store->cap <<= 1;
    store->list = _realloc_ds_array(store->list, Variable, store->cap);

    VarIdx idx = store->len;
    store->len++;

    return idx;
}

static bool validateIdx(VarStore* store, VarIdx idx)
{
    if(idx < store->len) {
        if(store->list[idx].status != DELETED)
            return true;
    }

    return false;
}

void initVarStore(VarStore* store)
{
    store->cap = 0x01 << 3;
    store->list = _alloc_ds_array(Variable, store->cap);

    // set up the error variable
    store->len = 1;
    Variable* var = &store->list[0];
    var->status = ACTIVE;
    var->isAssigned = true;
    var->val.type = ERROR;
}

void uninitVarStore(VarStore* store)
{
    if(store->list != NULL)
        _free(store->list);
}

VarIdx createVar(VarStore* store, ValType type)
{
    Value val;
    VarIdx idx = find_slot(store);
    val.type = type;
    store->list[idx].val = val;
    store->list[idx].isAssigned = false;
    store->list[idx].status = ACTIVE;

    return idx;
}

VarIdx assignVar(VarStore* store, VarIdx idx, Value val)
{
    if(!validateIdx(store, idx))
        return 0;
    else {
        store->list[idx].val = val;
        store->list[idx].isAssigned = true;
    }

    return idx;
}

VarIdx addVar(VarStore* store, Value val)
{
    VarIdx idx = find_slot(store);
    store->list[idx].val = val;
    store->list[idx].isAssigned = true;
    store->list[idx].status = ACTIVE;

    return idx;
}

Value getVar(VarStore* store, VarIdx idx)
{
    if(validateIdx(store, idx))
        return store->list[idx].val;
    else
        return store->list[0].val;
}

void delVar(VarStore* store, VarIdx idx)
{
    if(validateIdx(store, idx)) {
        store->list[idx].status = DELETED;
        store->free_slots ++;
    }
}
