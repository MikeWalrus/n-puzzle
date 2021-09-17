#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"

void die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	exit(1);
}

void *malloc_or_die(size_t size)
{
    void *ret = malloc(size);
    if (!ret) {
        die("Failed to allocate %zu bytes", size);
    }
    return ret;
}
