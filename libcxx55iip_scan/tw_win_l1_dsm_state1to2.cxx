#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/*
VALID_HANDLE�ϡ�
TWAIN v1.9���ͽ�(Spec1_9_197.pdf Page41)�Υ���ץ륳���ɤ�
���ܤ����뤬���ͤ�������ʤ���
twain_sdk/twack/Dca_glue.h�ˤϤ���Τǡ������ž�ܡ����Ѥ��롣
*/
#ifndef VALID_HANDLE
#define VALID_HANDLE 32 /* valid windows handle SB >= 32 */
#endif

/* �������ޥ͡�����(DSM)�Υ��� */
int tw_win_l1_dsm::state1to2( void )
{
	char ca_path[MAX_PATH];
/***#if defined _WIN64
	char *cp_twain_dll_file_name = "twain.dll";
#else***/
	char *cp_twain_dll_file_name = "TWAIN_32.DLL";
/***#endif***/
	OFSTRUCT	st_ofstruct;

	/* ����(state)��1�Ǥʤ��Ȥ��ϲ��⤷�ʤ� */
	if (TWAIN_STATE1_PRE_SESSION != this->twain_state) {
		return OK;
	}

	assert(NULL == this->_hm_dsm_dll);
	assert(NULL == this->_p_dsm_entry);

	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state1to2()" );
	}

	/* Windows�����ƥ�ؤΥǥ��쥯�ȥ�ѥ������� */
	if (0 == GetWindowsDirectory( ca_path, sizeof(ca_path) )) {
		pri_funct_err_bttvr(
	"Error : GetWindowsDirectory() returns zero" );

		pri_funct_err_bttvr(
	"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}

	/* �����ǥ��쥯�ȥ�ѥ��ν�ü�˶��ڤ�ʸ�����ɲ� */
	if ('\\' != ca_path[(strlen(ca_path) - 1)]){
		(void)strcat( ca_path, "\\" );
	}

	/* ����˥ե�����̾���ɲä�dll�ؤΥե�����ѥ��Ȥ��� */
	(void)strcat( ca_path, cp_twain_dll_file_name );

	/* TWAIN DLL�ե�����¸�ߤγ�ǧ */
	if (-1 == OpenFile( ca_path,&st_ofstruct,OF_EXIST )) {
		pri_funct_err_bttvr(
	 "Error : OpenFile(%s,,OF_EXIST) returns -1.",
			ca_path );
		return NG;
	}

	/* state 1-->2  �������ޥ͡�����(TWAIN DLL�ե�����)�Υ��� */ 
	this->_hm_dsm_dll = LoadLibrary( cp_twain_dll_file_name );
	if (NULL == this->_hm_dsm_dll) {
		pri_funct_err_bttvr(
 		"Error : LoadLibrary() returns NULL" );
		pri_funct_err_bttvr(
 		"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}
	if (this->_hm_dsm_dll < (HANDLE)VALID_HANDLE) {
		pri_funct_err_bttvr(
			"Error : LoadLibrary() returns invalid<%p>.",
			this->_hm_dsm_dll );
		return NG;
	}

	/* TWAIN DLL����ؿ��ݥ��󥿤μ��� */
	this->_p_dsm_entry = (DSMENTRYPROC)GetProcAddress(
		this->_hm_dsm_dll,
		MAKEINTRESOURCE(1) /* TWAIN spec 1.9�˵��ܤΤ���� */
				   /* "DSM_Entry"�Ȥ���ư��� */
	);
	if (NULL == this->_p_dsm_entry) {
		pri_funct_err_bttvr(
			"Error : GetProcAddress() returns zero" );
		pri_funct_err_bttvr(
 		"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}

	/* ����(state)��2�˿ʤ�� */
	this->twain_state = TWAIN_STATE2_SOURCE_MANAGER_LOADED;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 1 --> 2 : source manager loaded" );
	}

	return OK;
}
