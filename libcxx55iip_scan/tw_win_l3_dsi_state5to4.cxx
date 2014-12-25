#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* 5��4  ��������ž���ǥ������֥�򥢥ץ������
        or ���ץꡧ��������ǥ������֥�ˤ��� */
int tw_win_l3_dsi::state5to4( void )
{
	TW_UINT16 rc;

	/* ����(state)��5�Ǥʤ��Ȥ��ϲ��⤷�ʤ� */
	if (TWAIN_STATE5_SOURCE_ENABLE != this->twain_state) {
		return OK;
	}
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "tw_win_l3_dsi::state5to4()" );
	}

	rc = this->ds_entry(
		DG_CONTROL,DAT_USERINTERFACE,MSG_DISABLEDS,
		(TW_MEMREF)&(this->_tw_ui)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_USERINTERFACE,MSG_DISABLEDS", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* ����(state)��4���᤹ */
	this->twain_state = TWAIN_STATE4_SOURCE_OPENED;
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
		"twain state 5 --> 4 : source enable" );
		pri_funct_msg_ttvr(
		" _tw_ui.hParent is 0x%p, ShowUI is %s, ModalUIis %s",
			this->_tw_ui.hParent,
			(TRUE==this->_tw_ui.ShowUI)?"TRUE":"FALSE",
			(TRUE==this->_tw_ui.ModalUI)?"TRUE":"FALSE"
		);
	}

	return OK;
}
