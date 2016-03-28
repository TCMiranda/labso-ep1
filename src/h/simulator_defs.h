#ifndef SIMULATOR_DEFS
#define SIMULATOR_DEFS

/* DEBUG settings */
#define DEBUG false
#define LOOP_CYCLE_DELAY 75000

/* Memory management settings */
#define MAX_MEMORY_FRAMES 120
#define MAX_PAGE_MEMORY 30

/* IO management settings
 * Sets the time required to execute io requests.
 * The number of records to execute isn't used.
 *
 * IO execution time calculated by:
 * IO = IO_RECORD_EXEC_CYCLES * IO_DEFAULT_RECORD_SIZE
 */
#define IO_RECORD_EXEC_CYCLES 2
#define IO_DEFAULT_RECORD_SIZE 3

/* Scheduler settings
 *
 * SCHEDULER_ALGORITHM: one of [
 *   fcfs  : First come fisrt serve
 *   rr    : Round-robin
 * ]
 */
#define SCHEDULER_ALGORITHM "rr"
#define CPU_EXECUTION_SLICE 3

#endif
