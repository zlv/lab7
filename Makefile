SOURCEOBJS = main.cpp 
main :
	g++ -o lab7 $(SOURCEOBJS) 
main-32 :
	g++ -o lab7 main.cpp
main-debug :
	g++ -g -O1 -o lab7 $(SOURCEOBJS)
