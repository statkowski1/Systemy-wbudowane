/*******************************************************************************
 Explorer 16 Demo Main File
  Company:
    Microchip Technology Inc.
  File Name:
    main.c
  Summary:
    Explorer 16 Demo Main File.
  Description: 
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).
You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "app.h"

#define FCY 4000000ULL
#include <libpic30.h>

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void ConvertADCVoltage ( unsigned int  ) ;
extern void Hex2Dec ( unsigned char ) ;

int liczbaX = 0;

void lampki(int tab[8])
{
    if(tab[7]==1)
    {
        LED_On(LED_D3);
    }
    else
    {
        LED_Off(LED_D3);
    }
    if(tab[6]==1)
    {
        LED_On(LED_D4);
    }
    else
    {
        LED_Off(LED_D4);
    }
    if(tab[5]==1)
    {
        LED_On(LED_D5);
    }
    else
    {
        LED_Off(LED_D5);
    }
    if(tab[4]==1)
    {
        LED_On(LED_D6);
    }
    else
    {
        LED_Off(LED_D6);
    }
    if(tab[3]==1)
    {
        LED_On(LED_D7);
    }
    else
    {
        LED_Off(LED_D7);
    }
    if(tab[2]==1)
    {
        LED_On(LED_D8);
    }
    else
    {
        LED_Off(LED_D8);
    }
    if(tab[1]==1)
    {
        LED_On(LED_D9);
    }
    else
    {
        LED_Off(LED_D9);
    }
    if(tab[0]==1)
    {
        LED_On(LED_D10);
    }
    else
    {
        LED_Off(LED_D10);
    }
}

void bin_p()
{
    int liczba;
    liczba = 0;
    while(liczbaX==0)
    {
        int tmp = liczba;
        if(liczba>255)
        {
            liczba = 0;
        }
        int bin[8];
        for(int i=7; i>=0; i--)
        {
            bin[i] = tmp%2;
            tmp = tmp/2;
        }
        lampki(bin);
        liczba += 1;
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 8;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 1;
            __delay_ms(100);
            break;
        }
    }
}

void bin_m()
{
    int liczba;
    liczba = 256;
    while(liczbaX==1)
    {
        int tmp = liczba;
        if(liczba<1)
        {
            liczba = 256;
        }
        int bin[8];
        for(int i=7; i>=0; i--)
        {
            bin[i] = tmp%2;
            tmp = tmp/2;
        }

        lampki(bin);
        liczba -= 1;
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 0;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 2;
            __delay_ms(100);
            break;
        }
    }
}

void gray_p()
{
    int liczba = 0;
    int gray = 0;
    int gray_tab[8];
    int j = 0;
    while(liczbaX==2)
    {
        if(liczba==255)
        {
            liczba = 0;
        }
        for(int i = 7; i >= 0; i--)
        {
            gray_tab[j] = (gray >> i) & 1;
            j += 1;
        }
        j = 0;
        lampki(gray_tab);
        liczba += 1;
        gray = liczba ^ (liczba >> 1);
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 1;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 3;
            __delay_ms(100);
            break;
        }
    }
}

void gray_m()
{
    int liczba = 255;
    int gray = 0;
    int gray_tab[8];
    int j = 0;
    while(liczbaX==3)
    {
        gray = liczba ^ (liczba >> 1);
        for(int i = 7; i >= 0; i--)
        {
            gray_tab[j] = (gray >> i) & 1;
            j += 1;
        }
        j = 0;
        lampki(gray_tab);
        if(liczba==0)
        {
            liczba = 255;
        }
        liczba -= 1;
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 2;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 4;
            __delay_ms(100);
            break;
        }
    }
}

void bcd_p()
{
    int liczba = 0;
    while(liczbaX==4)
    {
        if(liczba>99)
        {
            liczba = 0;
        }
        int bcd[8];
        int tmp[2];
        tmp[0] = liczba/10;
        tmp[1] = liczba%10;
        int tmp2 = tmp[0];
        for(int i=3; i>=0; i--)
        {
            bcd[i] = tmp2%2;
            tmp2 = tmp2/2;
        }
        tmp2 = tmp[1];
        for(int i=7; i>=4; i--)
        {
            bcd[i] = tmp2%2;
            tmp2 = tmp2/2;
        }
        lampki(bcd);
        liczba += 1;
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 3;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 5;
            __delay_ms(100);
            break;
        }
    }
}

void bcd_m()
{
    int liczba = 99;
    while(liczbaX==5)
    {
        if(liczba<0)
        {
            liczba = 99;
        }
        int bcd[8];
        int tmp[2];
        tmp[0] = liczba/10;
        tmp[1] = liczba%10;
        int tmp2 = tmp[0];
        for(int i=3; i>=0; i--)
        {
            bcd[i] = tmp2%2;
            tmp2 = tmp2/2;
        }
        tmp2 = tmp[1];
        for(int i=7; i>=4; i--)
        {
            bcd[i] = tmp2%2;
            tmp2 = tmp2/2;
        }
        lampki(bcd);
        liczba -= 1;
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 4;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 6;
            __delay_ms(100);
            break;
        }
    }
}

void waz()
{
    int waz[8] = {0, 0, 0, 0, 0, 1, 1, 1};
    lampki(waz);
    __delay_ms(100);
    while(liczbaX==6)
    {
        for(int i=7; i>2; i--)
        {
            waz[i] = 0;
            waz[i-3] = 1;
            lampki(waz);
            __delay_ms(100);
        }
        for(int i=0; i<5; i++)
        {
            waz[i] = 0;
            waz[i+3] = 1;
            lampki(waz);
            __delay_ms(100);
        }
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 5;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 7;
            __delay_ms(100);
            break;
        }
    }
}

void kolejka()
{
    int kolejka[8] = {0, 0, 0, 0, 0, 0, 0, 1};
    int i = 7;
    while(liczbaX==7)
    {
        __delay_ms(100);
        lampki(kolejka);
        if(kolejka[6]==1&&kolejka[7]==1)
        {
            break;
        }
        if(i-1>0 || kolejka[i-1]==0)
        {
            kolejka[i] = 0;
            kolejka[i-1] = 1;
            i -= 1;
        }
        if(i-1<0 || kolejka[i-1]==1)
        {
            i = 7;
            __delay_ms(100);
            lampki(kolejka);
            kolejka[7] = 1;
        }
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 6;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 8;
            __delay_ms(100);
            break;
        }
    }
}

void lfsr()
{
    int lfsr = 0b1110011;
    while(liczbaX==8)
    {
        int lfsr_tab[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        int bit = ((lfsr >> 0) ^ (lfsr >> 3) ^ (lfsr >> 4) ^ (lfsr >> 6)) & 1;
        lfsr = (lfsr >> 1) | (bit << 5);
        int tmp_bin = lfsr;
        for(int i=7; i>=2; i--)
        {
            lfsr_tab[i] = tmp_bin%2;
            tmp_bin = tmp_bin/2;
        }
        lampki(lfsr_tab);
        __delay_ms(100);
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            liczbaX = 7;
            __delay_ms(100);
            break;
        }
        else if(BUTTON_IsPressed(BUTTON_S6))
        {
            liczbaX = 0;
            __delay_ms(100);
            break;
        }
    }
}

void zadanie1()
{
    if(liczbaX<0)
    {
        liczbaX = 8;
    }
    else if(liczbaX>8)
    {
        liczbaX = 0;
    }
    if(liczbaX==0)
    {
        bin_p();
    }
    else if(liczbaX==1)
    {
        bin_m();
    }
    else if(liczbaX==2)
    {
        gray_p();
    }
    else if(liczbaX==3)
    {
        gray_m();
    }
    else if(liczbaX==4)
    {
        bcd_p();
    }
    else if(liczbaX==5)
    {
        bcd_m();
    }
    else if(liczbaX==6)
    {
        waz();
    }
    else if(liczbaX==7)
    {
        kolejka();
    }
    else if(liczbaX==8)
    {
        lfsr();
    }
}

APP_DATA appData = {
                    .messageLine1 = "Explorer 16 Demo" ,
                    .messageLine2 = "Press S3 to cont" ,
                    .messageTime = "Time 00: 00: 00 " ,
                    .messageADC = " Pot = 0.00 Vdc "
} ;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    LED_Enable(LED_D3);
    LED_Enable(LED_D4);
    LED_Enable(LED_D5);
    LED_Enable(LED_D6);
    LED_Enable(LED_D7);
    LED_Enable(LED_D8);
    LED_Enable(LED_D9);
    LED_Enable(LED_D10);
    BUTTON_Enable(BUTTON_S3);
    BUTTON_Enable(BUTTON_S6);

    /* Call the System Intialize routine*/
    SYS_Initialize ( ) ;

    /* Display welcome message */
    LCD_PutString ( (char*) &appData.messageLine1[0] , sizeof (appData.messageLine1 ) - 1  ) ;
    LCD_PutString ( (char*) &appData.messageLine2[0] , sizeof (appData.messageLine2 ) - 1  ) ;

    /* wait here until switch S3 is pressed */
    while (!BUTTON_IsPressed ( BUTTON_S3 )) ;

    /*Initialize Timer*/
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;

    /*Initialize ADC configure it as 10 bit interrupt driven mode*/
    ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;
    
    /* Display initial ADC and Timer messages */
    LCD_PutString ( (char*) &appData.messageTime[0] , sizeof (appData.messageTime ) - 1 ) ;
    LCD_PutString ( (char*) &appData.messageADC[0] , sizeof (appData.messageADC ) - 1 ) ;


    /* Infinite Loop */
    while ( 1 )
    {
        /* check if time to update LCD with Timer data */
        if ( appData.rtc_lcd_update )
        {
            zadanie1();
            Hex2Dec ( appData.hours ) ;
            Update_LCD ( ) ;
            appData.rtc_lcd_update = 0 ;

            /* check if time to update LCD with ADC data */
            if ( appData.adc_lcd_update )
            {

                ConvertADCVoltage ( appData.temp1 ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( 'l' ) ;
                LCD_PutChar ( 'i' ) ;
                LCD_PutChar ( 'c' ) ;
                LCD_PutChar ( 'z' ) ;
                LCD_PutChar ( 'b' ) ;
                LCD_PutChar ( 'a' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( '=' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( liczbaX+48 ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( ' ' ) ;
                appData.adc_lcd_update = 0 ;
            }

        }
    } ;
}
/*******************************************************************************
  Function:
   void Update_LCD( void )
  Summary:
    Function to update LCD
  Description:
    This function will update the time on the LCD
  Precondition:
    None.
  Parameters:
    None.
  Returns:
    None.
  Remarks:
 */
/******************************************************************************/
void Update_LCD ( void )
{
    LCD_PutChar ( 'T' ) ;
    LCD_PutChar ( 'i' ) ;
    LCD_PutChar ( 'm' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.minutes ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.seconds ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

}

/*******************************************************************************
  Function:
   void ConvertADCVoltage ( unsigned int )
  Summary:
    Function to convert ADC data into volts
  Description:
     This is the file for the Explorer 16 Dem that converts raw 10 bit ADC data
    to volts suitable for the LCD display
  Precondition:
    None.
  Parameters:
    None.
  Returns:
    None.
  Remarks:
 */
/******************************************************************************/

void ConvertADCVoltage ( unsigned int adc_conv_data )
{
    /* reset values */
    appData.adones = 0 ;
    appData.adtens = 0 ;
    appData.adhunds = 0 ;
    appData.adthous = 0 ;

    while ( adc_conv_data > 0 )
    {
        /* test for 1 volt or greater */
        if ( adc_conv_data > ( ONE_VOLT - 1 ) )
        {
            /* increment 1 volt counter */
            appData.adones++ ;

            /* subtract 1 volt */
            adc_conv_data -= ONE_VOLT ;
        }


            /* test for 0.1 volt */
        else if ( adc_conv_data > ( ONE_TENTH_VOLT - 1 ) )
        {
            /* increment tenths */
            if ( appData.adtens < 9 )
            {
                appData.adtens++ ;
            }
            else
            {
                /* tenths has rolled over */
                appData.adones++ ;

                /* so increment ones and reset tenths */
                appData.adtens = 0 ;
            }

            adc_conv_data -= ONE_TENTH_VOLT ;
        }

            /* test for 0.01 volt */
        else if ( adc_conv_data > ( ONE_HUNDREDTH_VOLT - 1 ) )
        {
            /* increment hundredths */
            if ( appData.adhunds < 9 )
            {
                appData.adhunds++ ;
            }
            else
            {
                /* hundredths has rolled over */
                appData.adtens++ ;

                /* so increment tenths and reset hundredths */
                appData.adhunds = 0 ;
            }

            adc_conv_data -= ONE_HUNDREDTH_VOLT ;
        }

        else if ( adc_conv_data <= ( ONE_HUNDREDTH_VOLT - 1 ) )
        {
            appData.adthous++ ;
            adc_conv_data -- ;
        }
    }

    appData.adones += 0x30 ;
    appData.adtens += 0x30 ;
    appData.adhunds += 0x30 ;
    appData.adthous += 0x30 ;
}

/*******************************************************************************
  Function:
   void Hex2Dec ( unsigned char )
  Summary:
    Explorer 16 Demo Hex to Decimal Conversion File
  Description:
     This is the file for the Explorer 16 Dem that converts the hexadecimal data
    into decimal format.
  Precondition:
    None.
  Parameters:
    None.
  Returns:
    None.
  Remarks:
 */
/******************************************************************************/

void Hex2Dec ( unsigned char count )
{
    /* reset values */
    appData.hunds = 0 ;
    appData.tens  = 0 ;
    appData.ones = 0 ;

    while ( count >= 10 )
    {

        if ( count >= 200 )
        {
            count -= 200 ;
            appData.hunds = 0x02 ;
        }

        if (count >= 100)
        {
            count -= 100 ;
            appData.hunds++ ;
        }

        if (count >= 10 )
        {
            count -= 10 ;
            appData.tens++ ;
        }
    }

    appData.ones = count ;
}
