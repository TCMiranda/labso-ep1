#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <sys/resource.h>

/* Global */
#include <simulator_defs.h>

/* Data types */
#include <event_loop_keys.h>
#include <process.h>
#include <oneway_list.h>
#include <queue_cursor.h>
#include <memory_map.h>
#include <io_handling.h>

#include <event_loop.h>

/* Processes handlers */
#include <debug.h>
#include <parsing.h>
#include <entry_queue.h>

/* IO management */
#include <io_management.h>

/* Memory management */
#include <memory_management.h>

/* Scheduling */
#include <scheduler.h>
