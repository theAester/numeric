NAME = calc

all: lib/numeric.so
	gcc -g $(NAME).c lib/numeric.so -Iinclude/ -o build/$(NAME) 

lib/numeric.so:
	gcc -g --shared src/*.c -Iinclude/ -o lib/numeric.so -lm

lib: lib/numeric.so
