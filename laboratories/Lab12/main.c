#include <stdio.h>
#include "course-provided/queue.h"
#include "course-provided/graph.h"

#define TREE 0
#define BACKWARDS 1
#define FORWARD 2
#define CROSS 3

#define DEFAULT_FILE "in5.txt"

/* function prototypes */
void graph_bfs (graph_t *, vertex_t *);
int graph_bfs_count (graph_t *g, vertex_t *n);
int graph_bfs_distance (graph_t *g, vertex_t *n);

void graph_dfs (graph_t *, vertex_t *);
int *graph_dfs_type (graph_t *g, vertex_t *n);
int graph_dfs_depth (graph_t *g, vertex_t *n);
int graph_dfs_deepest (graph_t *g, vertex_t *n);

int graph_dfs_r (graph_t *, vertex_t *, int);
int graph_dfs_type_r(graph_t *g, vertex_t *n, int currTime, int *result);
int graph_dfs_depth_r(int count, graph_t *g, vertex_t *n, int currTime, int *result);
int graph_dfs_deepest_r(int length, graph_t *g, vertex_t *n, int currTime, int *result);

/*
 *  main program
 */
int main (int argc, char *argv[]) {
  graph_t *g;
  vertex_t *src, *n;
  int i;

  char* fileName;

  // util_check_m(argc>=2, "missing parameter.")
  if(argc != 2)
    fileName = DEFAULT_FILE;
  else
    fileName = argv[1];

  g = graph_load (fileName);

  printf("Initial vertex? ");
  scanf("%d", &i);

  printf ("Incoming/Outgoing Edges\n");
  src = graph_find (g, i);

  /* DFS */
  printf ("DFS\n");
  // Redundant after load
  graph_attribute_init (g);
  graph_dfs (g, src);

  graph_attribute_init (g);
  int *edgeTypes = graph_dfs_type(g, src);
  graph_attribute_init (g);
  int treeDepth = graph_dfs_depth(g, src);
  graph_attribute_init (g);
  int longest = graph_dfs_deepest(g, src);

  printf("T edge count: %d\nB edge count: %d\nF edge count: %d\nC edge count: %d\n", edgeTypes[TREE], edgeTypes[BACKWARDS], edgeTypes[FORWARD], edgeTypes[CROSS]);
  printf("Visit tree depth: %d\n", treeDepth);
  printf("Longest path that touches a node at most once: %d\n", longest);

  /* BFS */
  printf ("BFS\n");
  graph_attribute_init (g);
  graph_bfs (g, src);

  /* print reachable nodes with info */
  n = g->g;
  printf("List of vertices:\n");
  while (n != NULL) {
    if (n->color != WHITE) {
      printf("%2d: [%d] (%d)\n", n->id, n->dist, n->pred ? n->pred->id : -1);
    }
    n = n->next;
  }

  graph_dispose (g);

  return EXIT_SUCCESS;
}

/*
 *  perform BFS from vertex n
 */
void graph_bfs (graph_t *g, vertex_t *n) {
  queue_t *qp;
  vertex_t *d;
  edge_t *e;

  qp = queue_init (g->nv);
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);
    e = n->head;
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
	d->color = GREY;
	d->dist = n->dist + 1;
	d->pred = n;
	queue_put (qp, (void *)d);
      }
      e = e->next;
    }
    n->color = BLACK;
  }
  queue_dispose (qp, NULL);

  return;
}

/*
 *  perform BFS from vertex n counting touched nodes
 */
int graph_bfs_count (graph_t *g, vertex_t *n) {
  queue_t *qp;
  vertex_t *d;
  edge_t *e;

  int touchedNodes = 0;

  qp = queue_init (g->nv);
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);
    e = n->head;
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
	      d->color = GREY;
	      d->dist = n->dist + 1;
	      d->pred = n;
	      queue_put (qp, (void *)d);
      }
      e = e->next;
    }
    n->color = BLACK;
    ++touchedNodes;
  }
  queue_dispose (qp, NULL);

  return touchedNodes;
}

/*
 *  perform BFS from vertex n counting maximum distance from starting point
 */
int graph_bfs_distance (graph_t *g, vertex_t *n) {
  queue_t *qp;
  vertex_t *d;
  edge_t *e;

  int record = -1;

  qp = queue_init (g->nv);
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);
    e = n->head;
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
	      d->color = GREY;
	      d->dist = n->dist + 1;
	      d->pred = n;
	      queue_put (qp, (void *)d);
      }
      e = e->next;
    }
    n->color = BLACK;

    if(n->dist > record)
      record = n->dist;
  }
  queue_dispose (qp, NULL);

  return record;
}

/*
 *  perform DFS from vertex i
 */
void graph_dfs (graph_t *g, vertex_t *n) {
  int currTime=0;
  vertex_t *tmp, *tmp2;

  printf("List of edges:\n");
  currTime = graph_dfs_r (g, n, currTime);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    if (tmp->color == WHITE) {
      currTime = graph_dfs_r (g, tmp, currTime);
    }
  }

  printf("List of vertices:\n");
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    tmp2 = tmp->pred;
    printf("%2d: %2d/%2d (%d)\n",
      tmp->id, tmp->disc_time, tmp->endp_time,
      (tmp2!=NULL) ? tmp->pred->id : -1);
  }
}

/*
 *  perform DFS from vertex i returning number of tree, backwarad, forward, and cross edges
 */
int *graph_dfs_type (graph_t *g, vertex_t *n) {
  int currTime=0;
  vertex_t *tmp;

  int *result = malloc(4 * sizeof(int));
  for(int i = 0; i < 4; ++i)
    result[i] = 0;

  currTime = graph_dfs_type_r (g, n, currTime, result);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next)
    if (tmp->color == WHITE)
      currTime = graph_dfs_type_r (g, tmp, currTime, result);

  return result;
}

/*
 *  perform DFS from vertex i returning depth of visit tree
 */
int graph_dfs_depth (graph_t *g, vertex_t *n) {
  int currTime=0;
  vertex_t *tmp;

  int result = -1;

  currTime = graph_dfs_depth_r (0, g, n, currTime, &result);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next)
    if (tmp->color == WHITE)
      currTime = graph_dfs_depth_r (0, g, tmp, currTime, &result);

  return result;
}

/*
 *  perform DFS from vertex i returning maximum path that visits each node at most once
 */
int graph_dfs_deepest (graph_t *g, vertex_t *n) {
  int currTime=0;
  vertex_t *tmp;

  int result = -1;

  currTime = graph_dfs_deepest_r (0, g, n, currTime, &result);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next)
    if (tmp->color == WHITE)
      currTime = graph_dfs_deepest_r (0, g, tmp, currTime, &result);

  return result;
}

/*
 *  perform recursive DFS from vertex i:
 *  labels nodes with td/tq, edges as T/F/B/C
 */
int graph_dfs_r(graph_t *g, vertex_t *n, int currTime) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: printf("%d -> %d : T\n", n->id, tmp->id); break;
      case GREY : printf("%d -> %d : B\n", n->id, tmp->id); break;
      case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                  } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                  }
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_r (g, tmp, currTime);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;

  return currTime;
}

int graph_dfs_type_r(graph_t *g, vertex_t *n, int currTime, int *result) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: ++result[TREE]; break;
      case GREY : ++result[BACKWARDS]; break;
      case BLACK: if (n->disc_time < tmp->disc_time) ++result[FORWARD]; else ++result[CROSS];
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_type_r (g, tmp, currTime, result);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;

  return currTime;
}

int graph_dfs_depth_r(int count, graph_t *g, vertex_t *n, int currTime, int *result) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_depth_r ((count + 1), g, tmp, currTime, result);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;

  if(count > *result)
    *result = count;

  return currTime;
}

int graph_dfs_deepest_r(int length, graph_t *g, vertex_t *n, int currTime, int *result) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_deepest_r ((length + e->weight), g, tmp, currTime, result);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;

  if(length > *result)
    *result = length;

  return currTime;
}
