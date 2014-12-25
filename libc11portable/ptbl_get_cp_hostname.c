#if defined _WIN32
# include <stdlib.h>	/* getenv() */
#else
# include <unistd.h>	/* gethostname() */
# include <string.h>	/* strchr() */
# ifndef  HOST_NAME_MAX
#  define HOST_NAME_MAX 255
# endif
  /*���  'man gethostname'���
	SUSv2�Ǥ�
		�֥ۥ���̾��255�Х��Ȥ����¤�����
	���Ȥ��ݾڤ��Ƥ���
	POSIX 1003.1-2001 �Ǥ�
		�֥ۥ���̾(��ü�Υ̥�ʸ���ϴޤޤʤ�)��
		HOST_NAME_MAX�Х��Ȥ����¤�����
	���Ȥ��ݾڤ��Ƥ���
  */
#endif

#include "ptbl_funct.h"

/* �ۥ���̾�����롢�ۥ���̾�����Ĥ���ʤ��Ȥ���NULL���᤹ */
char *ptbl_get_cp_hostname( void )
{
	char	*cp_hostname;

#if defined _WIN32
	/* Windows�Ǥϡ��ۥ���̾�ϴĶ��ѿ�����Ȥ� */
	cp_hostname = getenv( "COMPUTERNAME" );
#else
	static char ca_hostname[HOST_NAME_MAX];
	char *cp_tmp;

	if (0 != gethostname(ca_hostname, HOST_NAME_MAX)) {
		cp_hostname = NULL;
	}
	else {
		cp_hostname = ca_hostname;

		/* �ɥᥤ��̾����ۥ���̾��������ʬ�Τ��ڤ�Ф� */
		/* hostname.co.jp --> hostname */
		cp_tmp = strchr( cp_hostname, (int)'.' );
		if (NULL != cp_tmp) { cp_tmp[0] = '\0'; }
	}
#endif
	return cp_hostname;
}

