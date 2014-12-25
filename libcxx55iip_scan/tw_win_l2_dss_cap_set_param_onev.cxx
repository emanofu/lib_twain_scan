#include "tw_win_l2_dss.h"

/* ���뤵���ͤ���� */
int tw_win_l2_dss::cap_set_d_brightness( double d_brightness )
{
	return this->_cap_set_ctnr_onevalue_fix32(
		    d_brightness,
		 ICAP_BRIGHTNESS,
		"ICAP_BRIGHTNESS" );
}

/* ����ȥ饹���ͤ���� */
int tw_win_l2_dss::cap_set_d_contrast( double d_contrast )
{
	return this->_cap_set_ctnr_onevalue_fix32(
		    d_contrast,
		 ICAP_CONTRAST,
		"ICAP_CONTRAST" );
}

/* ������ͤ���� */
int tw_win_l2_dss::cap_set_d_gamma( double d_gamma )
{
	return this->_cap_set_ctnr_onevalue_fix32(
		    d_gamma,
		 ICAP_GAMMA,
		"ICAP_GAMMA" );
}

/* GUI��ɽ���ΤȤ����ץ��쥹ɽ����ON/OFF */
int tw_win_l2_dss::_cap_set_indicators( TW_BOOL bo_val )
{
	return this->_cap_set_ctnr_onevalue_bool(
		    bo_val,
		 CAP_INDICATORS,
		"CAP_INDICATORS" );
}
int tw_win_l2_dss::cap_set_indicators_off_when_gui_off( void )
{ return this->_cap_set_indicators( FALSE ); }
int tw_win_l2_dss::cap_set_indicators_on_when_gui_off( void )
{ return this->_cap_set_indicators( TRUE ); }

/* ���������������٤���� */
int tw_win_l2_dss::cap_set_d_x_resolution( double d_x_reso )
{
	return this->_cap_set_ctnr_onevalue_fix32(
		    d_x_reso,
		 ICAP_XRESOLUTION,
		"ICAP_XRESOLUTION" );
}

/* ���������������٤���� */
int tw_win_l2_dss::cap_set_d_y_resolution( double d_y_reso )
{
	return this->_cap_set_ctnr_onevalue_fix32(
		    d_y_reso,
		 ICAP_YRESOLUTION,
		"ICAP_YRESOLUTION" );
}

/* �������ϰϻ���ˤ�����Ĺ����ñ�̤���ꤷ�ޤ���
	������᡼�ȥ롢������Τɤ��餫����ꤷ�ޤ���
	ICAP_PHYSICALHEIGHT,ICAP_PHYSICALWIDTH,DG_IMAGE/DAT_IMAGELAYOUT
	�Σ��Ĥ������ͤ˱ƶ����ޤ���
*/
int tw_win_l2_dss::_cap_set_units( TW_UINT16 ui16_units )
{
	return this->_cap_set_ctnr_onevalue_ui16(
		 ui16_units,
		 ICAP_UNITS,
		"ICAP_UNITS" );
}
int tw_win_l2_dss::cap_set_units_centimeters( void )
{ return this->_cap_set_units( TWUN_CENTIMETERS ); }
int tw_win_l2_dss::cap_set_units_inchs( void )
{ return this->_cap_set_units( TWUN_INCHES ); }

/* set transfer mechanisms
	�����ǡ�����ž���⡼�ɤ���ꤷ�ޤ�
	48(42,36)BitsColor��16(14,12)BitsGray�Ǥ�
	�ͥ��ƥ���ž���ϤǤ��ޤ���ɬ�����꡼ž������ꤷ�Ƥ�������
*/
int tw_win_l2_dss::_cap_set_xfermech( TW_UINT16 ui16_xfermech )
{
	return this->_cap_set_ctnr_onevalue_ui16(
		 ui16_xfermech,
		 ICAP_XFERMECH,
		"ICAP_XFERMECH" );
}
int tw_win_l2_dss::cap_set_xfermech_memory( void )
{ return this->_cap_set_xfermech( TWSX_MEMORY ); }
int tw_win_l2_dss::cap_set_xfermech_native( void )
{ return this->_cap_set_xfermech( TWSX_NATIVE ); }

int tw_win_l2_dss::_cap_set_pixeltype( TW_UINT16 ui16_pixeltype )
{
	return this->_cap_set_ctnr_onevalue_ui16(
		 ui16_pixeltype,
		 ICAP_PIXELTYPE,
		"ICAP_PIXELTYPE" );
}
int tw_win_l2_dss::cap_set_pixeltype_bw( void )
{ return this->_cap_set_pixeltype( TWPT_BW ); }
int tw_win_l2_dss::cap_set_pixeltype_gray( void )
{ return this->_cap_set_pixeltype( TWPT_GRAY ); }
int tw_win_l2_dss::cap_set_pixeltype_rgb( void )
{ return this->_cap_set_pixeltype( TWPT_RGB ); }

/* 0 ... 255 step 1, default 128 */
int tw_win_l2_dss::cap_set_d_threshold( double d_threshold )
{
	return this->_cap_set_ctnr_onevalue_fix32(
		 d_threshold,
		 ICAP_THRESHOLD,
		"ICAP_THRESHOLD" );
}

/* 1,8,(12,14,16) default 8 */
int tw_win_l2_dss::cap_set_i_bitdepth( int i_bitdepth )
{
	return this->_cap_set_ctnr_onevalue_ui16(
		 static_cast<TW_UINT16>(i_bitdepth),
		 ICAP_BITDEPTH,
		"ICAP_BITDEPTH" );
}

/* (0,1,2,3) default 0
(��) (2005.08.01)
TWAIN��ICAP_ORIENTATION��ǽ�ˤ�äƲ������ž��
���Ф����뤳�Ȥ��Ǥ��뤬��
��Υ���2�Ͳ�������2��ۤɤκ��Ǽ����ǲ�ž�����ۤ�����®��
���졼�������������1��ۤɤκ��Ǽ����ǲ�ž�����ۤ�����®��
RGB�����Ϥۤܺ��ʤ�
*/
int tw_win_l2_dss::cap_set_i_orientation( int i_orientation )
{
	return this->_cap_set_ctnr_onevalue_ui16(
		 static_cast<TW_UINT16>(i_orientation),
		 ICAP_ORIENTATION,
		"ICAP_ORIENTATION" );
}

