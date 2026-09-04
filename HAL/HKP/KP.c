#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"

#include "../../MCAL/MDIO/DIO.h"

#include "KP.h"
#include <util/delay.h>

u8 G_u8KpData[4][3] = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'},
		{'*', '0', '#'}
};

void HKP_voidInit          (u8 A_u8PortName)
{
	MDIO_voidInitPort(A_u8PortName, 0xF0) ;
	MDIO_voidSetPortValue(A_u8PortName, 0xFF) ;
}

u8   HKP_u8GetPressedValue (u8 A_u8PortName)
{
	u8 L_u8Row ;
	u8 L_u8Col ;

	for (L_u8Col = 0; L_u8Col < 3; L_u8Col++) {
	        MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_LOW);

	        for (L_u8Row = 0; L_u8Row < 4; L_u8Row++) {
	            if (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) == KP_PRESSED) {
	                _delay_ms(20);

	                if (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) == KP_PRESSED) {
	                    while (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) == KP_PRESSED);
	                    _delay_ms(20);

	                    MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_HIGH);

	                    return G_u8KpData[L_u8Row][L_u8Col];
	                }
	            }
	        }
	        MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_HIGH);
	    }

	    return KP_NOT_PRESSED;

}
