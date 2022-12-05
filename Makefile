NAME = calc.c

all: lib/numeric.so
	gcc $(NAME).c lib/numeric.so -Iinclude/ -o build/$(NAME) 

lib/numeric.so:
	gcc --shared src/*.c -Iinclude/ -o lib/numeric.so

lib: lib/numeric.so
