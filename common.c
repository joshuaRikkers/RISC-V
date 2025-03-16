#include "common.h"

void putchar(char c);

void printf(const char *fmt, ...) {
  va_list vargs;
  va_start(vargs, fmt);

  while (*fmt) {
    if (*fmt == '%') {
      fmt++;
      switch (*fmt) {
      case '0':
        putchar('%');
        goto end;
      case '%':
        putchar('%');
        break;
      case 's': {
        // 次の引数を取る
        const char *s = va_arg(vargs, const char *);
        while (*s) {
          putchar(*s);
          s++;
        }
        break;
      }
      case 'd': { // Print an integer in decimal
        int value = va_arg(vargs, int);
        unsigned magnitude = value;
        if (value < 0) {
          putchar('-');
          magnitude = -magnitude;
        }

        unsigned divisor = 1;
        while (magnitude / divisor > 9) {
          divisor *= 10;
        }

        while (divisor > 0) {
          putchar('0' + magnitude / divisor);
          magnitude %= divisor;
          divisor /= 10;
        }

        break;
      }
      case 'x': { // Print an integer in hex
        unsigned value = va_arg(vargs, unsigned);
        for (int ii = 7; ii >= 0; ii--) {
          unsigned nibble = (value >> (ii * 4)) & 0xf;
          putchar("0123456789abcdef"[nibble]);
        }
        break;
      }
      }
    } else {
      putchar(*fmt);
    }

    fmt++;
  }

end:
  va_end(vargs);
}
