void entryQueueProcessValidator(oneway_list* item, void* entry_queue) {

  if (item->process->arrival_time == 0) {

    oneway_list* node = getListNode();
    node->process = item->process;

    cursorPush(entry_queue, node);
  }

  item->process->arrival_time--;
}

void updateEntryQueue(queue_cursor* processes, queue_cursor* entry_queue) {

  forEachCursor(processes, &entryQueueProcessValidator, entry_queue);
}

queue_cursor* getEntryQueue() {

  queue_cursor* cursor = malloc(sizeof(queue_cursor*));

  return cursor;
}
