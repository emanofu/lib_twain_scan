#include "tw_win_l1_dsm.h"

/* ��ˡ�AppID���Ф������ꡢ
SourceID�ϥǡ��������������ץ�λ��ϡ��ɤ����ɤ�����ꤹ��Τǡ�
���ߡ�����ΤȤʤ� */
void tw_win_l1_dsm::_init_tw_id( TW_IDENTITY *p_tw_id )
{
	p_tw_id->Id = 0;
	p_tw_id->Version.MajorNum = 0;
	p_tw_id->Version.MinorNum = 1;
	p_tw_id->Version.Language = TWLG_JAPANESE;
	p_tw_id->Version.Country = TWCY_JAPAN;
	p_tw_id->ProtocolMajor = TWON_PROTOCOLMAJOR;
	p_tw_id->ProtocolMinor = TWON_PROTOCOLMINOR;
	p_tw_id->SupportedGroups = DG_IMAGE | DG_CONTROL;

	/* ��������ϥ��ץꥱ������󤴤Ȥ����� */

	strcpy(p_tw_id->Version.Info, "");

	/* ��ȯ��(�᡼����)(\0��ޤ��34ʸ��) */
	strcpy(p_tw_id->Manufacturer, "");

	/* ���꡼��̾(���ʥե��ߥ꡼)(\0��ޤ��34ʸ��) */
	strcpy(p_tw_id->ProductFamily, "");

	/* ����̾(\0��ޤ��34ʸ��) */
	strcpy(p_tw_id->ProductName, "");
}
