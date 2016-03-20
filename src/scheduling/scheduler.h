#include <fcfs.h>

typedef void (*schl_jobScheduler) (queue_cursor*, queue_cursor*, memory_map*);
typedef void (*schl_jobExecuter)  (queue_cursor*);

schl_jobScheduler schl_getNextJob;
schl_jobExecuter  schl_executeJob;

void* schl_configure() {

  schl_getNextJob = &fcfs_getNextJob;
  schl_executeJob = &fcfs_executeJob;
}

queue_cursor* schl_getJobQueue() {

  schl_configure();

  queue_cursor* job_queue = malloc(sizeof(queue_cursor*));

  return job_queue;
}
