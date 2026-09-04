#ifndef HAL_HKP_KP_H_
#define HAL_HKP_KP_H_

#define KP_PRESSED         0
#define KP_NOT_PRESSED     255


void HKP_voidInit          (u8 A_u8PortName) ;
u8   HKP_u8GetPressedValue (u8 A_u8PortName) ;

#endif /* HAL_HKP_KP_H_ */
