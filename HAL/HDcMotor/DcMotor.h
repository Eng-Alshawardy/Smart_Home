#ifndef HAL_HDCMOTOR_DCMOTOR_H_
#define HAL_HDCMOTOR_DCMOTOR_H_

void HDcMotor_voidInit (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin) ;
void HDcMotor_voidCW   (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin) ;
void HDcMotor_voidCCW  (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin) ;
void HDcMotor_voidStop (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin) ;

#endif /* HAL_HDCMOTOR_DCMOTOR_H_ */
