#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* state 6�����뤤��state 5����� */
int tw_win_l3_dsi::_state6to7to6native( void )
{
	TW_UINT16 rc;
	TW_PENDINGXFERS twPendingXfer;

	/* ���� method �� state 6 ��ư��� */
	if (TWAIN_STATE6_TRANSFER_READY != this->twain_state) {
		return OK;
	}

	this->_free_dib_mem();

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_ttvr( "tw_win_l3_dsi::_state6to7to6native()" );
	}

	/*
	twPendingXfer.Count ����
	 �������礭�� : Count �˻��ꤵ�줿����β�����ž���Ԥ��Ǥ�
	 ����           : ž�������٤��ǡ����Ϥ⤦����ޤ���
				��ưŪ�� State5 �ذܹԤ��ޤ�
	 �ޥ��ʥ���     : ����ĤΥǡ�����ž���Ԥ��Ǥ�
				ADF�ʤɤǻĤ������ʬ����ʤ��Ȥ��ʤ�
				�ˤ����ͤȤʤ�ޤ�
	*/

	twPendingXfer.Count = static_cast<TW_UINT16>(-1);
	while ( 0 != twPendingXfer.Count ) {

		/* DIB������������� */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"twain state 6 --> 7 : Transferring" );
		}
		this->twain_state = TWAIN_STATE7_TRANSFERRING;

		rc = this->ds_entry(
			DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET,
			(TW_MEMREF)&(this->_h_dib_image)
		);

		if (TWRC_FAILURE == rc) {
			/*
			����ž�����Ԥ��ޤ�����
			����ϳ��ݤ��������ɥ쥹(hBitmap)��̵���Ǥ���
			���顼�ξ����ϡ�Condition Code�ǳ�ǧ���ޤ���
			���֤��Ѳ��������ΤޤޤǤ���
			�����ǡ����ϻߤޤäƤ��ޤ���
			���ץꥱ��������ž����۾ｪλ�����Ƥ���������
			*/
			if (OK != this->ds_pri_error(
			"DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET", rc
			)) {
				pri_funct_err_bttvr(
			 "Error : this->ds_pri_error(-) returns NG." );
			}

			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
		"twain state --> 6 : because transfer failure" );
			}
			this->twain_state = TWAIN_STATE6_TRANSFER_READY;
			return NG;
		}

		/* ������ž����桼��������󥻥뤷�� */
		else if (TWRC_CANCEL == rc) {
/*
�桼����������ž���򥭥�󥻥뤷�ޤ�����
�������ݤ��ޤ��������ɥ쥹(hBitmap)��̵���ʥϥ�ɥ뤬����ޤ���
�����ơ����β�������γ����ϥ��ץꥱ������󤬤��ʤ���Фʤ�ޤ���
Source�ξ��֤Ϥޤ����Ǥ���
ž����α�β������ǧ����Data Source��λ���ʤ���Фʤ�ޤ���
*/
			/* ž���θ������Ԥ� */
			rc = this->ds_entry(
			 DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER,
			 (TW_MEMREF)&twPendingXfer
			);

			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
	"twain state 7 --> 6 : because user click cancel" );
			}
			this->twain_state = TWAIN_STATE6_TRANSFER_READY;

			if (TWRC_FAILURE == rc) {
				if (OK != this->ds_pri_error(
			"DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER", rc
				)) {
					pri_funct_err_bttvr(
			"Error : this->ds_pri_error(-) returns NG." );
				}
				return NG;
			}
	
			if (0 == twPendingXfer.Count) {
				if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
	"twain state 6 --> 5 : because pending transfer is zero" );
				}
				this->twain_state =
					TWAIN_STATE5_SOURCE_ENABLE;
			}
			/* ����󥻥�ˤ���������ߤʤΤǡ�
			����ž���롼�׽�������ȴ���� */
			//return OK;

			/* TWAIN ����� Cancel �ϥ��顼�Ȥ��� 2014-02-10 */
			pri_funct_msg_ttvr(
	"DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET --> TWRC_CANCEL" );
			return NG;
		}

		/* ������ž������λ���� */
		else if (TWRC_XFERDONE == rc) {
/*
����ž����λ���ޤ���
�������ݤ�������(DIB(Windows)���뤤��PICT(Mac))���Ǽ��
���Υ��ɥ쥹(hBitmap)���֤��ޤ�
�����ơ����β�������γ����ϥ��ץꥱ������󤬤��ʤ���Фʤ�ޤ���
Source�θ��ߤξ��֤ϣ��Ǥ���
���ξ��֤ǡ�����ž���ν�λ���ǧ����
¾��ž������������Τ���Data Source��λ����Τ����ޤ�
*/
			/* ž���θ������Ԥ� */
			rc = this->ds_entry(
			 DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER,
			 (TW_MEMREF)&twPendingXfer
			);

			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
			"twain state 7 --> 6 : because transfer done" );
			}
			this->twain_state = TWAIN_STATE6_TRANSFER_READY;

			if (TWRC_FAILURE == rc) {
				if (OK != this->ds_pri_error(
			"DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER", rc
				)) {
					pri_funct_err_bttvr(
			 "Error : this->ds_pri_error(-) returns NG." );
				}
				return NG;
			}
		}
		else {
			/* TWRC_FAILURE,TWRC_CANCEL,TWRC_XFERDONE��
			   3�Ĥ����֤��ʤ���
			   ����ʳ���TWAIN���ʤ��鳰��Ƥ��� */
			assert(0);
		}

		if (NULL != (this->_h_dib_image)) {
			/* p_dib_bmi_head��DIB�ؤΥݥ��󥿤��Ǽ���� */
			this->_p_dib_bitmapinfo =
			(BITMAPINFO *)GlobalLock(
				(this->_h_dib_image)
			);
		}
	}

	/* Count��0�ǡ�loop����ȴ������ưŪ�� State5 �ذܹԤ��� */
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr(
 "twain state 6 --> 5 : loop break, because pending transfer is zero" );
	}
	this->twain_state = TWAIN_STATE5_SOURCE_ENABLE;
	return OK;
}

/********************************************************************/

void tw_win_l3_dsi::_free_dib_mem( void )
{
	if (NULL != this->_h_dib_image) {
		GlobalUnlock(	this->_h_dib_image );
		GlobalFree(	this->_h_dib_image );
				this->_h_dib_image = NULL;
	}
	this->_p_dib_bitmapinfo = NULL;
}

/********************************************************************/
