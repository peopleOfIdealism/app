SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

$(SUB_TARGET):$(OBJ)
	$(LD) -r -o $(SUB_TARGET) $(OBJ)

$(OBJ): $(SRC)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(wildcard *.o)

