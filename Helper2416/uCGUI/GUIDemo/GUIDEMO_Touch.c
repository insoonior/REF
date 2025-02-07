/*
*********************************************************************************************************
*                                                uC/GUI
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
File        : GUIDEMO_Touch
Purpose     : Touch demo
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCD_ConfDefaults.h"      /* valid LCD configuration */
#include "GUIDEMO.h"
#include "GUITouchConf.h"


#if (GUI_WINSUPPORT && GUI_SUPPORT_TOUCH)

#include "BUTTON.h"
#include "EDIT.h"

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) {
  return p0 + ((p1 - p0) * (l - l0)) / (l1 - l0);
}

static void _Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1, int *p0, int *p1) {
  int l0 = 0;
  int l1 = (Coord == GUI_COORD_X) ? LCD_XSIZE - 1 : LCD_YSIZE - 1;
  *p0 = _Log2Phys(l0, Log0, Log1, Phys0, Phys1);
  *p1 = _Log2Phys(l1, Log0, Log1, Phys0, Phys1);
}

/*********************************************************************
*
*       _ExecCalibration
*
**********************************************************************
*/
int ts_get_x_data_raw_u(void);
int touch_state_pressed(void);
int ts_get_y_data_raw_u(void);
int GUI_TOUCH_Calibrate_Reverse(int Coord, int Log0, int Log1, int Phys0, int Phys1);

void _ExecCalibration(void) {
  int ax_Phys[2],ay_Phys[2];
/* calculate log. Positions */
  int ax[2] = { 10, LCD_XSIZE - 10};
//  const int ay[2] = { 15, LCD_YSIZE-1-15};
  int ay[2] = { LCD_YSIZE-10, 10};
  //GUI_TOUCH_SetDefaultCalibration();
/* _Calibrate upper left */
  
  int temp1;
  int temp2;
  int temp3;
  int temp4;
  int loop_count;

  loop_count = 0;
  
  while (1) {




	  while (1) {
	  	
	  GUI_SetBkColor(GUI_BLACK);  
	  GUI_Clear();
	  //GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[0], ay[0], 10);
	  GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[0], ay[0], 10);
	  //GUI_SetColor(GUI_WHITE);
	  GUI_DispStringAt("Press the red circle", LCD_XSIZE / 2, LCD_YSIZE / 2);
	  do {
	    //GUI_PID_STATE State;
	    //GUI_TOUCH_GetState(&State);
	    if (touch_state_pressed() == 1) {
	      ax_Phys[0] = ts_get_x_data_raw_u();
	      ay_Phys[0] = ts_get_y_data_raw_u();
	      break;
	    }
	    GUI_Delay (100);
	  } while (1);
	/* Tell user to release */
	  GUI_Clear();
	  //GUI_DispStringAt("OK", ax[0]+20, ay[0]);
	  do {
	    //GUI_PID_STATE State;
	    //GUI_TOUCH_GetState(&State);
	    if (touch_state_pressed() == 0) {
	      break;
	    }
	    GUI_Delay (100);
	  } while (1);
		loop_count++;
		
		if (loop_count == 1) {
			temp1 = ax_Phys[0];
			temp2 = ay_Phys[0];

		}

		else {

			temp3 = ax_Phys[0];
			temp4 = ay_Phys[0];

			if ((abs(temp3 - temp1) < 20) && (abs(temp4 - temp2) < 20)) {
				break;
			}

			else {
				loop_count = 0;

			}
			
		}

		
	  }

	  loop_count = 0;

	  while (1) {
	  
	/* _Calibrate lower right */
	  GUI_SetBkColor(GUI_BLACK);  
	  GUI_Clear();
	  //GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[1], ay[1], 10);
	  GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[1], ay[1], 10);
	  //GUI_SetColor(GUI_WHITE);
	  //GUI_SetTextAlign(GUI_TA_RIGHT);
	   GUI_DispStringAt("Press the red circle", LCD_XSIZE / 2, LCD_YSIZE / 2);
	 
	  
	  do {
	    //GUI_PID_STATE State;
	   // GUI_TOUCH_GetState(&State);
	    if (touch_state_pressed() == 1) {
	      ax_Phys[1] = ts_get_x_data_raw_u();
	      ay_Phys[1] = ts_get_y_data_raw_u();
	      break;
	    }
	    GUI_Delay (100);
	  } while (1);

	  GUI_Clear();
	  GUI_DispStringAt("OK", ax[1]-20, ay[1]);
	  do {
	    //GUI_PID_STATE State;
	    //GUI_TOUCH_GetState(&State);
	    if (touch_state_pressed() == 0) {
	      break;
	    }
	    GUI_Delay (100);
	  } while (1);


		loop_count++;
		
		if (loop_count == 1) {
			temp1 = ax_Phys[1];
			temp2 = ay_Phys[1];

		}

		else {

			temp3 = ax_Phys[1];
			temp4 = ay_Phys[1];

			if ((abs(temp3 - temp1) < 20) && (abs(temp4 - temp2) < 20)) {
				break;
			}

			else {

				loop_count = 0;
			}
		}


	  	}

	  
		if ((ax_Phys[0] > 0) && (ax_Phys[1] > 0) && (ay_Phys[0] > 0) && (ay_Phys[1] > 0)) {
			break;
		}
		
	}
	  
  	
	#if ((GUI_TOUCH_SWAP_XY == 0))
	Uart_Printf("^^^^^^^^^^^^^^^^^^^^^^^\n");
	GUI_TOUCH_Calibrate(GUI_COORD_X, ax[0], ax[1], ax_Phys[0], ax_Phys[1]);
	
	GUI_TOUCH_Calibrate(GUI_COORD_Y, ay[0], ay[1], ay_Phys[0], ay_Phys[1]);

	#else

	Uart_Printf("*************************\n");
	GUI_TOUCH_Calibrate(GUI_COORD_X, ax[0], ax[1], ay_Phys[0], ay_Phys[1]);

	GUI_TOUCH_Calibrate(GUI_COORD_Y, ay[0], ay[1], ax_Phys[0], ax_Phys[1]);

	#endif


	
  { /* calculate and display values for configuration file */
    int x0, x1;
    int y0, y1;
    GUI_Clear();
    _Calibrate(GUI_COORD_X, ax[0], ax[1], ax_Phys[0], ax_Phys[1], &x0, &x1);
    _Calibrate(GUI_COORD_Y, ay[0], ay[1], ay_Phys[0], ay_Phys[1], &y0, &y1);
    GUI_DispStringAt("x0: ", 0, 0); GUI_DispDec(x0, 4); GUI_DispNextLine();
    GUI_DispString  ("x1: ");       GUI_DispDec(x1, 4); GUI_DispNextLine();
    GUI_DispString  ("y0: ");       GUI_DispDec(y0, 4); GUI_DispNextLine();
    GUI_DispString  ("y1: ");       GUI_DispDec(y1, 4); GUI_DispNextLine();
    GUI_DispString  ("Please touch display to continue...");
    GUI_Delay(1000);
    do {
      GUI_PID_STATE State;
      GUI_TOUCH_GetState(&State);
      if (State.Pressed)
        break;
      GUI_Delay (10);
    } while (1);
  }
}

/*********************************************************************
*
*       _TestCalibration
*
**********************************************************************
*/

void _TestCalibration(void) {
  int IdleCnt=0;
  BUTTON_Handle hButton;
  GUI_SetBkColor(GUI_RED);  
  GUI_SetColor(GUI_WHITE);  
  GUI_Clear();
  hButton =  BUTTON_Create( 225, 15, 80, 40, 1, BUTTON_CF_SHOW );
  BUTTON_SetText (hButton, "ABORT");
  BUTTON_SetFont (hButton, &GUI_FontComic18B_ASCII);
  while ((IdleCnt<50) && (GUI_GetKey()==0)) {
    static GUI_PID_STATE StateLast;
    GUI_PID_STATE State;
    GUI_TOUCH_GetState(&State);
    if ((StateLast.Pressed != State.Pressed) && (State.Pressed == 0)) {
      GUI_Clear();
    }
    if ((StateLast.x != State.x) || ((StateLast.y != State.y))) {
      if (State.Pressed) {
        GUI_FillCircle(State.x, State.y, 5);
      }
      StateLast = State;
    }
    if (State.Pressed) {
      IdleCnt =0;
    } else {
      IdleCnt++;
    }
    GUI_Delay (100);
  }
  EDIT_Delete(hButton);
}

/*********************************************************************
*
*       _ExecKeyboard
*
**********************************************************************

This creates a sample keyboard.
The routine returns after ENTER or ESC has been pressed.
*/

#if (LCD_XSIZE == 320) && (LCD_YSIZE == 240)

static char _acText[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '='
                        ,0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'
                        ,0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Q'
                        ,0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '�', '�', '�'
                        ,' ', ' ', ' ', ' ', ' ', 0, 0
};

int _ExecKeyboard(void) {
  int i;
  int Key;
  BUTTON_Handle ahButton[52];
  BUTTON_Handle hButtonESC;
  EDIT_Handle   hEdit;
  GUI_RECT rText = {000,0, LCD_XSIZE, 20};
  GUI_SetBkColor(GUI_BLUE);  
  GUI_Clear();
  GUI_DrawBitmap(&bmMicriumLogo, 0, 0);
  GUI_SetFont(&GUI_Font16B_1);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRect("�C/GUI", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
  rText.y0 +=20;
  rText.y1 +=20;
  GUI_DispStringInRect("Touch screen demo", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
  /* Create Keyboard Buttons */
  for (i=0; i< 51; i++) {
    int Pos = (i < 47) ? i : i+4;
    int x0 = 5  + 28*(Pos%11);
    int y0 = 100 + 28*(Pos/11);
    char c = _acText[i];
    int Id = c ? c : 1;
    char ac[2] = {0};
    char *s= ac;
    ac[0] = c;
    ahButton[i] = BUTTON_Create( x0, y0, 25, 25, Id,BUTTON_CF_SHOW );
    BUTTON_SetText   (ahButton[i], s);
    #if GUI_SUPPORT_MEMDEV
      BUTTON_EnableMemdev(ahButton[i]);
    #endif
  }
  ahButton[i] = BUTTON_Create( 89, 212, 109, 25, ' ',BUTTON_CF_SHOW );
  hButtonESC = BUTTON_Create( 230, 40, 80, 25, GUI_ID_CANCEL,BUTTON_CF_SHOW );
  BUTTON_SetText   (hButtonESC, "ESC");
  hEdit = EDIT_Create( 5, 70, 310, 25, ' ', 80, 0 );
  EDIT_SetFont(hEdit, &GUI_Font8x16);
  BUTTON_SetBkColor(ahButton[49], 0, GUI_RED);
  BUTTON_SetBkColor(ahButton[50], 0, GUI_BLUE);
  /* Handle Keyboard until ESC or ENTER is pressed */
  do {
    Key = GUIDEMO_WaitKey();
    switch (Key) {
    case 0:
    case GUI_ID_CANCEL:
     break;
    default:
      EDIT_AddKey(hEdit, Key);
    }
  } while ((Key != 'N') && (Key!=GUI_ID_CANCEL) && (Key!=0));
  /* Cleanup */
  for (i=0; i< countof(ahButton); i++) {
    BUTTON_Delete(ahButton[i]);
  }
  BUTTON_Delete(hButtonESC);
  EDIT_Delete(hEdit);
  return Key;
}

#else

static char _acText[] = {
  '7','8','9','/',
  '4','5','6','*',
  '1','2','3','-',
  '0',',','+','=',0
};

int _ExecKeyboard(void) {
  int y0 = 75;
  int XSize = LCD_GetXSize();
  int YSize = LCD_GetYSize();
  int XStep = XSize / 4;
  int YStep = (YSize - y0) / 4;
  int i;
  int Key;
  BUTTON_Handle ahButton[16];
  BUTTON_Handle hButtonESC;
  EDIT_Handle   hEdit;
  GUI_RECT rText = {0};
  rText.x1 = LCD_GetXSize() - 3;
  rText.y1 = 20;
  GUI_SetBkColor(GUI_BLUE);  
  GUI_Clear();
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRect("�C/GUI", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
  rText.y0 +=20;
  rText.y1 +=20;
  GUI_DispStringInRect("Touch screen demo", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
  /* Create Keyboard Buttons */
  for (i=0; _acText[i]; i++) {
    int XPos = (i%4) * XStep + 3;
    int YPos = (i/4) * YStep + 3 + y0;
    char c = _acText[i];
    int Id = c ? c : 1;
    char ac[2] = {0};
    char *s= ac;
    ac[0] = c;
    ahButton[i] = BUTTON_Create( XPos, YPos, XStep - 5, YStep - 5, Id, BUTTON_CF_SHOW );
    BUTTON_SetText(ahButton[i], s);
    BUTTON_EnableMemdev(ahButton[i]);
  }
  hButtonESC = BUTTON_Create( 3, 3, 80, 25, GUI_ID_CANCEL, BUTTON_CF_SHOW );
  BUTTON_SetText(hButtonESC, "ESC");
  hEdit = EDIT_Create( 5, y0 - 30, XSize - 10, 25, ' ', 80, 0 );
  EDIT_SetFont(hEdit, &GUI_Font8x16);
  /* Handle Keyboard until ESC or ENTER is pressed */
  do {
    Key = GUIDEMO_WaitKey();
    switch (Key) {
    case 0:
    case GUI_ID_CANCEL:
     break;
    default:
      EDIT_AddKey(hEdit, Key);
    }
  } while ((Key != 'N') && (Key!=GUI_ID_CANCEL) && (Key!=0));
  /* Cleanup */
  for (i=0; i< countof(ahButton); i++) {
    BUTTON_Delete(ahButton[i]);
  }
  BUTTON_Delete(hButtonESC);
  EDIT_Delete(hEdit);
  return Key;
}

#endif

/*
**********************************************************************
*
*              USER_Task
*
**********************************************************************
*/

#if GUIDEMO_LARGE

void GUIDEMO_Touch(void) {
  #define ID_KEYBOARD  1
  #define ID_TESTCAL   2
  #define ID_CALIBRATE 3
  int i, r;
  int XSize = LCD_GetXSize();
  int YSize = LCD_GetYSize();
  int XMid = XSize / 2;
  int YMid = YSize / 2;
  GUIDEMO_NotifyStartNext();
  GUIDEMO_HideInfoWin();
  
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();

	GUI_SetFont(&GUI_Font16B_1);

	_ExecCalibration();
  
  
}

#else

void GUIDEMO_Touch(void) {}

#endif

#else

void GUIDEMO_Touch(void) {} /* avoid empty object files */

#endif /* #if GUI_WINSUPPORT */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
