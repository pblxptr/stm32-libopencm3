#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum _rbuff_options_t {
  RING_BUFFER_OPTION_DEFAULT = 0,
  RING_BUFFER_OPTION_ALLOW_OVERLAPPING = (1 << 0),
} rbuff_options_t;

typedef struct _ring_buffer_t {
  size_t head;
  size_t tail;
  uint8_t* data;
  size_t max;
  size_t capacity;
  uint8_t options;
} rbuff_t;

typedef rbuff_t* rbuff_handle_t;

typedef enum _rbuff_status_t {
  RING_BUFFER_WRITE_ERROR_FULL,
  RING_BUFFER_EMPTY,
  RING_BUFFER_OK
} rbuff_status_t;

void ring_buffer_init(rbuff_handle_t rbufhandle, uint8_t* data, size_t max, rbuff_options_t options);
size_t ring_buffer_capacity(rbuff_handle_t rbufhandle);

bool ring_buffer_full(rbuff_handle_t rbufhandle);
bool ring_buffer_is_option_set(rbuff_handle_t rbufhandle, rbuff_options_t option);

rbuff_status_t ring_buffer_write(rbuff_handle_t rbufhandle, uint8_t byte);
rbuff_status_t ring_buffer_read(rbuff_handle_t rbufhandle, uint8_t* dst);

inline void ring_buffer_clear(rbuff_handle_t rbufhandle)
{
  for (size_t i = 0; i < rbufhandle->max; i++) {
    rbufhandle->data[i] = 0;
  }
}

size_t ring_buffer_tail(rbuff_handle_t rbuffhandle);