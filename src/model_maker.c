#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "interactive_input.h"
#include "screen.h"

#define LOOP 01
#define CHANGING 02
#define REMOVING 04
#define COMMAND_INPUT 'u'
#define CHANGE_INPUT 'i'
#define REMOVE_INPUT 'o'
#define EXIT_INPUT 'e'

model* make_model() { //function
	int cursor_x = 0;
	int cursor_y = 0;
	int flags = LOOP;
	int size = 0;
	int model_array_index = 0;
	char input;
	char last_character = ' ';
	char cursor_character = 'c';


	screen_change(cursor_character, cursor_y, cursor_x);
	screen_update();

	while(flags & LOOP) {
		input = interactive_input();

		screen_change(last_character, cursor_y, cursor_x);
		screen_update();

		switch(input) {
		case 'w':
			cursor_y -= 1;
			break;
		case 's':
			cursor_y += 1;
			break;
		case 'a':
			cursor_x -= 1;
			break;
		case 'd':
			cursor_x += 1;
			break;
		case COMMAND_INPUT:
			if ((input = interactive_input()) == CHANGE_INPUT) {
				cursor_character = interactive_input();
				flags |= CHANGING;
				flags &= ~REMOVING;
			}
			else if (input == REMOVE_INPUT) {
				cursor_character = 'r';
				flags |= REMOVING;
				flags &= ~CHANGING;
			}
			else{
				cursor_character = 'c';
				flags &= ~(CHANGING | REMOVING);
			}
			break;
		case EXIT_INPUT:
			flags &= ~(LOOP);
			break;
		}
		last_character = screen_at_pixel(cursor_y, cursor_x);
		screen_change(cursor_character, cursor_y, cursor_x);
		screen_update();

		if ((flags & CHANGING)) {
			last_character = cursor_character;
		}
		else if ((flags & REMOVING)) {
			last_character = ' ';
		}

	}

	screen_change(' ', cursor_y, cursor_x);

	for(cursor_y = 0; cursor_y < SCREEN_HEIGHT; cursor_y++) {
		for(cursor_x = 0; cursor_x < SCREEN_WIDTH; cursor_x++) {
			if (screen_at_pixel(cursor_y, cursor_x) != ' ')
				size++;
		}
	}
	model* m = (model *) malloc(sizeof(model));
	pixel* model_array = (pixel *) malloc(sizeof(pixel) * size);
	m->size = size;
	m->pixel_array = model_array;

	for(cursor_y = 0; (cursor_y < SCREEN_HEIGHT) && (model_array_index < size); cursor_y++) {
		for(cursor_x = 0; (cursor_x < SCREEN_WIDTH) && (model_array_index < size); cursor_x++) {
			if ((input = screen_at_pixel(cursor_y, cursor_x)) != ' ') {
				model_array[model_array_index].height = cursor_y;
				model_array[model_array_index].width = cursor_x;
				model_array[model_array_index].character = input;
				model_array_index++;
			}
		}
	}
	screen_init();
	return m;
}


void save_model(model* m,const char* name) { //function
	char pathname[64];
	int size = m->size;
	int pixel_height;
	int pixel_width;
	char character;

	pathname[0] = '\0';
	strcat(pathname, "models/");
	strcat(pathname, name);

	FILE* fp = fopen(pathname, "w");
	fprintf(fp, "%d\n", size);
	for(int i = 0; i < m->size; i++) {
		pixel_height = m->pixel_array[i].height;
		pixel_width = m->pixel_array[i].width;
		character = m->pixel_array[i].character;
		fprintf(fp, "%d %d %c\n", pixel_height, pixel_width, character);
	}

	fclose(fp);
}

model* load_model(const char* name) { //function
	char pathname[64];
	char input[32];
	int size;
	int pixel_height;
	int pixel_width;
	char character;
	model* m = (model *) malloc(sizeof(model));

	pathname[0] = '\0';
	strcat(pathname, "models/");
	strcat(pathname, name);
	FILE* fp = fopen(pathname, "r");

	fscanf(fp, "%d", &size);
	pixel* model_array = (pixel *) malloc(sizeof(pixel) * size);

	m->size = size;
	m->pixel_array = model_array;

	for(int i = 0; i < size; i++) {
		fscanf(fp, "%d %d %c", &pixel_height, &pixel_width, &character);
		model_array[i].height = pixel_height;
		model_array[i].width = pixel_width;
		model_array[i].character = character;
	}

	fclose(fp);
	return m;
}