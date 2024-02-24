/* ========================================================================== *
 *
 *
 *
 * -------------------------------------------------------------------------- */

#ifndef _SYSTRAY_H
#  define _SYSTRAY_H 1

/* -------------------------------------------------------------------------- */

#  include "dwm.h"

/* -------------------------------------------------------------------------- */

#  define SYSTEM_TRAY_REQUEST_DOCK 0
/* XEMBED messages */
#  define XEMBED_EMBEDDED_NOTIFY   0
#  define XEMBED_WINDOW_ACTIVATE   1
#  define XEMBED_FOCUS_IN          4
#  define XEMBED_MODALITY_ON       10
#  define XEMBED_MAPPED            ( 1 << 0 )
#  define XEMBED_WINDOW_ACTIVATE   1
#  define XEMBED_WINDOW_DEACTIVATE 2
#  define VERSION_MAJOR            0
#  define VERSION_MINOR            0
#  define XEMBED_EMBEDDED_VERSION  ( VERSION_MAJOR << 16 ) | VERSION_MINOR


/* -------------------------------------------------------------------------- */

enum { Manager, Xembed, XembedInfo, XLast }; /* Xembed atoms */


/* -------------------------------------------------------------------------- */

typedef struct
{
  Window   win;
  Client * icons;
} Systray;


/* -------------------------------------------------------------------------- */

unsigned int
getsystraywidth();

void
removesystrayicon( Client * i );

void
resizebarwin( Monitor * m );

void
resizerequest( XEvent * e );

Monitor *
systraytomon( Monitor * m );

void
updatesystray( void );

void
updatesystrayicongeom( Client * i, int w, int h );

void
updatesystrayiconstate( Client * i, XPropertyEvent * ev );

Client *
wintosystrayicon( Window w );


/* -------------------------------------------------------------------------- */

static Systray * systray = NULL;
static Atom      xatom[XLast];


/* -------------------------------------------------------------------------- */

#endif /* ifndef _SYSTRAY_H */

/* -------------------------------------------------------------------------- *
 *
 *
 *
 * ========================================================================== */
