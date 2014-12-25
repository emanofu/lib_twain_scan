#include "tw_win_l2_dss.h"

int tw_win_l2_dss::cap_pri_units( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_UNITS,
		"ICAP_UNITS" );
}

int tw_win_l2_dss::cap_pri_xfermech( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_XFERMECH,
		"ICAP_XFERMECH" );
}

int tw_win_l2_dss::cap_pri_pixeltype( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_PIXELTYPE,
		"ICAP_PIXELTYPE" );
}

/* �ƿ������ͥ뤢����Υӥå�Ĺ��ɽ�����롣
�ͤ���³����������ʡ��˰�¸���ޤ���

���Ȥ��С�48�ӥåȥ��顼���ϲ�ǽ�ʵ���Ǥϡ�1,8,16����
36�ӥåȥ��顼���ϵ���Ǥϡ�1,8,12�Ȥʤ�ޤ���
*/
int tw_win_l2_dss::cap_pri_bitdepth( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_BITDEPTH,
		"ICAP_BITDEPTH" );
}

int tw_win_l2_dss::cap_pri_orientation( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_ORIENTATION,
		"ICAP_ORIENTATION" );
}
