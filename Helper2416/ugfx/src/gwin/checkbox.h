/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/**
 * @file    src/gwin/checkbox.h
 * @brief   GWIN Graphic window subsystem header file.
 *
 * @defgroup Checkbox Checkbox
 * @ingroup Widgets
 *
 * @details		GWIN allows it to easily create a group of checkbox buttons.
 *
 * @pre			GFX_USE_GWIN must be set to TRUE in your gfxconf.h
 * @pre			GWIN_NEED_CHECKBOX must be set to TRUE in your gfxconf.h
 * @{
 */

#ifndef _GWIN_CHECKBOX_H
#define _GWIN_CHECKBOX_H

/* This file is included within "gwin/gwidget.h" */

/*===========================================================================*/
/* Driver constants.														 */
/*===========================================================================*/

#define GEVENT_GWIN_CHECKBOX		(GEVENT_GWIN_FIRST+2)

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

typedef struct GEventGWinCheckbox {
	GEventType		type;			// The type of this event (GEVENT_GWIN_CHECKBOX)
	GHandle			checkbox;		// The checkbox that has been depressed (actually triggered on release)
	bool_t			isChecked;		// Is the checkbox currently checked or unchecked?
	#if GWIN_WIDGET_TAGS
		WidgetTag	tag;			// The checkbox tag
	#endif
} GEventGWinCheckbox;

/* A Checkbox window */
typedef struct GCheckboxObject {
	GWidgetObject			w;
	#if GINPUT_NEED_TOGGLE
		uint16_t			toggle;
	#endif
} GCheckboxObject;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief				Create a checkbox window.
 * @return				NULL if there is no resultant drawing area, otherwise a window handle.
 *
 * @param[in] g			The GDisplay to display this window on
 * @param[in] gb		The GCheckboxObject structure to initialise. If this is NULL, the structure is dynamically allocated.
 * @param[in] pInit		The initialization parameters to use
 *
 * @note				The drawing color and the background color get set to the current defaults. If you haven't called
 * 						@p gwinSetDefaultColor() or @p gwinSetDefaultBgColor() then these are White and Black respectively.
 * @note				The font gets set to the current default font. If you haven't called @p gwinSetDefaultFont() then there
 * 						is no default font and text drawing operations will no nothing.
 * @note				A checkbox remembers its normal drawing state. If there is a window manager then it is automatically
 * 						redrawn if the window is moved or its visibility state is changed.
 * @note				A checkbox supports mouse and a toggle input.
 * @note				When assigning a toggle, only one toggle is supported. If you try to assign more than one toggle it will
 * 						forget the previous toggle. When assigning a toggle the role parameter must be 0.
 *
 * @api
 */
GHandle gwinGCheckboxCreate(GDisplay *g, GCheckboxObject *gb, const GWidgetInit *pInit);
#define gwinCheckboxCreate(gb, pInit)			gwinGCheckboxCreate(GDISP, gb, pInit)

/**
 * @brief	Set the state of a checkbox
 *
 * @param[in] gh		The window handle (must be a checkbox window)
 * @param[in] isChecked	TRUE to set the check, FALSE to uncheck.
 *
 * @api
 */
void gwinCheckboxCheck(GHandle gh, bool_t isChecked);

/**
 * @brief	Get the state of a checkbox
 * @return	TRUE if the checkbox is currently checked
 *
 * @param[in] gh	The window handle (must be a checkbox window)
 *
 * @api
 */
bool_t gwinCheckboxIsChecked(GHandle gh);

/**
 * @brief	Some custom checkbox drawing routines
 * @details	These function may be passed to @p gwinSetCustomDraw() to get different checkbox drawing styles
 *
 * @param[in] gw			The widget (which must be a checkbox)
 * @param[in] param			A parameter passed in from the user
 *
 * @note				In your custom checkbox drawing function you may optionally call this
 * 						standard functions and then draw your extra details on top.
 * @note				The standard functions below ignore the param parameter.
 * @note				These custom drawing routines don't have to worry about setting clipping as the framework
 * 						sets clipping to the object window prior to calling these routines.
 *
 * @api
 * @{
 */
void gwinCheckboxDraw_CheckOnLeft(GWidgetObject *gw, void *param);
void gwinCheckboxDraw_CheckOnRight(GWidgetObject *gw, void *param);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _GWIN_CHECKBOX_H */
/** @} */

