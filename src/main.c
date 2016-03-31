#include <headers.h>

/*
 * Maintains the rerefences to execute the event loop
 *
 * * processes   -> Processes definitions list loaded from disk
 * * entry_queue -> Arrived processes queue, updated every loop
 * * job_queue   -> Executing processes queue, updated on scheduler call
 * * io_queue    -> Central queue to request io lock
 * * io_lock     -> Represents IO execution resource lock
 * * memory      -> Memory map, called on central memory request
 *
 * `cycle`       :: Maintains the current CPU cycle
 * `schedule`    :: Maintains the next event step
 */
int main() {

  queue_cursor* processes = getProcessesList();
  queue_cursor* entry_queue = getEntryQueue();
  queue_cursor* job_queue = schl_getJobQueue();
  queue_cursor* io_queue = io_getIOProcessQueue();

  io_lock* io_resources_lock = io_getIOResourcesLock();

  memory_map* memory = memm_getMemoryMap();

  event_loop_key current_task;

  printDebugHeaders();

  int cycle = 0;
  while (++cycle) {

    current_task = ev_getCurrentTask();

    printCurrentState(cycle, current_task,
                      qc_cpy(processes),
                      qc_cpy(entry_queue),
                      qc_cpy(job_queue),
                      qc_cpy(io_queue),
                      io_resources_lock);

    switch (current_task) {

    /** 0 **/ case DEFAULT_ENTRY:
    /** 1 **/ case PROCESSES_ENTRY:

      updateEntryQueue(processes, entry_queue);

      printf("Entry: "); qc_foreach(entry_queue, &processPrinter);
      printf("Processes: %d ", getProcessesLength(processes));

      ev_setNextTask(MEMORY_REQUEST);
      break;

    /** 2 **/ case MEMORY_REQUEST:

      schl_getNextJob(entry_queue, job_queue, memory);

      printf("Jobs: "); qc_foreach(qc_cpy(job_queue), &processPrinter);

      if (job_queue->head != NULL) {

        ev_setNextTask(CPU_REQUEST);
      }
      break;

    /** 3 **/ case CPU_REQUEST:

      schl_executeJob(job_queue);
      break;

    /** 4 **/ case IO_REQUEST:

      io_requestHandler(job_queue, io_queue);

      printf("IO Flushed. Jobs: "); qc_foreach(qc_cpy(job_queue), &processPrinter);
      printf("IO: ");               qc_foreach(qc_cpy(io_queue), &processPrinter);

      ev_setNextTask(IO_EXECUTION);
      break;

    /** 5 **/ case IO_EXECUTION:

      io_requestExecutionLock(io_resources_lock, io_queue);
      break;

    /** 6 **/ case IO_RELEASE:

      io_computeRelease(io_resources_lock, job_queue);

      printf("Jobs: "); qc_foreach(qc_cpy(job_queue), &processPrinter);

      if (io_queue->head != NULL) {

        ev_setNextTask(IO_EXECUTION);
      }
      break;

    /** 7 **/ case CPU_RELEASE:

      schl_releaseJob(job_queue, memory);
      break;

    default:

      printf("Reset. Default task");

      ev_setNextTask(PROCESSES_ENTRY);
      break;
    }

    updateEntryArrivalTime(processes);
    io_updateLockRemainingTime(io_resources_lock);

    printf("\n");

    if (( getProcessesLength(qc_cpy(entry_queue)) == 0 &&
          getProcessesLength(qc_cpy(job_queue))   == 0 &&
          getProcessesLength(qc_cpy(io_queue))    == 0 &&
          getProcessesLength(qc_cpy(processes))   == 0 )||
        current_task == EXIT ||
        cycle > 300
        ) break;

    (DEBUG && usleep(LOOP_CYCLE_DELAY));
  }

  printf("\nEnd.\n");
  return 0;
}
