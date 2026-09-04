#include "../LIB/StdTypes.h"
#include "../LIB/BitMath.h"
#include <util/delay.h>

#include "../MCAL/MDIO/DIO.h"
#include "../MCAL/MADC/ADC.h"
#include "../MCAL/MEEPROM/EEPROM.h"

#include "../HAL/HLCD/LCD.h"
#include "../HAL/HLED/Led.h"
#include "../HAL/HPB/PB.h"
#include "../HAL/HDcMotor/DcMotor.h"
#include "../HAL/HKP/KP.h"
#include "../HAL/HBUZZER/Buzzer.h"

u8 state_LED1 = 0;
u8 state_LED2 = 0;
u8 state_TV   = 0;
u8 state_AC   = 0;

void Update_Dashboard(void) {
    HLCD_voidClrScreen();

    HLCD_voidMoveCursor(LCD_ROW0, LCD_COL0);
    if(state_LED1) HLCD_voidDisplayStr((u8*)"LED1:ON ");
    else           HLCD_voidDisplayStr((u8*)"LED1:OFF");

    HLCD_voidMoveCursor(LCD_ROW1, LCD_COL0);
    if(state_LED2) HLCD_voidDisplayStr((u8*)"LED2:ON ");
    else           HLCD_voidDisplayStr((u8*)"LED2:OFF");

    HLCD_voidMoveCursor(LCD_ROW0, LCD_COL9);
    if(state_TV)   HLCD_voidDisplayStr((u8*)"TV :ON ");
    else           HLCD_voidDisplayStr((u8*)"TV :OFF");

    HLCD_voidMoveCursor(LCD_ROW1, LCD_COL9);
    if(state_AC)   HLCD_voidDisplayStr((u8*)"AC :ON ");
    else           HLCD_voidDisplayStr((u8*)"AC :OFF");
}

void Buzzer_ClickFeedback(void) {
    HBuzzer_voidBuzzerOn(DIO_PORTA, DIO_PIN5);
    _delay_ms(50);
    HBuzzer_voidBuzzerOff(DIO_PORTA, DIO_PIN5);
}

int main(void) {
    HLCD_voidInit();
    MADC_voidInit(ADC_PRESCALLER_64, REF_AVCC);
    HKP_voidInit(DIO_PORTC);

    HLED_voidLedInit(DIO_PORTD, DIO_PIN2);
    HLED_voidLedInit(DIO_PORTD, DIO_PIN3);
    HLED_voidLedInit(DIO_PORTD, DIO_PIN4);
    HLED_voidLedInit(DIO_PORTD, DIO_PIN5);

    HPB_voidInit(DIO_PORTA, DIO_PIN1);
    HPB_voidInit(DIO_PORTA, DIO_PIN2);
    HPB_voidInit(DIO_PORTA, DIO_PIN3);
    HPB_voidInit(DIO_PORTA, DIO_PIN4);

    HDcMotor_voidInit(DIO_PORTD, DIO_PIN0, DIO_PORTD, DIO_PIN1);

    HBuzzer_voidBuzzerInit(DIO_PORTA, DIO_PIN5);

    u8 stored_pass[4];
    u8 entered_pass[4];
    u8 is_authenticated = 0;

    if(MEEPROM_u8Read(0x0000) == 0xFF) {
        MEEPROM_voidWrite(0x0000, '1');
        MEEPROM_voidWrite(0x0001, '2');
        MEEPROM_voidWrite(0x0002, '3');
        MEEPROM_voidWrite(0x0003, '4');
    }

    stored_pass[0] = MEEPROM_u8Read(0x0000);
    stored_pass[1] = MEEPROM_u8Read(0x0001);
    stored_pass[2] = MEEPROM_u8Read(0x0002);
    stored_pass[3] = MEEPROM_u8Read(0x0003);

    while (is_authenticated == 0) {
        HLCD_voidClrScreen();
        HLCD_voidMoveCursor(LCD_ROW0, LCD_COL0);
        HLCD_voidDisplayStr((u8*)"Enter Password:");

        HLCD_voidMoveCursor(LCD_ROW1, LCD_COL0);

        u8 key_pressed = KP_NOT_PRESSED;
        for(u8 i = 0; i < 4; ) {
            key_pressed = HKP_u8GetPressedValue(DIO_PORTC);

            if(key_pressed != KP_NOT_PRESSED) {
                Buzzer_ClickFeedback();

                entered_pass[i] = key_pressed;
                HLCD_voidWriteData('*');
                i++;

                while(HKP_u8GetPressedValue(DIO_PORTC) != KP_NOT_PRESSED);
                _delay_ms(50);
            }
        }

        _delay_ms(300);

        if (entered_pass[0] == stored_pass[0] &&
            entered_pass[1] == stored_pass[1] &&
            entered_pass[2] == stored_pass[2] &&
            entered_pass[3] == stored_pass[3]) {

            HLCD_voidClrScreen();
            HLCD_voidDisplayStr((u8*)"Correct Pass");
            _delay_ms(1000);

            HLCD_voidClrScreen();
            HLCD_voidMoveCursor(LCD_ROW0, LCD_COL0);
            HLCD_voidDisplayStr((u8*)"Smart Home");
            HLCD_voidMoveCursor(LCD_ROW1, LCD_COL0);
            HLCD_voidDisplayStr((u8*)"Project");
            _delay_ms(1500);

            is_authenticated = 1;
        } else {
            HLCD_voidClrScreen();
            HLCD_voidDisplayStr((u8*)"Wrong Pass");

            HBuzzer_voidBuzzerOn(DIO_PORTA, DIO_PIN5);
            _delay_ms(1000);
            HBuzzer_voidBuzzerOff(DIO_PORTA, DIO_PIN5);
        }
    }

    Update_Dashboard();

    while(1) {
        if (HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN1) == PB_PRESSED) {
            state_LED1 ^= 1;
            HLED_voidLedTog(DIO_PORTD, DIO_PIN2);
            Update_Dashboard();
            Buzzer_ClickFeedback();
            while(HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN1) == PB_PRESSED);
            _delay_ms(50);
        }

        if (HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN2) == PB_PRESSED) {
            state_LED2 ^= 1;
            HLED_voidLedTog(DIO_PORTD, DIO_PIN3);
            Update_Dashboard();
            Buzzer_ClickFeedback();
            while(HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN2) == PB_PRESSED);
            _delay_ms(50);
        }

        if (HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN3) == PB_PRESSED) {
            state_TV ^= 1;
            HLED_voidLedTog(DIO_PORTD, DIO_PIN4);
            Update_Dashboard();
            Buzzer_ClickFeedback();
            while(HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN3) == PB_PRESSED);
            _delay_ms(50);
        }

        if (HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN4) == PB_PRESSED) {
            state_AC ^= 1;
            HLED_voidLedTog(DIO_PORTD, DIO_PIN5);
            Update_Dashboard();
            Buzzer_ClickFeedback();
            while(HPB_u8GetPbStatues(DIO_PORTA, DIO_PIN4) == PB_PRESSED);
            _delay_ms(50);
        }

        if (state_AC == 1) {
            MADC_voidStartConversion(ADC_CHANNEL0);
            u16 adc_value = MADC_u16ReadDataUsingPolling();

            u32 temp = ((u32)adc_value * 500) / 1024;

            if (temp > 25) {
                HDcMotor_voidCCW(DIO_PORTD, DIO_PIN0, DIO_PORTD, DIO_PIN1);
            } else {
                HDcMotor_voidCW(DIO_PORTD, DIO_PIN0, DIO_PORTD, DIO_PIN1);
            }
        } else {
            HDcMotor_voidStop(DIO_PORTD, DIO_PIN0, DIO_PORTD, DIO_PIN1);
        }
    }

    return 0;
}
