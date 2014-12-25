#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* State 5 -> 6 -> 5  ���ץꥱ��������ž�����������ä����Ȥ����� */
int tw_win_l3_dsi::state5to6to5event( void )
{
	TW_UINT16 rc;
	int	i_ret;
	MSG msg;
	TW_EVENT twEvent;
	TW_PENDINGXFERS twPendingXfer;

	while (GetMessage((LPMSG)&msg,NULL,0,0) != 0) {
	 /* TWAIN�ʳ���Windows���٥�ȤȤ��ƽ���� */
	 rc = TWRC_NOTDSEVENT;

	 if (TWAIN_STATE5_SOURCE_ENABLE == this->twain_state) {
	  twEvent.TWMessage = MSG_NULL;
	  twEvent.pEvent = (TW_MEMREF)&msg;
	  rc = this->ds_entry(
		DG_CONTROL,DAT_EVENT,MSG_PROCESSEVENT,
		(TW_MEMREF)&twEvent
	  );
	  switch (twEvent.TWMessage) {
	  case MSG_XFERREADY:
		/* �桼����GUI�Υ������ּ����ߡץܥ���򲡤����Ȥ���
		GUIɽ�����ʤ����ϡ�(���֤�)�����ʤꡢ
		���Υ��٥��(MSG_XFERREADY)������ */

	  	/* MSG_XFERREADY������������ץ��State5����6�ؿʤ� */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
	"twain state 5 --> 6 : because receive MSG_XFERREADY event" );
		}
		this->twain_state = TWAIN_STATE6_TRANSFER_READY;


		/* ����ž�� ��äƤ���state 6��state 5�ξ�礢�� */
		i_ret = this->_state6to7to6select();


		/* �Τ����ž��������λ��State 6����5����� */
		if (TWAIN_STATE6_TRANSFER_READY == this->twain_state) {
			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
	"twain state 6 --> 5 : because transfer error or cancel" );
			}
			this->twain_state = TWAIN_STATE5_SOURCE_ENABLE;

			rc = this->ds_entry(
				DG_CONTROL,DAT_PENDINGXFERS,MSG_RESET,
				(TW_MEMREF)&twPendingXfer
	  		);
			if (TWRC_SUCCESS != rc) {
				if (OK != this->ds_pri_error(
				"DG_CONTROL,DAT_PENDINGXFERS,MSG_RESET", rc
				)) {
					pri_funct_err_bttvr(
			 "Error : this->ds_pri_error(-) returns NG." );
				}
				/* return NG; */
			}
		}

		/* ����ž���ǥ��顼���ä��Ȥ��ϡ�
		MSG_RESET���Ƥ��饨�顼�꥿���� */
		if (OK != i_ret) {
			pri_funct_err_bttvr(
		 "Error : this->state6to7select() returns NG." );
			return NG;
		}

		/* GUI��Ȥ�ʤ��Ȥ����Υ��٥�ȥ롼�פ���ȴ���� */
		if (FALSE == this->_tw_ui.ShowUI) {
			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
			"break GetMessage(-) loop, when no GUI" );
			}
			return OK;
		}
		break;

	  case MSG_CLOSEDSREQ:
		/* �桼����GUI��close�ܥ���򲡤���
		���Υ��٥��(MSG_CLOSEDSREQ)������(2004.11.10) */
		if (ON == this->get_i_mv_sw()) {
 			pri_funct_msg_ttvr(
		"close TWAIN GUI,(get MSG_CLOSEDSREQ event)" );
		}
		return OK;
		break;

	  case MSG_CLOSEDSOK:
		/* DG_CONTROL/DAT_USERINTERFACE/MSG_ENABLEDSUIONLY
		��Ȥä��Ȥ�(��̣����...) */
		if (ON == this->get_i_mv_sw()) {
 			pri_funct_msg_ttvr( "get MSG_CLOSEDSOK event" );
		}
		return OK;
		break;

	  case MSG_NULL:
		/* GUI��ɽ�������ޤޤʤˤ⤷�ʤ���
		������֤��Ȥ��Υ��٥��(MSG_NULL)������ */
		break;/* ���Υ��٥�ȥ롼�פ�³�� */
	  }
	 }

	 /* TWAIN�ʳ���Windows���٥�� */
	 if (TWRC_NOTDSEVENT == rc) {
		TranslateMessage( (LPMSG)&msg );
		DispatchMessage( (LPMSG)&msg );
	 }
	}
	return OK;
}
