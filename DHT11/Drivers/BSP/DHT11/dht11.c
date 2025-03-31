#include "dht11.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

extern UART_HandleTypeDef huart1;
/**
  * @brief  ��ʪ�ȴ�����������
  * @param  void
  * @retval None
  */
void DHT11(void)
{
    if(DHT11_READ_DATA() == 1)
    {
        printf("����У��ɹ�!\r\n");
    }
    else
    {
        printf("DHT11û��Ӧ�����鴫����!\r\n");
    }
    HAL_Delay(1000);                              
  
}
 
/**
  * @brief  ��ʪ�ȴ����������źŷ���
  * @param  void
  * @retval None
  */
void DHT11_START(void)
{
    DHT11_GPIO_MODE_SET(0);                         //  ��������Ϊ���ģʽ
    
    DHT11_PIN_RESET;                                //  �������͵�ƽ
    
    HAL_Delay(20);                                  //  �����ȴ� 18 < ms > 30
    
    DHT11_GPIO_MODE_SET(1);                         //  ��������Ϊ����ģʽ���ȴ�DHT11��Ӧ
}                                                   //  ��Ϊ�������������룬GPIO -> 1
 
/**
  * @brief  ��ȡһλ���� 1bit
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_READ_BIT(void)
{
//    while(!DHT11_DQ_IN);                          //  �������ݵĵ͵�ƽ 
//    
//    Coarse_delay_us(40);

//    if(DHT11_DQ_IN)                               //  ��ʱ�����Ϊ�ߵ�ƽ������Ϊ 1
//    {
//        while(DHT11_DQ_IN);                       //  �������ݵĸߵ�ƽ
//        return 1;
//    }   
//    else                                            //  ����ʱΪ����Ϊ 0
//    {
//        return 0;
//    }
	uint8_t retry = 0;  /* ������� */

    while (DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }   /* �ȴ���Ϊ�͵�ƽ */

    retry = 0;

    while (! DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }   /* �ȴ���Ϊ�ߵ�ƽ*/

    delay_us(40);   /* �ȴ�40us */

    if (DHT11_DQ_IN)
        return 1;
    else
        return 0;
}
 
/**
  * @brief  ��ȡһ���ֽ����� 1byte / 8bit
  * @param  void
  * @retval temp
  */
unsigned char DHT11_READ_BYTE(void)
{
    uint8_t i,temp = 0;                             //  ��ʱ�洢����
    
    for(i=0; i<8 ;i++)
    {
        temp <<= 1;    
        temp |= DHT11_READ_BIT();  			
//        if(DHT11_READ_BIT())                        //  1byte -> 8bit
//        {
//            temp |= 1;                              //  0000 0001
//        }
    }
    return temp;
}
 
/**
  * @brief  ��ȡ��ʪ�ȴ��������� 5byte / 40bit
  * @param  void
  * @retval 0/1/2
  */
unsigned char DHT11_READ_DATA(void)
{
    uint8_t i;
	  uint8_t t = 0;
    uint8_t h = 0;
    uint8_t data[5] = {0};
    
    DHT11_START();                                  //  �������������ź�
    
    if(dht11_check())                               //  ���DHT11Ӧ��     
    {  
//        while(!DHT11_DQ_IN);                      //  ����DHT11���źŵĵ͵�ƽ
//        while(DHT11_DQ_IN);                       //  ����DHT11���źŵĸߵ�ƽ
        
//        for(i=0; i<5; i++)
//        {                        
//            data[i] = DHT11_READ_BYTE();            //  ��ȡ 5byte
//        }
//        
//        if(data[4] == (data[0] + data[1] + data[2] + data[3]))
//        {
//            printf("��ǰʪ�ȣ�%d.%d%%RH��ǰ�¶ȣ�%d.%d��C--\r\n",data[0],data[1],data[2],data[3]);
////					  printf("��ǰʪ�ȣ�%d.%d%%RH��ǰ�¶ȣ�%d.%d��C--\r\n",data[0],data[1],data[2],data[3]);
//            return 1;                               //  ����У��ͨ��
//        }
					for (i = 0; i < 5; i++)
					{
							data[i] = DHT11_READ_BYTE();
					}
				
				/* 4�����ݴ��� */
					if (data[4] == (data[0] + data[1] + data[2] + data[3]))
					{
							h = data[0];
							t = data[2];
						  printf("T:%d H:%d\r\n",t, h);
						  return 1; 
					}  
					
					else
					{
							return 0;                               //  ����У��ʧ��
					}
		}
		else                                            //  ���DHT11��Ӧ��
		{
				return 2;
		}
}
 
/**
  * @brief  �����ʪ�ȴ������Ƿ����(���DHT11��Ӧ���ź�)
  * @param  void
  * @retval 0/1
  */
//unsigned char DHT11_Check(void)
//{

//    Coarse_delay_us(40);
//    if(DHT11_READ_IO == 0)                          //  ��⵽DHT11Ӧ��
//    {
//        return 1;
//    }
//    else                                            //  ��⵽DHT11��Ӧ��
//    {
//        return 0;
//    }
//}

uint8_t dht11_check(void)
{
    uint8_t retry, rval = 0;
//	  printf("222\r\n");
    while (DHT11_DQ_IN && retry < 100)
    {
//			  printf("222\r\n");
        retry++;
        delay_us(1);
    }       /* DHT11������������Լ83us*/

    if (retry >= 100)   /* ��ʱ */
        rval = 1;
    else
    {
        retry = 0;

        while (! DHT11_DQ_IN && retry < 100)
        {
            retry++;
            delay_us(1);
        }   /* DHT11���ͺ���ٴ�����Լ87us*/

        if (retry >= 100)
            rval = 1;   /* ��ʱ */
    }

    return rval;
}
 
/**
  * @brief  ��������ģʽ
  * @param  mode: 0->out, 1->in
  * @retval None
  */
static void DHT11_GPIO_MODE_SET(uint8_t mode)
{  
	  DHT11_DQ_GPIO_CLK_ENABLE();
    if(mode)
    {    
			  
        /*  ����  */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = GPIO_PIN_6;                   //  9������
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;             //  ����ģʽ
        GPIO_InitStruct.Pull = GPIO_PULLUP;                 //  ��������
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else 
    {
        /*  ���  */
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin = GPIO_PIN_6;                //  9������
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;      //  Push Pull �������ģʽ
        GPIO_InitStructure.Pull = GPIO_PULLUP;              //  �������
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    //  ����
        HAL_GPIO_Init(GPIOB,&GPIO_InitStructure);
    }
}

/**
  * @brief  ������ʱ us , ������ 72M ��Ƶ��ʹ��
  * @param  us: <= 4294967295
  * @retval None
  */
void Coarse_delay_us(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}



