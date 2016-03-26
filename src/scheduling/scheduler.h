#include <fcfs.h>

typedef void (*schl_jobSchedulerDef) (queue_cursor*, queue_cursor*, memory_map*);
typedef void (*schl_jobExecuterDef)  (queue_cursor*);
typedef void (*schl_jobReleaseDef)  (queue_cursor*);

schl_jobSchedulerDef schl_getNextJob;
schl_jobExecuterDef  schl_executeJob;
schl_jobReleaseDef   schl_releaseJob;

void* schl_configure() {

  schl_getNextJob = &fcfs_getNextJob;
  schl_executeJob = &fcfs_executeJob;
  schl_releaseJob = &fcfs_releaseJob;
}

queue_cursor* schl_getJobQueue() {

  schl_configure();

  queue_cursor* job_queue = malloc(sizeof(queue_cursor*));

  return job_queue;
}
