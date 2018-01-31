#ifndef TICKS_H
#define TICKS_H

#ifdef __cplusplus
    extern "C"{
#endif

#define  TASK_STK_SIZE                 512       /* Size of start task's stacks                        */
#define  TASK_START_PRIO	       3	 /* Priority of your startup task		       */

typedef struct
{
	unsigned char imerror;
	unsigned char iferror;
}InputError_t;

void Create_TaskTicks(void);

#ifdef __cplusplus
}
#endif
#endif