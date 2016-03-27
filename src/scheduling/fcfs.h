void fcfs_getNextJob(queue_cursor* entry_queue, queue_cursor* job_queue, memory_map* memory) {

  if (job_queue->head == NULL && entry_queue->head == NULL) {

    return;
  }

  if (job_queue->head != NULL) {

    return;
  }

  oneway_list* job = ol_getListNode();
  job->process = entry_queue->head->process;

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

void fcfs_releaseJob(queue_cursor* job_queue) {

  printf("Released: %d; ", job_queue->current->process->id);

  qc_shift(job_queue);
  qc_reset(job_queue);

  ev_setNextTask(PROCESSES_ENTRY);
}

void fcfs_executeJob(queue_cursor* job_queue) {

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

        printf("Exec: %d; Remaining: %d; IO: %d of %d; ",
               job_queue->current->process->id,
               job_queue->current->process->cpu_cycles,
               job_queue->current->process->io_current + 1,
               job_queue->current->process->io_requests);
      }
    }
  }

  /* Continue execution until finished (fcfs) */
  ev_setNextTask(CPU_REQUEST);
}
