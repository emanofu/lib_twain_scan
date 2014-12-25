#ifndef __ptbl_funct_h__
#define __ptbl_funct_h__

#ifdef __cplusplus
extern "C" {
#endif

/* CPU����Little Endian�ʤ�1���֤���Big Endian�ʤ饼����֤� */
extern int ptbl_cpu_is_little_endian( void );

/* �ǥ��쥯�ȥꤢ�뤤�ϥե����뤬¸�ߤ���� 1 �򡢤ʤ���� 0 ���֤� */
extern int ptbl_dir_or_file_is_exist( char *cp_path );

/* �ۥ���̾�����롢�ۥ���̾�����Ĥ���ʤ��Ȥ���NULL���᤹ */
extern char *ptbl_get_cp_hostname( void );

/* login̾������(Windows�Ǥϥ�����̾)���Ĥ���ʤ��Ȥ���NULL���᤹ */
extern char *ptbl_get_cp_loginname( void );

/* ���ߤΥ桼����̾������(Cygwin�Ǥ�Admin...)
   ���Ĥ���ʤ��Ȥ���NULL���᤹ */
extern char *ptbl_get_cp_username( void );

/* ���ߤΥ桼����̾������(Cygwin�Ǥ�Admin...)
   ���Ĥ���ʤ��Ȥ���NULL���᤹ */
extern char *ptbl_get_cp_userrealname( void );

/* �ǥ��쥯�ȥ�򣱸ĺ�������(����� 0:����,-1:����) */
extern int ptbl_mkdir( char *cp_dirpath );

/* �ե�����ѥ�����ե�����̾�Τ�����(����.exe���ϻĤ�) */
extern char *ptbl_get_cp_filename_from_path( char *cp_filepath );

/* �ѥ��ζ��ڤ�ʸ��������(ʸ����������Ȥ��䤹���Τ�) */
extern char *ptbl_get_cp_path_separeter( void );

#ifdef __cplusplus
}
#endif

#endif /* !__ptbl_funct_h__ */
