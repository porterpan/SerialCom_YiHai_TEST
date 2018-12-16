del *.db /s
rd /s/q .\Debug
rd /s/q .\ipch 
::获取二级文件夹名
for /f "delims=" %%a in ('dir /ad/b ".\*"') do (
::复制文件
rd /s/q .\%%a\Debug
)
exit