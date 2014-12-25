名前
	lib_twain_scan - TWAINスキャン

バージョン
	1.0.0

環境
	Windows 7 Professional SP1
	Microsoft Visual C++ 2010 SP1
	TWAIN 1.9(twain.h)
	EPSON TWAIN Ver. 5.0.3.2 JA
	他の環境では動作未確認

解説
	C/C++プログラムから呼び出して使うライブラリーツールキット。
	Windowsパソコンと、
	TWAINドライバーソフトで動作するスキャナーを使って、
	画像をスキャンし、データとして取り込む。

	libc11portable/			ユーティリティ
	libc12pri/			ユーティリティ
	libcxx51iip_canvas/		ユーティリティ
	libcxx55iip_scan/		TWAIN SCAN
	twain_scan_comm/		実行コマンド
	one_step_build_vc2010md.bat	コマンドをビルド(/MDオプション)
	one_step_build_vc2010mt.bat	コマンドをビルド(/MTオプション)
	README.txt			このファイル
	twain.h.zip			TWAIN 1.9ヘッダーをzip圧縮

使い方
	"one_step_build_vc2010md.bat"でビルドした場合、
	"%HOMEDRIVE%%HOMEPATH%\utility_tools\vc2010md\x86\gts\bin\twain_scan_comm.exe"
	を実行

使用許諾
	ファイル"LICENSE"を見てください。
