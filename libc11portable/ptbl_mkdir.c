#if defined _WIN32
# include <direct.h>
#else
# include <sys/stat.h>
# include <sys/types.h>
#endif
#include "ptbl_funct.h"

/* �ǥ��쥯�ȥ�򣱸ĺ�������(����� 0:����,-1:����) */
int ptbl_mkdir( char *cp_dirpath )
{
#if defined _WIN32
	return _mkdir( cp_dirpath );
#else
	return mkdir( cp_dirpath, 0777 );
#endif
}

