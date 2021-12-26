SOURCES = animal_speak.cpp
OBJECTS = animal_speak.o
HEADERS = 
EXEBIN  = animal_speak


all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES) 

clean :
	rm -f $(EXEBIN) $(OBJECTS)

