#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"


/**************芯片设置命令*********************/
extern u8 SYN_StopCom[];
extern u8 SYN_SuspendCom[];
extern u8 SYN_RecoverCom[];
extern u8 SYN_ChackCom[];
extern u8 SYN_PowerDownCom[];

void EXTIX_Init(void);//外部中断初始化		 					    
#endif
