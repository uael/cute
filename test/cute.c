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

#include "cute.h"

CUTEST_DATA {
  unsigned dummy;
};

CUTEST_SETUP {
  ++self->dummy;
};

CUTEST_TEARDOWN {
  self->dummy += 2;
};

CUTEST(cute, dummy1) {
  ASSERT(1 == self->dummy);
  return NULL;
}

CUTEST(cute, dummy12) {
  ASSERT(1 == self->dummy);
  return NULL;
}

CUTEST(cute, dummy2) {
  ASSERT(7 == self->dummy);
  return NULL;
}

CUTEST(cute, dummy22) {
  ASSERT(1 == self->dummy);
  return NULL;
}

CUTEST(cute, dummy3) {
  ASSERT(13 == self->dummy);
  return NULL;
}

int main(void) {
  CUTEST_DATA test = {0};

  CUTEST_PASS(cute, dummy1);
  CUTEST_FAIL(cute, dummy12);
  CUTEST_PASS(cute, dummy2);
  CUTEST_FAIL(cute, dummy22);
  CUTEST_PASS(cute, dummy3);

  return EXIT_SUCCESS;
}
