@ECHO OFF

CD /D %~dp0..\

ECHO ========== PUBLISH SCRIPT (BEGIN) ==========

SET VERSION_MAJOR=0
SET VERSION_MINOR=0

IF EXIST .\build\version.bat (
	CALL .\build\version.bat
) else (
	TYPE nul > .\build\version.bat
)

svn info | findstr /B "URL:" > .\build\url.txt

for /f "delims=" %%a in (.\build\url.txt) do @set x=%%a

SET URL=%x:URL: =%
ECHO url = %URL%

for /f "delims=" %%a in ('svnversion') do @set x=%%a

SET VERSION=%VERSION_MAJOR%.%VERSION_MINOR%.%x%
ECHO version = %VERSION%

SET ID=%DATE:/=%
ECHO id = %ID%

SET TAG=%URL:trunk=tags%/%VERSION%_%ID%
ECHO tag = %TAG%

TIMEOUT 5

IF EXIST lib (
	IF EXIST data (
		svn copy --parents bin lib data doc include %TAG% -m "%VERSION% (%ID%)"
	) ELSE (
		svn copy --parents bin lib doc include %TAG% -m "%VERSION% (%ID%)"
	)
) ELSE (
	IF EXIST data (
		svn copy --parents bin data doc include %TAG% -m "%VERSION% (%ID%)"
	) ELSE (
		svn copy --parents bin doc include %TAG% -m "%VERSION% (%ID%)"
	)
)

ECHO ========== PUBLISH SCRIPT ( END ) ==========

TIMEOUT 5
