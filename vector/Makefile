SOURCES = vector.cpp
OBJECTS = vector.o
HEADERS = 
EXEBIN  = vector


all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES) 

clean :
	rm -f $(EXEBIN) $(OBJECTS)

