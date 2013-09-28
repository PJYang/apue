#!/usr/bin/env bash

i=1
s=1

while (( $i < 21 ))
do	
    awk -v b_="$s" '{if(NR==3){print "#define BUFFSIZE "b_}else{print $0}}' 3_4.cpp > /tmp/s
    mv /tmp/s 3_4.cpp

    make -f 3_4.mk clean
    make -f 3_4.mk
    
    echo -e "\nBUFFSIZE: $s"
    time ../bin/io_efficiency_test < 3_4.sample > /dev/null

    s=`expr $s \* 2`    
    i=`expr $i + 1 `
done

#run result as follows:
#Linux 3.5.0-40-generic #62~precise1-Ubuntu SMP Fri Aug 23 17:59:10 UTC 2013 i686 athlon i386 GNU/Linux
#read file size: 90824K
#BUFSIZE user_time  sys_time  real_time  
#1	0m11.985s	1m23.493s	1m55.334s
#2	0m6.460s	0m41.759s	0m53.773s
#4	0m3.056s	0m21.001s	0m27.400s
#8	0m1.424s	0m10.833s	0m14.732s
#16	0m0.744s	0m5.396s	0m7.239s
#32	0m0.384s	0m2.800s	0m3.694s
#64	0m0.184s	0m1.448s	0m1.886s
#128	0m0.096s	0m0.740s	0m0.995s
#256	0m0.036s	0m0.432s	0m0.580s
#512	0m0.016s	0m0.276s	0m0.385s
#1024	0m0.016s	0m0.192s	0m0.291s
#2048	0m0.012s	0m0.156s	0m0.248s
#4096	0m0.008s	0m0.136s	0m0.227s
#8192	0m0.000s	0m0.132s	0m0.225s
#16384	0m0.000s	0m0.136s	0m0.218s
#32768	0m0.000s	0m0.136s	0m0.217s
#65536	0m0.000s	0m0.136s	0m0.218s
#131072	0m0.000s	0m0.152s	0m0.250s
#262144	0m0.000s	0m0.268s	0m0.387s
#524288	0m0.000s	0m0.272s	0m0.387s

