#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include "clog.h"

static const char *LEVEL_NAMES [] = {
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL"
};

static int _min_level = 0;
static FILE *_stream = NULL;

/* Function Definition */
extern void clog_init (min_level, stream)
int min_level;
FILE *stream;
{
	_min_level = min_level;
	_stream = stream;
}

static int vlog (level, tag, format, args)
int         level;
const char *tag;
const char *format;
va_list     args;
{
	size_t nbytes;
	time_t now;
	char *nowstr;

	if (level < 0 || level >= sizeof (LEVEL_NAMES) / sizeof (LEVEL_NAMES[0]))
		return (0);
	if (level < _min_level)
		return (0);

	time (&now);
	nowstr = ctime (&now);
	nowstr[strlen(nowstr) - 1] = '\0';

	nbytes =  fprintf (_stream, "%-5s %s [%s] ",
				  LEVEL_NAMES[level],
				  nowstr,
				  tag);
	nbytes += vfprintf (_stream, format, args);
	fputc ('\n', _stream);
	return nbytes;

}

int clog_log (int level, const char *tag, const char *format, ...)
{
	size_t nbytes;
	va_list args;
	va_start (args, format);
	nbytes = vlog (level, tag, format, args);
	va_end (args);
	return nbytes;
}

int clog_debug (const char *tag, const char *format, ...)
{
	size_t nbytes;
	va_list args;
	va_start (args, format);
	nbytes = vlog (CLOG_DEBUG, tag, format, args);
	va_end (args);
	return nbytes;
}

int clog_info (const char *tag, const char *format, ...)
{
	size_t nbytes;
	va_list args;
	va_start (args, format);
	nbytes = vlog (CLOG_INFO, tag, format, args);
	va_end (args);
	return nbytes;
}

int clog_warn (const char *tag, const char *format, ...)
{
	size_t nbytes;
	va_list args;
	va_start (args, format);
	nbytes = vlog (CLOG_WARN, tag, format, args);
	va_end (args);
	return nbytes;
}

int clog_error (const char *tag, const char *format, ...)
{
	size_t nbytes;
	va_list args;
	va_start (args, format);
	nbytes = vlog (CLOG_ERROR, tag, format, args);
	va_end (args);
	return nbytes;
}

int clog_fatal (const char *tag, const char *format, ...)
{
	size_t nbytes;
	va_list args;
	va_start (args, format);
	nbytes = vlog (CLOG_FATAL, tag, format, args);
	va_end (args);
	return nbytes;
}

