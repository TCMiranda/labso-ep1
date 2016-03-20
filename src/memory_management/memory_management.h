memory_entry* getMemoryMapEntry() {

  memory_entry* entry = malloc(sizeof(memory_entry*));

  return entry;
}

void* memm_getMemoryMap() {

  memory_map* memory = malloc(sizeof(memory_map*));
  memory_entry** entries = malloc(sizeof(memory_entry**));

  memory->entries = entries;

  memory->max_frames = MAX_MEMORY_FRAMES;
  memory->available_frames = MAX_MEMORY_FRAMES;

  return memory;
}

bool memm_loadProcess(memory_map* memory, process* process) {

  if (process->memory <= memory->available_frames) {

    memory_entry* entry = malloc(sizeof(memory_entry*));

    entry->size = process->memory;
    entry->start = 0;

    memory->entries[process->id] = entry;
    memory->available_frames -= process->memory;

    return true;

  } else {

    printf("Memory overflow on process %d", process->id);

    return false;
  }
}
