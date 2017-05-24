/*
 * MIT License
 *
 * Copyright (c) 2017 Lucas Abel <www.github.com/uael>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef  U_CUTEST_H__
# define U_CUTEST_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER) || defined(__ICL) || defined(__ICC) || defined(__INTEL_COMPILER)
# define FORCEINLINE __forceinline
# define CONSTCALL
#elif defined(__GNUC__) || defined(__clang__)
# define FORCEINLINE inline __attribute__((__always_inline__))
# define CONSTCALL __attribute__((__const__))
#else
# warning Unknown compiler
# define FORCEINLINE
# define CONSTCALL
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
# define RESET
# define RED
# define GREEN
#else
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
#endif

#define CUTEST_DATA struct CUTEST
typedef CUTEST_DATA CUTEST_t;

#define CUTEST_SETUP void test_setup(CUTEST_t *self)
#define CUTEST_TEARDOWN void test_teardown(CUTEST_t *self)

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ ":" S2(__LINE__)
#define ASSERT(expr) do if (!(expr)) return LOCATION " -> " #expr; while (0)

#define CUTEST_PADDING "................................."
#define CUTEST_FN(suite, name) suite ## _ ## name ## _test
#define CUTEST_RUN(suite, name) \
  do if (test_run(&test, #suite ":" #name, sizeof(#suite ":" #name)-1, CUTEST_FN(suite, name)) == EXIT_FAILURE) \
      return EXIT_FAILURE; \
  while (0)
#define CUTEST(suite, name) static const char *CUTEST_FN(suite, name)(CUTEST_t *self)

CUTEST_SETUP;
CUTEST_TEARDOWN;

FORCEINLINE CONSTCALL int test_run(CUTEST_t *self, const char *id, unsigned id_len, const char *(*test_fn)(CUTEST_t *)) {
    const char *result;
    int s = sizeof(CUTEST_PADDING) - id_len - 1;

    printf("Test:     %s %*.*s   ", id, s, s, CUTEST_PADDING);
    test_setup(self);
    result = test_fn(self);
    test_teardown(self);
    if (result) {
        printf(RED "[FAILED] ‘%s’" RESET "\n", result);
        return EXIT_FAILURE;
    }
    puts(GREEN "[OK]" RESET);
    return EXIT_SUCCESS;
}

#endif /* U_CUTEST_H__ */