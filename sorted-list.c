/*
 * sorted-list.c
 */
 

 #include "sorted-list.h"
 #include <stdio.h>
 #include <stdlib.h>
 
SortedListPtr SLCreate(CompareFuncT cf){
	
	SortedListPtr list = (SortedListPtr)malloc(sizeof(struct SortedList));
	
	if(list != NULL){		/*------------------ Check malloc success */
		list->head = NULL;	/*------------------ initiate empty list and return */
		list->compFn=cf;
		return list;
	}else{
		return NULL;		/*-------------------Return NULL if malloc fails */
	}
	
};
	

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){

	SortedListIteratorPtr iterPtr = (SortedListIteratorPtr)malloc(sizeof(struct SortedListIterator));		
	
	if (iterPtr != NULL){						/*----- Check mallocc success */
		iterPtr->curr = list->head;				/*----- Set curr node to head of list and return */
		if (iterPtr->curr!=NULL){
			list->head->refCnt++;
		}
		return iterPtr;							
	}else{
		return NULL;							/*----- Return NULL if fail */
	}

}

 
void *SLNextItem(SortedListIteratorPtr iter){
	
	node* temp = iter->curr->next;		/*---- set a temp pointer to next node */
	
	if(iter->curr->refCnt ==1){			/*---- check if current node has been removed from list but not destroyed */
		NodeDestroy(iter->curr);
	}else{
		iter->curr->refCnt--;
	}
	
	iter->curr = temp;				/*---- Set current node to next node */
	
	if(iter->curr!=NULL){					/*---- If temp == NULL you are at the end of the list and return NULL */
		iter->curr->refCnt++;
		return iter->curr->obj;			/*---- Else you return the void* object */	
	}else{
		return NULL;
	}

}

int SLInsert(SortedListPtr list, void *newObj){
	int i;
	void* currObj;
	
	SortedListIteratorPtr iterPtr = SLCreateIterator(list);
	if (iterPtr == NULL){
		return 0;
	}
	node* prev = iterPtr->curr;
	
	if (iterPtr->curr == NULL || (*list->compFn)(newObj, iterPtr->curr->obj) == 1){		/*--- Empty list OR first object smaller */
		list->head = NodeCreate(newObj,iterPtr->curr);		/*--- Insert at head */
		SLDestroyIterator(iterPtr);
		return 1;
	}
	currObj=SLNextItem(iterPtr);
	
	while(iterPtr->curr != NULL){
	
		i = (*list->compFn)(newObj, currObj); /*--- Compare current and new objects */
		
		if(i >= 1){									/*--- Found spot to add! */
			break;
		}else if(i == 0){							/*--- Duplicate Object, Return without adding */
			SLDestroyIterator(iterPtr);
			return 1;
		}else{										/*--- Increment pointers and loop */
			prev = iterPtr->curr;
			currObj=SLNextItem(iterPtr);					
		}
	}
	prev->next = NodeCreate(newObj,iterPtr->curr);		/*---- Insert new node! */
    if (prev->next==NULL) {
        printf("Malloc fail!\n");
        return 0;
    }
	SLDestroyIterator(iterPtr);
	return 1;
}


node* NodeCreate(void* obj, node* next){
	node* newNode = (node*)malloc(sizeof(node));	/*-- Malloc space for new node and check for fail*/
	if(newNode == NULL){
		return NULL;
	}
	newNode->refCnt = 1;							/*-- Initiate values and return new node*/
	newNode->obj = obj;
	newNode->next = next;
	return newNode;

}

void NodeDestroy(node* n){		/*---- Destroy node, obj must be free'd from main */
	free(n);
}

int SLRemove(SortedListPtr list, void *newObj)
{
	int j;
	void* currObj;
	SortedListIteratorPtr remPtr = SLCreateIterator(list); /*---- Create iterator and check for success */
	if (remPtr == NULL){
        printf("Failed to create iterator!\n");
		return 0;
	}
    
	node *prev = remPtr->curr;
	j=(*list->compFn)(newObj, list->head->obj);
	if(j == 0){                                     /*--- Obj at head */
		list->head = list->head->next;
		if (remPtr->curr->refCnt==2){				/*--- Only head and remPtr pointing to node, so Destroy Node */
			NodeDestroy(remPtr->curr);	
		}
		SLDestroyIterator(remPtr);
		return 1;
	}
	currObj=SLNextItem(remPtr);
	while(remPtr->curr != NULL){                    /*---- Iterate through list until object found or End of List */
		
		j = (*list->compFn)(newObj, currObj);
		
		if(j==0){                                   /*---- Found match! Remove! */
			prev->next = remPtr->curr->next;
			if(remPtr->curr->refCnt == 2){
				NodeDestroy(remPtr->curr);          /*---- Destroy node If no other iterators pointing to it */
			}
			SLDestroyIterator(remPtr);
			return 1;
		}else{
			prev = remPtr->curr;
			currObj=SLNextItem(remPtr);
		}
	}
	SLDestroyIterator(remPtr);
    printf("Object not in list!\n");                /*----- End of list reached and obj not matched, Not in list! */
	return 0;
}

void SLDestroy(SortedListPtr list)                  /*---- Free list struct, All nodes must be removed first from main! */
{	
	free(list);
}

void SLDestroyIterator(SortedListIteratorPtr iter)
	if (iter->curr!=NULL){                                 /*---- Checks if current node has been removed from list and should be destroyed */
        if(iter->curr->refCnt <= 1){
            NodeDestroy(iter->curr);                       /*---- Else decrememnts refCnt if pointing to a node */
        }else {
            iter->curr->refCnt--;
        }
	}
	free(iter);                                            /*---- Free iterator struct */
}



 
