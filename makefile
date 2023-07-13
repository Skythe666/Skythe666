CC := gcc
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, obj/%.o, $(SRC))
HED := $(wildcard headers/*.h)
FINALFLAGS := 
LINKERFLAGS := -Iheaders/
.PHONY: headers

all: main
  
main: $(OBJ) $(HED)
	gcc -o main  $(OBJ) $(HED) $(FINALFLAGS) 
obj/%.o : src/%.c $(HED)
	gcc $(LINKERFLAGS) -c -o $@ $<
headers:
	./makeheaders.sh
