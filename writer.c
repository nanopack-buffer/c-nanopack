#include <nanopack/writer.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MOVE_END_PTR(by)                                                       \
	writer.end_ptr += by;                                                      \
	if (writer.end_ptr >= writer.capacity) {                                   \
		writer.buffer =                                                        \
			realloc(writer.buffer,                                             \
					writer.capacity * 2 + (writer.end_ptr - writer.capacity)); \
	}

np_writer_t np_writer_new(size_t initial_capacity) {
	np_writer_t writer;
	writer.buffer = malloc(initial_capacity * sizeof(uint8_t));
	writer.end_ptr = 0;
	return writer;
}

void np_writer_reserve_header_size(np_writer_t writer, size_t header_size) {
	writer.end_ptr += header_size;
}

void np_writer_write_typeid(np_writer_t writer, np_typeid_t type_id,
							size_t offset) {
	writer.buffer[offset] = type_id & 0x000000FF;
	writer.buffer[offset + 1] = (type_id & 0x0000FF00) >> 8;
	writer.buffer[offset + 2] = (type_id & 0x00FF0000) >> 16;
	writer.buffer[offset + 3] = (type_id & 0xFF000000) >> 24;
};

void np_writer_write_field_size(np_writer_t writer, int field_number,
								uint32_t size, int offset) {
	size_t p = offset + 4 * (field_number + 1);
	writer.buffer[p] = size & 0x000000FF;
	writer.buffer[p + 1] = (size & 0x0000FF00) >> 8;
	writer.buffer[p + 2] = (size & 0x00FF0000) >> 16;
	writer.buffer[p + 3] = (size & 0xFF000000) >> 24;
}

void np_writer_append_int8(np_writer_t writer, int8_t num) {
	MOVE_END_PTR(1);
	memcpy(writer.buffer + writer.end_ptr - 1, &num, 1);
};
void np_writer_append_uint8(np_writer_t writer, uint8_t num) {
	MOVE_END_PTR(1);
	writer.buffer[writer.end_ptr - 1] = num;
}

void np_writer_append_int32(np_writer_t writer, int32_t num) {
	MOVE_END_PTR(4);
	writer.buffer[writer.end_ptr - 4] = num & 0x000000FF;
	writer.buffer[writer.end_ptr - 3] = (num & 0x0000FF00) >> 8;
	writer.buffer[writer.end_ptr - 2] = (num & 0x00FF0000) >> 16;
	writer.buffer[writer.end_ptr - 1] = (num & 0xFF000000) >> 24;
}
void np_writer_append_uint32(np_writer_t writer, uint32_t num) {
	MOVE_END_PTR(4);
	writer.buffer[writer.end_ptr - 4] = num & 0x000000FF;
	writer.buffer[writer.end_ptr - 3] = (num & 0x0000FF00) >> 8;
	writer.buffer[writer.end_ptr - 2] = (num & 0x00FF0000) >> 16;
	writer.buffer[writer.end_ptr - 1] = (num & 0xFF000000) >> 24;
}

void np_writer_append_int64(np_writer_t writer, int64_t num) {
	MOVE_END_PTR(8);
	writer.buffer[writer.end_ptr - 8] = num & 0x00000000000000FF;
	writer.buffer[writer.end_ptr - 7] = (num & 0x000000000000FF00) >> 8;
	writer.buffer[writer.end_ptr - 6] = (num & 0x0000000000FF0000) >> 16;
	writer.buffer[writer.end_ptr - 5] = (num & 0x00000000FF000000) >> 24;
	writer.buffer[writer.end_ptr - 4] = (num & 0x000000FF00000000) >> 32;
	writer.buffer[writer.end_ptr - 3] = (num & 0x0000FF0000000000) >> 40;
	writer.buffer[writer.end_ptr - 2] = (num & 0x00FF000000000000) >> 48;
	writer.buffer[writer.end_ptr - 1] = (num & 0xFF00000000000000) >> 56;
}
void np_writer_append_uint64(np_writer_t writer, uint64_t num) {
	MOVE_END_PTR(8);
	writer.buffer[writer.end_ptr - 8] = num & 0x00000000000000FF;
	writer.buffer[writer.end_ptr - 7] = (num & 0x000000000000FF00) >> 8;
	writer.buffer[writer.end_ptr - 6] = (num & 0x0000000000FF0000) >> 16;
	writer.buffer[writer.end_ptr - 5] = (num & 0x00000000FF000000) >> 24;
	writer.buffer[writer.end_ptr - 4] = (num & 0x000000FF00000000) >> 32;
	writer.buffer[writer.end_ptr - 3] = (num & 0x0000FF0000000000) >> 40;
	writer.buffer[writer.end_ptr - 2] = (num & 0x00FF000000000000) >> 48;
	writer.buffer[writer.end_ptr - 1] = (num & 0xFF00000000000000) >> 56;
}

void np_writer_append_bool(np_writer_t writer, bool b) {
	MOVE_END_PTR(1);
	writer.buffer[writer.end_ptr - 1] = b ? 1 : 0;
}

void np_writer_append_double(np_writer_t writer, double d) {
	uint64_t i64 = *((uint64_t *)&d);
	MOVE_END_PTR(8);
	writer.buffer[writer.end_ptr - 8] = i64 & 0x00000000000000FF;
	writer.buffer[writer.end_ptr - 7] = (i64 & 0x000000000000FF00) >> 8;
	writer.buffer[writer.end_ptr - 6] = (i64 & 0x0000000000FF0000) >> 16;
	writer.buffer[writer.end_ptr - 5] = (i64 & 0x00000000FF000000) >> 24;
	writer.buffer[writer.end_ptr - 4] = (i64 & 0x000000FF00000000) >> 32;
	writer.buffer[writer.end_ptr - 3] = (i64 & 0x0000FF0000000000) >> 40;
	writer.buffer[writer.end_ptr - 2] = (i64 & 0x00FF000000000000) >> 48;
	writer.buffer[writer.end_ptr - 1] = (i64 & 0xFF00000000000000) >> 56;
}

void np_writer_append_string(np_writer_t writer, char *str) {
	size_t len = strlen(str);
	MOVE_END_PTR(len);
	memcpy(writer.buffer, str, len);
};

void np_writer_destroy(np_writer_t writer) { free(writer.buffer); }
