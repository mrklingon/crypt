cq.exe:	cq.c makefile
	gcc -mno-cygwin -o cq cq.c

install: cq.exe
	strip cq.exe
	cp cq.exe /unix/
