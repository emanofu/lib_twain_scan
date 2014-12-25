#include <windows.h>
#include "twain_scan_comm_adapter.cxx"
namespace {
 LRESULT CALLBACK WindowProc_(
	HWND WindowHandle_ ,UINT message ,WPARAM wParam ,LPARAM lParam
 ) {
	switch ( message ) {
		case WM_COMMAND: break;
		case WM_PAINT:   break;
		case WM_DESTROY: ::PostQuitMessage( 0 ); break;
		default:         break;
	}
	return ::DefWindowProc( WindowHandle_, message, wParam, lParam );
 }
}
int main(int argc ,char *argv[])
{
	double	left=0 ,right=29.718 ,top=0 ,bottom=43.18
		,reso=400.  ,pixel_type=1. /* 0:BW 1:GRAYSCALE 2:RGB */
		,threshold=128.  ,brightness=0 ,contrast=0 ,gamma=1.;
	std::string save_file_path;
	HWND WindowHandle_;
 {
	std::string msg;
	const int ret = argument_to_parameters_(
		argc ,argv
		,left ,right ,top ,bottom
		,reso ,pixel_type /* 0:BW 1:GRAYSCALE 2:RGB */
		,threshold ,brightness ,contrast ,gamma
		,save_file_path
		,msg
	);

	if (ret != 0 || save_file_path.empty()) {
		std::cout << msg; return 1;
	}
 }
 {
	const char WindowName_[] = "twain_scan";
	const char ClassName_[] = "twain_scan_class";
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WindowProc_;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= ClassName_;
	wcex.hIconSm		= NULL;
	::RegisterClassEx( &wcex );

	/* ウィンドウの作成 */
	WindowHandle_   = ::CreateWindow(
		ClassName_, WindowName_
		,WS_OVERLAPPEDWINDOW
		,CW_USEDEFAULT ,0 ,CW_USEDEFAULT ,0
		//,100 ,100 ,400 ,300
		,NULL ,NULL ,hInstance ,NULL
	);
	if ( !WindowHandle_ ) { return 2; }
 }
 {
	iip_scan iipscan;
	iipscan.set_hw_parent( WindowHandle_ );
	/*--- 上下左右位置はセンチメータ単位で処理する ---*/
	iipscan.i_centimeters_sw(ON);
	/*-- 設定 ---*/
	parameters_to_iip_scan_(
		left ,right ,top ,bottom
		,reso ,pixel_type /* 0:BW 1:GRAYSCALE 2:RGB */
		,threshold ,brightness ,contrast ,gamma
		,iipscan
	);
	/*--- 実行 ---*/
	if (NG == scan_( iipscan )) {
		return 3;
	}

	/*--- 保存 ---*/
	save_( iipscan ,save_file_path );
 }
	return 0;
}
