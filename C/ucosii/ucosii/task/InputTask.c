#include "includes.h"

static OS_STK TaskInputStk[TASK_INPUT_SIZE];
static void *TaskInput_Q[TASK_INPUT_QSIZE];
InputError_t InputError;

//��Ϣ���а�
static void Task_QInput(void *pdata)
{
	static char qstr[1024];
	static char qinit = 1;
	OS_EVENT *qinput = NULL;
	pdata = pdata;

	qinput = (OS_EVENT *)TaskEventGet("input", TASKEVENT_GET_QUEUE);

	while (1)
	{
		if (qinit)
		{
			printf("please input somethings\r\n");
			qinit = 0;
		}

		if (_kbhit())
		{
			memset(&qstr, 0, 1024);
			scanf("%s", &qstr);
			
			if (qinput != NULL)
			{
				if (OSQPost(qinput, (void *)&qstr) == OS_ERR_NONE)
					printf("QInputStr is:%s\r\n", &qstr);
				else
					printf("QInputError!\r\n");
			}
			else
			{
				printf("QInput is NULL\r\n");
			}
		}
		OSTimeDly(1000);//1s
	}

}

//�����
static void Task_MInput(void *pdata)
{
	static char mstr[1024];
	static char minit = 1;
	OS_EVENT *minput = NULL;
	pdata = pdata;

	minput = (OS_EVENT *)TaskEventGet("input", TASKEVENT_GET_MBOX);

	while (1)
	{
		if (minit)
		{
			printf("Please Input Somethings\r\n");
			minit = 0;
		}

		if (_kbhit())
		{
			memset(&mstr, 0, 1024);
			scanf("%s", &mstr);

			if (minput != NULL)
			{
				if (OSMboxPost(minput, (void *)&mstr) == OS_ERR_NONE)
					printf("MInputStr is:%s\r\n", &mstr);
				else
					printf("MInputError!\r\n");
			}
			else
			{
				printf("MInput is NULL\r\n");
			}
		}
		OSTimeDly(1000);//1s
	}

}

void Create_TaskInput(void)
{
	//��ʼ��һ����Ϣ����
	TaskEvntReg("input", TASKEVENT_REG_QUEUE, TaskInput_Q, TASK_INPUT_QSIZE, 0, 0, (void *)0, 0);

	//��ʼ��һ������
	TaskEvntReg("input", TASKEVENT_REG_MBOX, (void *)0, 0, 0, 0, (void *)0, 0);

	//��ʼ��һ���ź���
	TaskEvntReg("input", TASKEVENT_REG_SEM, (void *)0, 0, 1, 0, (void *)0, 0);

	//��ʼ��һ�������ź���
	TaskEvntReg("input", TASKEVENT_REG_MUTEX, (void *)0, 0, 0, 1, &InputError.imerror, 0);
	
	//��ʼ���¼���־��
	TaskEvntReg("input", TASKEVENT_REG_FLAG, (void *)0, 0, 0, 0, &InputError.iferror, 0);

	//��������
	OSTaskCreate(Task_MInput, (void *)0, &TaskInputStk[TASK_INPUT_SIZE - 1], TASK_INPUT_PRIO);
}

