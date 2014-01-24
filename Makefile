HEADERS = func.h util.h dynamical.h
SOURCEOBJS = main.cpp leftrect.cpp rightrect.cpp trapeze.cpp simpson.cpp dynamical.cpp PolStr.o
main : $(SOURCEOBJS) $(HEADERS)
	g++ -o lab7 $(SOURCEOBJS) 
main-32 :
	g++ -o lab7 main.cpp PolStr32.o
main-debug : $(SOURCEOBJS) $(HEADERS)
	g++ -g -O1 -o lab7 $(SOURCEOBJS)
