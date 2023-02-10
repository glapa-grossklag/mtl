# Introduction

MTL (Miles's Test Library) is a minimal (roughly 100 non-blank lines), single-header test library for C code.

# Example

Tests look like this:

```c
#include "mtl.h"

// Test functions are declared using `MTL_TEST()`.
MTL_TEST(test_int) {
	MTL_ASSERT(2 + 2 == 4);
}

MTL_TEST(test_float) {
	MTL_ASSERT(0.1 + 0.2 == 0.3);
}

// `MTL_MAIN()` implements a main function that runs the given tests.
MTL_MAIN(
	test_int,
	test_float
)
```

Output looks like this:

```
test_int: ok
test_float: not ok (0.1 + 0.2 == 0.3)
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
