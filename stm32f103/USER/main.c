#include "led.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"
#include "pwm.h"
//#include "lcd.h"/////////////未解决，若使用oled，舵机不会锁死
#include "syn6288.h"
#include "exti.h"
#include "usart.h"//黄线信号线，中间红色是vcc，棕线是gnd
//PA6 PA7 PA11//舵机pwm信号线
//满载检测接线定义  pb.0 pb.1 pb.2 pb.4四路外部中断，下降沿触发，位于exit文件中
/*语音模块接线定义：
		VCC--5V
		RXD--PB10
		TXD--PB11
		GND--GND*/




 int main(void)
 {	
	 int a=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	TIM3_PWM_Init(199,7199);//不分频。PWM频率===(7200*200)/72000000=0.02=20ms
	TIM1_PWM_Init(199,7199);//不分频。PWM频率===(7200*200)/72000000=0.02=20ms
	 usart1_init(115200);	 //串口1初始化为115200
	USART3_Init(9600);     //串口3初始化为9622
	LED_Init();		  	//初始化与LED连接的硬件接口
	EXTIX_Init();         	//初始化外部中断输入
	
	 
//	LCD_Init();
//POINT_COLOR=RED; 
   	while(1)
	{
	//	  POINT_COLOR=RED;	  
	//		LCD_ShowNum(60,130,USART1_RX_BUF[0],4,16);			
    //  LCD_ShowNum(60,150,USART1_RX_BUF[1],4,16);
	//   	LCD_ShowNum(60,170,USART1_RX_BUF[2],4,16);
		
		
if( a==0 )    //初始化0°
	{
			
			
				SYN_FrameInfo(2, "[v7][m1][t5]欢迎使用智能垃圾分类系统使用前请确保各平台水平放置");
//				delay_ms(1500);
//				delay_ms(1500);
//				delay_ms(1500);
//				delay_ms(1500);
//				delay_ms(1500);
				//暂停合成
				YS_SYN_Set(SYN_SuspendCom);
			
				//调节角度
				TIM_SetCompare1(TIM3,185); //1.5ms,185
				delay_ms(1800); 
						
				TIM_SetCompare2(TIM3,185); //1.5ms,185
				delay_ms(1800);
		
				TIM_SetCompare4(TIM1,185); //1.5ms,185
				delay_ms(1800); 
				 
				a++;
		
			
	}
	
if(  USART1_RX_BUF[0]=='2' )      //可回收垃圾识别
	{
		    delay_ms(100);
		    USART1_RX_STA=0;
		if(  USART1_RX_BUF[0]=='2' )      
	   {
		    delay_ms(100);
		    USART1_RX_STA=0;
		    
				if(  USART1_RX_BUF[0]=='2' )  
				{
					SYN_FrameInfo(2, "[v7][m1][t5]可回收垃圾");
					delay_ms(1500);
					delay_ms(1500);
					
					//暂停合成
					YS_SYN_Set(SYN_SuspendCom);
				
					//调节角度
					TIM_SetCompare1(TIM3,190); //1ms,190     -45°
					delay_ms(1800); 
					
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0°
					delay_ms(1800); 
					
					TIM_SetCompare2(TIM3,190); //1ms,190,      -45°
					delay_ms(1800); 
						
					TIM_SetCompare2(TIM3,185); //1.5ms,185,   0°
					delay_ms(1800);
						
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
	  
			}
		}
	}
		
	 
if(  USART1_RX_BUF[0]=='4' )    //其他垃圾识别
	{
		    delay_ms(100);
			  USART1_RX_STA=0;
		if(  USART1_RX_BUF[0]=='4' )  
	   {
		    delay_ms(100);
			  USART1_RX_STA=0;
		
			if(  USART1_RX_BUF[0]=='4' )
				{
					SYN_FrameInfo(2, "[v7][m1][t5]其他垃圾");
					delay_ms(1500);
					delay_ms(1500);
					
					//暂停合成
					YS_SYN_Set(SYN_SuspendCom);
					//调节角度		
					TIM_SetCompare1(TIM3,180); //2ms,180     45°
					delay_ms(1800); 
						
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0°
					delay_ms(1800); 
							
					TIM_SetCompare4(TIM1,180); //2ms,180     45°
					delay_ms(1800); 
						
					TIM_SetCompare4(TIM1,185); //1.5ms,185,   0°
					delay_ms(1800); 
										
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
			
			}
		}
	}
	
		
if(  USART1_RX_BUF[0]=='5' )    //有害垃圾识别
	{
		    delay_ms(100);
			  USART1_RX_STA=0;
		
		if(  USART1_RX_BUF[0]=='5' )   
	   {
		    delay_ms(100);
			  USART1_RX_STA=0;
		
				if(  USART1_RX_BUF[0]=='5' ) 
				{
					SYN_FrameInfo(2, "[v7][m1][t5]有害垃圾");
					delay_ms(1500);
					delay_ms(1500);
					
					//暂停合成
					YS_SYN_Set(SYN_SuspendCom);
					//调节角度
					TIM_SetCompare1(TIM3,180); //2ms,180     45°
					delay_ms(1800); 
						
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0°
					delay_ms(1800); 
						
					TIM_SetCompare4(TIM1,190); //1ms,190     -45°
					delay_ms(1800); 
						
					TIM_SetCompare4(TIM1,185); //1.5ms,185,   0°
					delay_ms(1800); 
						
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
				}
	
			}
	}
	

if(  USART1_RX_BUF[0]=='1' )    //厨余垃圾识别
		{
		    delay_ms(100);
			  USART1_RX_STA=0;
			if(  USART1_RX_BUF[0]=='1' )
			{
				delay_ms(100);
			  USART1_RX_STA=0;
			
				if(  USART1_RX_BUF[0]=='1' )  
				{
					SYN_FrameInfo(2, "[v7][m1][t5]厨余垃圾");
					delay_ms(1500);
					delay_ms(1500);
				
					//暂停合成
					YS_SYN_Set(SYN_SuspendCom);
					//调节角度
				
					 TIM_SetCompare1(TIM3,190); //1ms,190     -45°
					delay_ms(1800); 
						
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0°
					delay_ms(1800); 
						
					TIM_SetCompare2(TIM3,180); //2ms,180     45°
					delay_ms(1800); 
						
					TIM_SetCompare2(TIM3,185); //1.5ms,185,   0°
					delay_ms(1800); 
					
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
			}
		}
	 }
	} 
}
