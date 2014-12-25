#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined _WIN32
#elif defined __HP_aCC
# include <sys/types.h>
# include <sys/stat.h>
#else
# include <unistd.h>
#endif

#include "ptbl_returncode.h"
#include "ptbl_funct.h"

/* �ǥ��쥯�ȥꤢ�뤤�ϥե����뤬
	¸�ߤ���� 1 ���֤�
	�ʤ����   0 ���֤�
   ���֤�
 */
int ptbl_dir_or_file_is_exist( char *cp_path )
{
#if defined _WIN32
	int i_len,i_ret;
	char cc;
	struct _stat t_stat;

	/* cp_path��Dir�ΤȤ�
		��ʸ����'/'��'\'
	����_stat()��Ư���ʤ��Τ���ʸ������Ū�˽���
		��������"n:/"�ξ������
	*/
	cc = 0;
	i_len = (int)strlen(cp_path);
	if (	(2 < i_len) && 
		(':' != cp_path[i_len-2]) &&
		(
			('\\' == cp_path[i_len-1]) ||
			('/'  == cp_path[i_len-1])
		)
	) {
		cc = cp_path[i_len-1];
		cp_path[i_len-1] = '\0';
	}

	i_ret = _stat( cp_path, &t_stat );

	if (0 != cc) {
		cp_path[i_len-1] = cc;
	}

	return (0 == i_ret);
#else
	struct stat t_stat;
	return (0 == stat( cp_path, &t_stat));
#endif
}

