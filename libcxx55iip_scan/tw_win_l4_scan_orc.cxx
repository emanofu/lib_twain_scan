#include <assert.h>
#include "pri.h"
#include "tw_win_l4_scan.h"

int iip_scan::open( void )
{
	/*
	 * DLL���ɡ�DSM�Υ����ץ�DS�Υ����ץ�
	 */

	if (OK != this->state1to2()) { pri_funct_err_bttvr(
	 "Error : this->state1to2() returns NG." ); return NG; }
	if (OK != this->state2to3()) { pri_funct_err_bttvr(
	 "Error : this->state2to3() returns NG." ); return NG; }
	if (OK != this->state3to4()) { pri_funct_err_bttvr(
	 "Error : this->state3to4() returns NG." ); return NG; }

	/* TWAIN GUI���̻Ȥ�ʤ��Ȥ� */
	if (OFF == this->_i_twain_gui_sw) {
	 /* GUI�ʤ����б����Ƥ��뤫�ɤ���Ĵ�٤� */
	 if (OK != this->cap_get_lp_uicontrollable_sw(
			 &(this->_l_uicontrollable_sw))) {
		pri_funct_err_bttvr(
	  "Error : this->cap_get_lp_uicontrollable_sw() returns NG." );
		return NG;
	 }

	 /* GUI�ʤ����б����Ƥ��ʤ��ʤ饨�顼�Ȥ��� */
	 if (ON != this->_l_uicontrollable_sw) {
		pri_funct_err_bttvr(
  "Error : this->cap_get_lp_uicontrollable_sw(%ld is not ON).",
		   this->_l_uicontrollable_sw);
		return NG;
	 }
	}

	return OK;
}

int iip_scan::setup_unit( void )
{
	return this->set_icap_units_();
}
int iip_scan::set_icap_units_(void) {
	/* ���ͤ�ñ�̤����� */
	if (ON == this->_i_units_centimeters_sw) {
		if (OK != this->cap_set_units_centimeters()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_units_centimeters() return NG."
			);
			return NG;
		}
	} else {
		if (OK != this->cap_set_units_inchs()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_units_inchs() return NG.");
			return NG;
		}
	}
	return OK;
}

int iip_scan::get_physical_param( void )
{
	/* ���ز����٤����� */
	if (OK != this->cap_get_dp_x_native_resolution(
			&(this->_d_x_native_resolution))) {
		pri_funct_err_bttvr(
	 "Error : this->cap_get_dp_x_native_resolution() returns NG." );
		return NG;
	}

	if (OK != this->cap_get_dp_y_native_resolution(
			&(this->_d_y_native_resolution))) {
		pri_funct_err_bttvr(
	 "Error : this->cap_get_dp_y_native_resolution() returns NG." );
		return NG;
	}

	/* ʪ��Ū���礭�������� */
	if (OK != this->cap_get_dp_physical_width(
			&(this->_d_physical_width))) {
		pri_funct_err_bttvr(
	 "Error : this->cap_get_dp_physical_width() returns NG." );
		return NG;
	}
	if (OK != this->cap_get_dp_physical_height(
			&(this->_d_physical_height))) {
		pri_funct_err_bttvr(
	 "Error : this->cap_get_dp_physical_height() returns NG." );
		return NG;
	}

	return OK;
}

/*------------------------------------------------------------
White Paper:
Capability Ordering
The TWAIN Working Group
September 1, 2009
��ꡢ��ǽ(Capabiluty)���������ˤĤ���

01.CAP_INDICATORS	����Ω������ǽ(is Independent Capabilities)

�ʲ����夫�鲼�ء������鱦�ء��ν�����ꤹ�뤳��
02.ICAP_XFERMECH
   |
   v
03.ICAP_UNITS	��"iip_scan::setup_unit()"�Ǽ¹Ԥ��Ƥ��뤬�������ꤹ��
   |
   v
04.ICAP_PIXELTYPE --> ICAP_BITDEPTH	--> 05.ICAP_XRESOLUTION�Ȱ�¸����
   |					--> 05.ICAP_YRESOLUTION�Ȱ�¸����
   |					--> ICAP_BITDEPTHREDUCTION
   |						|
   |						v
   |					    06.ICAP_THRESHOLD�Ȱ�¸����
   v
ICAP_AUTOBRIGHT --> 07.ICAP_BRIGHTNESS�Ȱ�¸����
   |
   v
08.ICAP_CONTRAST
   |
   v
09.ICAP_GAMMA
   |
   v
10.ICAP_ORIENTATION

11.DAT_IMAGELAYOUT
---------------------------------------------
01 this->cap_set_indicators_on_when_gui_off()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	CAP_INDICATORS	TRUE
   this->cap_set_indicators_off_when_gui_off()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	CAP_INDICATORS	FALSE
02 this->cap_set_xfermech_memory()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_XFERMECH	TWSX_MEMORY
   this->cap_set_xfermech_native()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_XFERMECH	TWSX_NATIVE
03 this->cap_set_units_centimeters()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_UNITS TWUN_CENTIMETERS
   this->cap_set_units_inchs()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_UNITS TWUN_INCHES
04 this->cap_set_pixeltype_bw()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_PIXELTYPE	TWPT_BW
   this->cap_set_pixeltype_gray()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_PIXELTYPE	TWPT_GRAY
   this->cap_set_pixeltype_rgb()
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_PIXELTYPE	TWPT_RGB
05 this->cap_set_d_x_resolution(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_XRESOLUTION
   this->cap_set_d_y_resolution(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_YRESOLUTION
06 this->cap_set_d_threshold(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_THRESHOLD
07 this->cap_set_d_brightness(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_BRIGHTNESS
08 this->cap_set_d_contrast(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_CONTRAST
09 this->cap_set_d_gamma(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_GAMMA
10 this->cap_set_i_orientation(-)
	DG_CONTROL,DAT_CAPABILITY,MSG_SET	ICAP_ORIENTATION
11 this->imagelayout_set_d_area(-)
	DG_IMAGE,DAT_IMAGELAYOUT,MSG_SET	-
------------------------------------------------------------*/
int iip_scan::set_cat_indicators_(void) {
	/* TWAIN GUI���̻Ȥ�ʤ��Ȥ� */
	if (OFF == this->_i_twain_gui_sw) {
	 /* TWAIN GUI OFF����progress�С���ɽ�� */
	 if (ON == this->_i_indicators_sw) {
		if (OK != this->cap_set_indicators_on_when_gui_off()) {
			pri_funct_err_bttvr(
 "Error : this->cap_set_indicators_on_when_gui_off() return NG.");
			return NG;
		}
	 } else {
		if (OK != this->cap_set_indicators_off_when_gui_off()) {
			pri_funct_err_bttvr(
 "Error : this->cap_set_indicators_off_when_gui_off() return NG.");
			return NG;
		}
	 }
	}
	return OK;
}
int iip_scan::set_dat_imagelayout_(void) {
	/* �ɤ߼���ϰϤ����� */
	if ((this->_d_left != this->_d_right)
	&&  (this->_d_bottom != this->_d_top)) {
		if (OK != this->imagelayout_set_d_area(
		this->_d_left, this->_d_right,
		this->_d_bottom, this->_d_top
		)) {
			pri_funct_err_bttvr(
		 "Error : this->imagelayout_set_d_area(-) return NG.");
			return NG;
		}
	}
	return OK;
}
int iip_scan::set_icap_resolution_(void) {
	/* �ɤ߼������٤����� */
	if (OK != this->cap_set_d_x_resolution(this->_d_x_resolution)) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_d_x_resolution(-) return NG.");
		return NG;
	}
	if (OK != this->cap_set_d_y_resolution(this->_d_y_resolution)) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_d_y_resolution(-) return NG.");
		return NG;
	}
	return OK;
}
int iip_scan::set_icap_pixeltype_(void) {
	/* �ԥ����륿���פ����� */
	switch (this->_e_pixeltype) {
	case E_PIXELTYPE_BW:
		if (OK != this->cap_set_pixeltype_bw()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_pixeltype_bw(-) return NG.");
			return NG;
		}
		/****if (OK != this->cap_set_i_bitdepth(1)) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_i_bitdepth(1) return NG.");
			return NG;
		}***/
		break;
	case E_PIXELTYPE_GRAYSCALE:
		if (OK != this->cap_set_pixeltype_gray()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_pixeltype_gray(-) return NG.");
			return NG;
		}
		/****if (OK != this->cap_set_i_bitdepth(8)) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_i_bitdepth(8) return NG.");
			return NG;
		}***/
		break;
	case E_PIXELTYPE_RGB:
		if (OK != this->cap_set_pixeltype_rgb()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_pixeltype_rgb(-) return NG.");
			return NG;
		}
		/***if (OK != this->cap_set_i_bitdepth(8)) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_i_bitdepth(8) return NG.");
			return NG;
		}***/
		break;
	default:
		assert(0);
	}
	return OK;
}
int iip_scan::set_icap_threshold_(void) {
	/* bw���Τ������ͤ����� */
	if (OK != this->cap_set_d_threshold( this->_d_threshold )) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_d_threshold(-) return NG.");
		return NG;
	}
	return OK;
}
int iip_scan::set_icap_brightness_(void) {
	/* ���뤵 */
	if (OK != this->cap_set_d_brightness( this->_d_brightness )) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_d_brightness(-) return NG.");
		return NG;
	}
	return OK;
}
int iip_scan::set_icap_contrast_(void) {
	/* ����ȥ饹�� */
	if (OK != this->cap_set_d_contrast( this->_d_contrast )) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_d_contrast(-) return NG.");
		return NG;
	}
	return OK;
}
int iip_scan::set_icap_gamma_(void) {
	/* ����� */
	if (OK != this->cap_set_d_gamma( this->_d_gamma )) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_d_gamma(-) return NG.");
		return NG;
	}
	return OK;
}
int iip_scan::set_icap_xfermech_(void) {
	/* TWAIN�Ǥβ�������������ˡ */
	if (ON == this->_i_xfermech_memory_sw) {
		if (OK != this->cap_set_xfermech_memory()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_xfermech_memory(-) return NG.");
			return NG;
		}
	} else {
		if (OK != this->cap_set_xfermech_native()) {
			pri_funct_err_bttvr(
		 "Error : this->cap_set_xfermech_native(-) return NG.");
			return NG;
		}
	}
	return OK;
}
int iip_scan::set_icap_orientation_(void) {
	/* �����β�ž */
	if (OK != this->cap_set_i_orientation( this->_i_orientation )) {
		pri_funct_err_bttvr(
	 "Error : this->cap_set_i_orientation(-) return NG.");
		return NG;
	}
	return OK;
}
int iip_scan::setup_action( void )
{
	/* ��ǽ(Capability)������ */
	int ret=0;
	ret = this->set_cat_indicators_();	if (ret != OK) {return ret;}
	ret = this->set_icap_xfermech_();	if (ret != OK) {return ret;}
	ret = this->set_icap_units_();		if (ret != OK) {return ret;}
	ret = this->set_icap_pixeltype_();	if (ret != OK) {return ret;}
	ret = this->set_icap_resolution_();	if (ret != OK) {return ret;}
	ret = this->set_icap_threshold_();	if (ret != OK) {return ret;}

	ret = this->set_icap_brightness_();	if (ret != OK) {return ret;}
	ret = this->set_icap_contrast_();	if (ret != OK) {return ret;}
	ret = this->set_icap_gamma_();		if (ret != OK) {return ret;}
	ret = this->set_icap_orientation_();	if (ret != OK) {return ret;}
	ret = this->set_dat_imagelayout_();	if (ret != OK) {return ret;}

	return OK;
}

int iip_scan::print_all( void )
{
	double	d_x_reso,
		d_y_reso;

	if (OK != this->imageinfo_pri_all()) { return NG; }
	if (OK != this->imagelayout_pri_all()) { return NG; }
	if (OK != this->setupmemxfer_pri_all()) { return NG; }

	if (OK != this->imageinfo_get_dp_reso(&d_x_reso,&d_y_reso)) {
		return NG;
	}
	pri_funct_msg_vr( "imageinfo resolution x %.16g y %.16g",
		d_x_reso, d_y_reso );

	if (OK != this->cap_pri_brightness()) { return NG; }
	if (OK != this->cap_pri_contrast()) { return NG; }
	if (OK != this->cap_pri_gamma()) { return NG; }
	if (OK != this->cap_pri_xresolution()) { return NG; }
	if (OK != this->cap_pri_yresolution()) { return NG; }
	if (OK != this->cap_pri_indicators()) { return NG; }
	if (OK != this->cap_pri_units()) { return NG; }
	if (OK != this->cap_pri_xfermech()) { return NG; }
	if (OK != this->cap_pri_pixeltype()) { return NG; }
	if (OK != this->cap_pri_bitdepth()) { return NG; }
	if (OK != this->cap_pri_orientation()) { return NG; }
	if (OK != this->cap_pri_threshold()) { return NG; }

	/* TWAIN������ʡ������ɤ߼�ä����� */
	pri_funct_msg_vr( "native_resolution x %.16g y %.16g",
		this->_d_x_native_resolution,
		this->_d_y_native_resolution );
	pri_funct_msg_vr( "physical_area     x %.16g y %.16g",
		this->_d_physical_width,
		this->_d_physical_height );
	pri_funct_msg_vr( "uicontrollable_sw %ld",
		this->_l_uicontrollable_sw );

	return OK;
}

int iip_scan::read( void )
{
	HWND h_wnd = NULL;
	unsigned short us_show_ui = FALSE;
	unsigned short us_model_ui = FALSE;

	if (ON == this->_i_twain_gui_sw) {
		h_wnd = this->_hw_parent;
		us_show_ui = TRUE, 
		us_model_ui = TRUE;
	}

	if (OK != this->state4to5( h_wnd, us_show_ui, us_model_ui )) {
		pri_funct_err_bttvr(
	 "Error : this->state4to5() returns NG." ); return NG; }
	if (OK != this->state5to6to5event()) { pri_funct_err_bttvr(
	 "Error : this->state5to6to5event() returns NG." ); return NG; }
	if (OK != this->state5to4()) { pri_funct_err_bttvr(
	 "Error : this->state5to4() returns NG." ); return NG; }

	if (NULL != this->_p_dib_bitmapinfo) {
		/* Native�������ΤȤ��β������� */
		if (ON == this->get_i_pv_sw()) {
			this->_pri_bitmapinfoheader(
				&(this->_p_dib_bitmapinfo->bmiHeader)
			);
			this->_pri_rgbquad( this->_p_dib_bitmapinfo );
		}

		/* DIB������iip_canvas�����˰��� */
		if (OK != this->_trans_image(
			this->_p_dib_bitmapinfo,
			&(this->_cl_iip_canvas)
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_trans_image() returns NG." );
			return NG;
		}
	}

	return OK;
}

int iip_scan::close( void )
{
	if (OK != this->state4to3()) { pri_funct_err_bttvr(
	 "Error : this->state4to3() returns NG." ); return NG; }
	if (OK != this->state3to2()) { pri_funct_err_bttvr(
	 "Error : this->state3to2() returns NG." ); return NG; }
	if (OK != this->state2to1()) { pri_funct_err_bttvr(
	 "Error : this->state2to1() returns NG." ); return NG; }
	return OK;
}
