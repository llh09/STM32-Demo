#include "spi.h"

//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)
void LcdSpiInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
  
	//PA5 SPI1 SCK
	//PA7 SPI1 MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                        //����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                    //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		                          //ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                       	    //���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                            //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                    //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 0;	                              //CRCֵ����Ķ���ʽ
	
	SPI_Init(SPI1, &SPI_InitStructure);                                     //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(SPI1, ENABLE);    //ʹ��SPI����
}

uint8_t  LcdSpiSendReceiveByte(uint8_t data )
{
		/* �ȷ�һ�� */
	while(SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_TXE)==RESET);//	�ȴ��ϴ����ݷ������  
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_TXE);//�����ݾ����־�ˣ��ɲ�Ҫ��
	SPI_I2S_SendData(SPI1, data);//���ͱ�������
	/*��Ҫ���� */
	while(SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_RXNE)==RESET);//    �ȴ����յ�����
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_RXNE);//�����ݾ����־�ˣ��ɲ�Ҫ��
	return SPI_I2S_ReceiveData(SPI1);//	��ȡ����������
}
