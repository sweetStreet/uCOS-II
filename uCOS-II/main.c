/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                             (c) Copyright 1998-2004, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                            WIN32 Sample Code
*
* File : APP.C
* By   : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE    128
#define  TASK_START_PRIO    5

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK        AppStartTaskStk[TASK_STK_SIZE];
//Modify
//定义任务的栈空间
static OS_STK stack1[TASK_STK_SIZE];
static OS_STK stack2[TASK_STK_SIZE];
static OS_STK stack3[TASK_STK_SIZE];
static OS_STK stack4[TASK_STK_SIZE];
static OS_STK stack5[TASK_STK_SIZE];
static OS_STK stack6[TASK_STK_SIZE];
static OS_STK stack7[TASK_STK_SIZE];
static OS_STK stack8[TASK_STK_SIZE];
static OS_STK stack9[TASK_STK_SIZE];
static OS_STK stack10[TASK_STK_SIZE];
static OS_STK stack11[TASK_STK_SIZE];
static OS_STK stack12[TASK_STK_SIZE];


INT32S tasks[][3] = {
		{ 1, 3, 0 },//Prio1
		{ 3, 5, 0 },//Prio2
		{ 4, 9, 0 }//Prio3
};

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppStartTask(void *p_arg);
static void periodicTask(void *p_arg);

#if OS_VIEW_MODULE > 0
static  void  AppTerminalRx(INT8U rx_data);
#endif

/*
*********************************************************************************************************
*                                                _tmain()
*
* Description : This is the standard entry point for C++ WIN32 code.  
* Arguments   : none
*********************************************************************************************************
*/

void main(int argc, char *argv[])
{
	INT8U  err;


#if 0
    BSP_IntDisAll();                       /* For an embedded target, disable all interrupts until we are ready to accept them */
#endif

    OSInit();                              /* Initialize "uC/OS-II, The Real-Time Kernel"                                      */

    	OSTaskCreateExt(periodicTask,
		(void *)tasks[0],
		stack1 + (TASK_STK_SIZE - 1),
		(INT8U)(1),
		(INT16U)(1),
		stack1,
		(INT32U)TASK_STK_SIZE,
		(void *)&tasks[0],
		(INT16U)(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskCreateExt(periodicTask,
		(void *)tasks[1],
		stack2 + (TASK_STK_SIZE - 1),
		(INT8U)(2),
		(INT16U)(2),
		stack2,
		(INT32U)TASK_STK_SIZE,
		(void *)&tasks[1],
		(INT16U)(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskCreateExt(periodicTask,
		(void *)tasks[2],
		stack3 + (TASK_STK_SIZE - 1),
		(INT8U)(3),
		(INT16U)(3),
		stack3,
		(INT32U)TASK_STK_SIZE,
		(void *)&tasks[2],
		(INT16U)(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (INT8U *)"Start Task", &err);
#endif

#if OS_TASK_NAME_SIZE > 14
    OSTaskNameSet(OS_IDLE_PRIO, (INT8U *)"uC/OS-II Idle", &err);
#endif

#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_STAT_PRIO, "uC/OS-II Stat", &err);
#endif

    OSStart();                             /* Start multitasking (i.e. give control to uC/OS-II)                               */
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

void  AppStartTask (void *p_arg)
{
    p_arg = p_arg;

#if 0
    BSP_Init();                                  /* For embedded targets, initialize BSP functions                             */
#endif


#if OS_TASK_STAT_EN > 0
    OSStatInit();                                /* Determine CPU capacity                                                     */
#endif
    
    while (TRUE)                                 /* Task body, always written as an infinite loop.                             */
	{       		
		OS_Printf("Delay 1 second and print\n");  /* your code here. Create more tasks, etc.                                    */
        OSTimeDlyHMSM(0, 0, 1, 0);       
    }
}

//自定义的任务
static void periodicTask(void *p_arg)
{
	INT32S *p = (INT32S *)p_arg;

	INT32S start;
	INT32S end;
	INT32S toDelay;
	start = 0;

	while (1)
	{
		while (OSTCBCur->compTime > 0)
		{
			//Do nothing
		}
		end = OSTimeGet();
		toDelay = OSTCBCur->period - (end - start) % OSTCBCur->period;
		toDelay = toDelay < 0 ? 0 : toDelay;
		start += (OSTCBCur->period);
		OSTCBCur->compTime = OSTCBCur->fullCompTime;
		OSTimeDly(toDelay);
	}
}