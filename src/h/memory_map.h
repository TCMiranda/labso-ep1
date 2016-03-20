#ifndef MEMORY_MANAGEMENT_HEADERS
#define MEMORY_MANAGEMENT_HEADERS

typedef struct memory_entry {

  char* key;

  int size;
  int start;

} memory_entry;

typedef struct memory_map {

  bool* frames;

  memory_entry** entries;

  int max_frames;
  int available_frames;

} memory_map;

#endif
