#include <stdio.h>

#ifndef _CLOG_H_
#define _CLOG_H_

/* Constants */

/* Log levels */
#define CLOG_DEBUG 0
#define CLOG_INFO 1
#define CLOG_WARN 2
#define CLOG_ERROR 3
#define CLOG_FATAL 4

/* Timing modes */
enum clog_timing_mode { CLOG_TIMING_ABSOLUTE, CLOG_TIMING_RELATIVE };

extern void clog_init(int min_level, FILE *stream,
                      enum clog_timing_mode timing_mode);

extern int clog_log(int level, const char *tag, const char *message, ...);

extern void clog_perror(int level, const char *tag, const char *s);

extern int clog_debug(const char *tag, const char *format, ...);
extern int clog_info(const char *tag, const char *format, ...);
extern int clog_warn(const char *tag, const char *format, ...);
extern int clog_error(const char *tag, const char *format, ...);
extern int clog_fatal(const char *tag, const char *format, ...);

#endif /* _CLOG_H_ */
