#include "edu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int class_import(class_t* class, char* file){
	if(class == NULL || class->id == 0){
		return 1;
	}
	FILE* fp;
	if(file != NULL){
		fp = fopen(file, "r");
		if(fp == NULL){
			printf("[error] %s ....file opening error\n", file);
			return 1;
		}
	}
	else
		fp = stdin;
	class->stus = (stu_t*)calloc(class->size+1, sizeof(stu_t));
	if(class->stus == NULL){
		printf("[error] .....malloc error\n");
		fclose(fp);
		return 1;
	}
	char buf[BUFLEN], name[BUFLEN];
	id_t id = 0;
	int n = 0;
	while(fgets(buf, BUFLEN, fp) != NULL && n < class->size){
		if(sscanf(buf, "%u %s", &id, name) != 2){
			printf("[error] %s....format error\n", buf);
			free(class->stus);
			class->stus = NULL;
			fclose(fp);
			return 1;
		}
		if((id / 100) != class->id){
			printf("[error] %s....class id wrong\n", buf);
			free(class->stus);
			class->stus = NULL;
			printf("%u\n", class->size);
			fclose(fp);
			return 1;
		}
		if(class->stus[id%100].id){
			printf("[warning] %s....already exist\n", buf);
			continue;
		}
		class->stus[id%100].id = id;
		strncpy(class->stus[id%100].name, name, 9);
		class->stus[id%100].name[9] = '\0';
		n++;
	}
	if(n < class->size)
		class->size = n;
	fclose(fp);
	return 0;
}
int course_import(course_t* course, class_t* class ){
	if(course == NULL || class == NULL)
		return 1;
	if(course->id == 0)
		return 1;
	int i;
	for(i = 1; i <= class->size; i++){
		course_status *cur = class->stus[i].courseList;
		course_status *pre = cur;
		while(cur != NULL && cur->info != course){
			pre = cur;
			cur = cur->next;
		}
		if(cur != NULL)
			continue;
		cur = (course_status*)calloc(1, sizeof(course_status));
		cur->info = course;
		if(pre)
			pre->next = cur;
		else
			class->stus[i].courseList = cur;
		//printf("%p %p\n", pre, cur);
	}
	return 0;
}
int grade_import(course_t* course, class_t* class, char* file){
	if(course == NULL || class == NULL || course->id == 0 || class->id == 0)
		return 0;
	FILE* fp = fopen(file, "r");
	if(fp == NULL){
		printf("[error] %s ....file opening error\n", file);
		return 1;
	}
	char buf[BUFLEN];
	id_t id = 0;
	score_t score;
	while(fgets(buf, BUFLEN, fp) != NULL){
		if(sscanf(buf, "%u %u", &id, &score) != 2){
			printf("[error] %s....format error\n", buf);
			fclose(fp);
			return 1;
		}
	}
	rewind(fp);
	while(fgets(buf, BUFLEN, fp) != NULL){
		sscanf(buf, "%u %u", &id, &score);
		if(id%100 > class->size){
			printf("[warning] %s ....doesn't exsit\n", buf);
			continue;
		}
		course_status *cur = class->stus[id%100].courseList;
		while(cur){
			if(cur->info == course){
				cur->score = score % 101;
				break;
			}
			cur = cur->next;
		}
		if(cur == NULL){
			printf("[warning] %u %s ....doesn't exsit\n", course->id, course->name);
			continue;
		}
	}
	fclose(fp);
	return 0;
}
