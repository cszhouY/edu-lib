#include "edu.h"
#include <stdio.h>
int main()
{
	//初始化班级jk2002
	class_t jk2002;
	class_init(&jk2002, 2002, 5);
	class_import(&jk2002, "jk2002.txt");
	class_info(&jk2002);
	
	//初始化课程os
	course_t os;
	course_init(&os, 1, "os", 4, core);
	course_import(&os, &jk2002);
	//查看学生信息
	stu_info(&jk2002, 202);  //no stu
	//导入成绩并更新os课程排名
	grade_import(&os, &jk2002, "os02.txt");
	course_rank_update(&os, &jk2002);
	//查看学生信息
	stu_info(&jk2002, 200202);
	stu_info(&jk2002, 200201);
	stu_info(&jk2002, 200205);
	//分析jk2002班的os课成绩
	course_score_analyze(&os, &jk2002, AVE|PAS|SEG|LIST);
	printf("--------ok------------------\n");
	//初始化课程csapp
	course_t csapp;
	course_init(&csapp, 2, "csapp", 5, core);
	course_import(&csapp, &jk2002);
	//初始化课程english
	course_t english;
	course_init(&english, 3, "english", 2, general);
	course_import(&english, &jk2002);
	//导入两门课成绩
	grade_import(&csapp, &jk2002, "csapp02.txt");
	grade_import(&english, &jk2002, "english02.txt");
	stu_info(&jk2002, 200202);
	stu_info(&jk2002, 200201);
	stu_info(&jk2002, 200205);
	//csapp排名
	course_rank_update(&csapp, &jk2002);
	stu_info(&jk2002, 200202);
	stu_info(&jk2002, 200201);
	stu_info(&jk2002, 200205);
	//english排名
	course_rank_update(&english, &jk2002);
	stu_info(&jk2002, 200202);
	stu_info(&jk2002, 200201);
	stu_info(&jk2002, 200205);
	//分析csapp成绩
	course_score_analyze(&csapp, &jk2002, AVE|PAS|SEG|LIST);
	printf("--------ok------------------\n");
	//更新学生总成绩核心排名
	stu_rank_update(&jk2002, CORE_AVE);
	stu_info(&jk2002, 200203);
	stu_info(&jk2002, 200201);
	stu_info(&jk2002, 200205);
	//更新学生总成绩加权排名
	stu_rank_update(&jk2002, WEIGH_AVE);
	stu_info(&jk2002, 200203);
	stu_info(&jk2002, 200201);
	stu_info(&jk2002, 200205);
	
	//析构
	class_delete(&jk2002);
	return 0;
}
