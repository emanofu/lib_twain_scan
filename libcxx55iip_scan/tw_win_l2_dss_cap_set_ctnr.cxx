#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

/* set capability with container */
int tw_win_l2_dss::_cap_set_ctnr( TW_CAPABILITY *p_tw_capability )
{
	TW_UINT16	rc;

	/* ����ƥʡ�����ϸƽФ�¦�ǳ��ݤ��ʤ���Фʤ�ʤ� */
	assert(NULL != p_tw_capability->hContainer);

	/* �ͤ�twain source�����ꤹ�� */
	rc = this->ds_entry(
		DG_CONTROL,DAT_CAPABILITY,MSG_SET,
		(TW_MEMREF)p_tw_capability
	);

	/* ����ƥʡ�������ѻ������ä��ΤǤ����ǳ������Ƥ��ޤ� */
	GlobalFree(p_tw_capability->hContainer);
	p_tw_capability->hContainer = NULL;

	/* ����ͤ�����å�
	TWRC_SUCCESS - ������ͤ�set����
	TWRC_FAILURE - ���顼������ǥ�����󥳡��ɤ�����å�����
	TWRC_CHECKSTATUS - ���Τ�����Ǥ��ʤ��ä��Τ�(?)��
		���ꤷ���ͤˤǤ�������ᤤ�ͤ����ꤷ����
		�ɤ��ʤä����ϡ�MSG_GET���ͤ�ߤ�
		...�Ȥ������Ȥ�?(2004.11.30)
	*/
	if (TWRC_SUCCESS != rc) {
		if (TWRC_CHECKSTATUS == rc) {
			pri_funct_err_bttvr(
 "Error : this->ds_entry(DG_CONTROL,DAT_CAPABILITY,MSG_SET,) returns TWRC_CHECKSTATUS" );
		} else {
		 if (OK != this->ds_pri_error(
		 "DG_CONTROL,DAT_CAPABILITY,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		 }
		}
		return NG;
	}

	return OK;
}
