@Echo Off
:next
Set /p date=please input your birthday(exp. 20010101)


Set year=%date:~0,4%
Set monthday=%date:~4,4%
Set month=%date:~4,2%
Set day=%date:~6,2%

if "%month%" GTR "12" (
echo "输入格式错误,请重新输入"
goto next
)
if "%day%" GTR "31" (
echo "输入格式错误,请重新输入"
goto next)


Set /a mod=%year%%%12
 
if %mod%==0 Echo 你属猴
if %mod%==1 Echo 你属鸡
if %mod%==2 Echo 你属狗
if %mod%==3 Echo 你属猪
if %mod%==4 Echo 你属鼠
if %mod%==5 Echo 你属牛
if %mod%==6 Echo 你属虎
if %mod%==7 Echo 你属兔
if %mod%==8 Echo 你属龙
if %mod%==9 Echo 你属蛇
if %mod%==10 Echo 你属马
if %mod%==11 Echo 你属羊
 
 
 
if "%monthday%" LEQ "0119" echo 魔蝎座
if "%monthday%" GEQ "0120" if "%monthday%" LEQ "0218" echo 水瓶座
if "%monthday%" GEQ "0219" if "%monthday%" LEQ "0320" echo 双鱼座
if "%monthday%" GEQ "0321" if "%monthday%" LEQ "0419" echo 白羊座
if "%monthday%" GEQ "0420" if "%monthday%" LEQ "0520" echo 金牛座
if "%monthday%" GEQ "0521" if "%monthday%" LEQ "0621" echo 双子座
if "%monthday%" GEQ "0622" if "%monthday%" LEQ "0722" echo 巨蟹座
if "%monthday%" GEQ "0723" if "%monthday%" LEQ "0822" echo 狮子座
if "%monthday%" GEQ "0823" if "%monthday%" LEQ "0922" echo 处女座
if "%monthday%" GEQ "0923" if "%monthday%" LEQ "1023" echo 天秤座
if "%monthday%" GEQ "1024" if "%monthday%" LEQ "1122" echo 天蝎座
if "%monthday%" GEQ "1123" if "%monthday%" LEQ "1221" echo 天蝎座
if "%monthday%" GEQ "1222" echo 魔蝎座
goto next
Pause