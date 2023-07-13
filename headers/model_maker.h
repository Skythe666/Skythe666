typedef struct struct_model model;

model* make_model(); //function
void save_model(model* m,const char* name); //function
model* load_model(const char* name); //function
