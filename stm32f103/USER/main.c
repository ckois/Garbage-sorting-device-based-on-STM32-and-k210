#include "led.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"
#include "pwm.h"
//#include "lcd.h"/////////////δ�������ʹ��oled�������������
#include "syn6288.h"
#include "exti.h"
#include "usart.h"//�����ź��ߣ��м��ɫ��vcc��������gnd
//PA6 PA7 PA11//���pwm�ź���
//���ؼ����߶���  pb.0 pb.1 pb.2 pb.4��·�ⲿ�жϣ��½��ش�����λ��exit�ļ���
/*����ģ����߶��壺
		VCC--5V
		RXD--PB10
		TXD--PB11
		GND--GND*/




 int main(void)
 {	
	 int a=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	TIM3_PWM_Init(199,7199);//����Ƶ��PWMƵ��===(7200*200)/72000000=0.02=20ms
	TIM1_PWM_Init(199,7199);//����Ƶ��PWMƵ��===(7200*200)/72000000=0.02=20ms
	 usart1_init(115200);	 //����1��ʼ��Ϊ115200
	USART3_Init(9600);     //����3��ʼ��Ϊ9622
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	EXTIX_Init();         	//��ʼ���ⲿ�ж�����
	
	 
//	LCD_Init();
//POINT_COLOR=RED; 
   	while(1)
	{
	//	  POINT_COLOR=RED;	  
	//		LCD_ShowNum(60,130,USART1_RX_BUF[0],4,16);			
    //  LCD_ShowNum(60,150,USART1_RX_BUF[1],4,16);
	//   	LCD_ShowNum(60,170,USART1_RX_BUF[2],4,16);
		
		
if( a==0 )    //��ʼ��0��
	{
			
			
				SYN_FrameInfo(2, "[v7][m1][t5]��ӭʹ��������������ϵͳʹ��ǰ��ȷ����ƽ̨ˮƽ����");
//				delay_ms(1500);
//				delay_ms(1500);
//				delay_ms(1500);
//				delay_ms(1500);
//				delay_ms(1500);
				//��ͣ�ϳ�
				YS_SYN_Set(SYN_SuspendCom);
			
				//���ڽǶ�
				TIM_SetCompare1(TIM3,185); //1.5ms,185
				delay_ms(1800); 
						
				TIM_SetCompare2(TIM3,185); //1.5ms,185
				delay_ms(1800);
		
				TIM_SetCompare4(TIM1,185); //1.5ms,185
				delay_ms(1800); 
				 
				a++;
		
			
	}
	
if(  USART1_RX_BUF[0]=='2' )      //�ɻ�������ʶ��
	{
		    delay_ms(100);
		    USART1_RX_STA=0;
		if(  USART1_RX_BUF[0]=='2' )      
	   {
		    delay_ms(100);
		    USART1_RX_STA=0;
		    
				if(  USART1_RX_BUF[0]=='2' )  
				{
					SYN_FrameInfo(2, "[v7][m1][t5]�ɻ�������");
					delay_ms(1500);
					delay_ms(1500);
					
					//��ͣ�ϳ�
					YS_SYN_Set(SYN_SuspendCom);
				
					//���ڽǶ�
					TIM_SetCompare1(TIM3,190); //1ms,190     -45��
					delay_ms(1800); 
					
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0��
					delay_ms(1800); 
					
					TIM_SetCompare2(TIM3,190); //1ms,190,      -45��
					delay_ms(1800); 
						
					TIM_SetCompare2(TIM3,185); //1.5ms,185,   0��
					delay_ms(1800);
						
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
	  
			}
		}
	}
		
	 
if(  USART1_RX_BUF[0]=='4' )    //��������ʶ��
	{
		    delay_ms(100);
			  USART1_RX_STA=0;
		if(  USART1_RX_BUF[0]=='4' )  
	   {
		    delay_ms(100);
			  USART1_RX_STA=0;
		
			if(  USART1_RX_BUF[0]=='4' )
				{
					SYN_FrameInfo(2, "[v7][m1][t5]��������");
					delay_ms(1500);
					delay_ms(1500);
					
					//��ͣ�ϳ�
					YS_SYN_Set(SYN_SuspendCom);
					//���ڽǶ�		
					TIM_SetCompare1(TIM3,180); //2ms,180     45��
					delay_ms(1800); 
						
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0��
					delay_ms(1800); 
							
					TIM_SetCompare4(TIM1,180); //2ms,180     45��
					delay_ms(1800); 
						
					TIM_SetCompare4(TIM1,185); //1.5ms,185,   0��
					delay_ms(1800); 
										
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
			
			}
		}
	}
	
		
if(  USART1_RX_BUF[0]=='5' )    //�к�����ʶ��
	{
		    delay_ms(100);
			  USART1_RX_STA=0;
		
		if(  USART1_RX_BUF[0]=='5' )   
	   {
		    delay_ms(100);
			  USART1_RX_STA=0;
		
				if(  USART1_RX_BUF[0]=='5' ) 
				{
					SYN_FrameInfo(2, "[v7][m1][t5]�к�����");
					delay_ms(1500);
					delay_ms(1500);
					
					//��ͣ�ϳ�
					YS_SYN_Set(SYN_SuspendCom);
					//���ڽǶ�
					TIM_SetCompare1(TIM3,180); //2ms,180     45��
					delay_ms(1800); 
						
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0��
					delay_ms(1800); 
						
					TIM_SetCompare4(TIM1,190); //1ms,190     -45��
					delay_ms(1800); 
						
					TIM_SetCompare4(TIM1,185); //1.5ms,185,   0��
					delay_ms(1800); 
						
					USART1_RX_BUF[0]='6';	
					delay_ms(1800);
					delay_ms(1000);
					USART1_RX_STA=0;
				}
	
			}
	}
	

if(  USART1_RX_BUF[0]=='1' )    //��������ʶ��
		{
		    delay_ms(100);
			  USART1_RX_STA=0;
			if(  USART1_RX_BUF[0]=='1' )
			{
				delay_ms(100);
			  USART1_RX_STA=0;
			
				if(  USART1_RX_BUF[0]=='1' )  
				{
					SYN_FrameInfo(2, "[v7][m1][t5]��������");
					delay_ms(1500);
					delay_ms(1500);
				
					//��ͣ�ϳ�
					YS_SYN_Set(SYN_SuspendCom);
					//���ڽǶ�
				
					 TIM_SetCompare1(TIM3,190); //1ms,190     -45��
					delay_ms(1800); 
						
					TIM_SetCompare1(TIM3,185); //1.5ms,185,   0��
					delay_ms(1800); 
						
					TIM_SetCompare2(TIM3,180); //2ms,180     45��
					delay_ms(1800); 
						
					TIM_SetCompare2(TIM3,185); //1.5ms,185,   0��
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
