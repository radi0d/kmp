#include "kmp.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static size_t *z_function(const char *str, size_t len);

kmp_state_t *
kmp_init(const char *text, size_t tlen, const char *pat, size_t plen)
{
	assert(text);
	assert(tlen > 0);

	assert(pat);
	assert(plen > 0);

	// |pattern|\0|text|
	char *buf = (char *) calloc(plen + 1 + tlen, sizeof(char));
	if (!buf)
		return NULL;
	memcpy(buf, pat, plen * sizeof(char));
	memcpy(&buf[plen + 1], text, tlen * sizeof(char));

	size_t *res = z_function(buf, plen + 1 + tlen);
	if (!res)
		return NULL;

	kmp_state_t *state = (kmp_state_t *) calloc(1, sizeof(kmp_state_t));
	if (!state)
		return NULL;

	state->buf = res;
	state->buf_len = plen + 1 + tlen;
	state->cur = 0;
	state->pat_len = plen;

	free(buf);
	return state;
}

void
kmp_end(kmp_state_t *state)
{
	assert(state);
	assert(state->buf);

	free(state->buf);
	free(state);
}

ssize_t
kmp_next(kmp_state_t *state)
{
	assert(state);
	assert(state->buf);

	ssize_t res = -1;
	for (size_t i = state->cur + 1; i < state->buf_len; i++)
	{
		assert(i < state->buf_len);

		if (state->buf[i] == state->pat_len) {
			res = i - state->pat_len - 1;
			state->cur = i;
			break;
		}
	}

	return res;
}

static size_t *
z_function(const char *str, size_t len)
{
	assert(str);
	assert(len > 0);

	size_t *res = (size_t *) calloc(len, sizeof(size_t));
	if (!res)
		return NULL;

	size_t left = 0, right = 0;
	for (size_t i = 0; i < len; i++) {
		assert(i < len);

		res[i] = MAX(0, MIN((ssize_t) right - (ssize_t) i,
		                    (ssize_t) res[i - left]));
		while (i + res[i] < len && str[res[i]] == str[i + res[i]])
			res[i]++;
		if (i + res[i] > right) {
			left = i;
			right = i;
		}
	}

	return res;
}

