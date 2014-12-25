#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_cap_set_ctnr_onevalue( TW_UINT16 ui16_icap, TW_ONEVALUE tw_onevalue )
{
	TW_CAPABILITY	twCapability;
	pTW_ONEVALUE	p_tw_onevalue;

	/*
	www.twain.org/docs/Spec1_9_197.pdf
	 Page72,78
	 Chapter 4 -> Advenced Application Implementation
	 -> Capability -> Capability Negotiation -> Negotiation(Part 2)
	*/

	/* Step 1 : TW_CAPABILITY��¤�Τγ��ͤ����� */
	twCapability.Cap = ui16_icap;
	twCapability.ConType = TWON_ONEVALUE;

	/* Step 2 : ����ƥʡ��������ݤ����ͤ�����
		GlobalAlloc(GHND,)�ϡ���ư��ǽ�������ݤ���
		���ݤ�����������Ƥ򥼥�˽�������ޤ���
		����ͤϡ����ꥪ�֥������ȤΥϥ�ɥ�ˤʤ�ޤ���
		�ϥ�ɥ��ݥ��󥿤��Ѵ�����ˤϡ�
		GlobalLock()�ؿ�����Ѥ���
		�ͤ����ꤷ���Τ�GlobalUnlock()���ޤ���
	*/
	twCapability.hContainer = GlobalAlloc(GHND,sizeof(TW_ONEVALUE));
	if (NULL == twCapability.hContainer) {
		pri_funct_err_bttvr(
	"Error : GlobalAlloc(GHND,sizeof(TW_ONEVALUE)) returns NULL." );
		return NG;
	}
	p_tw_onevalue=(pTW_ONEVALUE)
	GlobalLock(twCapability.hContainer);
	*p_tw_onevalue = tw_onevalue; /* OneValue������ */
	GlobalUnlock(twCapability.hContainer);

	/* Step 3 : ���������ꤹ��
		(��)_cap_set_ctnr(-)����ǡ� GlobalFree()���Ƥ�
	*/
	if (OK!=this->_cap_set_ctnr(&twCapability)) {
		pri_funct_err_bttvr(
       "Error : this->_cap_set_ctnr(-) returns NG." );

		return NG;
	}

	return OK;
}

/*--------------------------------------------------------*/

int tw_win_l2_dss::_cap_set_ctnr_onevalue_bool( TW_BOOL bo_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	tw_onevalue.ItemType = TWTY_BOOL;
	tw_onevalue.Item = bo_val;

	if (OK != this->_cap_set_ctnr_onevalue(ui16_cap,
	tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_set_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	return OK;
}

int tw_win_l2_dss::_cap_set_ctnr_onevalue_fix32( double d_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	tw_onevalue.ItemType = TWTY_FIX32;
	this->_double_to_fix32( d_val,
		(TW_FIX32 *)&(tw_onevalue.Item) );

	if (OK != this->_cap_set_ctnr_onevalue(ui16_cap,
	tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_set_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	return OK;
}

int tw_win_l2_dss::_cap_set_ctnr_onevalue_ui16( TW_UINT16 ui16_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	tw_onevalue.ItemType = TWTY_UINT16;
	tw_onevalue.Item = ui16_val;

	if (OK != this->_cap_set_ctnr_onevalue(ui16_cap,
	tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_set_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	return OK;
}
