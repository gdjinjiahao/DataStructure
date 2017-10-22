#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_VALUE 0x7fffffff

//基数排序用到的链表节点定义
typedef struct RSElem {
	int e;
	struct RSElem *next;
}RSElem, *PRSElem;

void Straight_Isertion_Sort(int l, int r);

void Binary_Insertion_Sort(int l, int r);

void Shell_Sort(int l, int r);

void swap(int& a, int& b);

void Bubble_Sort(int l, int r);

void Quick_Sort(int l, int r);

void Simple_Selection_Sort(int l, int r);

int BuildTree(int rt, int l, int r, int tree[], int pos[]);

int getMin(int l, int r, int tree[], int pos[], int temp[]);

void Tree_Selection_Sort(int l, int r);

void Adjust_Heap(int *heap, int rt, int n);

void Heap_Sort();

void Merging_Sort(int temp[], int l, int r);

void RadixSort(int l, int r);