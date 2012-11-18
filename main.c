#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "sym.h"

#define TOKEN_CHAR_LIMIT        16
#define SYM_NAME_LIMIT          16
#define AST_PARSE_REC_LIMIT     64
#define AST_PARSE_NODE_LIMIT  1024


enum ast_node_type {
    AST_NODE_TYPE_SYM,
    AST_NODE_TYPE_CALL,
};

struct ast_node {
    enum ast_node_type type;
    struct ast_node *next;
    union {
        const struct sym *sym;  /* For SYM */
        struct ast_node *call;  /* For CALL */
    };
};

struct ast_node *ast_alloc(enum ast_node_type type)
{
    static struct ast_node ast_node_pool[AST_PARSE_NODE_LIMIT];
    static int ast_node_pool_count;

    struct ast_node *ret = &ast_node_pool[ast_node_pool_count++];

    ret->type = type;
    return ret;
}

static struct ast_node *ast_root = NULL;
static struct ast_node **ast_cur = &ast_root;

DECLARE_STACK(struct ast_node **, AST_PARSE_REC_LIMIT)
static DEFINE_STACK(struct ast_node **, ast_parse_stack)


void ast_debug_print(struct ast_node *node)
{
    switch (node->type) {
    case AST_NODE_TYPE_CALL:
        putchar('(');
        ast_debug_print(node->call);
        putchar(')');
        break;
    case AST_NODE_TYPE_SYM:
        printf("%s", sym_debug_get_name(node->sym));
        break;
    default:
        break;
    }

    if (node->next) {
        putchar(' ');
        ast_debug_print(node->next);
    }
}

int main(int argc, char *argv[])
{
    char token_buffer[TOKEN_CHAR_LIMIT];
    char *token_char = token_buffer;
    char c;

    while ((c = getchar()) != EOF) {
        if ((isblank(c) || c == ')') && token_char != token_buffer) {
            /* Terminate current token */
            *token_char = 0;
            token_char = token_buffer;

            *ast_cur = ast_alloc(AST_NODE_TYPE_SYM);
            (*ast_cur)->sym = sym_find(token_buffer);
            ast_cur = &(*ast_cur)->next;
        }

        if (c == ')') {
            /* Terminate the param list by going up the AST. */
            *ast_cur = NULL;
            ast_cur = &((*STACK_POP(ast_parse_stack))->next);
        }

        if (c == '(') {
            /* New callable: create a parameter ast tree */
            STACK_PUSH(ast_parse_stack, ast_cur);
            *ast_cur = ast_alloc(AST_NODE_TYPE_CALL);
            ast_cur = &(*ast_cur)->call;
            token_char = token_buffer;
        }

        if (!isblank(c) && c != '(' && c != ')') {
            /* Anything else is just a token */
            *token_char = c;
            token_char++;
        }
    }

    ast_debug_print(ast_root);
    printf("\n");
    return 0;
}
