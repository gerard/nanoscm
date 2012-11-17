#include <string.h>
#include <stdlib.h>
#include "sym.h"
#include "logging.h"

#define SYM_NAME_LIMIT          16
#define SYM_TABLE_LIMIT         128

enum sym_type {
    SYM_TYPE_INVALID,
    SYM_TYPE_LAMBDA,
    SYM_TYPE_INT,
};

struct sym {
    char name[SYM_NAME_LIMIT];
    enum sym_type type;
    union {
        long long nscm_int;
        void *lambda;
    } v;
};

static struct sym sym_table[SYM_TABLE_LIMIT] = {
    {
        .name = "+",
        .type = SYM_TYPE_LAMBDA,
        .v = { .lambda = NULL },
    },
    {
        .name = "*",
        .type = SYM_TYPE_LAMBDA,
        .v = { .lambda = NULL },
    },
    {
        .name = "make-lambda",
        .type = SYM_TYPE_LAMBDA,
        .v = { .lambda = NULL },
    },
};

static const struct sym *sym_find_no_runtime(const char *sname)
{
    int i;

    for (i = 0; sym_table[i].name[0] && i < SYM_TABLE_LIMIT; i++) {
        if (!strncmp(sym_table[i].name, sname, SYM_NAME_LIMIT)) {
            return &sym_table[i];
        }
    }

    return NULL;
}

static const struct sym *sym_generate_runtime(const char *sname)
{
    int i;

    for (i = 0; sym_table[i].type != SYM_TYPE_INVALID; i++);
    struct sym *sym = &sym_table[i];

    sym->v.nscm_int = strtoll(sname, NULL, 10);
    sym->type = SYM_TYPE_INT;
    strncpy(sym->name, sname, SYM_NAME_LIMIT);

    return sym;
}

const struct sym *sym_find(const char *sname)
{
    const struct sym *sym = sym_find_no_runtime(sname);
    return sym ? sym : sym_generate_runtime(sname);
}

const char *sym_debug_get_name(const struct sym *sym)
{
    return sym->name;
}
