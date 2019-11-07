#include "main.h"

int tblesze(void) {
	int pgdeslc = g_config.pgdeslc;
	size_t size = g_config.memsize;
	size <<= 0x00A;
	size >>= pgdeslc;

	return size;
}