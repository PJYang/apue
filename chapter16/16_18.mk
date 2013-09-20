target :=  ../bin/ruptimed_udp
CC := g++
src_file := 16_18.cpp 16_10.cpp

$(target): error_output.o apue.o 
	$(CC) -g -o $(target)  $(src_file)  error_output.o apue.o

error_output.o: ../include/error_output.cpp ../include/apue.h
	$(CC) -c  ../include/error_output.cpp
	
apue.o : ../include/apue.h ../include/apue.cpp error_output.o
	$(CC) -c ../include/apue.cpp

.PHONY : clean
clean :
	rm -rf *.o $(target)



