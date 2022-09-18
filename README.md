# Introduction

MTL (Miles's Test Library) is a minimal, single-header test library for C code.

# Example

Tests look like this:

```c
#include "mtl.h"

// All functions must return `void` and take `void`.
void test_addition(void) {
	// The `MTL_ASSERT()` macro will succeed if the argument evaluates to true.
	MTL_ASSERT(2 + 2 == 4);
}

void test_subtraction(void) {
	// The `MTL_ASSERT()` macro will fail if the argument evaluates to false.
	MTL_ASSERT(5 - 4 == 2);
}

// A test suite is a NULL-terminated array of `mtl_function`.
mtl_function suite[] = {
	test_addition,
	test_subtraction,
	NULL,
};

// The `MTL_MAIN()` macro will define a main function that runs the tests.
MTL_MAIN(suite)
```

Output looks like this:

```
test_addition: ok
test_subtraction: not ok (5 - 4 == 2)
```
