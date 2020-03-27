#include <ring_buffer.h>

void ring_buffer_init(rbuff_handle_t rbufhandle, uint8_t* data, size_t max, rbuff_options_t options)
{
  rbufhandle->data = data;
  rbufhandle->max = max;
  rbufhandle->capacity = 0;
  rbufhandle->head = 0;
  rbufhandle->tail = 0;
  rbufhandle->options = options;
}

size_t ring_buffer_capacity(rbuff_handle_t rbufhandle)
{
  return rbufhandle->capacity;
}

rbuff_status_t ring_buffer_write(rbuff_handle_t rbufhandle, uint8_t byte)
{
  const bool is_buffer_bull = ring_buffer_full(rbufhandle);

  if (!ring_buffer_is_option_set(rbufhandle, RING_BUFFER_OPTION_ALLOW_OVERLAPPING)
      && is_buffer_bull == true) {
    return RING_BUFFER_WRITE_ERROR_FULL;
  }
  rbufhandle->data[rbufhandle->head] = byte;
  rbufhandle->head = ((rbufhandle->head + 1) % rbufhandle->max);

  if (!is_buffer_bull) {
    rbufhandle->capacity++;
  }

  return RING_BUFFER_OK;
}

rbuff_status_t ring_buffer_read(rbuff_handle_t rbufhandle, uint8_t* dst)
{
  if (ring_buffer_capacity(rbufhandle) == 0) {
    return RING_BUFFER_EMPTY;
  }

  *dst = rbufhandle->data[rbufhandle->tail];
  rbufhandle->tail = ((rbufhandle->tail + 1) % rbufhandle->max);
  rbufhandle->capacity--;

  return RING_BUFFER_OK;
}

bool ring_buffer_full(rbuff_handle_t rbufhandle)
{
  return rbufhandle->capacity >= rbufhandle->max;
}

bool ring_buffer_is_option_set(rbuff_handle_t rbufhandle, rbuff_options_t option)
{
  return rbufhandle->options & option;
}

size_t ring_buffer_tail(rbuff_handle_t rbuffhandle)
{
  return rbuffhandle->tail;
}

