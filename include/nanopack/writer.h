#ifndef NANOPACK__WRITER_H
#define NANOPACK__WRITER_H

#include "nanopack.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint8_t *buffer;
	size_t end_ptr;
	size_t capacity;
} np_writer_t;

np_writer_t np_writer_new(size_t initial_capacity);

void np_writer_reserve_header_size(np_writer_t writer, size_t header_size);

void np_writer_write_typeid(np_writer_t writer, np_typeid_t type_id,
							size_t offset);

void np_writer_write_field_size(np_writer_t writer, int field_number,
								uint32_t size, int offset);

void np_writer_append_int8(np_writer_t writer, int8_t num);
void np_writer_append_uint8(np_writer_t writer, uint8_t num);

void np_writer_append_int32(np_writer_t writer, int32_t num);
void np_writer_append_uint32(np_writer_t writer, uint32_t num);

void np_writer_append_int64(np_writer_t writer, int64_t num);
void np_writer_append_uint64(np_writer_t writer, uint64_t num);

void np_writer_append_bool(np_writer_t writer, bool b);

void np_writer_append_double(np_writer_t writer, double d);

void np_writer_append_string(np_writer_t writer, char *str);

void np_writer_destroy(np_writer_t writer);

#endif
