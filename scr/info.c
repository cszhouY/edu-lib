#include "edu.h"
#include <stdio.h>
#include <stdlib.h>

void class_info(class_t* class){
	if(class){
		printf("class: %u\n", class->id);
		int i;
		for(i = 1; i<=class->size; i++){
			if(class->stus[i].id)
				printf("%u %s\n", class->stus[i].id, class->stus[i].name);
		}
	}
}
void stu_info(class_t *class, id_t id){
	if(class == NULL)
		return;
	int i;
	for(i = 1; i <= class->size; i++){
		if(class->stus[i].id == id)
			break;
	}
	if(i > class->size || class->stus[i].id == 0){
		printf("no stu\n");
		return;
	}
	printf("id: %u name: %s score: %u rank: %u\n", 
			class->stus[i].id, 
			class->stus[i].name,
			class->stus[i].score,
			class->stus[i].rank
		);
	course_status *cur = class->stus[i].courseList;
	printf("classid  name   score rk\n");
	while(cur){
		//printf("%p\n", cur);
		printf("%-8u %-8s %-3u %-3u\n", cur->info->id, cur->info->name, cur->score, cur->rank);
		cur = cur->next;
	}
}
