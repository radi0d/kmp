#pragma once

#include <stddef.h>

#include <sys/types.h>

typedef struct kmp_state {
	size_t *buf;    // buffer with the result of Z function
	size_t buf_len; // length of the buffer
	size_t cur;     // current found position
	size_t pat_len; // length of the pattern
} kmp_state_t;

kmp_state_t *kmp_init(const char *text, size_t tlen,
                      const char *pat, size_t plen);
void kmp_end(kmp_state_t *state);

ssize_t kmp_next(kmp_state_t *state);

