#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy() */
#include <limits.h>	/* CHAR_BIT */
#include <assert.h>
#include "pri.h"
#include "iip_canvas.h"

/* �������ͥ���ΥХ��ȿ������ */
long iip_canvas::_get_l_scanline_channel_bytes( long l_width, long l_bytes )
{
	/* 1bit��Υ�����Ĵ */
	if (0L == l_bytes) {
		return l_width / CHAR_BIT +
			((0L == (l_width % CHAR_BIT))? 0L: 1L);
	}
	/* ����¾ --- �Х���ñ�̤Υ����ͥ� */
	else {
		return	l_width * l_bytes;
	}
}

/* ����Х��ο������ͥ���ΥХ��ȿ������ */
long iip_canvas::get_l_scanline_channel_bytes( void )
{
	return this->_get_l_scanline_channel_bytes(
			this->_l_width,
			this->cl_ch_info.get_l_bytes()
	);
}

/* �礭����Ʊ���ǡ������
��郎���äƤ���С��Ƥ��饫��Х��򥳥ԡ����� */
void iip_canvas::copy_image_from_parent( const char *ccp_object_name_of_mv )
{
	iip_canvas *clpp;

	clpp = this->get_clp_parent();

	/*
	�Ƥ����ơ�
	���ġ��Ƥ��������äƤ��ơ�
	���ġ���ʬ����Ω��������Х�������äƤ���ʤ顢
	�Ƥβ�����ʬ�Υ���Х��˥��ԡ�����
	(��ʬ�Υ���Х���ʣ�̤��ƽ�������) */
	if ((NULL != clpp)
	&&  (NULL != clpp->get_vp_canvas())
	&&  (ON == this->get_i_must_be_free_self_sw()) ) {
		(void)memcpy(
			this->get_vp_canvas(),
			clpp->get_vp_canvas(),
			this->_l_height *
			this->_l_channels *
			this->get_l_scanline_channel_bytes()
		);
		/* Methodɽ�� */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"%s : copy from parent canvas",
				ccp_object_name_of_mv
			);
		}
	}
}

/* ����Х��������ݤ��� */
int iip_canvas::mem_alloc_canvas( void )
{
	/* ��¸�Υ��곫�� */
	this->mem_free_canvas();

	/* �������Υ����å����礭����������Ȥ��� */
	if ((this->_l_width) <= 0L) {
		pri_funct_err_bttvr(
		"Error : this->_l_width<%ld> is bad.",
			this->_l_width );
		return NG;
	}
	if ((this->_l_height) <= 0L) {
		pri_funct_err_bttvr(
		"Error : this->_l_height<%ld> is bad.",
			this->_l_height);
		return NG;
	}
	if ((this->_l_channels) <= 0L) {
		pri_funct_err_bttvr(
		"Error : this->_l_channels<%ld> is bad.",
			this->_l_channels );
		return NG;
	}

	if (OK != this->cl_ch_info.chk_e_ch_num_type()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_ch_info.chk_e_ch_num_type() returns NG" );
		return NG;
	}

	/* Method and Parameterɽ�� */
	if ((ON == this->_i_mv_sw) || (ON == this->_i_pv_sw)) {
		assert( NULL != this->_ccp_object_name_of_mv );
		pri_funct_msg_ttvr(
			"Alloc. %s %d bytes(%d x %d x %d x %s)",
			this->_ccp_object_name_of_mv,
			this->_l_height *
			this->_l_channels *
			this->get_l_scanline_channel_bytes(),
			this->_l_width,
			this->_l_height,
			this->_l_channels,
			this->cl_ch_info.get_cp_ch_num_type()
		);
	}

	/* ������� */
	this->_vp_canvas = calloc(
		this->_l_height,
		this->_l_channels *
		this->get_l_scanline_channel_bytes()
	);

	/* ���ݤ���������礭���򵭲����Ƥ���(free��ɽ���Τ���) */
	this->_l_free_width = this->_l_width;
	this->_l_free_height = this->_l_height;
	this->_l_free_channels = this->_l_channels;
	this->_cl_free_ch_info.set_e_ch_num_type(
		this->cl_ch_info.get_e_ch_num_type() );

	if (NULL == this->_vp_canvas) {
		pri_funct_err_bttvr(
		  "Error : calloc(%ld, %ld x %ld) returns NULL.",
			this->_l_height,
			this->_l_channels,
			this->get_l_scanline_channel_bytes()
		);
		return NG;
	}

	/* �������(free())��ʬ����� */
	this->_i_must_be_free_self_sw = ON;

	return OK;
}

/* ����Х������������ */
void iip_canvas::mem_free_canvas( void )
{
	/* canvas���ʤ� */
	if (NULL == this->_vp_canvas) { return; }

	/* canvas�ϻ��Ȥ��Ƥ���ΤǾ���˳������ʤ� */
	if (OFF == this->_i_must_be_free_self_sw) { return; }

	/* Method and Parameterɽ�� */
	if ((ON == this->_i_mv_sw) || (ON == this->_i_pv_sw)) {
		assert( NULL != this->_ccp_object_name_of_mv );

		pri_funct_msg_ttvr(
			"Free %s %d bytes(%d x %d x %d x %s)",
			this->_ccp_object_name_of_mv,
			this->_l_free_height *
			this->_l_free_channels *
			this->_get_l_scanline_channel_bytes(
			 this->_l_free_width,
			 this->_cl_free_ch_info.get_l_bytes()
			),
			this->_l_free_width,
			this->_l_free_height,
			this->_l_free_channels,
			this->_cl_free_ch_info.get_cp_ch_num_type()
		);
	}
	free( this->_vp_canvas );
	this->_vp_canvas = NULL;
	this->_i_must_be_free_self_sw = OFF;
}
