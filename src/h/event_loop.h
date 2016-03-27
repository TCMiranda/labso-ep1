#ifndef EVENT_LOOP_HEADERS
#define EVENT_LOOP_HEADERS

#define EV_ENTRY_TASK PROCESSES_ENTRY

/* Global ev_queue cursor
 * Shouldn't be accessed manually */
queue_cursor* ev_queue = NULL;

event_loop_key ev_setNextTask(event_loop_key next_task) {

  oneway_list* node = ol_getListNode();
  node->ev_key = next_task;

  qc_push(ev_queue, node);

  return next_task;
}

event_loop_key ev_getCurrentTask() {

  if (ev_queue == NULL) {

    ev_queue = malloc(sizeof(queue_cursor));
    ev_setNextTask(EV_ENTRY_TASK);
  }

  if (ev_queue->head == NULL) {

    ev_setNextTask(EV_ENTRY_TASK);
  }

  event_loop_key current_task = ev_queue->head->ev_key;

  qc_shift(ev_queue);

  return current_task;
}

#endif
