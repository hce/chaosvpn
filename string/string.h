#ifndef __STRING_H
#define __STRING_H

#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


/* FUNCTIONS WORKING WITH struct string */
/* ------------------------------------ */

struct string {
    size_t length;
    size_t size;
    size_t growby;
    char* s;
};

void string_clear(struct string*);
bool string_concat(struct string*, const char*);
bool string_concatb(struct string*, const char*, size_t);
bool string_concat_sprintf(struct string* s, const char *msg, ...);
bool string_putc(struct string*, char);
bool string_putint(struct string*, int);
void string_free(struct string*);
char* string_get(struct string*);
bool string_init(struct string*, size_t, size_t);
void string_move(struct string*, struct string*);
bool string_equals(struct string*, struct string*);
void string_lazyinit(struct string*, size_t);
bool string_initfromstringz(struct string*, const char *);
bool string_read(struct string*, const int, const size_t, intptr_t*);
void string_hexdump(struct string*, const void *, const size_t);
void debug_hexdump(const void *, const size_t);


static inline size_t string_length(struct string *s) {
    /* amount of bytes filled with content */
    return s->length;
}

static inline size_t string_size(struct string *s) {
    /* amount of memory (in bytes) currently allocated */
    return s->size;
}

static inline bool
string_concats(struct string* s, struct string* ss)
{
    return string_concatb(s, ss->s, ss->length);
}

static inline bool
string_ensurez(struct string* s)
{
    if (s->s)
        if (s->s[s->length - 1] == 0)
            return true;
    if (!string_putc(s, 0)) return false;
    --s->length;
    return true;
}

static inline void
string_mkstatic(struct string* s, char* z)
{
    s->s = z;
    s->growby = 0;
    s->size = strlen(z);
    s->length = s->size;
}


/* FUNCTIONS WORKING WITH PLAIN char* */
/* ---------------------------------- */

static inline bool str_is_empty(const char *s) {
    if (s != NULL && strlen(s) > 0) {
        return false;
    } else {
        return true;
    }
}
static inline bool str_is_nonempty(const char *s) {
    if (s != NULL && strlen(s) > 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool str_is_true(const char *s, bool def) {
    if (str_is_nonempty(s)) {
        if (strcmp(s, "0")==0 || strcasecmp(s,"no")==0) {
            return false;
        } else if (strcmp(s, "1")==0 || strcasecmp(s,"yes")==0) {
            return true;
        } else {
            return def; /* TODO: something better needed */
        }
    } else {
        return def;
    }
}

/* str_split_at - break string at first delimiter, return remainder */
static inline char *str_split_at(char *string, int delimiter) {
    char *cp;

    if ((cp = strchr(string, delimiter)) != NULL)
        *cp++ = 0;

    return (cp);
}

/* str_split_at_right - break string at last delimiter, return remainder */
static inline char *str_split_at_right(char *string, int delimiter) {
    char *cp;

    if ((cp = strrchr(string, delimiter)) != NULL)
        *cp++ = 0;
    return (cp);
}

/* str_alldig - return true if string is all digits */
static inline bool str_alldig(const char *string) {
    const char *cp;

    if (*string == 0)
        return false;
    for (cp = string; *cp != 0; cp++)
        if (!isascii((unsigned char) *cp) || !isdigit((unsigned char) *cp))
            return false;
    return true;
}

static inline char *str_skip_spaces(const char *str) {
    while (isspace(*str))
        ++str;
    return (char *)str;
}

static inline char *str_trim(char *s) {
    size_t size;
    char *end;
    
    s = str_skip_spaces(s);
    size = strlen(s);
    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    return s;
}

#endif
