#include <stdio.h>
#include "pri.h"

static int32_t	pri_param_i32_ysize,
		pri_param_i32_pos_before;

/* ������ȥ����󳫻� */
void pri_funct_cv_start( int32_t i32_ys )
{
	/* ����ɽ�� */
	(void)fprintf(stdout,
	"0%%  10   20   30   40   50   60   70   80   90   100%%\n" );
	(void)fprintf(stdout,
	"....v....v....v....v....v....v....v....v....v....v\n" );

	/* �ѥ�᡼��������� */
	pri_param_i32_ysize = i32_ys;
	pri_param_i32_pos_before = 0;
}
/* ������ȥ�����¹��� */
void pri_funct_cv_run( int32_t i32_y )
{
	int32_t	i32_pos_current, ii;

	/* ������θ��߰���(1...50) */
	i32_pos_current = 50 * (i32_y + 1) / pri_param_i32_ysize;

	/* ����45�٤��뤯�륫���󥿡� */
	/******switch (i32_y%4) {
	case 0: (void)fprintf(stdout, "-\b"  ); break;
	case 1: (void)fprintf(stdout, "\\\b" ); break;
	case 2: (void)fprintf(stdout, "|\b"  ); break;
	case 3: (void)fprintf(stdout, "/\b"  ); break;
	}
	(void)fflush(stdout);******/

	/* ��������������֤�Ʊ���ʤ�ȴ���� */
	if (i32_pos_current == pri_param_i32_pos_before) return;

	/* �������ʤ���Ȥ� */
	for (ii = pri_param_i32_pos_before; ii<i32_pos_current; ++ii) {
		/* �������ʾ�ʤ���Ȥ��Τ����� */
		if ((ii + 1) < i32_pos_current) {
			(void)fprintf(stdout, "." );
		}
		/* ������ʬ */
		else {
			(void)fprintf(stdout, "^" );
		}
	}
	(void)fflush(stdout);

	/* ���߰��֤򵭲����� */
	pri_param_i32_pos_before = i32_pos_current;
}
/* ������ȥ�����λ */
void pri_funct_cv_end( void )
{
	/* ���� */
	(void)fprintf(stdout, "\n" );
}

/**********main( int argc, char *argv[] )
{
	int32_t	i32_ys,ii;

	if (2 != argc) {
		(void)fprintf(stdout, "Usage : %s ysize\n", argv[0] );
		exit(0);
	}
	i32_ys = atol(argv[1]);

	pri_funct_cv_start( i32_ys );
	for (ii = 0L; ii < i32_ys; ++ii) {
		pri_funct_cv_run( ii );
		//usleep(100000);
	}
	pri_funct_cv_end();
}**********/
