#ifndef MIDWARE_H
#define MIDWARE_H

#ifdef __cplusplus
    extern "C"{
#endif

#define TASKEVENT_REG_QUEUE 0x01
#define TASKEVENT_REG_MBOX 0x02
#define TASKEVENT_REG_SEM 0x03
#define TASKEVENT_REG_MUTEX 0x04
#define TASKEVENT_REG_FLAG 0x05

#define TASKEVENT_GET_QUEUE 0x01
#define TASKEVENT_GET_MBOX 0x02
#define TASKEVENT_GET_SEM 0x03
#define TASKEVENT_GET_MUTEX 0x04
#define TASKEVENT_GET_FLAG 0x05

/*允许注册的最大事件个数*/
#define TASKEVENT_MAXSIZE 10

typedef enum
{
	Mbox,
	Queue,
	Sem,
	Mutex,
	Flag,

}TaskEventType_e;

typedef struct
{
	char *taskname;
	void *taskeve;
	TaskEventType_e type;
}TaskEventNode_t;

typedef struct
{
	TaskEventNode_t TaskEventNode[TASKEVENT_MAXSIZE];
	unsigned int index;
}TaskEvent_t;


void TaskEvntReg(char *tname, unsigned char tevent,
	void **tstart, unsigned short int tsize,
	unsigned short int scnt,
	unsigned char mprio, unsigned char *merror,
	OS_FLAGS flag);
void *TaskEventGet(char *tname, unsigned char tevent);

#ifdef __cplusplus
}
#endif
#endif