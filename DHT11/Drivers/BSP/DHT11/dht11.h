#ifndef __DHT11_H__
#define __DHT11_H__
 
/* Private includes ----------------------------------------------------------*/
#include "main.h"
//#include "gpio.h"
#include "stdio.h"
#include "stm32f1xx.h"

//DHT11_DQ_IN



/* Private define ------------------------------------------------------------*/
#define DHT11_PIN_SET   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)                                            //  设置GPIO为高
#define DHT11_PIN_RESET HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)                                          //  设置GPIO为低
//#define DHT11_READ_IO   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)                                                          //  DHT11 GPIO定义
#define DHT11_DQ_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)                             /* PG口时钟使能 */
 
#define DHT11_DQ_GPIO_PORT                  GPIOG
#define DHT11_DQ_GPIO_PIN                   GPIO_PIN_11
//#define DHT11_DQ_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PG口时钟使能 */

/******************************************************************************************/

/* IO操作函数 */
#define DHT11_DQ_OUT(x)     do{ x ? \
                                HAL_GPIO_WritePin(DHT11_DQ_GPIO_PORT, DHT11_DQ_GPIO_PIN, GPIO_PIN_SET) : \
                                HAL_GPIO_WritePin(DHT11_DQ_GPIO_PORT, DHT11_DQ_GPIO_PIN, GPIO_PIN_RESET); \
                            }while(0)                                                /* 数据端口输出 */
#define DHT11_DQ_IN         HAL_GPIO_ReadPin(DHT11_DQ_GPIO_PORT, DHT11_DQ_GPIO_PIN)  /* 数据端口输入 */
 
/* Private function prototypes -----------------------------------------------*/
void DHT11(void);
void DHT11_START(void);
unsigned char DHT11_READ_BIT(void);
unsigned char DHT11_READ_BYTE(void);
unsigned char DHT11_READ_DATA(void);
uint8_t  dht11_check(void);
static void DHT11_GPIO_MODE_SET(uint8_t mode);

void Coarse_delay_us(uint32_t us);
    
#endif

