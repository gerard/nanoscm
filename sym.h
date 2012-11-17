#ifndef _SYM_H_
#define _SYM_H_

struct sym;

const struct sym *sym_find(const char *sname);
const char *sym_debug_get_name(const struct sym *sym);

#endif
