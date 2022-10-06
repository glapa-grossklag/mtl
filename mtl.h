/**
 * MTL: Miles's Test Library
 */
#ifndef MTL_H
#define MTL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>

#define MTL_MAX_MESSAGE_SIZE 4096

/* MTL_STR() stringifies the given macro parameter, and MTL_STR_() is a helper
 * for MTL_STR() */
#define MTL_STR_(X) #X
#define MTL_STR(X) MTL_STR_(X)

#define MTL_ASSERT(CONDITION) \
	do { \
		mtl_successful = (CONDITION); \
		if (mtl_successful) { \
			snprintf(mtl_message, MTL_MAX_MESSAGE_SIZE, "%s: ok\n", __func__); \
		} else { \
			snprintf(mtl_message, MTL_MAX_MESSAGE_SIZE, "%s: not ok (%s)\n", __func__, MTL_STR(CONDITION)); \
			return; \
		} \
	} while (0)

#define MTL_FAIL(MESSAGE) \
	do { \
		mtl_successful = false; \
		snprintf(mtl_message, MTL_MAX_MESSAGE_SIZE, "%s: not ok (\"%s\")\n", __func__, MESSAGE); \
		return; \
	} while (0)

#define MTL_MAIN(SUITE) \
	int main(int argc, char **argv) { \
		return mtl_main(argc, argv, SUITE); \
	}

// Declare a new test:
#define MTL_TEST(NAME) static void NAME(void)

// Declare a new suite:
#define MTL_SUITE(NAME) static mtl_function NAME[] =

typedef void (*mtl_function)(void);

// Global variables:
static bool mtl_successful = true;
static unsigned mtl_number_of_failures = 0;
static unsigned mtl_number_of_tests = 0;
static char mtl_message[MTL_MAX_MESSAGE_SIZE] = {0};
static bool mtl_verbose = false;
static bool mtl_fail_fast = false;

static void mtl_run_test(mtl_function test) {
	// Reset globals before test, because a test might not change them if
	// `MTL_ASSERT` is never called inside the test.
	mtl_successful = true;
	mtl_message[0] = '\0';

	test();

	if (mtl_successful) {
		if (mtl_verbose) {
			fprintf(stderr, "%s", mtl_message);
		}
	} else {
		mtl_number_of_failures += 1;
		fprintf(stderr, "%s", mtl_message);
	}
}

static void mtl_run_suite(mtl_function tests[]) {
	mtl_number_of_failures = 0;
	mtl_number_of_tests = 0;

	for (unsigned i = 0; tests[i] != NULL; i += 1) {
		mtl_run_test(tests[i]);
		mtl_number_of_tests += 1;

		if (mtl_fail_fast && mtl_number_of_failures > 0) {
			break;
		}
	}
}

static int mtl_main(int argc, char **argv, mtl_function mtl_suite[]) {
	static const char short_options[] = "hvf";
	static const struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"verbose", no_argument, 0, 'v'},
		{"fail-fast", no_argument, 0, 'f'},
		{0, 0, 0, 0},
	};

	static const char help[] = \
		"Options:\n" \
		"    --help (-h): show this message\n" \
		"    --verbose (-v): more chatter\n" \
		"    --fail-fast (-f): exit upon first failure\n";

	int option = 0;
	while ((option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch (option) {
			case 'h':
				fprintf(stderr, "%s", help);
				return 0;

			case 'v':
				mtl_verbose = true;
				break;

			case 'f':
				mtl_fail_fast = true;
				break;

			default:
				fprintf(stderr, "%s", help);
				return 2;
		}
	}

	mtl_run_suite(mtl_suite);

	if (mtl_verbose) {
		fprintf(stderr, "\n%u of %u (%.1lf%%) ok\n",
			mtl_number_of_tests - mtl_number_of_failures,
			mtl_number_of_tests,
			100.0 * (mtl_number_of_tests - mtl_number_of_failures) / mtl_number_of_tests
		);
	}

	return mtl_number_of_failures == 0 ? 0 : 1;
}

#endif
