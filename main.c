/*
 * sorted-list.c
 */

#include	<string.h>
#include	<stdio.h>
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int main(int argc, char *argv[])
{
	
	SortedListPtr list = SLCreate(compareDoubles);
	SortedListIteratorPtr itrPtr1;
	
	double* d1 = (double*)malloc(sizeof(double));		/* Insert into list */
	*d1 = 53;
	SLInsert(list,(void*)d1);
	double* d2 = (double*)malloc(sizeof(double));
	*d2 = 42;
	SLInsert(list,(void*)d2);
	double* d3 = (double*)malloc(sizeof(double));
	*d3 = 12;
	SLInsert(list,(void*)d3);
	double* d4 = (double*)malloc(sizeof(double));
	*d4 = 43;
	SLInsert(list,(void*)d4);
	double* d5 = (double*)malloc(sizeof(double));
	*d5 = 32;
	SLInsert(list,(void*)d5);
	
	itrPtr1 = SLCreateIterator(list);				/*--- Print current list */
	while(itrPtr1->curr!=NULL){
		printf("%.0f\n",*(double*)itrPtr1->curr->obj);
		SLNextItem(itrPtr1);
	}
    
    SLDestroyIterator(itrPtr1);
	
	printf("\nRemove 53\n");							/*--- Remove items from list */
	SLRemove(list,(void*)d1);
	printf("Remove 42\n");
	SLRemove(list,(void*)d2);
	printf("Remove 12\n\n");
	SLRemove(list,(void*)d3);
	
	itrPtr1 = SLCreateIterator(list);				/*---- Print current list */
	if (itrPtr1->curr!=NULL) {
		while(itrPtr1->curr!=NULL){
			printf("%.0f\n",*(double*)itrPtr1->curr->obj);
			SLNextItem(itrPtr1);
		}
	}else{
		printf("\nThe list is Empty!!\n");
		
	}
    SLDestroyIterator(itrPtr1);
	
	printf("Remove 43\n");									/*--- Remove all items from list */
	SLRemove(list,(void*)d4);
	printf("Remove 32\n\n");
	SLRemove(list,(void*)d5);
	
	itrPtr1 = SLCreateIterator(list);
	if (itrPtr1->curr!=NULL) {
		while(itrPtr1->curr!=NULL){
			printf("%.0f\n",*(double*)itrPtr1->curr->obj);
			SLNextItem(itrPtr1);
		}
	}else{
		printf("\nThe list is Empty!!\n");
	
	}
	
	free(d1);
	free(d2);
	free(d3);
	free(d4);
	free(d5);
	
	SLDestroyIterator(itrPtr1);
	SLDestroy(list);
		  
	return 0;
		
	
}
