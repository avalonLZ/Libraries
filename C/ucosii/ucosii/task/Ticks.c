#include "includes.h"

static OS_STK TaskStartStk[TASK_STK_SIZE];

static void  TaskStart(void *pdata)
{
//	INT16S key;
	pdata = pdata;                                         /* Prevent compiler warning                 */


#if OS_TASK_STAT_EN > 0
	OSStatInit();                                          /* Initialize uC/OS-II's statistics         */
#endif

	/* Create all other application tasks here        						       */
#ifdef __WIN32__
	printf("##### uCOS-II V%4.2f Port V%4.2f for WIN32 #####\n", ((FP32)OSVersion()) / 100, ((FP32)OSPortVersion()) / 100);
	printf("##### (C) by Werner.Zimmermann@hs-esslingen - Startup task\n");
#endif
#ifdef __LINUX__
	printf("##### uCOS-II V%4.2f Port V%4.2f for LINUX #####\n", ((FP32)OSVersion()) / 100, ((FP32)OSPortVersion()) / 100);
	printf("##### (C) by Werner.Zimmermann@hs-esslingen - Startup task\n");
#endif

	while (1)						   /* Startup task's infinite loop	       */
	{
		printf("Now running for %6u ticks\r\n", OSTime);

		//if (pc_getkey(&key) == true) {                     /* see if key has been pressed              */
		//    if (key == 'q') {                             /* yes, see if it's the escape key          */
		//        exit(0);  	                           /* end program                              */
		//    }
		//}
		OSTimeDly(1000);//1s 
	}
}

void Create_TaskTicks(void)
{
	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], TASK_START_PRIO);
}