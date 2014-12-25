#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* this->_dsm_entry(-)�˴ؤ��륨�顼ɽ�� */
int tw_win_l1_dsm::_dsm_pri_error( char *cp_tri, TW_UINT16 rc )
{
	TW_UINT16 ui16_cc;

	/* ����ͤ�����(TWRC_SUCCESS)�ξ�硢�ʤˤ⤻��OK���֤� */
	if (TWRC_SUCCESS == rc) { return OK; }

	/* ����ͤ�����(TWRC_SUCCESS)�Ǥʤ���硢���ܤΥ��顼ɽ�� */
	pri_funct_err_bttvr(
		"Error : this->_dsm_entry(%s,) returns %u.",
		cp_tri, rc );

	/* ����ͤ�����(TWRC_FAILURE)�ξ�硢Condition Code������ */
	if (TWRC_FAILURE == rc) {
		/* Condition Code������Τ˼��� */
		if (OK != this->_get_dsm_cc( &ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_get_dsm_cc(-) returns NG." );
			return NG;
		}
		/* /* Condition Code�ΰ�̣��ɽ�� */
		if (OK != this->_pri_cc( ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_pri_cc(-) returns NG.");
			return NG;
		}
	}
	return OK;
}

/* this->ds_entry(-)�˴ؤ��륨�顼ɽ�� */
int tw_win_l1_dsm::ds_pri_error( char *cp_tri, TW_UINT16 rc )
{
	TW_UINT16 ui16_cc;

	/* ����ͤ�����(TWRC_SUCCESS)�ξ�硢�ʤˤ⤻��OK���֤� */
	if (TWRC_SUCCESS == rc) { return OK; }

	/* ����ͤ�����(TWRC_SUCCESS)�Ǥʤ���硢���ܤΥ��顼ɽ�� */
	pri_funct_err_bttvr(
		"Error : this->_ds_entry(%s,) returns %u.",
		cp_tri, rc );

	/* ����ͤ�����(TWRC_FAILURE)�ξ�硢Condition Code������ */
	if (TWRC_FAILURE == rc) {
		/* Condition Code������Τ˼��� */
		if (OK != this->_get_ds_cc( &ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_get_ds_cc(-) returns NG." );
			return NG;
		}
		/* /* Condition Code�ΰ�̣��ɽ�� */
		if (OK != this->_pri_cc( ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_pri_cc(-) returns NG.");
			return NG;
		}
	}
	return OK;
}
