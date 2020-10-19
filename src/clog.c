#include <stdio.h>
#include <time.h>
#include <string.h>

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

extern int clog_log (level, tag, message)
int level;
const char *tag;
const char *message;
{
	if (level < 0 || level >= sizeof (LEVEL_NAMES) / sizeof (LEVEL_NAMES[0]))
		return (0);
	if (level < _min_level)
		return (0);

	time_t now;
	time (&now);
	char *nowstr = ctime (&now);
	nowstr[strlen(nowstr) - 1] = '\0';

	return fprintf (_stream, "%-5s %s [%s] %s\n",
				  LEVEL_NAMES[level],
				  nowstr,
				  tag,
				  message);
}

extern int clog_debug (tag, message)
const char *tag;
const char *message;
{
	return clog_log (CLOG_DEBUG, tag, message);
}

extern int clog_info (tag, message)
const char *tag;
const char *message;
{
	return clog_log (CLOG_INFO, tag, message);
}

extern int clog_warn (tag, message)
const char *tag;
const char *message;
{
	return clog_log (CLOG_WARN, tag, message);
}

extern int clog_error (tag, message)
const char *tag;
const char *message;
{
	return clog_log (CLOG_ERROR, tag, message);
}

extern int clog_fatal (tag, message)
const char *tag;
const char *message;
{
	return clog_log (CLOG_FATAL, tag, message);
}

