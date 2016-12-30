COMPILER        =       gcc
CFLAGS          =       -O3 -Wall -fno-stack-protector
LFLAGS          =       -lm
OBJECTS         =       genal.o myFunctions.o GAlib.o DNAPolygon.o DNAPicture.o
INCLUDES        =       myFunctions.h GAlib.h DNAPolygon.h DNAPicture.h

genal:           $(OBJECTS)
		$(COMPILER) $(CFLAGS) -o genal $(OBJECTS) $(LFLAGS)

genal.o: 		$(INCLUDES) genal.c
		$(COMPILER) $(CFLAGS) -c genal.c $(LFLAGS)

myFunctions.o:			myFunctions.c $(INCLUDES)
		$(COMPILER) $(CFLAGS) -c myFunctions.c $(LFLAGS)

GAlib.o:			GAlib.c $(INCLUDES)
		$(COMPILER) $(CFLAGS) -c GAlib.c $(LFLAGS)

DNAPolygon.o:			DNAPolygon.c $(INCLUDES)
		$(COMPILER) $(CFLAGS) -c DNAPolygon.c $(LFLAGS)

DNAPicture.o:			DNAPicture.c $(INCLUDES)
		$(COMPILER) $(CFLAGS) -c DNAPicture.c $(LFLAGS)

clean:
		rm -f *.o *~

realclean:	clean
		rm -f genal
