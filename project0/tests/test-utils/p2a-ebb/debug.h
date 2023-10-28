#ifdef DEBUG
#define DEBUG_PRINT(...)                                                       \
  do {                                                                         \
    fprintf(stderr, __VA_ARGS__);                                              \
  } while (false)
#else
#define DEBUG_PRINT(...)                                                       \
  do {                                                                         \
  } while (false)
#endif
