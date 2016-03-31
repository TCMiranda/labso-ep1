queue_cursor* io_getIOProcessQueue() {

  queue_cursor* cursor = malloc(sizeof(queue_cursor));
  return cursor;
}

io_lock* io_getIOResourcesLock() {

  io_lock* lock = malloc(sizeof(io_lock));
  return lock;
}

void io_requestHandler(queue_cursor* job_queue, queue_cursor* io_queue) {

  oneway_list* io_node = ol_getListNode();
  io_node->process = job_queue->current->process;

  qc_push(io_queue, io_node);

  qc_deleteCurrent(job_queue);
}

void io_requestExecutionLock(io_lock* io_resources_lock, queue_cursor* io_queue) {

  if (io_resources_lock->process == NULL) {

    if (io_queue->head != NULL) {

      process* p = io_queue->head->process;

      io_resources_lock->process = p;
      io_resources_lock->io_remaining_time = IO_RECORD_EXEC_CYCLES * p->io_record_size;

      qc_shift(io_queue);
      qc_reset(io_queue);

      printf("Lock IO for %d for %d cycles",
             io_resources_lock->process->id,
             io_resources_lock->io_remaining_time);

    } else { printf("Empty IO requests queue"); }

  } else { printf("IO resources locked."); }
}

void io_computeRelease(io_lock* io_resources_lock, queue_cursor* job_queue) {

  if (io_resources_lock->process == NULL) {

    return;
  }

  process* p = io_resources_lock->process;
  io_resources_lock->process = NULL;

  oneway_list* job_node = ol_getListNode();
  job_node->process = p;

  qc_push(job_queue, job_node);

  printf("Unlock: %d; ", p->id);
}

void io_updateLockRemainingTime(io_lock* io_resources_lock) {

  if (io_resources_lock->process == NULL) {

    return;
  }

  if (--io_resources_lock->io_remaining_time <= 0) {

    ev_setNextTask(IO_RELEASE);
  }
}
