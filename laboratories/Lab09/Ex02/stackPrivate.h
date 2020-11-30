#ifndef _STACK_PRIVATE
#define _STACK_PRIVATE

#include <stdio.h>
#include "stackPublic.h"
#include "util.h"

/* structure declarations */
typedef struct node {
  void *data;
  struct node *next;
} node_t;

struct stack {
  node_t *head;
  int num;
};

void fifo_print_r(FILE *fp, node_t *np, void (*print)(FILE *, void *));

#endif
