#ifndef __ptbl_stdint_h__
#define __ptbl_stdint_h__

/* 固定ビット数の整数変数の定義 */

/* Windowsではstdint.hが見つからない */
#if defined _WIN32
typedef signed char		int8_t;
typedef short int		int16_t;
typedef int			int32_t;
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;

/* Cygwinではstdint.hが見つからない */
/***#elif defined i386_redhat_cygwin1_3_15
# include <sys/types.h>
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;***/

/* IRIX6.5.xとHP-UX B.11.11ではstdint.hが見つからない */
/***#elif defined mips3n32_sgi_irix6_5 || defined __HP_aCC
# include <inttypes.h>***/

#else
# include <stdint.h>
#endif

#endif /* !__ptbl_stdint_h__ */
