#include <stdlib.h>	/* getenv() */
#include <string.h>	/* strrchr() */
#include <assert.h>	/* assert() */

#include "ptbl_funct.h"

/* �ե�����ѥ�����ե�����̾�Τ�����(����.exe���ϻĤ�) */
char *ptbl_get_cp_filename_from_path( char *cp_filepath )
{
	char	*cp_sepa, *cp_tmp, *cp_comm_body;

	cp_comm_body = cp_filepath;
	cp_sepa = ptbl_get_cp_path_separeter();

	cp_tmp = strrchr( cp_filepath, (int)(cp_sepa[0]) );
	if (NULL != cp_tmp) { cp_comm_body = &cp_tmp[1]; }

	return cp_comm_body;
}

/* �ѥ��ζ��ڤ�ʸ��������(ʸ����������Ȥ��䤹���Τ�) */
char *ptbl_get_cp_path_separeter( void )
{
#if defined _WIN32
	return "\\";
#else
	return "/";
#endif
}

