/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 2004-... Werner.Zimmermann@hs-esslingen.de
*                 (Similar to Example 1 of the 80x86 Real Mode port by Jean J. Labrosse)
*                                           All Rights Reserved
*
*                                           Application Template
*********************************************************************************************************
*/

#include "includes.h"


int main (void)
{
    OSInit();                                              /* Initialize uC/OS-II                      */


	Create_TaskTicks();
	Create_TaskInput();
	Create_TaskOutput();
	OSStart();                                             /* Start multitasking                       */

    return 0;
}




