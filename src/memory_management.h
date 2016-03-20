void* getMemoryMap() {

  memory_map* memory = malloc(sizeof(memory_map*));
  bool* frames = malloc(sizeof(bool) * MAX_MEMORY_FRAMES);

  memory_entry** entries = malloc(sizeof(memory_entry**));
  memory_entry* first_entry = malloc(sizeof(memory_entry*));

  entries[0] = first_entry;

  memory->frames = frames;
  memory->entries = entries;

  memory->max_frames = MAX_MEMORY_FRAMES;
  memory->available_frames = MAX_MEMORY_FRAMES;
}
