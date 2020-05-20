::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
: This batch file only handles 20 options for the compiler. This should
: be sufficient. You can figure out how to add more, if necessary.
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
@echo off

set /a count=1

:BEGIN
if "%1"=="" goto END
set arg%count%=%1
shift
set /a count=%count%+1
goto BEGIN

:END
c:\mingw32\mingw32\bin\g++.exe %arg1% %arg2% %arg3% %arg4% %arg5% %arg6% %arg7% %arg8% ^
%arg9% %arg10% %arg11% %arg12% %arg13% %arg14% %arg15% %arg16% ^
%arg17% %arg18% %arg19% %arg20%

set arg1=
set arg2=
set arg3=
set arg4=
set arg5=
set arg6=
set arg7=
set arg8=
set arg9=
set arg10=
set arg11=
set arg12=
set arg13=
set arg14=
set arg15=
set arg16=
set arg17=
set arg18=
set arg19=
set arg20=
