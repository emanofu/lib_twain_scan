#ifndef __tw_win_l4_scan_h__
#define __tw_win_l4_scan_h__

#include "iip_canvas.h"
#include "tw_win_l3_dsi.h"

typedef enum {
	E_PIXELTYPE_BW = 1,
	E_PIXELTYPE_GRAYSCALE,
	E_PIXELTYPE_RGB
} E_PIXELTYPE;

class iip_scan : public tw_win_l3_dsi {
public:
	iip_scan()
	{
		/* �������ϰϤȲ����� */
		this->_i_units_centimeters_sw = OFF; /* OFF is inchs */
		this->_d_left = 0.0;
		this->_d_right = 0.0;
		this->_d_bottom = 0.0;
		this->_d_top = 0.0;
		this->_d_x_resolution = 72.0;
		this->_d_y_resolution = 72.0;

		/* ��ž */
		this->_i_orientation = 0;	/* TWOR_ROT0 */

		/* �ԥ����볬Ĵ */
		this->_e_pixeltype = E_PIXELTYPE_BW;
		this->_d_threshold = 128.0; /* 0 ... 255 */

		/* ���뤵������ȥ饹�ȡ������ */
		this->_d_brightness = 0.0;
		this->_d_contrast = 0.0;
		this->_d_gamma = 1.0;

		/* ������ư��˴ؤ��� */
		this->_i_twain_gui_sw = OFF;
		this->_i_indicators_sw = ON;  /* GUI OFF����PROGRESS*/
		this->_i_xfermech_memory_sw = OFF; /* OFF is native */

		/* TWAIN������ʡ�����ξ��� */
		this->_l_uicontrollable_sw = 0L;
		this->_d_x_native_resolution = 0.0;
		this->_d_y_native_resolution = 0.0;
		this->_d_physical_width = 0.0;
		this->_d_physical_height = 0.0;

		this->_cl_iip_canvas.set_ccp_object_name_of_mv(
			"iip_scan"
		);
	}
	/* �������ϰϤȲ����� */
	int  i_centimeters_sw( void )
	{ return this->_i_units_centimeters_sw;}
	void i_centimeters_sw( int sw )
	{        this->_i_units_centimeters_sw = sw;}
	double d_left( void ) { return this->_d_left; }
	void   d_left( double dd ) {   this->_d_left = dd; }
	double d_right( void ) { return this->_d_right; }
	void   d_right( double dd ) {   this->_d_right = dd; }
	double d_bottom( void ) { return this->_d_bottom; }
	void   d_bottom( double dd ) {   this->_d_bottom = dd; }
	double d_top( void ) { return this->_d_top; }
	void   d_top( double dd ) {   this->_d_top = dd; }
	double d_x_resolution( void ) { return this->_d_x_resolution; }
	void   d_x_resolution( double dd ) { this->_d_x_resolution=dd; }
	double d_y_resolution( void ) { return this->_d_y_resolution; }
	void   d_y_resolution( double dd ) { this->_d_y_resolution=dd; }

	/* ��ž */
	int  i_orientation( void ) { return this->_i_orientation; }
	void i_orientation( int ii ) { this->_i_orientation=ii; }

	/* �ԥ����볬Ĵ */
	E_PIXELTYPE  e_pixeltype( void ) { return this->_e_pixeltype;}
	void e_pixeltype( E_PIXELTYPE tt ) { this->_e_pixeltype = tt;}
	double d_threshold( void ) { return this->_d_threshold; }
	void   d_threshold( double dd ) {   this->_d_threshold = dd; }

	/* ���뤵������ȥ饹�ȡ������ */
	double d_brightness( void ) { return this->_d_brightness; }
	void   d_brightness( double dd ) {   this->_d_brightness = dd; }
	double d_contrast( void ) { return this->_d_contrast; }
	void   d_contrast( double dd ) {   this->_d_contrast = dd; }
	double d_gamma( void ) { return this->_d_gamma; }
	void   d_gamma( double dd ) {   this->_d_gamma = dd; }

	/* ������ư��˴ؤ��� */
	int  i_twain_gui_sw( void )
	{ return this->_i_twain_gui_sw; }
	void i_twain_gui_sw( int sw )
	{        this->_i_twain_gui_sw = sw;}
	int  i_indicators_sw( void )
	{ return this->_i_indicators_sw; }
	void i_indicators_sw( int sw )
	{        this->_i_indicators_sw = sw;}
	int  i_xfer_memory_sw( void )
	{ return this->_i_xfermech_memory_sw;}
	void i_xfer_memory_sw( int sw )
	{        this->_i_xfermech_memory_sw = sw;}

	/* TWAIN������ʡ�����ξ��� */
	double d_x_native_resolution( void )
	{ return this->_d_x_native_resolution; }
	double d_y_native_resolution( void )
	{ return this->_d_y_native_resolution; }
	double d_physical_width( void )
	{ return this->_d_physical_width; }
	double d_physical_height( void )
	{ return this->_d_physical_height; }

	/* ������ʡ��ؤΥ������� */
	int open( void );

	int get_physical_param( void );
	int setup_unit( void );
	int setup_action( void );
	int print_all( void );

	int read( void );

	int close( void );

	/* ����������� */
	iip_canvas *get_clp_canvas( void )
	{ return &(this->_cl_iip_canvas); }
private:
	/* �������ϰϤȲ����� */
	int	_i_units_centimeters_sw;/* def. units_inchs     */
	double	_d_left,
		_d_right,
		_d_bottom,
		_d_top;
	double	_d_x_resolution,
		_d_y_resolution;

	/* ��ž */
	int	_i_orientation;

	/* �ԥ����볬Ĵ */
	E_PIXELTYPE _e_pixeltype;
	double	_d_threshold;         /* 0 ... 255 */

	/* ���뤵������ȥ饹�ȡ������ */
	double	_d_brightness,
		_d_contrast,
		_d_gamma;

	/* ������ư��˴ؤ��� */
	int	_i_twain_gui_sw,
		_i_indicators_sw, /* def. indicators_on_when_gui_off */
		_i_xfermech_memory_sw;  /* def. xfermech_native */

	/* TWAIN������ʡ�����ξ��� */
	long	_l_uicontrollable_sw;
	double	_d_x_native_resolution,
		_d_y_native_resolution,
		_d_physical_width,
		_d_physical_height;


	/* ����������� */
	iip_canvas	_cl_iip_canvas;

	/* dib�����Υإå���ɽ�� */
	void _pri_bitmapinfoheader( BITMAPINFOHEADER *tp_bmih );
	void _pri_rgbquad_table( int i_count, RGBQUAD *tp_bmic );
	void _pri_rgbquad( BITMAPINFO *tp_bmi );

	/* dib������iip_canvas�������Ѵ����� */
	void _trans_from_4bytes_threshold( long l_w, long l_h, long l_d_bits, unsigned char *ucharp_dib, unsigned char *ucharp_canvas );
	int _trans_image( BITMAPINFO *p_dib_bitmapinfo, iip_canvas *clp_canvas );

	/* �Ƽ�����ؿ� */
	int set_cat_indicators_(void);
	int set_icap_xfermech_(void);
	int set_icap_units_(void);
	int set_icap_pixeltype_(void);
	int set_icap_resolution_(void);
	int set_icap_threshold_(void);

	int set_icap_brightness_(void);
	int set_icap_contrast_(void);
	int set_icap_gamma_(void);
	int set_icap_orientation_(void);
	int set_dat_imagelayout_(void);
};
#endif /* !__tw_win_l4_scan_h__ */
