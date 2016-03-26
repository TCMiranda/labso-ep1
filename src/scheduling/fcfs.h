void fcfs_getNextJob(queue_cursor* entry_queue, queue_cursor* job_queue, memory_map* memory) {

  if (job_queue->head == NULL && entry_queue->head == NULL) {

    return;
  }

  if (job_queue->head != NULL) {

    return;
  }

  oneway_list* job = getListNode();
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

    printf("Exec: %d; ", job_queue->current->process->id);

    if (--job_queue->current->process->cpu_cycles < 0) {

      printf("Finished: %d; ", job_queue->current->process->id);

      ev_setNextTask(CPU_RELEASE);
      return;
    }
  }

  /* Continue execution until finished (fcfs) */
  ev_setNextTask(CPU_REQUEST);
}
