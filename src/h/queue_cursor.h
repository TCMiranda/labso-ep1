#ifndef PROCESS_HEADERS
#define PROCESS_HEADERS

typedef struct queue_cursor {

  oneway_list* head;
  oneway_list* tail;
  oneway_list* previous;
  oneway_list* current;

} queue_cursor;

typedef void (*qc_foreach_callback) (oneway_list*, va_list);
typedef void (*qc_iterate_callback) (queue_cursor*, va_list);

queue_cursor* qc_reset(queue_cursor* cursor) {

  cursor->current = cursor->head;
  cursor->previous = NULL;
  return cursor;
}

void qc_foreach(queue_cursor* cursor, qc_foreach_callback callback, ... ) {

  cursor = qc_reset(cursor);

  va_list vas;
  while (true) {

    if (cursor->current != NULL) {

      va_start(vas, callback);
      callback(cursor->current, vas);
      va_end(vas);

    } else break;

    if (cursor->current->next != NULL) {

      cursor->previous = cursor->current;
      cursor->current = cursor->current->next;

    } else {

      qc_reset(cursor);
      break;
    }
  }
}

void qc_iterate(queue_cursor* cursor, qc_iterate_callback callback, ... ) {

  cursor = qc_reset(cursor);

  va_list vas;
  while (true) {

    if (cursor->current != NULL) {

      va_start(vas, callback);
      callback(cursor, vas);
      va_end(vas);

    } else break;

    if (cursor->current &&
        cursor->current->next != NULL) {

      cursor->previous = cursor->current;
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

  if (cursor->head->next != NULL) {

    cursor->head = cursor->head->next;

  } else {

    cursor->head = NULL;
  }
}

void qc_deleteCurrent(queue_cursor* cursor) {

  if (cursor->current == NULL) {
    return;
  }

  if (cursor->current == cursor->tail) {

    if (cursor->previous != NULL) {

      cursor->previous->next = NULL;
      cursor->tail = cursor->previous;
      cursor->current = cursor->tail;

    } else {

      cursor->head = NULL;
      cursor->previous = NULL;
      cursor->current = NULL;
      cursor->tail = NULL;
    }
  }

  else if (( cursor->current == cursor->head ) ||
           ( cursor->previous == NULL )) {

    qc_shift(cursor);
    qc_reset(cursor);
  }

  else {

    if (cursor->current->next != NULL) {

      cursor->previous->next = cursor->current->next;
      cursor->current = cursor->previous;

    } else {

      cursor->previous->next = NULL;
      cursor->current = cursor->previous;
    }
  }

  qc_reset(cursor);
}

void qc_next(queue_cursor* cursor) {

  if (cursor->current->next != NULL) {

    cursor->previous = cursor->current;
    cursor->current = cursor->current->next;

  } else {

    qc_reset(cursor);
  }
}

queue_cursor* qc_cpy(queue_cursor* source) {

  queue_cursor* dest = malloc(sizeof(queue_cursor));

  dest->head     = source->head;
  dest->previous = source->previous;
  dest->current  = source->current;
  dest->tail     = source->tail;

  return dest;
}

void qc_dump(queue_cursor* cursor) {

  printf("[");
  if (cursor->head != NULL) {
    printf("%d|", cursor->head->process->id);
  } else { printf("_|"); }
  if (cursor->previous != NULL) {
    printf("%d|", cursor->previous->process->id);
  } else { printf("_|"); }
  if (cursor->current != NULL) {
    printf("%d|", cursor->current->process->id);
  } else { printf("_|"); }
  if (cursor->tail != NULL) {
    printf("%d", cursor->tail->process->id);
  } else { printf("_"); }
  printf("] ");
}

#endif
