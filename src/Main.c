#include <stdio.h>
#include "screen.h"
#include "model_maker.h"
#include "interactive_input.h"

int main() {
	int choice;
	int loop = 1;
	char name[64];
	model* m;
	screen_init();
	init_interactive_input();

	printf("A rudimentary text painter: \n");

	while(loop) {
		printf("Choose your option: \n");
		printf("1. Make (or clear) a model.\n");
		printf("2. Edit	 a model. \n");
		printf("3. Exit.\n");
		scanf("%d", &choice);
		switch(choice) {
		case 1:
			printf("Type in the name of the model: ");
			scanf("%s", name);
			screen_init();
			m = make_model();
			save_model(m, name);
			break;
		case 2:
			printf("Type in the name of the model: ");
			scanf("%s", name);
			m = load_model(name);
			screen_change_model(m, 0, 0);
			screen_update();
			m = make_model();
			save_model(m, name);
			break;
		case 3:
			loop = 0;
			break;
		default: 
			printf("No option like that.\n");
			break;
		}
	}

	return 0;

}