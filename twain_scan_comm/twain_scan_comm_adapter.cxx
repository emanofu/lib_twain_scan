#include <windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "pri.h"
#include "tw_win_l4_scan.h" // iip_scan

/* twainに送っているパラメータが何かは以下のコード
../libcxx55iip_scan/tw_win_l4_scan_orc.cxx */

namespace {
 /*------ 引数 ------*/
 void help_(
	const char *title
	,double left
	,double right
	,double top
	,double bottom
	,double reso
	,double pixel_type /* 0:BW 1:GRAYSCALE 2:RGB */
	,double threshold
	,double brightness
	,double contrast
	,double gamma
	,std::string&msg
 ) {
	std::ostringstream ost;
	ost
		<< "Usage : " << title << " file [options]\n"
		<< "file\n"
		<< " Save raw image[file.raw] and\n"
		<< "           info[file.txt].\n"
		<< "[options]\n"
<< " -h  "  << "        :Help\n"
<< " -le " << std::setw(8) << std::left << left	<< ":left\n"
<< " -ri " << std::setw(8) << std::left << right	<< ":right\n"
<< " -to " << std::setw(8) << std::left << top	<< ":top\n"
<< " -bo " << std::setw(8) << std::left << bottom	<< ":bottom\n"
<< " -re " << std::setw(8) << std::left << reso	<< ":reso\n"
<< " -pi " << std::setw(8) << std::left << pixel_type
				<< ":pixel_type 0:BW 1:GRAYSCALE 2:RGB\n"
<< " -th " << std::setw(8) << std::left << threshold	<< ":threshold\n"
<< " -br " << std::setw(8) << std::left << brightness<< ":brightness\n"
<< " -co " << std::setw(8) << std::left << contrast	<< ":contrast\n"
<< " -ga " << std::setw(8) << std::left << gamma	<< ":gamma\n"
		;
	msg += ost.str();
 }
 int argument_to_parameters_(
	int argc ,char *argv[]
	,double&left
	,double&right
	,double&top
	,double&bottom
	,double&reso
	,double&pixel_type /* 0:BW 1:GRAYSCALE 2:RGB */
	,double&threshold
	,double&brightness
	,double&contrast
	,double&gamma
	,std::string&save_file_path
	,std::string&msg
 ) {
	int ret = 0;
	for (int ii=1; ii< argc; ++ii) {
	 if      (!strcmp(argv[ii], "-h")) { ret = 1; break; }
	 else if (!strcmp(argv[ii], "-le")) { left	=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-ri")) { right	=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-to")) { top	=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-bo")) { bottom	=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-re")) { reso	=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-pi")) { pixel_type=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-th")) { threshold =atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-br")) { brightness=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-co")) { contrast	=atof(argv[++ii]);}
	 else if (!strcmp(argv[ii], "-ga")) { gamma	=atof(argv[++ii]);}
	 else {
		if (!save_file_path.empty()) {
			msg += "Error : too many filenames\n";
			ret = 2;
			break;
		}
		save_file_path = argv[ii];
	 }
	}
	if (save_file_path.empty()) {
		msg += "Error : no filename\n";
		ret = 3;
	}
	if (ret != 0) {
		help_(	argv[0]
			,left ,right ,top ,bottom
			,reso ,pixel_type /* 0:BW 1:GRAYSCALE 2:RGB */
			,threshold ,brightness ,contrast ,gamma
			,msg
		);
		return ret;
	}
	return 0;
 }
 /*------ 設定 ------*/
 void parameters_to_iip_scan_(
	const double left
	,const double right
	,const double top
	,const double bottom
	,const double reso
	,const double pixel_type /* 0:BW 1:GRAYSCALE 2:RGB */
	,const double threshold
	,const double brightness
	,const double contrast
	,const double gamma
	,iip_scan&iipscan
 ) {
	/* 上下左右切り取り(原点左上のため画面上より下が大きい値となる) */
	iipscan.d_left(  left );
	iipscan.d_right( right );
	iipscan.d_top(   top );
	iipscan.d_bottom(bottom );

	/* 解像度 */
	iipscan.d_x_resolution( reso );
	iipscan.d_y_resolution( reso );

	/* ピクセルタイプ */
	switch ( (int)pixel_type ) { /* 0:BW 1:GRAYSCALE 2:RGB */
	case 0:
		iipscan.e_pixeltype( E_PIXELTYPE_BW );
		iipscan.d_threshold( threshold );
		break;
	case 1:
		iipscan.e_pixeltype( E_PIXELTYPE_GRAYSCALE );
		iipscan.d_brightness( brightness );
		iipscan.d_contrast( contrast );
		iipscan.d_gamma( gamma );
		break;
	case 2:
		iipscan.e_pixeltype( E_PIXELTYPE_RGB );
		iipscan.d_brightness( brightness );
		iipscan.d_contrast( contrast );
		iipscan.d_gamma( gamma );
		break;
	}
 }
 /*------ 実行 ------*/
 int scan_action_( iip_scan&iipscan ) {
	/* スキャナーに対して、スキャンの単位を一番始めに設定 */
	if (OK != iipscan.setup_unit()) {
		pri_funct_err_bttvr(
	 "Error : iipscan.setup_unit() returns NG.");
		return NG;
	}

	/* スキャナーのハード情報を取って来る */
	if (OK != iipscan.get_physical_param()) {
		pri_funct_err_bttvr(
	 "Error : iipscan.get_physical_param() returns NG.");
		return NG;
	}

	/* パラメータ設定をスキャナーへ送る */
	if (OK != iipscan.setup_action()) {
		pri_funct_err_bttvr(
	 "Error : iipscan.setup_action() returns NG.");
		return NG;
	}

	/* 設定したスキャナー情報を表示 */
/***
	if (OK != iipscan.print_all()) {
		pri_funct_err_bttvr(
	"Error : iipscan.print_all() returns NG" );
		return NG;
	}
***/

	/* 画像をスキャンして読む */
	if (OK != iipscan.read()) {
		pri_funct_err_bttvr(
	 "Error : iipscan.read() returns NG.");
		return NG;
	}

	return OK;
 }
 int scan_( iip_scan&iipscan ) {
	int	i_ret;

	if (OK != iipscan.open()) {
		pri_funct_err_bttvr(
	 "Error : iipscan.open() returns NG.");
		return NG;
	}

	i_ret = OK;
	if (OK != scan_action_( iipscan )) {
		pri_funct_err_bttvr(
	 "Error : scan_action_(-) returns NG.");
		i_ret = NG; /* ここでエラーがおきてもclose()はやる */
	}

	if (OK != iipscan.close()) {
		pri_funct_err_bttvr(
	 "Error : iipscan.close() returns NG.");
		return NG;
	}

	return i_ret;
 }
 /*------ 保存 ------*/
 void save_(
	iip_scan&iipscan
	,const std::string&save_file_path
 ) {
	iip_canvas *iip_canvas_ptr = iipscan.get_clp_canvas();

	/*--- raw画像(左上原点)を保存 ---*/
 	std::string save_raw( save_file_path );
 	save_raw += ".raw";
	std::cout << "Save Start " << save_raw << std::endl;
	int scanline_size = 0;
	if (0 < iip_canvas_ptr->cl_ch_info.get_l_bytes()) {
		scanline_size = iip_canvas_ptr->get_l_width() *
				iip_canvas_ptr->get_l_channels() *
				iip_canvas_ptr->cl_ch_info.get_l_bytes();
	} else {
		scanline_size = ((iip_canvas_ptr->get_l_width() / 8) +
				(((iip_canvas_ptr->get_l_width()%8)!=0)?1:0)
				) *
				iip_canvas_ptr->get_l_channels();
	}
	const int siz =	iip_canvas_ptr->get_l_height() * scanline_size;
	std::ofstream ofs_raw( save_raw.c_str()  ,std::ios::binary );
	ofs_raw.write( (const char *)iip_canvas_ptr->get_vp_canvas() ,siz );
	ofs_raw.close();
	std::cout<< "Save End   "<< save_raw <<std::endl;

	/*--- 画像情報を保存 ---*/
 	std::string save_txt( save_file_path );
 	save_txt += ".txt";
	std::cout << "Save Start " << save_txt << std::endl;
	std::ofstream ofs_txt( save_txt.c_str() );
	ofs_txt
		<< "幅         " << iip_canvas_ptr->get_l_width() << "\n"
		<< "高         " << iip_canvas_ptr->get_l_height() << "\n"
		<< "チャンネル " << iip_canvas_ptr->get_l_channels() << "\n"
		<< "ビット     " <<
			((0 < iip_canvas_ptr->cl_ch_info.get_l_bytes())
			    ? iip_canvas_ptr->cl_ch_info.get_l_bytes()*8
			    : 1
			)
			<< "\n"
		<< "型番         \""
			<< iipscan.get_cp_machine_type() << "\"" << "\n"
		<< "物理的解像度 "
			<< "縦=" << iipscan.d_x_native_resolution() << "dot"
			<<" 横=" << iipscan.d_y_native_resolution() << "dot"
			<< "\n"
		<< "物理的最大   "
			<< "幅=" << iipscan.d_physical_width()
			<< ((ON == iipscan.i_centimeters_sw())?"cm":"inch")
			<< " 高=" << iipscan.d_physical_height()
			<< ((ON == iipscan.i_centimeters_sw())?"cm":"inch")
			<< "\n"
		;
	ofs_txt.close();
	std::cout<< "Save End   "<< save_txt <<std::endl;
 }
}
