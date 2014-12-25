rem
title Microsoft Visual Studio 2010 C/C++ x86 /MT
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
rem ------------------------
for %%a in (
 libc11portable
 libc12pri
 libcxx51iip_canvas
 libcxx55iip_scan
 twain_scan_comm
) do (
 echo ------ %%a ------
 pushd %%a
 nmake /f makefile-vc2010mt all inst clean_obj
 if errorlevel 1 goto err
 popd
)
rem ------------------------
goto end
:err
echo ------------ Error ------------
popd
:end
