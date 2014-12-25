#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

/* get capability with container */
int tw_win_l2_dss::_cap_get_ctnr( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability )
{
	TW_UINT16 rc;

	/*
	www.twain.org/docs/Spec1_9_197.pdf
	 Page71, 75
	 Chapter 4 -> Advenced Application Implementation
	 -> Capability -> Capability Negotiation -> Negotiation(Part 1)
	*/

	/* Step 1 : ����ͤ����� */
	p_tw_capability->Cap = ui16_cap;
	p_tw_capability->ConType = TWON_DONTCARE16;
	p_tw_capability->hContainer = NULL;

	/* Step 2,3 : �ؿ���¹Ԥ����ͤ�ȤäƤ��� */
	rc = this->ds_entry(
		DG_CONTROL,DAT_CAPABILITY,MSG_GET,
		(TW_MEMREF)p_tw_capability
	);

	/* Step 4 : ����ͤ�����å����롣�Ρ����ݡ��ȡ����뤤�ϥ��顼
		    �ʤ顢����ǥ�����󥳡��ɤ�����å����� */
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_CAPABILITY,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	/* ����ƥʤ˥ǡ��������ݤ���Ƥ��ʤ�...
	���Υ����å��ǰ��ä����äƤ���Ϥ��ʤΤǡ������ǰ��ä�����
	�Ȥ������Ȥϡ�TWAIN �ץ���ߥ󥰤μ��������꤬���롣 */
	if (NULL == p_tw_capability->hContainer) {
		pri_funct_err_bttvr(
	   "Error : p_tw_capability->hContainer is NULL." );
		return NG;
	}

	return OK;
}

/* get_current capability with container */
int tw_win_l2_dss::_cap_getcrnt_ctnr( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability )
{
	TW_UINT16 rc;

	/* Step 1 : ����ͤ����� */
	p_tw_capability->Cap = ui16_cap;
	p_tw_capability->ConType = TWON_DONTCARE16;
	p_tw_capability->hContainer = NULL;

	/* Step 2,3 : �ؿ���¹Ԥ����ͤ�ȤäƤ��� */
	rc = this->ds_entry(
		DG_CONTROL,DAT_CAPABILITY,MSG_GETCURRENT,
		(TW_MEMREF)p_tw_capability
	);

	/* Step 4 : ����ͤ�����å����롣�Ρ����ݡ��ȡ����뤤�ϥ��顼
		    �ʤ顢����ǥ�����󥳡��ɤ�����å����� */
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_CAPABILITY,MSG_GETCURRENT", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	/* ����ƥʤ˥ǡ��������ݤ���Ƥ��ʤ�...
	���Υ����å��ǰ��ä����äƤ���Ϥ��ʤΤǡ������ǰ��ä�����
	�Ȥ������Ȥϡ�TWAIN �ץ���ߥ󥰤μ��������꤬���롣 */
	if (NULL == p_tw_capability->hContainer) {
		pri_funct_err_bttvr(
	   "Error : p_tw_capability->hContainer is NULL." );
		return NG;
	}

	return OK;
}
