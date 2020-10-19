#ifndef _CLOG_H_
#define _CLOG_H_

/* Constants */

/* Log levels */
extern const int CLOG_DEBUG = 0;
extern const int CLOG_INFO = 1;
extern const int CLOG_WARN = 2;
extern const int CLOG_ERROR = 3;
extern const int CLOG_FATAL = 4;

extern void clog_init (int min_level, FILE *stream);

extern int clog_log (int level, const char *tag, const char *message);

extern int clog_debug (const char *tag, const char *message);
extern int clog_info (const char *tag, const char *message);
extern int clog_warn (const char *tag, const char *message);
extern int clog_error (const char *tag, const char *message);
extern int clog_fatal (const char *tag, const char *message);

#endif /* _CLOG_H_ */

