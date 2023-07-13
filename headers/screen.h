#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 50

struct model_pixel {
	int height;
	int width;
	char character;
};

typedef struct model_pixel pixel;

struct struct_model {
	pixel* pixel_array;
	int size;
};

typedef struct struct_model model;

void screen_init(void); //function
int screen_change(char c, int height, int width); //function
void screen_update(); //function
void screen_change_model(model *m, int height, int width); //function
int screen_at_pixel(int height, int width); //function
