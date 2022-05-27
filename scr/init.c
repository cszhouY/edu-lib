#include "edu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void class_init(class_t* class, id_t classID, int num){
	if(class == NULL)
		return;
	memset(class, 0, sizeof(class_t));
	if(classID/1000 == 0 || classID/1000 >=10){
		printf("[error] classID: %u ...should be four digit\n", classID);
		return;
	}
	if(num <=0 || num >50){
		printf("[error] num: %d ...should be in [1, 50]\n", num);
		return;
	}
	class->id = classID;
	class->size = num;
	class->stus = NULL;
}
void course_init(course_t* course, id_t id, char* course_name, score_t credit, type_t type){
	if(course == NULL)
		return;
	memset(course, 0, sizeof(course_t));
	if(id ==0 || id > 100){
		printf("[error] courseID: %u ...should be in [1, 100]\n", id);
		return;
	}
	course->id = id;
	strncpy(course->name, course_name, 14);
	course->name[14] = '\0';
	if(credit ==0 || credit > 5){
		printf("[warning] credit: %u ...should be in [1, 5], default: 1\n", credit);
		credit = 1;
	}
	course->credit = credit;
	course->type = type;
}
