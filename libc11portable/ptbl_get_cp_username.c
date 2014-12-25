#if defined _WIN32
# include <stdlib.h>	/* getenv() */
#else
# include <sys/types.h>	/* getuid(),getpwuid() */
# include <unistd.h>	/* getuid() */
# include <pwd.h>	/* getpwuid() */
#endif
#include "ptbl_funct.h"

/* ���ߤΥ桼����̾������(Cygwin�Ǥ�Admin...)
   ���Ĥ���ʤ��Ȥ���NULL���᤹ */
char *ptbl_get_cp_username( void )
{
	char	*cp_username;

#if defined _WIN32
	/* Windows�Ǥ�(user̾��)�Ķ��ѿ�USERNAME����Ȥ� */
	/* getenv()�ϴĶ�ʸ����ؤ��ͤؤΥݥ��󥿤��֤� */
	cp_username = getenv( "USERNAME" );
#else
	/* cp_username = tp_pw->pw_name;��������ϡ�
	   �ؿ�����̤��Ƥ�¸�ߤ���? */
	struct passwd *tp_pw; /* static�Ǥʤ��Ƥ⤤��? */
	tp_pw = getpwuid( getuid() );
	if (NULL == tp_pw) { cp_username = NULL; }
	else               { cp_username = tp_pw->pw_name; }

#endif
	return cp_username;
}

