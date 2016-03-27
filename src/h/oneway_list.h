#ifndef ONEWAY_LIST_HEADERS
#define ONEWAY_LIST_HEADERS

typedef struct oneway_list_item {

  struct oneway_list_item* next;

  union {

    event_loop_key ev_key;
    process* process;
  };

} oneway_list;

oneway_list* ol_getListNode() {

  oneway_list* node = malloc(sizeof(oneway_list));
  node->process = NULL;
  node->next = NULL;

  return node;
}

#endif
