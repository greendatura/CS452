
#include <kernel.h>

#include <common/utils.h>


/*
 * Task Related Functions
 * 
 * priority(1 to 16, inclusive)
 */ 

int Task_Create(int priority, void (*code)()){
	return 0;
	
}



/*
 * Scheduler Related Functions
 */ 


static int Scheduler_isQueueEmpty(kernGlobal* kernelData, int qIdx){
	priorityQueue* qItem = &((kernelData->priorityQueues)[qIdx]);
	
	return (qItem->head == NULL && qItem->tail == NULL) ? 1 : 0;
}

static int Scheduler_findNextPriorityQueue(kernGlobal* kernelData){
	int i;
	
	for (i = 0; i < MAX_PRIORITY; i++)
	{
		if (isQueueEmpty(kernelData, i))
			continue;
		return i;
	}
	return -1;
}

static task* Scheduler_popQueue(kernGlobal* kernelData, int qIdx){
	priorityQueue* qItem = &((kernelData->priorityQueues)[qIdx]);
	
	task* retval = qItem->head;
	
	qItem->head = (retval)->nextTask;
	
	(retval)->nextTask = NULL;
	/*
	 * EQC(Empty Queue Check)
	 */ 
	if(qItem->head == NULL && qItem->tail == retval){	
		qItem->tail = NULL;
	}
			
	return retval;
}

task* Scheduler_getNextTask(kernGlobal* kernelData){	
	int i = findNextPriorityQueue(kernelData);
	
	if (i >= 0)
		return popQueue(kernelData, i);
			
	return NULL;
}


void Scheduler_pushQueue(kernGlobal* kernelData, int qIdx, task* tsk){
	priorityQueue* qItem = &((kernelData->priorityQueues)[qIdx]);

	if (isQueueEmpty(kernelData, qIdx)){
			qItem->head=tsk;
			qItem->tail=tsk;
	}
	else{
			(qItem->tail)->nextTask = tsk;
			qItem->tail = (qItem->tail)->nextTask;
	}
}

