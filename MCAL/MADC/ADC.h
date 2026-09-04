#ifndef MCAL_MADC_ADC_H_
#define MCAL_MADC_ADC_H_


#define REF_AREF     0
#define REF_AVCC     1
#define REF_INTERNAL 2

#define ADC_PRESCALLER_2     0
#define ADC_PRESCALLER_4     1
#define ADC_PRESCALLER_8     2
#define ADC_PRESCALLER_16    3
#define ADC_PRESCALLER_32    4
#define ADC_PRESCALLER_64    5
#define ADC_PRESCALLER_128   6

#define ADC_CHANNEL0   0
#define ADC_CHANNEL1   1
#define ADC_CHANNEL2   2
#define ADC_CHANNEL3   3
#define ADC_CHANNEL4   4
#define ADC_CHANNEL5   5
#define ADC_CHANNEL6   6
#define ADC_CHANNEL7   7

#define ADC_INTERRUPT_ENABLE   0

#define ADMUX      (*(volatile u8*)(0x27))
#define ADCSRA     (*(volatile u8*)(0x26))
#define ADC        (*(volatile u16*)(0x24))
#define SFIOR      (*(volatile u8*)(0x50))
#define SREG       (*(volatile u8*)(0x5F))


void MADC_voidInit                  (u8 A_u8Prescaller , u8 A_u8Ref) ;
void MADC_voidStartConversion       (u8 A_u8ChannelNum             ) ;
u16  MADC_u16ReadDataUsingInterrupt (void                          ) ;
u16  MADC_u16ReadDataUsingPolling   (void                          ) ;
void MADC_voidCallBack              (void (*fptr)(void)            ) ;

#endif /* MCAL_MADC_ADC_H_ */
