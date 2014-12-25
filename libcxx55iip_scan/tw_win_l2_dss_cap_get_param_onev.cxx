#include "tw_win_l2_dss.h"

int tw_win_l2_dss::cap_get_dp_x_native_resolution( double *dp_x_native_res )
{
	return this->_cap_get_ctnr_onevalue_fix32(
		  dp_x_native_res,
		 ICAP_XNATIVERESOLUTION,
		"ICAP_XNATIVERESOLUTION" );
}

int tw_win_l2_dss::cap_get_dp_y_native_resolution( double *dp_y_native_res )
{
	return this->_cap_get_ctnr_onevalue_fix32(
		  dp_y_native_res,
		 ICAP_YNATIVERESOLUTION,
		"ICAP_YNATIVERESOLUTION" );
}

/* ��³������ʤ��б��������������� */
int tw_win_l2_dss::cap_get_dp_physical_width( double *dp_width )
{
	return this->_cap_get_ctnr_onevalue_fix32(
			   dp_width,
		 ICAP_PHYSICALWIDTH,
		"ICAP_PHYSICALWIDTH" );
}

/* ����⤵ */
int tw_win_l2_dss::cap_get_dp_physical_height( double *dp_height )
{
	return this->_cap_get_ctnr_onevalue_fix32(
			   dp_height,
		 ICAP_PHYSICALHEIGHT,
		"ICAP_PHYSICALHEIGHT" );
}

/* UI��ɽ���ǥ������β��ݤ򼨤��ޤ���
TRUE==tw_onevalue.Item���֤�ȡ�UI���ץ쥹�⡼�ɤǤ�ư���ǽ��
�ĤޤꡢTW_USERINTERFACE.ShowUI��FALSE�����ꤹ�뤳�Ȥ���ǽ�Ǥ���
*/
int tw_win_l2_dss::cap_get_lp_uicontrollable_sw( long *lp_bool )
{
	int	i_ret;
	TW_UINT32	ui32_val;

	i_ret = this->_cap_get_ctnr_onevalue_bool(
		&ui32_val,
		 CAP_UICONTROLLABLE,
		"CAP_UICONTROLLABLE" );
	if (TRUE == ui32_val) { *lp_bool = ON; }
	else                  { *lp_bool = OFF; }
	return i_ret;
}

/*----------------------------------------------------------*/

int tw_win_l2_dss::cap_getcrnt_lp_xfermech( long *lp_xfermech )
{
	TW_UINT16 ui16_val;
	int i_ret;

	i_ret = this->_cap_getcrnt_ctnr_onevalue_ui16(
		  &ui16_val,
		 ICAP_XFERMECH,
		"ICAP_XFERMECH" );

	*lp_xfermech = ui16_val;
	return i_ret;
}
