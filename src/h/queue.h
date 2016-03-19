#ifndef PROCESS_HEADERS
#define PROCESS_HEADERS

typedef struct queue_cursor {

  oneway_list* head;
  oneway_list* tail;
  oneway_list* current;

} queue_cursor;

typedef void (*cursorCallback) (oneway_list*, void*);

queue_cursor* resetCursor(queue_cursor* cursor) {

  cursor->current = cursor->head;
  return cursor;
}

void forEachCursor(queue_cursor* cursor, cursorCallback callback, void* arg ) {

  while (true) {

    callback(cursor->current, arg);

    if (cursor->current->next != NULL) {

      cursor->current = cursor->current->next;

    } else {

      cursor = resetCursor(cursor);
      break;
    }
  }
}

void cursorPush(queue_cursor* cursor, oneway_list* item) {

  (cursor->head == NULL)     && (cursor->head = item);
  (cursor->current == NULL)  && (cursor->current = item);

  (cursor->tail != NULL)     && (cursor->tail->next = item);

  cursor->tail = item;
}

#endif
