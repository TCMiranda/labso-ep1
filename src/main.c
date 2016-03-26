#include <headers.h>

/*
 * Maintains the rerefences to execute the event loop
 *
 * * processes   -> Processes definitions list loaded from disk
 * * entry_queue -> Arrived processes queue, updated every loop
 * * job_queue   -> Executing processes queue, updated on scheduler call
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

  memory_map* memory = memm_getMemoryMap();

  int cycle = 0;

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
  while (++cycle) {

    printf("\\_Cycle %d__\\", cycle);

    updateEntryQueue(processes, entry_queue);

    printf("\n[Ready] ");
    qc_foreach(entry_queue, &processPrinter);

    /* GetNextJob and push it to job_queue if not already pushed */
    schl_getNextJob(entry_queue, job_queue, memory);

    printf("\n[Jobs] ");
    qc_foreach(job_queue, &processPrinter);

    printf("\n[Memm] %d",
           memory->max_frames - memory->available_frames);

    /* Execute the process */
    schl_executeJob(job_queue);

    printf("\n");
    if (cycle > 67) break;

    (DEBUG && usleep(LOOP_CYCLE_DELAY));
  }

  printf("\n\\-_\nReset cursor, current id: %d\n",
         processes->current->process->id);

  printf("End.\n");
  return 0;
}
