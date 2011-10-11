/*
 *
 * stdbool.h
 */

#ifndef _STDBOOL_H
#define _STDBOOL_H

#ifndef __cplusplus

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
#	if !defined(__GNUC__) ||(__GNUC__ < 3)
typedef char _Bool;		/* For C compilers without _Bool */
#	endif
#endif

#define bool  _Bool
#define true  1
#define false 0

#endif

#endif /* _STDBOOL_H */
