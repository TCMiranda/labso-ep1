queue_cursor* getEntryQueue() {

  queue_cursor* cursor = malloc(sizeof(queue_cursor));
  return cursor;
}

/* Push processes to entry queue
 */
void entryQueueProcessValidator(queue_cursor* processes_queue, va_list vas) {

  queue_cursor* entry_queue = va_arg(vas, queue_cursor*);

  if (processes_queue->current->process->arrival_time <= 0) {

    oneway_list* entry_node = ol_getListNode();
    entry_node->process = processes_queue->current->process;

    qc_deleteCurrent(processes_queue);

    qc_reset(entry_queue);
    qc_push(entry_queue, entry_node);
  }
}
void updateEntryQueue(queue_cursor* processes, queue_cursor* entry_queue) {

  qc_iterate(processes, &entryQueueProcessValidator, entry_queue);
}

/* Decreases processes arrival_time
 * Should be called at the end of each loop */
void entryQueueArrivalTimeValidator(oneway_list* node, va_list vas) {

  node->process->arrival_time--;
}
void updateEntryArrivalTime(queue_cursor* processes) {

  qc_foreach(processes, &entryQueueArrivalTimeValidator);
}
