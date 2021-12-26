CFLAGS = -std=c99 -Wall -Wshadow -Wextra -pedantic -Ofast -flto -march=native
LDLIBS = -lm

all: convert_ascii_to_float 

convert_ascii_to_float: convert_ascii_to_float.o 

run: sendData
	./$^
	
	#./$^ /dev/ttyACM0

clean:
	$(RM) *.o


.PHONY: all
	
