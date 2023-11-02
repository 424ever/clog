#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "clog.h"

static const char *LEVEL_NAMES[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

static int _min_level = 0;
static FILE *_stream = NULL;
static enum clog_timing_mode _timing_mode;
static clock_t start_time;

/* Function Definition */
extern void clog_init(min_level, stream, timing_mode) int min_level;
FILE *stream;
enum clog_timing_mode timing_mode;
{
  _min_level = min_level;
  _stream = stream;
  _timing_mode = timing_mode;
  start_time = clock();
}

static int vlog(level, tag, format, args)
int level;
const char *tag;
const char *format;
va_list args;
{
  size_t nbytes;
  time_t now;
  double secs;
  char *nowstr;

  if (level < 0 || level >= sizeof(LEVEL_NAMES) / sizeof(LEVEL_NAMES[0]))
    return (0);
  if (level < _min_level)
    return (0);

  if (_timing_mode == CLOG_TIMING_ABSOLUTE) {
    time(&now);
    nowstr = ctime(&now);
    nowstr[strlen(nowstr) - 1] = '\0';
  } else if (_timing_mode == CLOG_TIMING_RELATIVE) {
    secs = 1.0 * (clock() - start_time) / CLOCKS_PER_SEC;
    nowstr = (char *)malloc(7 + 5 + 1);
    sprintf(nowstr, "%7.5lf", secs);
  }

  nbytes = fprintf(_stream, "%-5s %s [%s] ", LEVEL_NAMES[level], nowstr, tag);
  nbytes += vfprintf(_stream, format, args);
  fputc('\n', _stream);
  if (_timing_mode == CLOG_TIMING_RELATIVE)
    free(nowstr);
  return nbytes;
}

int clog_log(int level, const char *tag, const char *format, ...) {
  size_t nbytes;
  va_list args;
  va_start(args, format);
  nbytes = vlog(level, tag, format, args);
  va_end(args);
  return nbytes;
}

int clog_debug(const char *tag, const char *format, ...) {
  size_t nbytes;
  va_list args;
  va_start(args, format);
  nbytes = vlog(CLOG_DEBUG, tag, format, args);
  va_end(args);
  return nbytes;
}

int clog_info(const char *tag, const char *format, ...) {
  size_t nbytes;
  va_list args;
  va_start(args, format);
  nbytes = vlog(CLOG_INFO, tag, format, args);
  va_end(args);
  return nbytes;
}

int clog_warn(const char *tag, const char *format, ...) {
  size_t nbytes;
  va_list args;
  va_start(args, format);
  nbytes = vlog(CLOG_WARN, tag, format, args);
  va_end(args);
  return nbytes;
}

int clog_error(const char *tag, const char *format, ...) {
  size_t nbytes;
  va_list args;
  va_start(args, format);
  nbytes = vlog(CLOG_ERROR, tag, format, args);
  va_end(args);
  return nbytes;
}

int clog_fatal(const char *tag, const char *format, ...) {
  size_t nbytes;
  va_list args;
  va_start(args, format);
  nbytes = vlog(CLOG_FATAL, tag, format, args);
  va_end(args);
  return nbytes;
}

void clog_perror(int level, const char *tag, const char *s) {
  if (s != NULL && *s != '\0') {
    clog_log(level, tag, "%s: %s", s, strerror(errno));
  } else {
    clog_log(level, tag, "%s", strerror(errno));
  }
}
