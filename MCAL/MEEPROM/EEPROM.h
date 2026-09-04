#ifndef MCAL_MEEPROM_EEPROM_H_
#define MCAL_MEEPROM_EEPROM_H_

#define EEAR    (*(volatile u16*)(0x3E))
#define EECR    (*(volatile u8*)(0x3C))
#define EEDR    (*(volatile u8*)(0x3D))


void MEEPROM_voidWrite (u16 A_u16Address , u8 A_u8Data) ;
u8   MEEPROM_u8Read    (u16 A_u16Address) ;


#endif /* MCAL_MEEPROM_EEPROM_H_ */
