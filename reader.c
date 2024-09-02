#include <nanopack/reader.h>
#include <stdint.h>
#include <string.h>

int8_t np_read_int8(uint8_t *buffer, size_t offset) {
	int8_t i;
	memcpy(&i, buffer + offset, 1);
	return i;
}

uint8_t np_read_uint8(uint8_t *buffer, size_t offset) { return buffer[offset]; }

int32_t np_read_int32(uint8_t *buffer, size_t offset) {
	int32_t i;
	memcpy(&i, buffer + offset, 4);
	return i;
};
uint32_t np_read_uint32(uint8_t *buffer, size_t offset) {
	uint32_t i;
	memcpy(&i, buffer + offset, 4);
	return i;
};

int64_t np_read_int64(uint8_t *buffer, size_t offset) {
	int64_t i;
	memcpy(&i, buffer + offset, 8);
	return i;
};
uint64_t np_read_uint64(uint8_t *buffer, size_t offset) {
	uint64_t i;
	memcpy(&i, buffer + offset, 8);
	return i;
};

double np_read_double(uint8_t *buffer, size_t offset) {
	double i;
	memcpy(&i, buffer + offset, 8);
	return i;
};

bool np_read_bool(uint8_t *buffer, size_t offset) {
	return buffer[offset] == 1;
};

void np_read_string(uint8_t *buffer, size_t offset, size_t size, char *dest) {
	memcpy(dest, buffer, size);
	dest[size - 1] = '\0';
};

np_typeid_t np_read_typeid(uint8_t *buffer) {
	return np_read_uint32(buffer, 0);
};

size_t np_read_field_size(uint8_t *buffer, int field_number) {
	return np_read_uint32(buffer, 4 * (field_number + 1));
};
