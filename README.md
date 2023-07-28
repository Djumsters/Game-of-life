# Game-of-life
Game of Life on C language for terminal Linux
## Libraries
- [`ncurses`](https://en.wikipedia.org/wiki/Ncurses) - for real-time mode 
- [`unistd`](https://en.wikipedia.org/wiki/Unistd.h) - for the delay between cards in microseconds
- [`stdio`](https://www.tutorialspoint.com/c_standard_library/stdio_h.htm) - for other primitive actions (e. g. printf())

## Compilation
Enter in the terminal:
```
$ make
```
Use the following combination to start the game ```./Game_of_Life < (your txt file)```.
As an example, let's take pistol.txt, then in the terminal you need to write:
```
$ ./Game_of_Life < pistol.txt
```
### Control

You can change the speed of the game, use the keys to do this `'w'` - speed up, `'s'` - speed down.
To exit the game, press the `'q'` key.
