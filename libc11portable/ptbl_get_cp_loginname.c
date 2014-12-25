#if defined _WIN32
# include <stdlib.h>	/* getenv() */
#else
# include <unistd.h>	/* getlogin() */
#endif

#include "ptbl_funct.h"

/* login̾������(Windows�Ǥϥ�����̾)���Ĥ���ʤ��Ȥ���NULL���᤹ */
char *ptbl_get_cp_loginname( void )
{
	char	*cp_loginname;

#if defined _WIN32
	/* Windows�Ǥ�(������̾��)�Ķ��ѿ�USERNAME����Ȥ� */
	/* getenv()�ϴĶ�ʸ����ؤ��ͤؤΥݥ��󥿤��֤� */
	cp_loginname = getenv( "USERNAME" );
#else
	/* getlogin()�ϥ桼����̾��ʸ����ؤΥݥ��󥿤��֤� */
	cp_loginname = getlogin();
#endif

	return cp_loginname;
}

