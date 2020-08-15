clear
current_date_time="`date +%Y/%m/%d---%H:%M:%S`";
echo Fecha y hora de comienzo: $current_date_time
echo Programa en modo debug
make cleanL
echo compilando programa...
make debug
echo ejecutando programa....
./debug
current_date_time="`date +%Y/%m/%d---%H:%M:%S`";
echo Fecha y hora de termino:  $current_date_time
