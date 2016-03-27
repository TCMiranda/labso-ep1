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
 *
 */
int main() {

  queue_cursor* processes = getProcessesList();
  queue_cursor* entry_queue = getEntryQueue();
  queue_cursor* job_queue = schl_getJobQueue();
  queue_cursor* io_queue = io_getIOProcessQueue();

  io_lock* io_resources_lock = io_getIOResourcesLock();

  memory_map* memory = memm_getMemoryMap();

  /*
   * Main event loop
   *
   * The cycle is currently executing all steps at once.
   * It should instead apply only one action per cicle:
   *
   * -> Update entry queue
   *   -> Decrease arrival_time
   *   -> Push arrived events to entry queue
   *
   * -> Get next job (job or entry queue)
   *   -> Check job queue
   *   -> Load job in memory
   *
   * -> Execute job slice
   *   -> Removes from job queue if finished
   *
   * -> Loop
   */
  printf(" Cycle   Task  ->  Output\n");

  event_loop_key current_task;

  int cycle = 0;
  while (++cycle) {

    current_task = ev_getCurrentTask();
    printf("[ % 4d ]   %d   ->  ", cycle, current_task);
    fflush(stdout);

    switch (current_task) {

    /** 1 **/ case PROCESSES_ENTRY:

      updateEntryQueue(processes, entry_queue);

      printf("Entry: "); qc_foreach(entry_queue, &processPrinter);
      printf("Processes: %d ", getProcessesLength(processes));

      ev_setNextTask(MEMORY_REQUEST);
      break;

    /** 2 **/ case MEMORY_REQUEST:

      schl_getNextJob(entry_queue, job_queue, memory);

      printf("Jobs: "); qc_foreach(job_queue, &processPrinter);

      if (job_queue->head != NULL) {

        ev_setNextTask(CPU_REQUEST);

      } else {

        ev_setNextTask(PROCESSES_ENTRY);
      }
      break;

    /** 3 **/ case CPU_REQUEST:

      schl_executeJob(job_queue);

      break;

    /** 4 **/ case IO_REQUEST:

      io_requestHandler(job_queue, io_queue);

      ev_setNextTask(IO_EXECUTION);
      break;

    /** 5 **/ case IO_EXECUTION:

      io_requestExecutionLock(io_resources_lock, io_queue);
      break;

    /** 6 **/ case IO_RELEASE:

      io_computeRelease(io_resources_lock, job_queue);

      if (io_queue->head != NULL) {

        ev_setNextTask(IO_EXECUTION);
      }
      break;

    /** 7 **/ case CPU_RELEASE:

      schl_releaseJob(job_queue);
      break;

    default:

      ev_setNextTask(PROCESSES_ENTRY);
      break;
    }

    updateEntryArrivalTime(processes);
    io_updateLockRemainingTime(io_resources_lock);

    printf("\n");

    if ( getProcessesLength(entry_queue) == 0 &&
         getProcessesLength(job_queue)   == 0 &&
         getProcessesLength(io_queue)    == 0 &&
         getProcessesLength(processes)   == 0 ||
         current_task == EXIT ||
         cycle > 250
         ) break;

    (DEBUG && usleep(LOOP_CYCLE_DELAY));
  }

  printf("\nEnd. Print metrics.\n");
  return 0;
}
