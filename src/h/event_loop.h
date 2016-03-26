#ifndef EVENT_LOOP_HEADERS
#define EVENT_LOOP_HEADERS

typedef enum {

  EXIT = 0,
  PROCESSES_ENTRY,
  MEMORY_REQUEST,
  CPU_REQUEST,
  IO_REQUEST,
  IO_EXECUTION,
  IO_RELEASE,
  CPU_RELEASE

} event_loop_key;

event_loop_key ev_current_task = PROCESSES_ENTRY;

event_loop_key ev_getCurrentTask() {
  return ev_current_task;
}

event_loop_key ev_setNextTask(event_loop_key next_task) {
  return (ev_current_task = next_task);
}

#endif
