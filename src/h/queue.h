#ifndef PROCESS_HEADERS
#define PROCESS_HEADERS

typedef struct queue_cursor {

  oneway_list* head;
  oneway_list* tail;
  oneway_list* current;

} queue_cursor;

typedef void (*qc_callback) (oneway_list*, va_list);

queue_cursor* qc_reset(queue_cursor* cursor) {

  cursor->current = cursor->head;
  return cursor;
}

void qc_foreach(queue_cursor* cursor, qc_callback callback, ... ) {

  va_list vas;
  while (true) {

    if (cursor->current) {

      va_start(vas, callback);
      callback(cursor->current, vas);
      va_end(vas);

    } else {

      break;
    }

    if (cursor->current->next != NULL) {

      cursor->current = cursor->current->next;

    } else {

      cursor = qc_reset(cursor);
      break;
    }
  }
}

void qc_push(queue_cursor* cursor, oneway_list* item) {

  (cursor->head == NULL)     && (cursor->head = item);
  (cursor->current == NULL)  && (cursor->current = item);

  (cursor->tail != NULL)     && (cursor->tail->next = item);

  cursor->tail = item;
}

void qc_shift(queue_cursor* cursor) {

  oneway_list* head = cursor->head;

  if (cursor->head->next != NULL) {

    cursor->head = cursor->head->next;

  } else {

    cursor->head = NULL;
  }
}

#endif
