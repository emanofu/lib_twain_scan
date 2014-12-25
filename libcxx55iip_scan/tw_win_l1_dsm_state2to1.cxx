#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* �������ޥ͡�����(DSM)�Υ������ */
int tw_win_l1_dsm::state2to1( void )
{
	/* ����(state)��2�Ǥʤ��Ȥ��ϲ��⤷�ʤ� */
	if (TWAIN_STATE2_SOURCE_MANAGER_LOADED != this->twain_state) {
		return OK;
	}

	assert(NULL != this->_hm_dsm_dll);
	assert(NULL != this->_p_dsm_entry);

	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state2to1()" );
	}

	/* dll�Υ������ */
	if (0 == FreeLibrary(this->_hm_dsm_dll)) {
		pri_funct_err_bttvr(
	"Error : FreeLibrary() returns zero" );
		pri_funct_err_bttvr(
 	"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}

	this->_hm_dsm_dll  = NULL; /* dll�ؤΥϥ�ɥ��ꥻ�å� */
	this->_p_dsm_entry = NULL; /* �ؿ��ݥ��󥿤Υꥻ�å�    */

	/* ����(state)��1���᤹ */
	this->twain_state = TWAIN_STATE1_PRE_SESSION;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 2 --> 1 : source manager unloaded" );
	}

	return OK;
}
