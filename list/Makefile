SOURCES = list.cpp
OBJECTS = list.o
HEADERS = 
EXEBIN  = list


all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES) 

clean :
	rm -f $(EXEBIN) $(OBJECTS)

