#include <stdio.h>
#include <unistd.h>
#include "screen.h"

static char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

void screen_init(void) { //function
	for(int i = 0; i < SCREEN_HEIGHT; i++)
		for(int j = 0; j < SCREEN_WIDTH; j++)
			screen[i][j] = ' ';
}

int screen_change(char c, int height, int width) { //function
	if (height < 0 || height >= SCREEN_HEIGHT){
		return -1;
	}

	if (width < 0 || width >= SCREEN_WIDTH) {
		return -1;
	}
	screen[height][width] = c;
	return 0;
}

void screen_update() { //function
	system("clear");
	for(int i = 0; i < SCREEN_HEIGHT; i++) {
		for(int j = 0; j < SCREEN_WIDTH; j++) {
			printf("%c", screen[i][j]);
		}
		printf("\n");
	}
}

void screen_change_model(model *m, int height, int width) { //function
	for(int i = 0; i < m->size; i++) {
		screen_change(m->pixel_array[i].character, m->pixel_array[i].height + height, m->pixel_array[i].width + width);
	}
}

int screen_at_pixel(int height, int width) { //function
	if (height < 0 || height >= SCREEN_HEIGHT){
		printf("screen at pixel error.\n");
		return -1;
	}

	if (width < 0 || width >= SCREEN_WIDTH) {
		printf("screen at pixel error.\n");
		return -1;

	}

	return screen[height][width];
}