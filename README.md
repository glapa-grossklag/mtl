# Introduction

MTL (Miles's Test Library) is a minimal, single-header test library for C code.

# Example

Tests look like this:

```c
#include "mtl.h"

// Test functions are declared using `MTL_TEST()`.
MTL_TEST(test_addition) {
	// The test will pass if the parameter to `MTL_ASSERT()` evaluates to true.
	MTL_ASSERT(2 + 2 == 4);
}

MTL_TEST(test_subtraction) {
	// The test will fail if the parameter to `MTL_ASSERT()` evaluates to false.
	MTL_ASSERT(9 - 4 == 1);
}

MTL_TEST(test_multiplication) {
	// The test will fail with a custom message if `MTL_FAIL()` is called.
	MTL_FAIL("We haven't figured this one out yet...");
}

// Test suites are declared using `MTL_SUITE()` -- the array must end in `NULL`.
MTL_SUITE(suite) {
	test_addition,
	test_subtraction,
	test_multiplication,
	NULL,
};

// `MTL_MAIN()` implements a main function that runs the given suite.
MTL_MAIN(suite)
```

Output looks like this (with `--verbose`):

```
test_addition: ok
test_subtraction: not ok (9 - 4 == 1)
test_multiplication: not ok (We haven't figured this one out yet...)
```

All options can be listed with `--help`:

```
Options:
    --help (-h): show this message
    --verbose (-v): more chatter
    --fail-fast (-f): exit upon first failure
```

# Notes

- Do not declare any variables nor functions beginning with `mtl_`, as the
  names may conflict with the library's internal names.
- The library is unable to catch segmentation faults and other related errors,
  so check your bounds before running tests.
