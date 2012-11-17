#include <string.h>
#include "sym.h"
#include "logging.h"

#define SYM_NAME_LIMIT          16
#define SYM_TABLE_LIMIT         128


struct sym {
    char name[SYM_NAME_LIMIT];
};

static struct sym sym_table[SYM_TABLE_LIMIT];

const struct sym *sym_find(const char *sname)
{
    int i;

    for (i = 0; sym_table[i].name[0] && i < SYM_TABLE_LIMIT; i++) {
        if (!strncmp(sym_table[i].name, sname, SYM_NAME_LIMIT)) {
            LOG_DEBUG("Found in table symbol[%3d]: %s", i, sname);
            return &sym_table[i];
        }
    }

    LOG_DEBUG("Adding new symbol[%3d]: %s", i, sname);
    strncpy(sym_table[i].name, sname, SYM_NAME_LIMIT);
    return &sym_table[i];
}

const char *sym_debug_get_name(const struct sym *sym)
{
    return sym->name;
}
