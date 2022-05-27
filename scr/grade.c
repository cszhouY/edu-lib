#include "edu.h"
#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b){
	return ((unsigned int*)a)[0] < ((unsigned int*)b)[0];
}
void course_rank_update(course_t* course, class_t* class){
	if(course == NULL || class == NULL)
		return;
	unsigned int rankBuf[class->size][2];
	int i, j = 0, num=0;
	for(i=1; i<=class->size; i++){
		while(class->stus[++j].id == 0);
		course_status *cur = class->stus[j].courseList;
		while(cur){
			if(cur->info == course){
				rankBuf[num][0] = cur->score;
				rankBuf[num][1] = class->stus[j].id;
				num++;
				break;
			}
			cur = cur->next;
		}
	}
	/*for(i=0; i<num; i++){
		printf("%u %u\n", rankBuf[i][0], rankBuf[i][1]);
	}*/
	qsort(rankBuf, num, 2*sizeof(unsigned int), cmp);
	for(i=0; i<num; i++){
		printf("%u %u\n", rankBuf[i][0], rankBuf[i][1]);
	}
	int bltmp = 1, rtmp = 0, stmp = -1;
	for(i = 0; i < num; i++){
		if(rankBuf[i][0] == stmp){
			bltmp++;
		}
		else{
			rtmp += bltmp;
			bltmp = 1;
			stmp = rankBuf[i][0];
		}
		course_status *cur = class->stus[rankBuf[i][1]%100].courseList;
		while(cur){
			if(cur->info == course){
				cur->rank = rtmp;
				break;
			}
			cur = cur->next;
		}
	}
	printf("update  succeed!\n");
}
void course_score_analyze(course_t* course, class_t* class, int mod){
	if(course == NULL || class == NULL)
		return;
	unsigned int rankBuf[class->size][2];
	int i, j = 0, num=0;
	score_t sum = 0;
	int scoreSeg[3] = {0};
	for(i=1; i<=class->size; i++){
		while(class->stus[++j].id == 0);
		course_status *cur = class->stus[j].courseList;
		while(cur){
			if(cur->info == course){
				rankBuf[num][0] = cur->score;
				if(rankBuf[num][0] >=85)
					scoreSeg[0]++;
				else if(rankBuf[num][0] <60 )
					scoreSeg[2]++;
				sum += rankBuf[num][0];
				rankBuf[num][1] = class->stus[j].id;
				num++;
				break;
			}
			cur = cur->next;
		}
	}
	scoreSeg[1] = num - scoreSeg[0] - scoreSeg[2];
	qsort(rankBuf, num, 2*sizeof(unsigned int), cmp);
	if(mod & AVE){
		printf("class %u average score: %.2f\n", class->id, sum/(float)num);
	}
	if(mod & PAS){
		printf("pass: %d  ratio: %.2f\n", num-scoreSeg[2], (num-scoreSeg[2])/(float)num);
	}
	if(mod & SEG){
		printf("[85, 100] %d  ", scoreSeg[0]);
		for(i=0; i<scoreSeg[0]; i++)
			printf("#");
		printf("\n");
		printf("[60,  84] %d  ", scoreSeg[1]);
		for(i=0; i<scoreSeg[1]; i++)
			printf("#");
		printf("\n");
		printf("[0 ,  59] %d  ", scoreSeg[2]);
		for(i=0; i<scoreSeg[2]; i++)
			printf("#");
		printf("\n");
	}
	if(mod & LIST){
		printf("id        score\n");
		for(i = 0; i<num; i++){
			printf("%-10u %u\n", rankBuf[i][1], rankBuf[i][0]);
		}
	}
}
void stu_rank_update(class_t* class, int mod){
	if(class == NULL || class->id == 0){
		return;
	}
	if(mod != 0 && (mod & CORE_AVE) != 0 && (mod & WEIGH_AVE) != 0)
		return;
	//printf("ok\n");
	unsigned int rankBuf[class->size+1][2];
	int i, j = 0;
	for(i=1; i<=class->size; i++){
		while(class->stus[++j].id == 0);
		rankBuf[i][1] = class->stus[j].id;
		rankBuf[i][0] = 0;
		course_status *cur = class->stus[j].courseList;
		int courseNum = 0;
		score_t creditSum = 0;
		if(cur == NULL)
			continue;
		while(cur){
			if(!(mod & CORE_AVE && cur->info->type == general)){
				//printf("core\n");
				courseNum++;
				creditSum += cur->info->credit;
				if(mod & WEIGH_AVE)
					rankBuf[i][0] += cur->info->credit*cur->score;
				else
					rankBuf[i][0] += cur->score;
				//printf("%u\n", rankBuf[i][0]);
			}
			cur = cur->next;
		}
		if((mod & WEIGH_AVE) && creditSum){
			//printf("*******************%u\n",creditSum);
			rankBuf[i][0] /= creditSum;
			//printf("*******************%u\n",rankBuf[i][0]);
		}
		else if(courseNum){
			rankBuf[i][0] /= courseNum;
		}
	}
	qsort(rankBuf, class->size+1, 2*sizeof(unsigned int), cmp);
	int bltmp = 1, rtmp = 0, stmp = -1;
	for(i = 1; i < class->size+1; i++){
		if(rankBuf[i][0] == stmp){
			bltmp++;
		}
		else{
			rtmp += bltmp;
			stmp = rankBuf[i][0];
			bltmp = 1;
		}
		class->stus[rankBuf[i][1]%100].score = stmp;
		class->stus[rankBuf[i][1]%100].rank = rtmp;  //i start from 1
	}
	for(i = 1; i<=class->size; i++){
		printf("%u %u\n", rankBuf[i][0], rankBuf[i][1]);
	}
	printf("update  succeed!\n");
}
