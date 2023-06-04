void util_memory_copy(char *src, char *dest, int bytes) {
  int i = 0;
  while (i < bytes) {
    *(dest + i) = *(src + i);
    i++;
  }
}

void util_int_to_ascii(int n, char output[]) {
  int sign = n;

  if (sign < 0) {
    n = -n;
  }

  int i = 0;
  do {
    output[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) {
    output[i++] = '-';
  }
  output[i] = '\0';

  /* TODO: implement "reverse" */
}
