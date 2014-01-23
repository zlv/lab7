SOURCEOBJS = main.cpp leftrect.cpp rightrect.cpp PolStr.o
main :
	g++ -o lab7 $(SOURCEOBJS) 
main-32 :
	g++ -o lab7 main.cpp PolStr32.o
main-debug :
	g++ -g -O1 -o lab7 $(SOURCEOBJS)
