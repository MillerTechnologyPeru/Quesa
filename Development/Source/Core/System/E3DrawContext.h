/*  NAME:
        E3DrawContext.h

    DESCRIPTION:
        Header file for E3DrawContext.c.

    COPYRIGHT:
        Quesa Copyright � 1999-2001, Quesa Developers.
        
        For the list of Quesa Developers, and contact details, see:
        
            Documentation/contributors.html

        For the current version of Quesa, see:

        	<http://www.quesa.org/>

		This library is free software; you can redistribute it and/or
		modify it under the terms of the GNU Lesser General Public
		License as published by the Free Software Foundation; either
		version 2 of the License, or (at your option) any later version.

		This library is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
		Lesser General Public License for more details.

		You should have received a copy of the GNU Lesser General Public
		License along with this library; if not, write to the Free Software
		Foundation Inc, 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
    ___________________________________________________________________________
*/
#ifndef E3DRAWCONTEXT_HDR
#define E3DRAWCONTEXT_HDR
//=============================================================================
//      Include files
//-----------------------------------------------------------------------------
// Include files go here





//=============================================================================
//		C++ preamble
//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif





//=============================================================================
//      Public types
//-----------------------------------------------------------------------------
// Forward declaration
typedef struct TQ3DrawContextUnionData *TQ3DrawContextUnionDataPtr;



// Definition of TQ3XDrawRegion
typedef struct OpaqueTQ3XDrawRegion {
	// Link back to owning draw context's draw region list
	TQ3Uns32									ownerIndex;
	TQ3DrawContextUnionDataPtr					theOwner;


	// State
	float										deviceScaleX;
	float										deviceScaleY;
	float										deviceOffsetX;
	float										deviceOffsetY;
	float										windowScaleX;
	float										windowScaleY;
	float										windowOffsetX;
	float										windowOffsetY;
	TQ3Matrix4x4								deviceTransform;
	TQ3Boolean									isActive;
	TQ3Bitmap									clipMask;
	TQ3XClipMaskState							clipMaskState;
	TQ3Uns32									platformClip;
	TQ3Uns32									platformHandle;
	TQ3Boolean									useDefaultRenderer;
	TQ3XDrawRegionDescriptor					theDescriptor;
	void										*imageBuffer;
	void										*rendererPrivate;
	TQ3XDrawRegionRendererPrivateDeleteMethod	rendererPrivateDelete;
} OpaqueTQ3XDrawRegion;



// Draw context state
#if QUESA_OS_MACINTOSH
typedef struct {
	TQ3MacDrawContextData			theData;
	Rect							windowRect;
	RgnHandle						visRgn;
} TQ3MacDrawContextState;


#elif QUESA_OS_UNIX
typedef struct OpaqueTQ3XBufferObject {
	TQ3Uns32						numBuffers;
	Display							*theDisplay;
	Window							theWindow;
} OpaqueTQ3XBufferObject;

typedef struct {
	TQ3XDrawContextData				theData;
} TQ3XDrawContextState;


#elif QUESA_OS_WIN32
typedef struct {
	TQ3Win32DCDrawContextData		theData;
} TQ3Win32DCDrawContextState;

typedef struct {
	TQ3DDSurfaceDrawContextData		theData;
} TQ3DDSurfaceDrawContextState;


#elif QUESA_OS_BE
typedef struct {
	TQ3BeDrawContextData			theData;
} TQ3BeDrawContextState;


#elif QUESA_OS_COCOA
typedef struct {
	TQ3CocoaDrawContextData			theData;
} TQ3CocoaDrawContextState;

#endif



// Draw context data
typedef struct TQ3DrawContextUnionData {
	// Common data
	TQ3XDrawContextValidation			theState;
	TQ3Uns32							numDrawRegions;
	OpaqueTQ3XDrawRegion				*drawRegions;


	// Platform specific. Note that we assume that a TQ3DrawContextData
	// structure is the first item within each draw context structure,
	// since this lets us use a union and have the common data overlap.
	union	{
		TQ3DrawContextData 				common;
		TQ3PixmapDrawContextData		pixmapData;

#if QUESA_OS_MACINTOSH
		TQ3MacDrawContextState			macData;

#elif QUESA_OS_UNIX
		TQ3XDrawContextState			x11Data;

#elif QUESA_OS_WIN32
		TQ3Win32DCDrawContextState		win32Data;
		TQ3DDSurfaceDrawContextState	winDDData;

#elif QUESA_OS_BE
		TQ3BeDrawContextState			beData;

#elif QUESA_OS_COCOA
		TQ3CocoaDrawContextState		cocoaData;
#endif
	} data;
} TQ3DrawContextUnionData;





//=============================================================================
//      Function prototypes
//-----------------------------------------------------------------------------
// Cross platform
TQ3Status				E3DrawContext_RegisterClass(void);
TQ3Status				E3DrawContext_UnregisterClass(void);
TQ3Status				E3DrawContext_Update(TQ3DrawContextObject drawContext);
void					E3DrawContext_ResetState(TQ3DrawContextObject drawContext);
TQ3Status				E3DrawContext_CreateRegions(TQ3DrawContextObject drawContext, TQ3Uns32 numRegions);
TQ3XDevicePixelType		E3DrawContext_GetDevicePixelTypeFromBPP(TQ3Uns32 pixelSize);
TQ3XDevicePixelType		E3DrawContext_GetDevicePixelTypeFromQD3DType(TQ3PixelType qd3dType);

TQ3ObjectType			E3DrawContext_GetType(TQ3DrawContextObject drawContext);
TQ3Status				E3DrawContext_SetData(TQ3DrawContextObject drawContext, const TQ3DrawContextData *contextData);
TQ3Status				E3DrawContext_GetData(TQ3DrawContextObject drawContext, TQ3DrawContextData *contextData);
TQ3Status				E3DrawContext_SetClearImageColor(TQ3DrawContextObject drawContext, const TQ3ColorARGB *color);
TQ3Status				E3DrawContext_GetClearImageColor(TQ3DrawContextObject drawContext, TQ3ColorARGB *color);
TQ3Status				E3DrawContext_SetPane(TQ3DrawContextObject drawContext, const TQ3Area *pane);
TQ3Status				E3DrawContext_GetPane(TQ3DrawContextObject drawContext, TQ3Area *pane);
TQ3Status				E3DrawContext_SetPaneState(TQ3DrawContextObject drawContext, TQ3Boolean state);
TQ3Status				E3DrawContext_GetPaneState(TQ3DrawContextObject drawContext, TQ3Boolean *state);
TQ3Status				E3DrawContext_SetClearImageMethod(TQ3DrawContextObject drawContext, TQ3DrawContextClearImageMethod method);
TQ3Status				E3DrawContext_GetClearImageMethod(TQ3DrawContextObject drawContext, TQ3DrawContextClearImageMethod *method);
TQ3Status				E3DrawContext_SetMask(TQ3DrawContextObject drawContext, const TQ3Bitmap *mask);
TQ3Status				E3DrawContext_GetMask(TQ3DrawContextObject drawContext, TQ3Bitmap *mask);
TQ3Status				E3DrawContext_SetMaskState(TQ3DrawContextObject drawContext, TQ3Boolean state);
TQ3Status				E3DrawContext_GetMaskState(TQ3DrawContextObject drawContext, TQ3Boolean *state);
TQ3Status				E3DrawContext_SetDoubleBufferState(TQ3DrawContextObject drawContext, TQ3Boolean state);
TQ3Status				E3DrawContext_GetDoubleBufferState(TQ3DrawContextObject drawContext, TQ3Boolean *state);

TQ3DrawContextObject	E3PixmapDrawContext_New(const TQ3PixmapDrawContextData *drawContextData);
TQ3Status				E3PixmapDrawContext_SetPixmap(TQ3DrawContextObject drawContext, const TQ3Pixmap *pixmap);
TQ3Status				E3PixmapDrawContext_GetPixmap(TQ3DrawContextObject drawContext, TQ3Pixmap *pixmap);


// Mac specific
#if QUESA_OS_MACINTOSH
TQ3Status				E3MacDrawContext_RegisterClass(void);
TQ3Status				E3MacDrawContext_UnregisterClass(void);

TQ3DrawContextObject	E3MacDrawContext_New(const TQ3MacDrawContextData *drawContextData);
TQ3Status				E3MacDrawContext_SetWindow(TQ3DrawContextObject drawContext, CWindowPtr window);
TQ3Status				E3MacDrawContext_GetWindow(TQ3DrawContextObject drawContext, CWindowPtr *window);
TQ3Status				E3MacDrawContext_SetGXViewPort(TQ3DrawContextObject drawContext, gxViewPort viewPort);
TQ3Status				E3MacDrawContext_GetGXViewPort(TQ3DrawContextObject drawContext, gxViewPort *viewPort);
TQ3Status				E3MacDrawContext_SetGrafPort(TQ3DrawContextObject drawContext, CGrafPtr grafPort);
TQ3Status				E3MacDrawContext_GetGrafPort(TQ3DrawContextObject drawContext, CGrafPtr *grafPort);
TQ3Status				E3MacDrawContext_Set2DLibrary(TQ3DrawContextObject drawContext, TQ3MacDrawContext2DLibrary library);
TQ3Status				E3MacDrawContext_Get2DLibrary(TQ3DrawContextObject drawContext, TQ3MacDrawContext2DLibrary *library);
#endif


// Unix specific
#if QUESA_OS_UNIX
TQ3Status				E3XDrawContext_RegisterClass(void);
TQ3Status				E3XDrawContext_UnregisterClass(void);

TQ3DrawContextObject	E3XDrawContext_New(const TQ3XDrawContextData * xContextData);
TQ3Status				E3XDrawContext_SetDisplay(TQ3DrawContextObject drawContext, const Display *display);
TQ3Status				E3XDrawContext_GetDisplay(TQ3DrawContextObject drawContext, Display **display);
TQ3Status				E3XDrawContext_SetDrawable(TQ3DrawContextObject drawContext, Drawable drawable);
TQ3Status				E3XDrawContext_GetDrawable(TQ3DrawContextObject drawContext, Drawable *drawable);
TQ3Status				E3XDrawContext_SetVisual(TQ3DrawContextObject drawContext, const Visual *visual);
TQ3Status				E3XDrawContext_GetVisual(TQ3DrawContextObject drawContext, Visual **visual);
TQ3Status				E3XDrawContext_SetColormap(TQ3DrawContextObject drawContext, Colormap colormap);
TQ3Status				E3XDrawContext_GetColormap(TQ3DrawContextObject drawContext, Colormap *colormap);
TQ3Status				E3XDrawContext_SetColormapData(TQ3DrawContextObject drawContext, const TQ3XColormapData *colormapData);
TQ3Status				E3XDrawContext_GetColormapData(TQ3DrawContextObject drawContext, TQ3XColormapData *colormapData);
TQ3XBufferObject		E3XBuffers_New(Display *dpy, TQ3Uns32 numBuffers, Window window);
void					E3XBuffers_Swap(Display *dpy, TQ3XBufferObject buffers);
XVisualInfo			   *E3X_GetVisualInfo(Display *dpy, Screen *screen);
#endif


// Windows specific
#if QUESA_OS_WIN32
TQ3Status				E3Win32DCDrawContext_RegisterClass(void);
TQ3Status				E3Win32DCDrawContext_UnregisterClass(void);

TQ3DrawContextObject	E3Win32DCDrawContext_New(const TQ3Win32DCDrawContextData *drawContextData);
TQ3Status				E3Win32DCDrawContext_SetDC(TQ3DrawContextObject drawContext, HDC newHDC);
TQ3Status				E3Win32DCDrawContext_GetDC(TQ3DrawContextObject drawContext, HDC *curHDC);

TQ3Status				E3DDSurfaceDrawContext_RegisterClass(void);
TQ3Status				E3DDSurfaceDrawContext_UnregisterClass(void);

TQ3DrawContextObject	E3DDSurfaceDrawContext_New(const TQ3DDSurfaceDrawContextData *drawContextData);
TQ3Status				E3DDSurfaceDrawContext_SetDirectDrawSurface(TQ3DrawContextObject drawContext, const TQ3DDSurfaceDescriptor *ddSurfaceDescriptor);
TQ3Status				E3DDSurfaceDrawContext_GetDirectDrawSurface(TQ3DrawContextObject drawContext, TQ3DDSurfaceDescriptor *ddSurfaceDescriptor);
#endif


// Be specific
#if QUESA_OS_BE
TQ3Status				E3BeDrawContext_RegisterClass(void);
TQ3Status				E3BeDrawContext_UnregisterClass(void);

TQ3DrawContextObject	E3BeDrawContext_New(const TQ3BeDrawContextData *drawContextData);
TQ3Status				E3BeDrawContext_SetView(TQ3DrawContextObject drawContext, BView *theView);
TQ3Status				E3BeDrawContext_GetView(TQ3DrawContextObject drawContext, BView **theView);
#endif


// Cocoa specific
#if QUESA_OS_COCOA
TQ3Status				E3CocoaDrawContext_RegisterClass(void);
TQ3Status				E3CocoaDrawContext_UnregisterClass(void);

TQ3DrawContextObject	E3CocoaDrawContext_New(const TQ3CocoaDrawContextData *drawContextData);
TQ3Status				E3CocoaDrawContext_SetNSView(TQ3DrawContextObject drawContext, void *nsView);
TQ3Status				E3CocoaDrawContext_GetNSView(TQ3DrawContextObject drawContext, void **nsView);
#endif





//=============================================================================
//		C++ postamble
//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif

