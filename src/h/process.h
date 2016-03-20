#ifndef PROCESS_TYPES_HEADERS
#define PROCESS_TYPES_HEADERS

typedef enum {
  true  = 1,
  false = 0
} bool;

typedef struct process {

  int id;            // process id
  int arrival_time;  // arrival time in "loop units"
  int cpu_cycles;    // cpu cycles consumption
  int memory;        // memory to be loaded
  int io;            // i/o event number

} process;

typedef struct oneway_list_item {

  process* process;

  struct oneway_list_item* next;

} oneway_list;

oneway_list* getListNode() {

  oneway_list* node = malloc(sizeof(oneway_list*));
  node->process = NULL;
  node->next = NULL;

  return node;
}

#endif
