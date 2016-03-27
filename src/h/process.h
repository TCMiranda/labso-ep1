#ifndef PROCESS_TYPES_HEADERS
#define PROCESS_TYPES_HEADERS

typedef enum {
  true  = 1,
  false = 0
} bool;

typedef struct process {

  /* Defined on the entry file */
  int id;             // Process id
  int arrival_time;   // Arrival time in "loop units"
  int cpu_cycles;     // Cpu cycles consumption
  int memory;         // Memory to be loaded
  int io_requests;    // I/O event number

  /* Computed and cached at setup */
  int io_current;     // Current i/o request arrival
  int io_interval;    // I/O requests computed interval
  int io_record_size; // Record size to simulate read/write

} process;

#endif
