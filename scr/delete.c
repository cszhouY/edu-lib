#include "edu.h"
#include <stdio.h>
#include <stdlib.h>

void class_delete(class_t* class){
	if(class == NULL)
		return;
	if(class->stus)
		free(class->stus);
	class->stus = NULL;
	class->size = 0;
	class->id = 0;
	return;
}
