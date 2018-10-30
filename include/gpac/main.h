/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Authors: Jean Le Feuvre
 *			Copyright (c) Telecom ParisTech 2017-2018
 *					All rights reserved
 *
 *  This file is part of GPAC 
 *
 *  GPAC is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  GPAC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef _GF_MAIN_H_
#define _GF_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *	\file <gpac/main.h>
 *	\brief main() macro for win32.
 */
	
/*!
 * \addtogroup cst_grp Constants
 *	\brief main() macro for windows systems to handle UTF input.
 *
 *	@{
 */

#include <gpac/setup.h>
#include <gpac/utf.h>




#if defined(WIN32) && !defined(NO_WMAIN)

#define GPAC_DEC_MAIN(__fun) \
int wmain( int argc, wchar_t** wargv )\
{\
	int i;\
	int res;\
	size_t len;\
	size_t res_len;\
	char **argv;\
	argv = (char **)malloc(argc*sizeof(wchar_t *));\
	for (i = 0; i < argc; i++) {\
		wchar_t *src_str = wargv[i];\
		len = UTF8_MAX_BYTES_PER_CHAR*gf_utf8_wcslen(wargv[i]);\
		argv[i] = (char *)malloc(len + 1);\
		res_len = gf_utf8_wcstombs(argv[i], len, &src_str);\
		argv[i][res_len] = 0;\
		if (res_len > len) {\
			fprintf(stderr, "Length allocated for conversion of wide char to UTF-8 not sufficient\n");\
			return -1;\
		}\
	}\
	res = __fun(argc, argv);\
	for (i = 0; i < argc; i++) {\
		free(argv[i]);\
	}\
	free(argv);\
	return res;\
}

#else

#define GPAC_DEC_MAIN(__fun) \
int main(int argc, char **argv) {\
	return __fun( argc, argv ); \
}

#endif //win32

/*! structure holding a gpac arg (not a filter arg)*/
typedef struct
{
	/*! name of arg*/
	const char *name;
	/*! alternate name of arg*/
	const char *altname;
	/*! description of arg*/
	const char *desc;
	/*! default value of arg*/
	const char *val;
	/*! possible value of arg*/
	const char *values;
	/*! argument type for UI construction - note that argument values are not parsed and shall be set as strings*/
	u16 type;
	/*! argument flags*/
	u16 flags;
} GF_GPACArg;

/*! argument applies to the log subsystem*/
#define GF_ARG_IS_LOG 1<<1
/*! argument applies to the HTTP subsystem*/
#define GF_ARG_IS_HTTP 1<<2
//these 3 values match argument hints of filters
/*! argument is of advanced type*/
#define GF_ARG_HINT_ADVANCED 1<<3
/*! argument is of expert type*/
#define GF_ARG_HINT_EXPERT (1<<4)
/*! argument should not be presented in UIs*/
#define GF_ARG_HINT_HIDE 1<<5

/*! argument is a boolean*/
#define GF_ARG_BOOL		0
/*! argument is a 32 bit integer*/
#define GF_ARG_INT		1
/*! argument is a double*/
#define GF_ARG_DOUBLE	2
/*! argument is a string*/
#define GF_ARG_STRING	3
/*! argument is a camma-separated list of strings*/
#define GF_ARG_STRINGS	4

#define GF_DEF_ARG(_a, _b, _c, _d, _e, _f, _g) {_a, _b, _c, _d, _e, _f, _g}

/*! gets the options defined for libgpac
\return array of options*/
const GF_GPACArg *gf_gpac_args();

/*! check if the given option is a libgpac argument
\return GF_TRUE if this is the case, GF_FALSE otherwise*/
Bool gf_is_libgpac_arg(const char *arg_name);

/*! @} */

#ifdef __cplusplus
}
#endif

#endif	//_GF_MAIN_H_

