# cute
cute - c unit test as simple as possible

[![Build Status](https://travis-ci.org/uael/cute.svg?branch=master)](https://travis-ci.org/uael/cute)
[![Build status](https://ci.appveyor.com/api/projects/status/ka4dcr4vuvwcfsb6/branch/master?svg=true)](https://ci.appveyor.com/project/uael/cute/branch/master)

1 header 1 assertion and without fonctionality :tada:

```bash
$ mkdir build & cd build
$ cmake ..
$ make
$ ctest --verbose
...
    Start 1: cute

1: Test command: /home/travis/build/uael/cute/build/test/cute_test
1: Test timeout computed to be: 9.99988e+06
1: Test:     cute:dummy1 ......................   [PASS ~>  OK]
1: Test:     cute:dummy12 .....................   [FAIL ~>  OK] '/home/travis/build/uael/cute/test/cute.c:46 -> 1 == self->dummy'
1: Test:     cute:dummy2 ......................   [PASS ~>  OK]
1: Test:     cute:dummy22 .....................   [FAIL ~>  OK] '/home/travis/build/uael/cute/test/cute.c:56 -> 1 == self->dummy'
1: Test:     cute:dummy3 ......................   [PASS ~>  OK]
1/1 Test #1: cute .............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
