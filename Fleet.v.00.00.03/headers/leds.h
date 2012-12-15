#define MAIN_LED_OFF_TMO 1
#define LED4_PIN                         GPIO_Pin_12
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOD 

extern OS_TID t_LED_TOGGLE;
extern OS_ID  tmr1;

void LED_Init(void);
void create_LED_Control_Task(void);
