SOURCES = factory.cpp
OBJECTS = factory.o
HEADERS = 
EXEBIN  = factory
FLAGS   = 

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES) 

clean :
	rm -f $(EXEBIN) $(OBJECTS)

