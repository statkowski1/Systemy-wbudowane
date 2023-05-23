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
    BUTTON_Enable(BUTTON_S3);
    BUTTON_Enable(BUTTON_S6);
    
    int gracz1_czas1 =0;
    int gracz1_czas2=0;
    int gracz1_czas3=0;
    int gracz2_czas1=0;
    int gracz2_czas2=0;
    int gracz2_czas3=0;
    int czas;
    int gracz = 2;
    int wyswietl = 0;
    int ogranicznik = 0;

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
        ConvertADCVoltage(appData.temp1);
        czas = appData.adones;
        
        if(wyswietl == 0)
        {
            LCD_PutChar('G');
            LCD_PutChar('r');
            LCD_PutChar('a');
            LCD_PutChar('c');
            LCD_PutChar('z');
            LCD_PutChar(' ');
            LCD_PutChar('1');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar('G');
            LCD_PutChar('r');
            LCD_PutChar('a');
            LCD_PutChar('c');
            LCD_PutChar('z');
            LCD_PutChar(' ');
            LCD_PutChar('2');

            LCD_PutChar(gracz1_czas1+48);
            LCD_PutChar(':');
            LCD_PutChar(gracz1_czas2+48);
            LCD_PutChar(gracz1_czas3+48);
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(gracz2_czas1+48);
            LCD_PutChar(':');
            LCD_PutChar(gracz2_czas2+48);
            LCD_PutChar(gracz2_czas3+48);
        }
        else if(wyswietl == 1)
        {
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar('W');
            LCD_PutChar('Y');
            LCD_PutChar('G');
            LCD_PutChar('R');
            LCD_PutChar('Y');
            LCD_PutChar('W');
            LCD_PutChar('A');
            LCD_PutChar('!');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar('G');
            LCD_PutChar('R');
            LCD_PutChar('A');
            LCD_PutChar('C');
            LCD_PutChar('Z');
            LCD_PutChar(' ');
            LCD_PutChar('1');
            LCD_PutChar('!');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
        }
        else if(wyswietl == 2)
        {
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar('W');
            LCD_PutChar('Y');
            LCD_PutChar('G');
            LCD_PutChar('R');
            LCD_PutChar('Y');
            LCD_PutChar('W');
            LCD_PutChar('A');
            LCD_PutChar('!');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar('G');
            LCD_PutChar('R');
            LCD_PutChar('A');
            LCD_PutChar('C');
            LCD_PutChar('Z');
            LCD_PutChar(' ');
            LCD_PutChar('2');
            LCD_PutChar('!');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
        }
        
        if(ogranicznik == 0)
        {
            __delay_ms(3000);
        }
        
        if((czas-48 == 0 || czas-48 == 1) && gracz == 2)
        {
            gracz1_czas1 = 1;
            gracz1_czas2 = 0;
            gracz1_czas3 = 0;
            gracz2_czas1 = 1;
            gracz2_czas2 = 0;
            gracz2_czas3 = 0;
        }
        else if((czas-48 == 2) && gracz == 2)
        {
            gracz1_czas1 = 3;
            gracz1_czas2 = 0;
            gracz1_czas3 = 0;
            gracz2_czas1 = 3;
            gracz2_czas2 = 0;
            gracz2_czas3 = 0;
        }
        else if((czas-48 == 3) && gracz == 2)
        {
            gracz1_czas1 = 5;
            gracz1_czas2 = 0;
            gracz1_czas3 = 0;
            gracz2_czas1 = 5;
            gracz2_czas2 = 0;
            gracz2_czas3 = 0;
        }
        
        if(gracz1_czas3 == 0 && gracz1_czas2!=0 && gracz == 1)
        {
            gracz1_czas2 -= 1;
            gracz1_czas3 = 9;
            
        }
        else if(gracz1_czas3 == 0 && gracz1_czas2==0 && gracz1_czas1!=0 && gracz == 1)
        {
            gracz1_czas1 -= 1;
            gracz1_czas2 = 5;
            gracz1_czas3 = 9;
        }
        else if(gracz == 1 && gracz1_czas3!=0)
        {
            gracz1_czas3 -= 1;
        }
        
        if(gracz2_czas3 == 0 && gracz2_czas2!=0 && gracz == 0)
        {
            gracz2_czas2 -= 1;
            gracz2_czas3 = 9;
            
        }
        else if(gracz2_czas3 == 0 && gracz2_czas2==0 && gracz2_czas1!=0 && gracz == 0)
        {
            gracz2_czas1 -= 1;
            gracz2_czas2 = 5;
            gracz2_czas3 = 9;
        }
        else if(gracz == 0 && gracz2_czas3!=0)
        {
            gracz2_czas3 -= 1;
        }
        
        if(BUTTON_IsPressed(BUTTON_S3))
        {
            gracz = 0;
        }
        if(BUTTON_IsPressed(BUTTON_S6))
        {
            gracz = 1;
        }
        
        if(gracz2_czas1 == 0 && gracz2_czas2 == 0 && gracz2_czas3 == 0)
        {
            wyswietl = 1;
        }
        else if(gracz1_czas1 == 0 && gracz1_czas2 == 0 && gracz1_czas3 == 0)
        {
            wyswietl = 2;
        }
        
        __delay_ms(1000);
        ogranicznik = 1;
        
        /* check if time to update LCD with Timer data */
        if ( appData.rtc_lcd_update )
        {
            Hex2Dec ( appData.hours ) ;
            Update_LCD ( ) ;
            appData.rtc_lcd_update = 0 ;

            /* check if time to update LCD with ADC data */
            if ( appData.adc_lcd_update )
            {

//                ConvertADCVoltage ( appData.temp1 ) ;
//                LCD_PutChar ( ' ' ) ;
//                LCD_PutChar ( ' ' ) ;
//                LCD_PutChar ( 'P' ) ;
//                LCD_PutChar ( 'o' ) ;
//                LCD_PutChar ( 't' ) ;
//                LCD_PutChar ( ' ' ) ;
//                LCD_PutChar ( '=' ) ;
//                LCD_PutChar ( ' ' ) ;
//                LCD_PutChar ( appData.adones ) ;
//                LCD_PutChar ( '.' ) ;
//                LCD_PutChar ( appData.adtens ) ;
//                LCD_PutChar ( appData.adhunds ) ;
//                LCD_PutChar ( ' ' ) ;
//                LCD_PutChar ( 'V' ) ;
//                LCD_PutChar ( 'd' ) ;
//                LCD_PutChar ( 'c' ) ;
//                LCD_PutChar ( ' ' ) ;
//                appData.adc_lcd_update = 0 ;
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
//    LCD_PutChar ( 'T' ) ;
//    LCD_PutChar ( 'i' ) ;
//    LCD_PutChar ( 'm' ) ;
//    LCD_PutChar ( 'e' ) ;
//    LCD_PutChar ( ' ' ) ;
//    LCD_PutChar ( appData.tens + 0x30 ) ;
//    LCD_PutChar ( appData.ones + 0x30 ) ;
//
//    Hex2Dec ( appData.minutes ) ;
//    LCD_PutChar ( ':' ) ;
//    LCD_PutChar ( ' ' ) ;
//    LCD_PutChar ( appData.tens + 0x30 ) ;
//    LCD_PutChar ( appData.ones + 0x30 ) ;
//
//    Hex2Dec ( appData.seconds ) ;
//    LCD_PutChar ( ':' ) ;
//    LCD_PutChar ( ' ' ) ;
//    LCD_PutChar ( appData.tens + 0x30 ) ;
//    LCD_PutChar ( appData.ones + 0x30 ) ;

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
