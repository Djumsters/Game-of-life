start: *.c
	gcc -o Game_of_Life *.c -lncurses

clean:
	rm -rf Game_of_Life
