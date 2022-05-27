#ifndef _EDU_H_
#define _EDU_H_

#define AVE 0x1
#define PAS 0x2
#define SEG 0x4
#define LIST 0x8
#define BUFLEN 50
#define CORE_AVE 0x1
#define WEIGH_AVE 0x4

typedef unsigned int score_t;
typedef unsigned int id_t;
typedef enum{ general = 1, core} type_t;
typedef struct course_t{
	id_t id;
	char name[15];
	score_t credit;
	type_t type;
	//struct course_t* next;
}course_t;

typedef struct course_status{
	course_t* info;
	score_t score;
	score_t rank;
	struct course_status* next;
}course_status;

typedef struct stu_t{
	id_t id;
	char name[10];
	course_status* courseList;
	score_t score;
	score_t rank;
}stu_t;

typedef struct class_t{
	stu_t* stus;
	id_t id;
	int size;
}class_t;
void class_init(class_t* class, id_t classID, int num);
int class_import(class_t* class, char* file);
void class_info(class_t* class);
void course_init(course_t* course, id_t id, char* course_name, score_t credit, type_t type);
int course_import(course_t* course, class_t* class);
void stu_info(class_t *class, id_t id);
int grade_import(course_t* course, class_t* class, char* file);
void course_rank_update(course_t* course, class_t* class);
void stu_rank_update(class_t* class, int mod);
void course_score_analyze(course_t* course, class_t* class, int mod);
void class_delete(class_t* class);

#endif
