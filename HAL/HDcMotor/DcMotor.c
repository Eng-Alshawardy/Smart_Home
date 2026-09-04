#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"

#include "../../MCAL/MDIO/DIO.h"

#include "DcMotor.h"

void HDcMotor_voidInit (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin)
{
	MDIO_voidInitPin(A_u8APort, A_u8APin, DIO_OUTPUT) ;
	MDIO_voidInitPin(A_u8BPort, A_u8BPin, DIO_OUTPUT) ;
}
void HDcMotor_voidCW   (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin)
{
	MDIO_voidSetPinValue(A_u8APort, A_u8APin, DIO_HIGH) ;
	MDIO_voidSetPinValue(A_u8BPort, A_u8BPin, DIO_LOW) ;
}
void HDcMotor_voidCCW  (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin)
{
	MDIO_voidSetPinValue(A_u8APort, A_u8APin, DIO_LOW) ;
	MDIO_voidSetPinValue(A_u8BPort, A_u8BPin, DIO_HIGH) ;
}
void HDcMotor_voidStop (u8 A_u8APort , u8 A_u8APin , u8 A_u8BPort , u8 A_u8BPin)
{
	MDIO_voidSetPinValue(A_u8APort, A_u8APin, DIO_LOW) ;
	MDIO_voidSetPinValue(A_u8BPort, A_u8BPin, DIO_LOW) ;
}

