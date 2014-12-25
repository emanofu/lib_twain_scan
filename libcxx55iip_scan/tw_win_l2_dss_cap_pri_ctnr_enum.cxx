#include "pri.h"
#include "tw_win_l2_dss.h"

/* get enumeration_ui16(container) */
int tw_win_l2_dss::_cap_get_ctnr_enum_ui16_not_free( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability, TW_ENUMERATION **pp_tw_enumration )
{
	/* TWAIN���狼��ǡ������äƤ��� */
	if (OK != this->_cap_get_ctnr( ui16_cap, p_tw_capability ) ) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr() returns NG." );
		return NG;
	}

	/* �ǡ����Υ���ƥʥ����פ��㤦 */
	if (TWON_ENUMERATION != p_tw_capability->ConType) {
		pri_funct_err_bttvr(
	"Error : p_tw_capability->ConType is not TWON_ENUMERATION." );

		/* Windows ��ͭ�Τ��ޤ��ʤ�1/3 */
		GlobalFree( (HANDLE)p_tw_capability->hContainer );
		return NG;
	}

	/* Windows ��ͭ�Τ��ޤ��ʤ�2/3 */
	(*pp_tw_enumration) = (pTW_ENUMERATION)GlobalLock(
		(HANDLE)p_tw_capability->hContainer
	);

	/* �ǡ�������Ĥ�ʤ� */
	if ((*pp_tw_enumration)->NumItems <= 0) {
		pri_funct_err_bttvr(
   "Error : (*pp_tw_enumration)->NumItems is zero." );
		GlobalUnlock( (HANDLE)p_tw_capability->hContainer );
		GlobalFree( (HANDLE)p_tw_capability->hContainer );
		return NG;
	}

	/* �ǡ�������η������å� */
	if (TWTY_UINT16 != (*pp_tw_enumration)->ItemType) {
		pri_funct_err_bttvr(
	"Error : (*pp_tw_enumration)->ItemType is not TWTY_UINT16." );
		GlobalUnlock( (HANDLE)p_tw_capability->hContainer );
		GlobalFree( (HANDLE)p_tw_capability->hContainer );
		return NG;
	}

	/*
	GlobalUnlock( (HANDLE)p_tw_capability->hContainer );
	GlobalFree( (HANDLE)p_tw_capability->hContainer );
	���������Τǡ��ƤӽФ����Ǽ¹Ԥ��뤳�ȡ�
	*/

	return OK;
}

int tw_win_l2_dss::_cap_pri_ctnr_enum_ui16( TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_CAPABILITY tw_capability;
	TW_ENUMERATION *p_tw_enumration;
	unsigned short	*ushortp_tmp;

	long	ii;


	if (OK != this->_cap_get_ctnr_enum_ui16_not_free( ui16_cap,
	&tw_capability, &p_tw_enumration )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_enum_ui16_not_free(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	pri_funct_msg_vr(
	"%-16s 0x%04x TW_ENUM. type %u num %lu crnt %lu def %lu",
		cp_cap_name,
		ui16_cap,
		p_tw_enumration->ItemType,
		p_tw_enumration->NumItems,
		p_tw_enumration->CurrentIndex,
		p_tw_enumration->DefaultIndex
	);

	/* p_tw_enumration->ItemList[ii]�� unsigned char(TW_UINT8)��
	p_tw_enumration->ItemType is 4
	#define TWTY_UINT16 0x0004
	*/
	ushortp_tmp = (unsigned short *)(p_tw_enumration->ItemList);

	pri_funct_msg_v( "\t\t\t\t" );
	for (ii = 0L; ii < (long)(p_tw_enumration->NumItems); ++ii) {
		pri_funct_msg_v( " %u", ushortp_tmp[ii] );
	}
	pri_funct_msg_v( "\n" );

	/* Windows ��ͭ�Τ��ޤ��ʤ�3/3 */
	GlobalUnlock( (HANDLE)tw_capability.hContainer );
	GlobalFree( (HANDLE)tw_capability.hContainer );

	return OK;
}
