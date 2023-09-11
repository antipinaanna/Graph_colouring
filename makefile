all: main.o 
	g++ -o GC main.o 
main.o: main.cpp 
	g++ -c -g main.cpp

clean: cleanobj cleanmain 

cleanobj:
	rm -f *.o

cleanmain:
	rm GC

.PHONY: clean cleanobj cleanmain