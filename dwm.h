/* ========================================================================== *
 *
 *
 *
 * -------------------------------------------------------------------------- */

#ifndef _DWM_H
#  define _DWM_H 1

/* -------------------------------------------------------------------------- */

#  include <X11/Xatom.h>
#  include <X11/Xlib.h>
#  include <X11/Xproto.h>
#  include <X11/Xutil.h>
#  include <X11/keysym.h>


/* -------------------------------------------------------------------------- */

/* enums */
enum { CurNormal, CurResize, CurMove, CurLast }; /* cursor */
enum { SchemeNorm, SchemeSel };                  /* color schemes */
enum { NetSupported, NetWMName, NetWMState, NetWMCheck,
       NetSystemTray, NetSystemTrayOP, NetSystemTrayOrientation,
       NetSystemTrayOrientationHorz, NetWMFullscreen, NetActiveWindow,
       NetWMWindowType, NetWMWindowTypeDialog, NetClientList, NetLast
}; /* EWMH atoms */
enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast }; /* default atoms */
enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */
enum { MonPrev, MonNext, Mon0, Mon1, Mon2 }; /* Monitors */


/* -------------------------------------------------------------------------- */

typedef struct
{
  const char * r_class;
  const char * instance;
  const char * title;
  unsigned int tags;
  int          isfloating;
  int          monitor;
} Rule;


/* -------------------------------------------------------------------------- */

typedef union
{
  int          i;
  unsigned int ui;
  float        f;
  const void * v;
} Arg;


/* -------------------------------------------------------------------------- */

typedef struct
{
  unsigned int click;
  unsigned int mask;
  unsigned int button;
  void ( *func )( const Arg * arg );
  const Arg arg;
} Button;


/* -------------------------------------------------------------------------- */

typedef struct Clientlist Clientlist;
typedef struct Monitor    Monitor;
typedef struct Client     Client;
struct Client
{
  char         name[256];
  float        mina, maxa;
  int          x, y, w, h;
  int          oldx, oldy, oldw, oldh;
  int          basew, baseh, incw, inch, maxw, maxh, minw, minh;
  int          bw, oldbw;
  unsigned int tags;
  int       isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
  Client *  next;
  Client *  snext;
  Monitor * mon;
  Window    win;
};


/* -------------------------------------------------------------------------- */

struct Clientlist
{
  Client * clients;
  Client * stack;
};


/* -------------------------------------------------------------------------- */

typedef struct
{
  unsigned int mod;
  KeySym       keysym;
  void ( *func )( const Arg * );
  const Arg arg;
} Key;


/* -------------------------------------------------------------------------- */

typedef struct
{
  const char * symbol;
  void ( *arrange )( Monitor * );
} Layout;


/* -------------------------------------------------------------------------- */

struct Monitor
{
  char           ltsymbol[16];
  float          mfact;
  int            nmaster;
  int            num;
  int            by;             /* bar geometry */
  int            mx, my, mw, mh; /* screen size */
  int            wx, wy, ww, wh; /* window area  */
  unsigned int   seltags;
  unsigned int   sellt;
  unsigned int   tagset[2];
  int            showbar;
  int            topbar;
  Clientlist *   cl;
  Client *       sel;
  Monitor *      next;
  Window         barwin;
  const Layout * lt[2];
};


/* -------------------------------------------------------------------------- */

#  define noop ( (void) 0 )


/* -------------------------------------------------------------------------- */

int
sendevent( Window w,
           Atom   proto,
           int    m,
           long   d0,
           long   d1,
           long   d2,
           long   d3,
           long   d4 );


/* -------------------------------------------------------------------------- */

int
applysizehints( Client * c, int * x, int * y, int * w, int * h, int interact );


/* -------------------------------------------------------------------------- */

Atom
getatomprop( Client * c, Atom prop );


/* -------------------------------------------------------------------------- */

void
setclientstate( Client * c, long state );


/* -------------------------------------------------------------------------- */

#  define TEXTW( X ) ( drw_fontset_getwidth( drw, ( X ) ) + lrpad )


/* -------------------------------------------------------------------------- */

#endif /* ifndef _DWM_H */

/* -------------------------------------------------------------------------- *
 *
 *
 *
 * ========================================================================== */
