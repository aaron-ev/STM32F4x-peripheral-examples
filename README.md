## **Description**
Small examples of how to use some stm32f4x peripherals. 

## **Modules**

| Module name| Description |
| ------ | ----------- |
| HSE_SYSCLK_8MHz| Setting HSE (High Speed External clock)to 8MHz.|
| time_base_100ms| timer6 set to generate an overflow every 100ms.|
| time_base_100ms_it| timer6 set to generate an overflow every 100ms without interrupt capability.|
| timer_IC_1| timer2 in capture mode to mesure LSE (Low Speed External clock) .|
| timer_IC_2| timer2 in capture mode to mesure a 1Hz signal generaded from timer6.|
| timer_OC_1| timer2 in compare mode to generate 500Hz,1KHz,2KHz,4KHz in CH1,CH2,CH3,CH4 respectively.|
| timer_OC_PWM_1| timer2 in PWM mode to generate a 1Hz signal with 25,45,75,90 of duty cycle in CH1,CH2,CH3,CH4 respectively.|
