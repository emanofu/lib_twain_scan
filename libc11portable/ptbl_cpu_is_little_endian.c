#include "ptbl_stdint.h"
#include "ptbl_funct.h"

/* �����ȥ����ƥ�ΥХ��ȥ���������
   �ӥå�����ǥ�����ʤΤ���ȥ륤��ǥ�����ʤΤ�Ƚ��
	little endian �ʤ� 1 ���֤�
	big    endian �ʤ� 0 ���֤�
 */

int ptbl_cpu_is_little_endian( void )
{
	union { int32_t i; int8_t c[4]; } u;
/*
 byte order������
  union u�ˤơ�
   int32_t i ��1��ä���ȡ�
	--------+---------------+--------
   int32_t i	|             1 |
	--------+---------------+--------
		              |
		              v
		+---+---+---+---+
   int8_t c[4]	|   |   |   | 1 |
		+---+---+---+---+
		  0   1   2   3   Big Endian
		              |
		              v
		+---+---+---+---+
   int8_t c[4]	|   |   |   | 1 |
		+---+---+---+---+
		  3   2   1   0   Little Endian
   Big    Endian�Ǥϡ�u.c[3] �� 1
   Little Endian�Ǥϡ�u.c[0] �� 1
   �Ȥʤ롣
*/
	u.i = 1;
	return (1 == u.c[0]);
}

