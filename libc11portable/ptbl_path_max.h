/*
	�ե�����̾��Ǽ�Ѥΰ���ݴɥХåե����礭���Ȥ��ơ�
	FILENAME_MAX��Ȥ���������HP-UX�ˤ�14�Ǥ�������
	�ƥ����ƥ���ͤ���äƤ������������ʤ����Ȥ��ʤ���
	�Ѥ������(PTBL_FILE_PATH_BUF_MAX)�򤷤Ƥ���
	(2005.01.05)

	�ե�����ѥ���Ǽ�Ѥΰ���ݴɥХåե����礭���Ȥ��ơ�
	PATH_MAX,_POSIX_PATH_MAX�����뤬��
	�ƥ����ƥ���ͤ���äƤ������������ʤ�
	(2005.10.07)

	�Ѥ������(PTBL_FILE_PATH_BUF_MAX)��
	PTBL_PATH_MAX���ѹ���
	(2005.10.13)
*/

#if 0	/* ------------------- comment out ----------------------*/
Redhat9
/usr/include/stdio.h --> /usr/include/bits/stdio_lim.h
#define FILENAME_MAX 4096

WindowsXp
/cygdrive/c/Program\ Files/Microsoft\ Visual\ Studio/VC98/Include/STDIO.H
#define FILENAME_MAX    260

IRIX6.5.x
/usr/include/stdio.h
#define FILENAME_MAX    1024

HP-UX B.11.11 U
/usr/include/stdio.h
#define FILENAME_MAX    14
*/

Redhat9
/usr/include/linux/limits.h
#define PATH_MAX       4096 /* # chars in a path name */
/usr/include/bits/posix1_lim.h
#define _POSIX_PATH_MAX 256 /* Number of bytes in a pathname. */

WindowsXp (���)-D_POSIX_���ץ����ɬ��
C:\Program Files\Microsoft Visual Studio\VC98\Include\LIMITS.H
#define PATH_MAX        512
#define _POSIX_PATH_MAX 255

HP-UX B.11.11 U
/usr/include/limits.h
#define PATH_MAX    1023    /* max number of characters in a pathname (not including terminating null) */
#define _POSIX_PATH_MAX 255 /* The number of bytes in a pathname */
#endif	/* ------------------- comment out ----------------------*/

#ifndef PTBL_PATH_MAX
#define PTBL_PATH_MAX 4096
#endif
