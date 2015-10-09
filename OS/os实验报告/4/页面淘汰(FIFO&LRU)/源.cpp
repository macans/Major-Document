#include <cstdio>
#include <iostream>
#include <time.h>
using namespace std;
#define TOTAL_INSTRUCTION 320
#define TOTAL_VP 32
#define INVALID -1
#define INF 9999999
typedef struct{
	int pn;
	int pfn;
	int counter;
	int time;
} pl_type;
pl_type pl[TOTAL_VP];

struct pfc_struct{
	int pn, pfn;
	struct pfc_struct *next;
};
typedef struct pfc_struct pfc_type;
pfc_type pfc[TOTAL_VP], *freepf_head, *busypf_head, *busypf_tail;
int a[TOTAL_INSTRUCTION], page[TOTAL_INSTRUCTION], offset[TOTAL_INSTRUCTION];
int total_pf;//总页面数
int disaffect;//失效页面数

void init(int total_pf){
	int i;
	disaffect = 0;
	for (i = 0; i < TOTAL_VP; i++)
	{
		pl[i].pn = i;
		pl[i].pfn = INVALID;
		pl[i].counter = 0;
		pl[i].time = -1;
	}
	for (i = 0; i < total_pf - 1; i++)
	{
		pfc[i].next = &pfc[i + 1];
		pfc[i].pfn = i;
	}
	pfc[total_pf - 1].next = NULL;
	pfc[total_pf - 1].pfn = total_pf - 1;
	freepf_head = &pfc[0];
}

void FIFO(int total_pf){
	int i;
	pfc_type *p;
	init(total_pf);
	//disaffect表示缺页数目
	disaffect = 0;
	//head、tail分别表示队首和队尾
	busypf_head = busypf_tail = NULL;
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		if (pl[page[i]].pfn == INVALID)
		{
			//页面失效时，缺页数+1
			disaffect += 1;
			if (freepf_head == NULL)
			{	//当前没有空闲页面，则将队首淘汰
				p = busypf_head->next;
				pl[busypf_head->pn].pfn = INVALID;
				freepf_head = busypf_head;
				freepf_head->next = NULL;
				busypf_head = p;
			}
			//更改页面状态
			p = freepf_head->next;
			freepf_head->next = NULL;
			freepf_head->pn = page[i];
			pl[page[i]].pfn = freepf_head->pfn;

			if (busypf_tail == NULL)
				//当前没有忙页面则重置指针
				busypf_head = busypf_tail = freepf_head;
			else
			{	//将当前空页面加入队列
				busypf_tail->next = freepf_head;  		
				busypf_tail = freepf_head;
			}
			freepf_head = p;
		}
	}
	printf("FIFO缺页率: %.2f\n", (float)disaffect / TOTAL_INSTRUCTION);
}

void LRU(int total_pf)
{
	int min, minj, i, j, present_time;
	init(total_pf); 
	present_time = 0;
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		if (pl[page[i]].pfn == INVALID)     
		{
			//页面失效时，缺页数+1
			disaffect++;
			if (freepf_head == NULL) 
			{
				//当前没有空闲页面
				min = INF;
				//寻找最少使用次数的页面
				for (j = 0; j < TOTAL_VP; j++)
				if (min>pl[j].time&&pl[j].pfn != INVALID)
				{
					min = pl[j].time;
					minj = j;
				}
				//淘汰该页面
				freepf_head = &pfc[pl[minj].pfn];
				pl[minj].pfn = INVALID;
				pl[minj].time = -1;
				freepf_head->next = NULL;
			}
			pl[page[i]].pfn = freepf_head->pfn;
			pl[page[i]].time = present_time;
			freepf_head = freepf_head->next;
		}
		else
			//更新使用次数
			pl[page[i]].time = present_time;
		present_time++;
	}
	printf("LRU缺页率: %.2f\n", (float)disaffect / TOTAL_INSTRUCTION);
}


int main(){
	int i, o, temp;
	srand((unsigned)time(NULL));
	o = rand() % 320 + 1;
	for (i = 0; i < TOTAL_INSTRUCTION; i++){
		a[i] = i;
	}

	for (i = 0; i < TOTAL_INSTRUCTION; i++){
		o = rand() % TOTAL_INSTRUCTION;
		swap(a[i], a[o]);
	}
	for (i = 0; i < TOTAL_INSTRUCTION; i++){
		page[i] = a[i] / 10;
		offset[i] = a[i] / 10;
	}
	for (i = 4; i <= 32; i++){
		printf("%d page frames\n", i);
		FIFO(i);
		LRU(i);
	}
}