#include <stdio.h>
#include <termios.h>
#include <unistd.h>

struct termios original;
struct termios raw;

void init_interactive_input(void) { //function
	tcgetattr(STDIN_FILENO, &original);
	raw = original;
	cfmakeraw(&raw);
}

int interactive_input(void) { //function
	char c;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &original);
	return c;
}