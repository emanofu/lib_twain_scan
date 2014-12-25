#ifndef __iip_channel_info_h__
#define __iip_channel_info_h__

#include <stdio.h>
#include "ptbl_returncode.h"

/*
 * �����ͥ����
 */
typedef	enum {
	E_NUM_INTEGER = 1,
	E_NUM_FLOATING
} E_NUM_FORM;

typedef	enum {
	E_CH_NUM_EMPTY = 1, /* empty(not set channel_number_type) */
	E_CH_NUM_UCHAR, /* unsigned char */
	E_CH_NUM_USHRT, /* unsigned short */
	E_CH_NUM_ULONG, /* unsigned long */
	E_CH_NUM_DOUBL, /* double */
	E_CH_NUM_BITBW  /* 1bit�ǥ�Υ�����Ĵ */
} E_CH_NUM_TYPE;

class iip_channel_info {
public:
	iip_channel_info()
	{
		this->set_e_ch_num_type( E_CH_NUM_EMPTY );
	}
	~iip_channel_info()
	{
		this->set_e_ch_num_type( E_CH_NUM_EMPTY );
	}
	/* �����פ���ꤹ�뤳�Ȥǳƥѥ�᡼�������ꤹ�� */
	void set_e_ch_num_type( E_CH_NUM_TYPE e_type );

	/* �ƥѥ�᡼�����饿���פ��֤� */
	E_CH_NUM_TYPE get_e_ch_num_type( void );

	/* �ƥѥ�᡼�����饿����̾���֤�
	get_cp_ch_num_type()�ϡ��ؿ��Υ����С����ɤ�äƤޤ���
	��ջ��ࡧ�ǥե���Ȱ����ϻȤäƤϤ����ޤ���
		  �ɤä��δؿ���Ƥ���Τ����̤��Ĥ��ʤ��ʤ�ޤ���
	*/
	const char *get_cp_ch_num_type( void );
	const char *get_cp_ch_num_type( E_CH_NUM_TYPE e_type );

	/* (�����)���ꤷ�Ƥ��뤫�����å� */
	int chk_e_ch_num_type( void );

	/* �����Х�������ݤΤ�������ͥ�Х��ȿ�
	E_CH_NUM_BITBW�ΤȤ��ϥ�����֤� */
	long get_l_bytes( void ) { return this->_l_bytes; }

	/* TIFF�ե��������¸�������ɬ�פ�method */
	long get_l_bits( void ) { return this->_l_bits; }

private:
	long	_l_bytes,
		_l_bits;
	E_NUM_FORM _e_num_form;
};

#endif /* !__iip_channel_info_h__ */
