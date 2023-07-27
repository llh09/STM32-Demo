#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "spi.h"
#include "lcd.h"

int main(void)
{
	delay_init();
	uart_init(115200);
	LcdInit();
	LED_GPIO_Config();
	
	LcdClear(GREEN);
	
	printf("ok \r\n");
	while(1)
	{
		//LcdDrawLine(5,50,50,100,RED);
		LcdClear(GREEN);
		delay_ms(5);
		LcdClear(RED);
		delay_ms(5);
	}
}

