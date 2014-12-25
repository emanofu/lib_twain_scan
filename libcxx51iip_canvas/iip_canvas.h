#ifndef __iip_canvas_h__
#define __iip_canvas_h__

#include <stdio.h>
#include "ptbl_returncode.h"
#include "iip_channel_info.h"

/*
 * �ԥ��������
 */
#ifndef CH_RED
#define CH_RED 0 /* �����Ǽ�����֥����ͥ�Υ��ե��åȰ��� */
#endif
#ifndef CH_GRE
#define CH_GRE 1 /* �����Ǽ�����Х����ͥ�Υ��ե��åȰ��� */
#endif
#ifndef CH_BLU
#define CH_BLU 2 /* �����Ǽ�����ĥ����ͥ�Υ��ե��åȰ��� */
#endif
#ifndef CH_ALP
#define CH_ALP 3 /* �����Ǽ���Φ������ͥ�Υ��ե��åȰ��� */
#endif
#ifndef SZ_RGB
#define SZ_RGB 3 /* RGB�����Ǽ�����礭�� */
#endif
#ifndef SZ_RGBA
#define SZ_RGBA 4 /* RGBA�����Ǽ�����礭�� */
#endif

/*
 * ����Х�
 */
class iip_canvas {
public:
	/* constructor */
	iip_canvas()
	{
		this->_i_mv_sw = 0;
		this->_i_pv_sw = 0;
		this->_i_cv_sw = 0;
		this->_ccp_object_name_of_mv = NULL;

		this->_clp_parent = NULL;
		this->_vp_canvas = NULL;
		this->_i_must_be_free_self_sw = OFF;

		this->_l_width = 0L;
		this->_l_height = 0L;
		this->_l_channels = 0L;

		this->_l_free_width = 0L;
		this->_l_free_height = 0L;
		this->_l_free_channels = 0L;
	}

	/* destructor */
	~iip_canvas()
	{
		this->mem_free_canvas();

		this->_i_mv_sw = 0;
		this->_i_pv_sw = 0;
		this->_i_cv_sw = 0;
		this->_ccp_object_name_of_mv = NULL;

		this->_clp_parent = NULL;
		this->_vp_canvas = NULL;
		this->_i_must_be_free_self_sw = OFF;

		this->_l_width = 0L;
		this->_l_height = 0L;
		this->_l_channels = 0L;
	}

	/* �Ѿ����ƻȤ��Ȥ��Υ��֥�������̾������ */
	void set_ccp_object_name_of_mv( const char *ccp ) {
	  this->_ccp_object_name_of_mv = ccp; }
	const char *get_ccp_object_name_of_mv( void ) {
    return this->_ccp_object_name_of_mv; }

	/* ����ɽ�������å� */
	void set_i_mv_sw( int sw ) { this->_i_mv_sw = sw; }
	void set_i_pv_sw( int sw ) { this->_i_pv_sw = sw; }
	void set_i_cv_sw( int sw ) { this->_i_cv_sw = sw; }
	int get_i_mv_sw( void ) { return this->_i_mv_sw; }
	int get_i_pv_sw( void ) { return this->_i_pv_sw; }
	int get_i_cv_sw( void ) { return this->_i_cv_sw; }

	void set_l_width(    long ll ) { this->_l_width = ll; }
	void set_l_height(   long ll ) { this->_l_height = ll; }
	void set_l_channels( long ll ) { this->_l_channels = ll; }
	long get_l_width(    void ) { return this->_l_width; }
	long get_l_height(   void ) { return this->_l_height; }
	long get_l_channels( void ) { return this->_l_channels; }

	/* �ƥ����ͥ���β��Х��ȿ������ */
	long get_l_scanline_channel_bytes( void );

	/* �ƥ����ͥ���ξ��� */
	iip_channel_info cl_ch_info;

	/* ¾(����)�ȤĤʤ��롢�̤οƤȤĤʤ��äƤ������ڤ���㤦��� */
	void set_clp_parent( iip_canvas *clp ) {this->_clp_parent=clp;}

	/* ¾(����)��canvas�������򥳥ԡ�
	(���)����canvas�����ꤷ�Ƥ���¹Ԥ��뤳�� */
	void set_canvas_size( iip_canvas *clp ) {
		this->_l_width    = clp->get_l_width();
		this->_l_height   = clp->get_l_height();
		this->_l_channels = clp->get_l_channels();
		this->cl_ch_info.set_e_ch_num_type(
			clp->cl_ch_info.get_e_ch_num_type()
		);
	}

	/* ¾(����)�Υ���򡢻���(free()���ʤ�)canvas�Ȥ������ꤹ��
	(���)����canvas����ݤ��Ƥ���¹Ԥ��뤳�� */
	void set_vp_reference_canvas( void *vp ) {
	  this->mem_free_canvas();
	  this->_vp_canvas = vp;
	  this->_i_must_be_free_self_sw = OFF;
	}
	/* ¾(����)����Υ����canvas�����ꤷ����(free)�򤳤���Ǥ����
	(���)����canvas����ݤ��Ƥ���¹Ԥ��뤳�� */
	void set_vp_independence_canvas( void *vp ) {
	  this->mem_free_canvas();
	  this->_vp_canvas = vp;
	  this->_i_must_be_free_self_sw = ON;
	}

	/* ����ɬ�פ�(������)����Х����꤫ */
	int get_i_must_be_free_self_sw( void ) {
  return this->_i_must_be_free_self_sw;
	}

	/* ¾(����)�λ��� */
	iip_canvas *get_clp_parent( void ) { return this->_clp_parent; }

	/* canvas���� */
	int mem_alloc_canvas( void );

	/* canvas���� */
	void *get_vp_canvas( void ) { return this->_vp_canvas;}

	/* ��濫���С��Ƥβ�����ʬ�ΤȤ���ˤ�äƤ��� */
	void copy_image_from_parent( const char *ccp_object_name_of_mv );

	/* canvas�õ� */
	void mem_free_canvas( void );
private:
	/* �С��ܡ����ϸġ������ꤷ�Ƥ��饳�ԡ����ʤ� */
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	/* pointer���ѹ��Ǥ��뤬���ؤ�����ʸ������ѹ��Ǥ��ʤ� */
	const char *_ccp_object_name_of_mv;

	iip_canvas *_clp_parent;

	/*
	canvas�ϳ���(����)����򻲾Ȥ�����ΤǤ�褤��
	���ξ�硢_i_must_be_free_self_sw��OFF����
	�������(free()���뤫�ݤ�)���鳰����
	*/
	void	*_vp_canvas;
	int	_i_must_be_free_self_sw;

	/* ���������Х����礭��(byteñ��) */
	long	_l_width,
		_l_height,
		_l_channels;

	/* ���������Х����礭��free��ɽ���Τ���ε��� */
	long	_l_free_width,
		_l_free_height,
		_l_free_channels;
	iip_channel_info _cl_free_ch_info;

	/* �������ؿ�etc. */
	long _get_l_scanline_channel_bytes(long l_width, long l_bytes);
};

#endif /* !__iip_canvas_h__ */
