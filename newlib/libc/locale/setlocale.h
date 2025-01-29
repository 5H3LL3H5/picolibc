/*-
 * Copyright (C) 1997 by Andrey A. Chernov, Moscow, Russia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/lib/libc/locale/setlocale.h,v 1.4 2001/12/20 18:28:52 phantom Exp $
 */

#ifndef _SETLOCALE_H_
#define	_SETLOCALE_H_

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <langinfo.h>
#include <stdbool.h>

__BEGIN_DECLS

extern struct __locale_t __global_locale;

#define __get_global_locale() (&__global_locale)

#define ENCODING_LEN 31
#define CATEGORY_LEN 11


struct lc_ctype_T
{
  const char	*codeset;	 /* codeset for mbtowc conversion */
  const char	*mb_cur_max;
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
  const char	*outdigits[10];
  const wchar_t	*woutdigits[10];
#endif
};
extern const struct lc_ctype_T _C_ctype_locale;

struct lc_monetary_T
{
  const char	*int_curr_symbol;
  const char	*currency_symbol;
  const char	*mon_decimal_point;
  const char	*mon_thousands_sep;
  const char	*mon_grouping;
  const char	*positive_sign;
  const char	*negative_sign;
  const char	*int_frac_digits;
  const char	*frac_digits;
  const char	*p_cs_precedes;
  const char	*p_sep_by_space;
  const char	*n_cs_precedes;
  const char	*n_sep_by_space;
  const char	*p_sign_posn;
  const char	*n_sign_posn;
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
  const char	*int_p_cs_precedes;
  const char	*int_p_sep_by_space;
  const char	*int_n_cs_precedes;
  const char	*int_n_sep_by_space;
  const char	*int_p_sign_posn;
  const char	*int_n_sign_posn;
  const char	*codeset;	 /* codeset for mbtowc conversion */
  const wchar_t	*wint_curr_symbol;
  const wchar_t	*wcurrency_symbol;
  const wchar_t	*wmon_decimal_point;
  const wchar_t	*wmon_thousands_sep;
  const wchar_t	*wpositive_sign;
  const wchar_t	*wnegative_sign;
#endif
};
extern const struct lc_monetary_T _C_monetary_locale;

struct lc_numeric_T
{
  const char	*decimal_point;
  const char	*thousands_sep;
  const char	*grouping;
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
  const char	*codeset;	 /* codeset for mbtowc conversion */
  const wchar_t	*wdecimal_point;
  const wchar_t	*wthousands_sep;
#endif
};
extern const struct lc_numeric_T _C_numeric_locale;

struct lc_time_T
{
  const char	*mon[12];
  const char	*month[12];
  const char	*wday[7];
  const char	*weekday[7];
  const char	*X_fmt;
  const char	*x_fmt;
  const char	*c_fmt;
  const char	*am_pm[2];
  const char	*date_fmt;
  const char	*alt_month[12];	/* unused */
  const char	*md_order;
  const char	*ampm_fmt;
  const char	*era;
  const char	*era_d_fmt;
  const char	*era_d_t_fmt;
  const char	*era_t_fmt;
  const char	*alt_digits;
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
  const char	*codeset;	 /* codeset for mbtowc conversion */
  const wchar_t	*wmon[12];
  const wchar_t	*wmonth[12];
  const wchar_t	*wwday[7];
  const wchar_t	*wweekday[7];
  const wchar_t	*wX_fmt;
  const wchar_t	*wx_fmt;
  const wchar_t	*wc_fmt;
  const wchar_t	*wam_pm[2];
  const wchar_t	*wdate_fmt;
  const wchar_t	*wampm_fmt;
  const wchar_t	*wera;
  const wchar_t	*wera_d_fmt;
  const wchar_t	*wera_d_t_fmt;
  const wchar_t	*wera_t_fmt;
  const wchar_t	*walt_digits;
#endif
};
extern const struct lc_time_T _C_time_locale;

struct	lc_messages_T
{
  const char	*yesexpr;
  const char	*noexpr;
  const char	*yesstr;
  const char	*nostr;
#ifdef __HAVE_LOCALE_INFO__
  const char	*codeset;	 /* codeset for mbtowc conversion */
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
  const wchar_t	*wyesexpr;
  const wchar_t	*wnoexpr;
  const wchar_t	*wyesstr;
  const wchar_t	*wnostr;
#endif
#endif
};
extern const struct lc_messages_T _C_messages_locale;

struct __lc_cats
{
  const void	*ptr;
  char		*buf;
};

struct __locale_t
{
  char			 categories[_LC_LAST][ENCODING_LEN + 1];
  int			(*wctomb) (char *, wchar_t,
				   mbstate_t *);
  int			(*mbtowc) (wchar_t *,
				   const char *, size_t, mbstate_t *);
  int			 cjk_lang;
#ifdef _MB_EXTENDED_CHARSETS_ANY
  const char		 *ctype_ptr;
#endif
  struct lconv		 lconv;
#ifndef __HAVE_LOCALE_INFO__
  char			 mb_cur_max[2];
  char			 ctype_codeset[ENCODING_LEN + 1];
  char			 message_codeset[ENCODING_LEN + 1];
#else
  struct __lc_cats	 lc_cat[_LC_LAST];
#endif
};

#define __WCTOMB        (__get_current_locale()->wctomb)
#define __MBTOWC        (__get_current_locale()->mbtowc)
#define __WCTOMB_L(l)   ((l)->wctomb)
#define __MBTOWC_L(l)   ((l)->mbtowc)

#ifdef _MB_CAPABLE
extern char *__loadlocale (struct __locale_t *, int, char *);
extern const char *__get_locale_env(int);
#endif /* _MB_CAPABLE */

extern struct lconv *__localeconv_l (struct __locale_t *locale);

#ifdef __HAVE_LOCALE_INFO__
#define NEWLIB_THREAD_LOCAL_LOCALE NEWLIB_THREAD_LOCAL
extern NEWLIB_THREAD_LOCAL_LOCALE struct __locale_t *_locale;
#endif

/* In POSIX terms the current locale is the locale used by all functions
   using locale info without providing a locale as parameter (*_l functions).
   The current locale is either the locale of the current thread, if the
   thread called uselocale, or the global locale if not. */
__elidable_inline struct __locale_t *
__get_current_locale (void)
{
#ifdef __HAVE_LOCALE_INFO__
  return _locale ?: __get_global_locale ();
#else
  return __get_global_locale();
#endif
}

/* Only access fixed "C" locale using this function.  Fake for !_MB_CAPABLE
   targets by returning ptr to globale locale. */
__elidable_inline struct __locale_t *
__get_C_locale (void)
{
#ifndef _MB_CAPABLE
  return __get_global_locale ();
#else
  extern const struct __locale_t __C_locale;
  return (struct __locale_t *) &__C_locale;
#endif
}


#ifdef __HAVE_LOCALE_INFO__
__elidable_inline const struct lc_ctype_T *
__get_ctype_locale (struct __locale_t *locale)
{
  return (const struct lc_ctype_T *) (locale)->lc_cat[LC_CTYPE].ptr;
}

__elidable_inline const struct lc_ctype_T *
__get_current_ctype_locale (void)
{
  return (const struct lc_ctype_T *)
	 _locale->lc_cat[LC_CTYPE].ptr;
}
#endif

__elidable_inline int
__locale_mb_cur_max_l (struct __locale_t *locale)
{
#ifdef __HAVE_LOCALE_INFO__
  return __get_ctype_locale (locale)->mb_cur_max[0];
#else
  return locale->mb_cur_max[0];
#endif
}

#ifdef __HAVE_LOCALE_INFO__
__elidable_inline const struct lc_monetary_T *
__get_monetary_locale (struct __locale_t *locale)
{
  return (const struct lc_monetary_T *) (locale)->lc_cat[LC_MONETARY].ptr;
}

__elidable_inline const struct lc_monetary_T *
__get_current_monetary_locale (void)
{
  return (const struct lc_monetary_T *)
	 _locale->lc_cat[LC_MONETARY].ptr;
}

__elidable_inline const struct lc_numeric_T *
__get_numeric_locale (struct __locale_t *locale)
{
  return (const struct lc_numeric_T *) (locale)->lc_cat[LC_NUMERIC].ptr;
}

__elidable_inline const struct lc_numeric_T *
__get_current_numeric_locale (void)
{
  return (const struct lc_numeric_T *)
	 _locale->lc_cat[LC_NUMERIC].ptr;
}

__elidable_inline const struct lc_time_T *
__get_time_locale (struct __locale_t *locale)
{
  return (const struct lc_time_T *) (locale)->lc_cat[LC_TIME].ptr;
}

__elidable_inline const struct lc_time_T *
__get_current_time_locale (void)
{
  return (const struct lc_time_T *)
	 _locale->lc_cat[LC_TIME].ptr;
}

__elidable_inline const struct lc_messages_T *
__get_messages_locale (struct __locale_t *locale)
{
  return (const struct lc_messages_T *) (locale)->lc_cat[_LC_MESSAGES].ptr;
}

__elidable_inline const struct lc_messages_T *
__get_current_messages_locale (void)
{
  return (const struct lc_messages_T *)
	 _locale->lc_cat[_LC_MESSAGES].ptr;
}

#else /* ! __HAVE_LOCALE_INFO__ */
__elidable_inline const struct lc_monetary_T *
__get_monetary_locale (struct __locale_t *locale)
{
  (void) locale;
  return &_C_monetary_locale;
}

__elidable_inline const struct lc_monetary_T *
__get_current_monetary_locale (void)
{
  return &_C_monetary_locale;
}

__elidable_inline const struct lc_numeric_T *
__get_numeric_locale (struct __locale_t *locale)
{
  (void) locale;
  return &_C_numeric_locale;
}

__elidable_inline const struct lc_numeric_T *
__get_current_numeric_locale (void)
{
  return &_C_numeric_locale;
}

__elidable_inline const struct lc_time_T *
__get_time_locale (struct __locale_t *locale)
{
  (void) locale;
  return &_C_time_locale;
}

__elidable_inline const struct lc_time_T *
__get_current_time_locale (void)
{
  return &_C_time_locale;
}

__elidable_inline const struct lc_messages_T *
__get_messages_locale (struct __locale_t *locale)
{
  (void) locale;
  return &_C_messages_locale;
}

__elidable_inline const struct lc_messages_T *
__get_current_messages_locale (void)
{
  return &_C_messages_locale;
}
#endif /* !__HAVE_LOCALE_INFO__ */

/* LC_NUMERIC data */
#define DECIMAL_POINT           (__get_current_numeric_locale()->decimal_point)
#define DECIMAL_POINT_L(l)      (__get_numeric_locale(l)->decimal_point)
#define THOUSANDS_SEP           (__get_current_numeric_locale()->thousands_sep)
#define THOUSANDS_SEP_L(l)      (__get_numeric_locale(l)->thousands_sep)
#define NUMERIC_GROUPING        (__get_current_numeric_locale()->grouping)
#define NUMERIC_GROUPING_L(l)   (__get_numeric_locale(l)->grouping)
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
#define WDECIMAL_POINT          (__get_current_numeric_locale()->wdecimal_point)
#define WDECIMAL_POINT_L(l)     (__get_numeric_locale(l)->wdecimal_point)
#define WTHOUSANDS_SEP          (__get_current_numeric_locale()->wthousands_sep)
#define WTHOUSANDS_SEP_L(l)     (__get_numeric_locale(l)->wthousands_sep
#endif

/* LC_TIME data */
#define TIME_ERA_L(l)           (__get_time_locale(l)->era)
#define TIME_ERA                (__get_current_time_locale()->era)
#define TIME_ERA_D_T_FMT_L(l)   (__get_time_locale(l)->era_d_t_fmt)
#define TIME_ERA_D_T_FMT        (__get_current_time_locale()->era_d_t_fmt)
#define TIME_ERA_D_FMT_L(l)     (__get_time_locale(l)->era_d_fmt)
#define TIME_ERA_D_FMT          (__get_current_time_locale()->era_d_fmt)
#define TIME_ERA_T_FMT_L(l)     (__get_time_locale(l)->era_t_fmt)
#define TIME_ERA_T_FMT          (__get_current_time_locale()->era_t_fmt)
#define TIME_ALT_DIGITS_L(l)    (__get_time_locale(l)->alt_digits)
#define TIME_ALT_DIGITS         (__get_current_time_locale()->alt_digits)
#define TIME_WDAY               (__get_current_time_locale()->wday)
#define TIME_WEEKDAY            (__get_current_time_locale()->weekday)
#define TIME_MON                (__get_current_time_locale()->mon)
#define TIME_MONTH              (__get_current_time_locale()->month)
#define TIME_AM_PM              (__get_current_time_locale()->am_pm)
#define TIME_C_FMT              (__get_current_time_locale()->c_fmt)
#define TIME_X_FMT              (__get_current_time_locale()->x_fmt)
#define TIME_UX_FMT             (__get_current_time_locale()->X_fmt)
#define TIME_AMPM_FMT           (__get_current_time_locale()->ampm_fmt)

#ifdef __HAVE_LOCALE_INFO_EXTENDED__
#define WTIME_ERA_L(l)          (__get_time_locale(l)->wera)
#define WTIME_ERA               (__get_current_time_locale()->wera)
#define WTIME_ERA_D_T_FMT_L(l)  (__get_time_locale(l)->wera_d_t_fmt)
#define WTIME_ERA_D_T_FMT       (__get_current_time_locale()->wera_d_t_fmt)
#define WTIME_ERA_D_FMT_L(l)    (__get_time_locale(l)->wera_d_fmt)
#define WTIME_ERA_D_FMT         (__get_current_time_locale()->wera_d_fmt)
#define WTIME_ERA_T_FMT_L(l)    (__get_time_locale(l)->wera_t_fmt)
#define WTIME_ERA_T_FMT         (__get_current_time_locale()->wera_t_fmt)
#define WTIME_ALT_DIGITS_L(l)   (__get_time_locale(l)->walt_digits)
#define WTIME_ALT_DIGITS        (__get_current_time_locale()->walt_digits)
#define WTIME_WDAY              (__get_current_time_locale()->wwday)
#define WTIME_WEEKDAY           (__get_current_time_locale()->wweekday)
#define WTIME_MON               (__get_current_time_locale()->wmon)
#define WTIME_MONTH             (__get_current_time_locale()->wmonth)
#define WTIME_AM_PM             (__get_current_time_locale()->wam_pm)
#define WTIME_C_FMT             (__get_current_time_locale()->wc_fmt)
#define WTIME_X_FMT             (__get_current_time_locale()->wx_fmt)
#define WTIME_UX_FMT            (__get_current_time_locale()->wX_fmt)
#define WTIME_AMPM_FMT          (__get_current_time_locale()->wampm_fmt)
#endif

__elidable_inline const char *
__locale_charset (struct __locale_t *locale)
{
  (void) locale;
#ifdef __HAVE_LOCALE_INFO__
  return __get_ctype_locale (locale)->codeset;
#else
  return locale->ctype_codeset;
#endif
}

__elidable_inline const char *
__current_locale_charset (void)
{
#ifdef __HAVE_LOCALE_INFO__
  return __get_current_ctype_locale ()->codeset;
#else
  return __get_current_locale()->ctype_codeset;
#endif
}

__elidable_inline const char *
__locale_msgcharset (void)
{
#ifdef __HAVE_LOCALE_INFO__
#ifdef __HAVE_LOCALE_INFO_EXTENDED__
  return (char *) __get_current_messages_locale ()->codeset;
#else
  return (char *) __get_current_ctype_locale ()->codeset;
#endif
#else
  return (char *) __get_current_locale()->message_codeset;
#endif
}

__elidable_inline int
__locale_cjk_lang (void)
{
  return __get_current_locale()->cjk_lang;
}

__elidable_inline bool
__locale_is_C(struct __locale_t *locale)
{
    if (!locale)
        locale = __get_current_locale();
    const char *ctype_locale = locale->categories[LC_CTYPE - LC_ALL];

    return strcmp (ctype_locale, "C") == 0;
}

int __ctype_load_locale (struct __locale_t *, const char *, void *,
			 const char *, int);
int __monetary_load_locale (struct __locale_t *, const char *, void *,
			    const char *);
int __messages_load_locale (struct __locale_t *, const char *, void *,
			    const char *);

__END_DECLS

#endif /* !_SETLOCALE_H_ */
