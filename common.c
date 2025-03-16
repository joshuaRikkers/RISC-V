#include "common.h"

void putchar(char c);

/**
 * 文字列をフォーマットして出力する関数。
 *
 * @param fmt フォーマット文字列
 * @param ... 可変長引数
 * */
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

/**
 * srcからnバイト分をdstにコピーします。
 *
 * @param dest コピー先
 * @param src コピー元
 * @param n コピーするバイト数
 *
 * @return dstのアドレスを返す
 * */
void *memcpy(void *dst, const void *src, size_t n) {
  uint8_t *d = (uint8_t *)dst;
  const uint8_t *s = (const uint8_t *)src;
  while (n--) {
    *d++ = *s++;
  }
  return dst;
}

/**
 * bufの先頭からnバイト分をcで埋めます。
 *
 * @param buf 埋めるメモリのポインター
 * @param c 設定する値
 * @param n 設定するバイトすう
 *
 * @return bufのアドレスを返す。
 * */
void *memset(void *buf, char c, size_t n) {
  uint8_t *p = (uint8_t *)buf;
  while (n--) {
    *p++ = c;
  }
  return buf;
}

/**
 * srcの文字列をdestにコピーします。
 *
 * @param dst コピー先のポインタ
 * @param src コピー元の文字列
 *
 * @return dst のアドレスを返す。
 *
 * @note もしdestのメモリりょういきよりsrcの方が長いとき、
 * dstのメモリりょういきをこえてコピーを行うことが可能です。
 * */
char *strcpy(char *dst, const char *src) {
  char *d = dst;
  while (*src) {
    *d++ = *src++;
  }
  *d = '\0';
  return dst;
}

/** TODO - コメント*/
int strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) {
      break;
    }
    s1++;
    s2++;
  }

  return *(unsigned char *)s1 - *(unsigned char *)s2;
}
