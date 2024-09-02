#ifndef NANOPACK__READER_H
#define NANOPACK__READER_H

#include "nanopack.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int8_t np_read_int8(uint8_t *buffer, size_t offset);
uint8_t np_read_uint8(uint8_t *buffer, size_t offset);

int32_t np_read_int32(uint8_t *buffer, size_t offset);
uint32_t np_read_uint32(uint8_t *buffer, size_t offset);

int64_t np_read_int64(uint8_t *buffer, size_t offset);
uint64_t np_read_uint64(uint8_t *buffer, size_t offset);

double np_read_double(uint8_t *buffer, size_t offset);

bool np_read_bool(uint8_t *buffer, size_t offset);

void np_read_string(uint8_t *buffer, size_t offset, size_t size, char *dest);

np_typeid_t np_read_typeid(uint8_t *buffer);

size_t np_read_field_size(uint8_t *buffer, int field_number);

#endif
