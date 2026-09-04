#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"
#include "EEPROM.h"

void MEEPROM_voidWrite (u16 A_u16Address , u8 A_u8Data)
{
	EEAR = A_u16Address ;
	EEDR = A_u8Data ;

	SET_BIT(EECR , 2) ;

	SET_BIT(EECR , 1) ;

	while (READ_BIT(EECR , 1) == 1) ;
}
u8   MEEPROM_u8Read    (u16 A_u16Address)
{
	EEAR = A_u16Address ;
	SET_BIT(EECR , 0) ;
	return EEDR ;
}

