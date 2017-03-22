struct mem_struct {
  char *memory;
  size_t size;
};

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);