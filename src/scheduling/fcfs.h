void fcfs_getNextJob(queue_cursor* entry_queue, queue_cursor* job_queue, memory_map* memory) {

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

    free(job);
  }
}

void fcfs_executeJob(queue_cursor* job_queue) {

  printf("\n[Exec] %d\n", job_queue->current->process->id);

  if (--job_queue->current->process->cpu_cycles < 0) {

    /* remove process from job_queue */

    printf("* End %d\n", job_queue->current->process->id);
  }
}
