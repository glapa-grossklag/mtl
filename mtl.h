/**
 * MTL: Miles's Test Library
 */
#ifndef MTL_H
#define MTL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* MTL_STR() stringifies the given macro parameter, and MTL_STR_() is a helper
 * for MTL_STR() */
#define MTL_STR_(X) #X
#define MTL_STR(X) MTL_STR_(X)

#define MTL_ASSERT(CONDITION) \
	do { \
		bool is_successful = (CONDITION); \
		if (is_successful) { \
			/* The "\r" is necessary because multiple MTL_ASSERT calls may be
			 * successful, but we don't want to print "ok" for each of them. */ \
			fprintf(stderr, "\r%s: ok", __func__); \
		} else { \
			fprintf(stderr, "\r%s: not ok (%s)", __func__, MTL_STR(CONDITION)); \
			return; \
		} \
	} while (0)

#define MTL_MAIN(SUITE) \
	int main(void) { \
		mtl_function *mtl_suite = (SUITE); \
		for (unsigned i = 0; mtl_suite[i] != NULL; i += 1) { \
			mtl_suite[i](); \
			fprintf(stderr, "\n"); \
		} \
		return EXIT_SUCCESS; \
	}

typedef void (*mtl_function)(void);

#endif
