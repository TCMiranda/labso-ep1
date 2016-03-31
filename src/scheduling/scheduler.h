#include <fcfs.h>
#include <rr.h>

typedef void (*schl_jobSchedulerDef) (queue_cursor*, queue_cursor*, memory_map*);
typedef void (*schl_jobExecuterDef)  (queue_cursor*);
typedef void (*schl_jobReleaseDef)  (queue_cursor*, memory_map*);

schl_jobSchedulerDef schl_getNextJob;
schl_jobExecuterDef  schl_executeJob;
schl_jobReleaseDef   schl_releaseJob;

void* schl_configure() {

  if (SCHEDULER_ALGORITHM == "fcfs") {

    schl_getNextJob = &fcfs_getNextJob;
    schl_executeJob = &fcfs_executeJob;
    schl_releaseJob = &fcfs_releaseJob;
  }

  else if (SCHEDULER_ALGORITHM == "rr") {

    schl_getNextJob = &rr_getNextJob;
    schl_executeJob = &rr_executeJob;
    schl_releaseJob = &rr_releaseJob;
  }

  else {

    printf("Undefined scheduler %s\n", SCHEDULER_ALGORITHM);
    exit(1);
  }
}

queue_cursor* schl_getJobQueue() {

  schl_configure();

  queue_cursor* job_queue = malloc(sizeof(queue_cursor));

  return job_queue;
}
