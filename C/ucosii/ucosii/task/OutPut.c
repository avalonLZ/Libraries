#include "includes.h"

static OS_STK TaskOutputStk[TASK_INPUT_SIZE];

//消息队列版
static void Task_QOutput(void *pdata)
{
	OS_EVENT *qoutput = NULL;
	INT8U qerr = 0;
	char *qoutputmsg = NULL;
	pdata = pdata;

	printf("Output Start!\r\n");

	while (1)
	{
		qoutput = (OS_EVENT *)TaskEventGet("input", TASKEVENT_GET_QUEUE);
		
		if(qoutput != NULL)
			qoutputmsg = (char *)OSQPend(qoutput, 0, &qerr);
	
		if (qoutputmsg != NULL)
		{
			printf("QOutput is:%s\r\n", qoutputmsg);
		}
		else
			printf("Wait Input\r\n");
	}
	
}

//邮箱版
static void Task_MOutput(void *pdata)
{
	OS_EVENT *moutput = NULL;
	INT8U merr = 0;
	char *moutputmsg = NULL;
	pdata = pdata;

	printf("Output Start!\r\n");

	while (1)
	{
		moutput = (OS_EVENT *)TaskEventGet("input", TASKEVENT_GET_MBOX);

		if (moutput != NULL)
			moutputmsg = (char *)OSMboxPend(moutput, 0, &merr);

		if (moutputmsg != NULL)
		{
			printf("MOutput is:%s\r\n", moutputmsg);
		}
		else
			printf("Wait Input\r\n");
	}

}

void Create_TaskOutput(void)
{
	OSTaskCreate(Task_MOutput, (void *)0, &TaskOutputStk[TASK_OUTPUT_SIZE - 1], TASK_OUTPUT_PRIO);
}
