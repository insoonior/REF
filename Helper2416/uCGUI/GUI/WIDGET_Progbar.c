/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : WIDGET_Progbar.c
Purpose     : Simple demo shows the use of the PROGBAR widget
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "PROGBAR.h"
#include <stddef.h>

/*******************************************************************
*
*       static code
*
********************************************************************
*/

/*******************************************************************
*
*       _DemoProgBar
*/
static void _DemoProgBar(void) {
  int i;
  PROGBAR_Handle ahProgBar[2];
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WIDGET_Progbar - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringAt("Progress bar", 100,80);
  /* Create the progbars */  
  ahProgBar[0] = PROGBAR_Create(100,100,100,20, WM_CF_SHOW);
  ahProgBar[1] = PROGBAR_Create( 80,150,140,10, WM_CF_SHOW);
  /* Use memory device (optional, for better looks) */
  PROGBAR_EnableMemdev(ahProgBar[0]);
  PROGBAR_EnableMemdev(ahProgBar[1]);
  PROGBAR_SetMinMax(ahProgBar[1], 0, 500);
  PROGBAR_SetFont(ahProgBar[0], &GUI_Font8x16);
  GUI_Delay(500);
  while(1) {
    PROGBAR_SetFont(ahProgBar[0], &GUI_Font8x16);
    if (LCD_GetDevCap(LCD_DEVCAP_BITSPERPIXEL) <= 4) {
      PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_DARKGRAY);
      PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_LIGHTGRAY);
    } else {
      PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_GREEN);
      PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_RED);
    }
    PROGBAR_SetTextAlign(ahProgBar[0], GUI_TA_HCENTER);
    PROGBAR_SetText(ahProgBar[0], NULL);
    for (i=0; i<=100; i++) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], i);
      GUI_Delay(5);
    }
    PROGBAR_SetText(ahProgBar[0], "Tank empty");
    for (; i>=0; i--) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 200-i);
      GUI_Delay(5);
    }
    PROGBAR_SetText(ahProgBar[0], "Any text...");
    PROGBAR_SetTextAlign(ahProgBar[0], GUI_TA_LEFT);
    for (; i<=100; i++) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 200+i);
      GUI_Delay(5);
    }
    PROGBAR_SetTextAlign(ahProgBar[0], GUI_TA_RIGHT);
    for (; i>=0; i--) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 400-i);
      GUI_Delay(5);
    }
    PROGBAR_SetFont(ahProgBar[0], &GUI_FontComic18B_1);
    PROGBAR_SetText(ahProgBar[0], "Any font...");
    for (; i<=100; i++) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 400+i);
      GUI_Delay(5);
    }
    GUI_Delay(500);
  }
}

/*******************************************************************
*
*       MainTask
*
*       Demonstrates the use of the PROGBAR widget
*
********************************************************************
*/

void MainTask(void) {
  GUI_Init();
  while (1) {
    _DemoProgBar();
  }
}
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
