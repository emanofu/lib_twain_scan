#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "ptbl_path_max.h"
#include "ptbl_vsnprintf.h"
#include "pri.h"

static char *pri_param_cp_com_name = "#";

void pri_funct_set_cp_title( char *cp_title )
{
	pri_param_cp_com_name = cp_title;
}

/* print  Valiable_argument */
void pri_funct_msg_v( const char* fmt, ...)
{
	int	i_ret;
	va_list ap;
	char	buf[PTBL_PATH_MAX];

	va_start(ap, fmt);
	i_ret = vsnprintf( buf,PTBL_PATH_MAX, fmt, ap);
	va_end(ap);
	if (i_ret < 0) {
		(void)fprintf( stderr,
			"\007Error : 1 : vsnprintf(-) return <%d>\n",
			i_ret);
		(void)fflush( stderr );
		return;
	}

	/* ���Ѱ���,���� */
	(void)fprintf(stdout,"%s", buf);
	(void)fflush(stdout);
}

/* print  Valiable_argument, Return_code */
void pri_funct_msg_vr( const char* fmt, ...)
{
	int	i_ret;
	va_list ap;
	char	buf[PTBL_PATH_MAX];

	va_start(ap, fmt);
	i_ret = vsnprintf( buf,PTBL_PATH_MAX, fmt, ap);
	va_end(ap);
	if (i_ret < 0) {
		(void)fprintf( stderr,
			"\007Error : 1 : vsnprintf(-) return <%d>\n",
			i_ret);
		(void)fflush( stderr );
		return;
	}

	/* ���Ѱ���,���� */
	(void)fprintf(stdout,"%s\n", buf);
	(void)fflush(stdout);
}

/* print  Title, Time_stamp, Valiable_argument, Return_code */
void pri_funct_msg_ttvr( const char* fmt, ...)
{
	time_t	tt;
	char	*cc;

	int	i_ret;
	va_list ap;
	char	buf[PTBL_PATH_MAX];

	tt = time(NULL);
	cc = asctime(localtime(&tt));
	/*
		cc��26ʸ���ȥ̥�ʸ�������ä�ʸ����ؤΥݥ��󥿡�
			Example : "Fri Sep 13 00:00:00 1986\n\0"
				   12345678901234567890123456
				   01234567890123456789012345
		cc�μ���ʸ�����static�ΰ�ʤΤ�free()���ƤϤ����ޤ���
	*/
	cc[24] = '\0';

	va_start(ap, fmt);
	i_ret = vsnprintf( buf,PTBL_PATH_MAX, fmt, ap);
	va_end(ap);
	if (i_ret < 0) {
		(void)fprintf( stderr,
			"\007Error : 2 : vsnprintf(-) return <%d>\n",
			i_ret);
		(void)fflush( stderr );
		return;
	}

	/* �٥�,�����ȥ�,����,���Ѱ���,���� */
	(void)fprintf(stdout,"%s  %s  %s\n",
		pri_param_cp_com_name, cc, buf);
	(void)fflush(stdout);
}
/* print  Bell, Title, Time_stamp, Valiable_argument, Return_code */
void pri_funct_err_bttvr( const char* fmt, ...)
{
	time_t	tt;
	char	*cc;

	int	i_ret;
	va_list ap;
	char	buf[PTBL_PATH_MAX];

	tt = time(NULL);
	cc = asctime(localtime(&tt));
	/*
		cc��26ʸ���ȥ̥�ʸ�������ä�ʸ����ؤΥݥ��󥿡�
			Example : "Fri Sep 13 00:00:00 1986\n\0"
				   12345678901234567890123456
				   01234567890123456789012345
		cc�μ���ʸ�����static�ΰ�ʤΤ�free()���ƤϤ����ޤ���
	*/
	cc[24] = '\0';
	/* 26-character Example : "Fri Sep 13 00:00:00 1986\n\0" */

	va_start(ap, fmt);
	i_ret = vsnprintf( buf,PTBL_PATH_MAX, fmt, ap);
	va_end(ap);
	if (i_ret < 0) {
		(void)fprintf( stderr,
			"\007Error : 3 : vsnprintf(-) return <%d>\n",
			i_ret);
		(void)fflush( stderr );
		return;
	}

	/* �٥�,�����ȥ�,����,���Ѱ���,���� */
	(void)fprintf(stderr,"\007%s  %s  %s\n",
		pri_param_cp_com_name, cc, buf);
	(void)fflush(stderr);
}
/******int main()
{
pri_funct_set_cp_title( "pri test main program" );
pri_funct_err_bttvr( "Error is ? : x1 %ld y1 %ld pi %.16g",
128,256, 3.1415926535897932384626433832795029 );
pri_funct_msg_ttvr( "Message is ? : x1 %ld y1 %ld pi %.16g",
128,256, 3.1415926535897932384626433832795029 );
}******/
