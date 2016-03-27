#ifndef PROCESS_IO_HANDLING_HEADERS
#define PROCESS_IO_HANDLING_HEADERS

typedef struct io_lock {

  process* process;

  int io_remaining_time;

} io_lock;

#endif
