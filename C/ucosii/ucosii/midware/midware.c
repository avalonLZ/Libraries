#include "includes.h"

static TaskEvent_t TaskEvent;

/******************************************************************************
 * TaskEventGetFlag - �����¼���־��ָ��
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void *TaskEventGetFlag(char *name)
{
	unsigned int i = 0;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].taskname == NULL)
			return NULL;
		if (TaskEvent.TaskEventNode[i].type == Flag
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			return TaskEvent.TaskEventNode[i].taskeve;
		}
	}
	return NULL;
}

/******************************************************************************
 * TaskEventRegFlag - ע���¼���־���¼�
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void TaskEventRegFlag(char *name, OS_FLAGS fflag, unsigned char *ferror)
{
	unsigned char namesize = 0;
	unsigned int i = 0;
	OS_CPU_SR cpu_sr = 0;

	namesize = strlen(name) + 1;

	for(i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].type == Flag
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			printf("Rename Error,TaskEventRegFlag\r\n");
			return;
		}
	}

	OS_ENTER_CRITICAL();

	if (TaskEvent.index < TASKEVENT_MAXSIZE)
	{
		TaskEvent.TaskEventNode[TaskEvent.index].taskname = malloc(namesize);

		if (TaskEvent.TaskEventNode[TaskEvent.index].taskname != NULL)
		{
			memcpy(TaskEvent.TaskEventNode[TaskEvent.index].taskname, name, namesize);
			TaskEvent.TaskEventNode[TaskEvent.index].taskeve = (void *)OSFlagCreate(fflag, ferror);
			TaskEvent.TaskEventNode[TaskEvent.index].type = Flag;
			TaskEvent.index++;
		}
		else
		{
			printf("Name Malloc Error,TaskEventRegFlag\r\n");
		}

	}
	else
	{
		printf("Full Error,TaskEventRegFlag!\r\n");
	}
	OS_EXIT_CRITICAL();
}

/******************************************************************************
 * TaskEventGetMutex - ���ػ����ź���ָ��
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void *TaskEventGetMutex(char *name)
{
	unsigned int i = 0;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].taskname == NULL)
			return NULL;
		if (TaskEvent.TaskEventNode[i].type == Mutex
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			return TaskEvent.TaskEventNode[i].taskeve;
		}
	}
	return NULL;
}

/******************************************************************************
 * TaskEventRegMutex - ע�ụ���ź����¼�
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void TaskEventRegMutex(char *name, unsigned char mmprio, unsigned char *mmerror)
{
	unsigned char namesize = 0;
	OS_CPU_SR cpu_sr = 0;
	unsigned int i = 0;
	
	namesize = strlen(name) + 1;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].type == Mutex
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			printf("Rename Error,TaskEventRegMutex\r\n");
			return;
		}
	}

	OS_ENTER_CRITICAL();

	if (TaskEvent.index < TASKEVENT_MAXSIZE)
	{
		TaskEvent.TaskEventNode[TaskEvent.index].taskname = malloc(namesize);

		if (TaskEvent.TaskEventNode[TaskEvent.index].taskname != NULL)
		{
			memcpy(TaskEvent.TaskEventNode[TaskEvent.index].taskname, name, namesize);
			TaskEvent.TaskEventNode[TaskEvent.index].taskeve = (void *)OSMutexCreate(mmprio, mmerror);
			TaskEvent.TaskEventNode[TaskEvent.index].type = Mutex;
			TaskEvent.index++;
		}
		else
		{
			printf("Name Malloc Error,TaskEventRegMutex\r\n");
		}

	}
	else
	{
		printf("Full Error,TaskEventRegMutex!\r\n");
	}
	OS_EXIT_CRITICAL();
}

/******************************************************************************
 * TaskEventGetSem - �����ź���ָ��
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void *TaskEventGetSem(char *name)
{
	unsigned int i = 0;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].taskname == NULL)
			return NULL;
		if (TaskEvent.TaskEventNode[i].type == Sem
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			return TaskEvent.TaskEventNode[i].taskeve;
		}
	}
	return NULL;
}

/******************************************************************************
 * TaskEventRegSem - ע���ź����¼�
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void TaskEventRegSem(char *name, unsigned short int sscnt)
{
	unsigned char namesize = 0;
	OS_CPU_SR cpu_sr = 0;
	unsigned int i = 0;
	
	namesize = strlen(name) + 1;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].type == Sem
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			printf("Rename Error,TaskEventRegSem\r\n");
			return;
		}
	}

	OS_ENTER_CRITICAL();

	if (TaskEvent.index < TASKEVENT_MAXSIZE)
	{
		TaskEvent.TaskEventNode[TaskEvent.index].taskname = malloc(namesize);

		if (TaskEvent.TaskEventNode[TaskEvent.index].taskname != NULL)
		{
			memcpy(TaskEvent.TaskEventNode[TaskEvent.index].taskname, name, namesize);
			TaskEvent.TaskEventNode[TaskEvent.index].taskeve = (void *)OSSemCreate(sscnt);
			TaskEvent.TaskEventNode[TaskEvent.index].type = Sem;
			TaskEvent.index++;
		}
		else
		{
			printf("Name Malloc Error,TaskEventRegSem\r\n");
		}

	}
	else
	{
		printf("Full Error,TaskEventRegSem!\r\n");
	}
	OS_EXIT_CRITICAL();
}

/******************************************************************************
 * TaskEventGetMBox - ��ȡ�����¼�ָ��
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void *TaskEventGetMBox(char *name)
{
	unsigned int i = 0;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].taskname == NULL)
			return NULL;
		if (TaskEvent.TaskEventNode[i].type == Mbox
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			return TaskEvent.TaskEventNode[i].taskeve;
		}
	}
	return NULL;
}

/******************************************************************************
 * TaskEventRegMbox - ע�������¼�
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void TaskEventRegMbox(char *name)
{
	unsigned char namesize = 0;
	OS_CPU_SR cpu_sr = 0;
	unsigned int i = 0;
	
	namesize = strlen(name) + 1;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].type == Mbox
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			printf("Rename Error,TaskEventRegMbox\r\n");
			return;
		}
	}

	OS_ENTER_CRITICAL();

	if (TaskEvent.index < TASKEVENT_MAXSIZE)
	{
		TaskEvent.TaskEventNode[TaskEvent.index].taskname = malloc(namesize);

		if (TaskEvent.TaskEventNode[TaskEvent.index].taskname != NULL)
		{
			memcpy(TaskEvent.TaskEventNode[TaskEvent.index].taskname, name, namesize);
			TaskEvent.TaskEventNode[TaskEvent.index].taskeve = (void *)OSMboxCreate(NULL);
			TaskEvent.TaskEventNode[TaskEvent.index].type = Mbox;
			TaskEvent.index++;
		}
		else
		{
			printf("Name Malloc Error,TaskEventRegMbox\r\n");
		}

	}
	else
	{
		printf("Full Error,TaskEventRegMbox!\r\n");
	}
	OS_EXIT_CRITICAL();
}

/******************************************************************************
 * TaskEventGetQueue - ��ȡ��Ϣ�����¼�ָ��
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void *TaskEventGetQueue(char *name)
{
	unsigned int i = 0;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].taskname == NULL)
			return NULL;
		if (TaskEvent.TaskEventNode[i].type == Queue
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			return TaskEvent.TaskEventNode[i].taskeve;
		}
	}
	return NULL;
}

/******************************************************************************
 * TaskEventRegQueue - ע����Ϣ�����¼�
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
static void TaskEventRegQueue(char *name, void **qstart, unsigned short int size)
{
	unsigned char namesize = 0;
	OS_CPU_SR cpu_sr = 0;//���ٽ��ʱ���붨��ˣ����ڴ��浱ǰCPU״̬
	unsigned int i = 0;
	
	namesize = strlen(name) + 1;

	for (i = 0; i < TaskEvent.index; ++i)
	{
		if (TaskEvent.TaskEventNode[i].type == Mbox
			&& strcmp(name, TaskEvent.TaskEventNode[i].taskname) == 0)
		{
			printf("Rename Error,TaskEventRegMbox\r\n");
			return;
		}
	}

	//�ر������жϣ�Ϊ�˷�ֹ���̵��ȣ���֤�ú�����ȫ
	OS_ENTER_CRITICAL();

	if (TaskEvent.index < TASKEVENT_MAXSIZE)
	{
		TaskEvent.TaskEventNode[TaskEvent.index].taskname = malloc(namesize);

		if (TaskEvent.TaskEventNode[TaskEvent.index].taskname != NULL)
		{
			memcpy(TaskEvent.TaskEventNode[TaskEvent.index].taskname, name, namesize);
			TaskEvent.TaskEventNode[TaskEvent.index].taskeve = (void *)OSQCreate(qstart, size);
			TaskEvent.TaskEventNode[TaskEvent.index].type = Queue;
			TaskEvent.index++;
		}
		else
		{
			printf("Name Malloc Error,TaskEventRegQueue\r\n");
		}
		
	}
	else
	{
		printf("Full Error,TaskEventRegQueue!\r\n");
	}
	OS_EXIT_CRITICAL();
}

/******************************************************************************
 * TaskEvntReg - ע���¼�
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
void TaskEvntReg(char *tname, unsigned char tevent,
	void **tstart, unsigned short int tsize,
	unsigned short int scnt,
	unsigned char mprio, unsigned char *merror,
	OS_FLAGS flag)
{
	switch(tevent)
	{
		case TASKEVENT_REG_QUEUE:
			TaskEventRegQueue(tname, tstart, tsize);
			break;

		case TASKEVENT_REG_MBOX:
			TaskEventRegMbox(tname);
			break;

		case TASKEVENT_REG_SEM:
			TaskEventRegSem(tname, scnt);
			break;

		case TASKEVENT_REG_MUTEX:
			TaskEventRegMutex(tname, mprio, merror);
			break;
		
		case TASKEVENT_REG_FLAG:
			TaskEventRegFlag(tname, flag, merror);
			break;
		
		default:
			break;
	}
}

/******************************************************************************
 * TaskEventGet - ��ȡ�¼�ָ��
 * 
 * Input: 
 * Output: 
 * Returns: 
 * modification history
 * --------------------
 * 31-jan-2018, ���� written
 * --------------------
 ******************************************************************************/
void *TaskEventGet(char *tname, unsigned char tevent)
{
	void *taskeventget = NULL;

	switch (tevent)
	{
		case TASKEVENT_GET_QUEUE:
			taskeventget = TaskEventGetQueue(tname);
			break;

		case TASKEVENT_GET_MBOX:
			taskeventget = TaskEventGetMBox(tname);
			break;

		case TASKEVENT_GET_SEM:
			taskeventget = TaskEventGetSem(tname);
			break;

		case TASKEVENT_GET_MUTEX:
			taskeventget = TaskEventGetMutex(tname);
			break;

		case TASKEVENT_GET_FLAG:
			taskeventget = TaskEventGetFlag(tname);
			break;

		default:
			break;
	}
	return taskeventget;
}

