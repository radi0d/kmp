#include "kmp.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>

int
main(void)
{
	char *text = readline("Enter the text: ");
	const size_t text_len = strlen(text);
	if (!text || !text_len) {
		fprintf(stderr, "[ERR] The input is empty!\n");
		return 1;
	}

	char *pat = readline("Enter the pattern: ");
	const size_t pat_len = strlen(pat);
	if (!pat || !pat_len) {
		fprintf(stderr,"[ERR] The input is empty!\n");
		return 1;
	}

	kmp_state_t *s = kmp_init(text, text_len, pat, pat_len);
	if (!s) {
		fprintf(stderr,"[ERR] Allocation error!\n");
		return 1;
	}
	ssize_t next = kmp_next(s);
	if (next < 0) {
		printf("Not found!\n");
		return 2;
	}

	printf("Found at:\n");
	printf("%s\n", text);
	for (size_t i = 0; i < text_len; i++) {
		assert(i < text_len);

		if (next >= 0 && (size_t) next == i) {
			printf("^");
			next = kmp_next(s);
			continue;
		}
		printf(" ");
	}
	printf("\n");
	kmp_end(s);

	free(text);
	free(pat);
	return 0;
}

