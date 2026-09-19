@echo off
setlocal

echo ==========================================
echo Cleaning tracked development artifacts
echo ==========================================
echo.

git rm --cached --ignore-unmatch server
git rm --cached --ignore-unmatch 30-Jul/sniffer
git rm --cached --ignore-unmatch 30-Jul/rev_server
git rm --cached --ignore-unmatch 30-Jul/test-serverAug18
git rm --cached --ignore-unmatch 30-Jul/udp-server
git rm --cached --ignore-unmatch 30-Jul/.gdb_history

echo.
echo ==========================================
echo Git status after cleanup
echo ==========================================
git status

echo.
echo Files have NOT been committed yet.
echo Review the status above before committing.
echo.

pause