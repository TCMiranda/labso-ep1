int rr_slice_cache = CPU_EXECUTION_SLICE;

void rr_getNextJob(queue_cursor* entry_queue, queue_cursor* job_queue, memory_map* memory) {

  if (job_queue->head == NULL && entry_queue->head == NULL) {
    return;
  }

  while (true) {

    if (entry_queue->head == NULL) {
      return;
    }

    oneway_list* job = ol_getListNode();
    job->process = entry_queue->head->process;

    //printf("[%d] ", entry_queue->head->process->id);

    if (memm_loadProcess(memory, job->process)) {

      /*
       * push next available process, fcfs
       * shift entry queue to job queue */
      qc_push(job_queue, job);

      qc_shift(entry_queue);
      qc_reset(entry_queue);

    } else {

      /* Failed to allocate momory, do smth */
    }
  }
}

void rr_releaseJob(queue_cursor* job_queue) {

  printf("Release: %d; ", job_queue->current->process->id);

  rr_slice_cache = CPU_EXECUTION_SLICE;

  qc_shift(job_queue);
  qc_reset(job_queue);

  ev_setNextTask(PROCESSES_ENTRY);
}

void rr_rotateQueue(queue_cursor* job_queue) {

  rr_slice_cache = CPU_EXECUTION_SLICE;

  qc_next(job_queue);
}

void rr_executeJob(queue_cursor* job_queue) {

  if (job_queue->current) {

    /* Choose between CPU processing or IO request */
    if (job_queue->current->process->io_requests > 0 &&
        job_queue->current->process->io_current == 0) {

      printf("IO Request. Release: %d; ", job_queue->current->process->id);

      job_queue->current->process->io_requests--;
      job_queue->current->process->io_current = job_queue->current->process->io_interval;

      /* Set IO_REQUEST task */
      ev_setNextTask(IO_REQUEST);
      return;

    } else {

      --job_queue->current->process->io_current;

      if (--job_queue->current->process->cpu_cycles < 0) {

        printf("Finish: %d; ", job_queue->current->process->id);

        ev_setNextTask(CPU_RELEASE);
        return;

      } else {

        printf("\\%d; Exec: %d; Remaining: %d; IO: %d of %d; ",
               rr_slice_cache,
               job_queue->current->process->id,
               job_queue->current->process->cpu_cycles,
               job_queue->current->process->io_current + 1,
               job_queue->current->process->io_requests);

        if (--rr_slice_cache <= 0) {

          rr_rotateQueue(job_queue);
          ev_setNextTask(PROCESSES_ENTRY);
          return;
        }
      }
    }
  }

  /* Continue until end of slice */
  ev_setNextTask(CPU_REQUEST);
}
