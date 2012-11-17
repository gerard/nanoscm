#ifndef _STACK_H_
#define _STACK_H_
#include <assert.h>

#define DECLARE_STACK(type, depth)      \
    struct stack {                      \
        unsigned int cur;               \
        type s[depth];                  \
    };

#define DEFINE_STACK(type, stk)         \
    struct stack stk;

#define STACK_PUSH(stk, v)    ({        \
    stk.s[stk.cur++] = v;               \
})

#define STACK_POP(stk)        ({        \
    assert(stk.cur);                    \
    stk.s[--stk.cur];                   \
})

#endif
