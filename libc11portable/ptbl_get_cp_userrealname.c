#include "ptbl_funct.h"

/* ���ߤΥ桼����̾������(Cygwin�Ǥ�Admin...)
   ���Ĥ���ʤ��Ȥ���NULL���᤹ */
char *ptbl_get_cp_userrealname( void )
{
#if defined i386_redhat_cygwin1_3_15
//	return ptbl_get_cp_loginname();
#else
	return ptbl_get_cp_username();
#endif
}

