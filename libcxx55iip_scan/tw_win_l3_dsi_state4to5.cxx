#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* 4��5  ���ץꡧ�������򥤥͡��֥�ˤ���
	1. ���͡��֥��ȯ�Ԥ���
	2. ��TWAIN ����(��)�פ�ɽ��(��ɽ��)
	(��)����ɥ桼������ľ�ܳƼ�����ڤ�ž��(?)�ޤǼ¹ԤǤ���
	  ���������ܥå���
	3. ����4(Source Open)�������5(Source Enable)�Ȥʤ�
	4. ��������ž�������ˤ�����
	5. �����������ȥ������ϥ��٥��(MSG_XFERREADY)��ȯ������
	6. ����5(Source Enable)�������6(Transfer Ready)�Ȥʤ�

TWAIN GUI����ɽ��
	this->_tw_ui.hParent = this->_hWnd;
	this->_tw_ui.ShowUI  = TRUE; --> TWAIN ���̤�ɽ������
	this->_tw_ui.ModalUI = TRUE;

TWAIN CUI�¹�
	this->_tw_ui.hParent = NULL;
	this->_tw_ui.ShowUI  = FALSE; --> TWAIN ���̤���ɽ��(��)�Ȥ���
	this->_tw_ui.ModalUI = FALSE;
	(��)���ξ�硢TWAIN �ɥ饤��¦��������ɽ�����б�
	    ���Ƥ���ɬ�פ����롣
*/
int tw_win_l3_dsi::state4to5( HWND h_wnd, unsigned short us_show_ui, unsigned short us_model_ui )
{
	TW_UINT16 rc;

	/* ����(state)��4�Ǥʤ��Ȥ��ϲ��⤷�ʤ� */
	if (TWAIN_STATE4_SOURCE_OPENED != this->twain_state) {
		return OK;
	}
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "tw_win_l3_dsi::state4to5()" );
	}

	this->_tw_ui.hParent = h_wnd;
	this->_tw_ui.ShowUI  = us_show_ui;
	this->_tw_ui.ModalUI = us_model_ui;

	rc = this->ds_entry(
		DG_CONTROL, DAT_USERINTERFACE, MSG_ENABLEDS,
		(TW_MEMREF)&(this->_tw_ui)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_USERINTERFACE,MSG_ENABLEDS", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* ����(state)��5�˿ʤ�� */
	this->twain_state = TWAIN_STATE5_SOURCE_ENABLE;
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
		"twain state 4 --> 5 : source enable" );
		pri_funct_msg_ttvr(
		" _tw_ui.hParent is 0x%p, ShowUI is %s, ModalUIis %s",
			this->_tw_ui.hParent,
			(TRUE==this->_tw_ui.ShowUI)?"TRUE":"FALSE",
			(TRUE==this->_tw_ui.ModalUI)?"TRUE":"FALSE"
		);
	}

	return OK;
}
