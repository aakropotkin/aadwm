/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red_orange[]  = "#772200";
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_cyan,  col_red_organge  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class          instance    title       tags mask     isfloating   monitor */
  { "Gimp",         NULL,       NULL,       0,            1,           -1 },
  { "Firefox",      NULL,       NULL,       1 << 8,       0,           -1 },
  { "stalonetray",  NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]||",     tile_vsplit },  /* first entry is default */
  { "[]=",      tile_hsplit },
  { "[M]",      monocle },      /* Fullscreen mode */
  { "><>",      NULL },         /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,    view,          {.ui = 1 << TAG} },  \
  { MODKEY|ControlMask,           KEY,    toggleview,    {.ui = 1 << TAG} },  \
  { MODKEY|ShiftMask,             KEY,    tag,           {.ui = 1 << TAG} },  \
  { MODKEY|ControlMask|ShiftMask, KEY,    toggletag,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD( cmd ) { .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } }

/* Commands */
/* component of dmenucmd, manipulated in spawn() */
static char dmenumon[2] = "0";
static const char * dmenucmd[] = {
  "dmenu_run", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1,
               "-nf", col_gray3, "-sb", col_cyan,  "-sf", col_gray4, NULL
};
static const char * termcmd[]  = { "urxvtc", "-tr", "-sh", "8", NULL };
static const char * visualcmd[]  = { "my-emacs", NULL };
static const char * browsercmd[]  = { "firefox", NULL };
static const char * soundcmd[] = { "pavucontrol", NULL };

static Key keys[] = {
  /* modifier            key        function        argument */
  { MODKEY,              XK_p,      spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,    XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,              XK_f,      spawn,          {.v = termcmd } },
  { MODKEY,              XK_v,      spawn,          {.v = visualcmd } },
  { MODKEY,              XK_g,      spawn,          {.v = browsercmd } },
  { MODKEY,              XK_b,      togglebar,      {0} },
  { MODKEY,              XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,              XK_k,      focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,    XK_j,      incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,    XK_k,      incnmaster,     {.i = -1 } },
  //{ MODKEY,              XK_i,      incnmaster,     {.i = +1 } },
  //{ MODKEY,              XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,              XK_d,      spawn,          {.v = soundcmd } },
  { MODKEY,              XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,              XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,              XK_Return, zoom,           {0} },
  //{ MODKEY,              XK_Tab,    view,           {0} },
  { MODKEY,              XK_Tab,    focusstack,     {.i = +1 } },
  //{ MODKEY|ShiftMask,    XK_c,      killclient,     {0} },
  { MODKEY,              XK_grave,  killclient,     {0} },
  { MODKEY,              XK_Escape, killclient,     {0} },
  //{ MODKEY,              XK_t,      setlayout,      {.v = &layouts[0]} },
  //{ MODKEY,              XK_f,      setlayout,      {.v = &layouts[1]} },
  //{ MODKEY,              XK_m,      setlayout,      {.v = &layouts[2]} },
  //{ MODKEY,              XK_space,  setlayout,      {0} },
  /* Fullscreen layout */
  { MODKEY|ShiftMask,    XK_f,      setlayout,      {.v = &layouts[2]} },
  /* Cycle layouts */
  { MODKEY,              XK_space,  inclayout,      {.i = 1} },
  { MODKEY|ShiftMask,    XK_space,  togglefloating, {0} },
  { MODKEY,              XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,    XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,              XK_w,      focusmon,       {.ui = Mon0 } },
  { MODKEY,              XK_e,      focusmon,       {.ui = Mon1 } },
  { MODKEY,              XK_r,      focusmon,       {.ui = Mon2 } },
  { MODKEY,              XK_comma,  focusmon,       {.ui = MonPrev } },
  { MODKEY,              XK_period, focusmon,       {.ui = MonNext } },
  { MODKEY|ShiftMask,    XK_w,      tagmon,         {.ui = Mon0 } },
  { MODKEY|ShiftMask,    XK_e,      tagmon,         {.ui = Mon1 } },
  { MODKEY|ShiftMask,    XK_r,      tagmon,         {.ui = Mon2 } },
  { MODKEY|ShiftMask,    XK_comma,  tagmon,         {.ui = MonPrev } },
  { MODKEY|ShiftMask,    XK_period, tagmon,         {.ui = MonNext } },
  TAGKEYS(               XK_1,                      0)
  TAGKEYS(               XK_2,                      1)
  TAGKEYS(               XK_3,                      2)
  TAGKEYS(               XK_4,                      3)
  TAGKEYS(               XK_5,                      4)
  TAGKEYS(               XK_6,                      5)
  TAGKEYS(               XK_7,                      6)
  TAGKEYS(               XK_8,                      7)
  TAGKEYS(               XK_9,                      8)
  { MODKEY|ShiftMask,    XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click          event mask  button     function        argument */
  { ClkLtSymbol,    0,          Button1,   setlayout,      {0} },
  { ClkLtSymbol,    0,          Button3,   setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,    0,          Button2,   zoom,           {0} },
  { ClkStatusText,  0,          Button2,   spawn,          {.v = termcmd } },
  { ClkClientWin,   MODKEY,     Button1,   movemouse,      {0} },
  { ClkClientWin,   MODKEY,     Button2,   togglefloating, {0} },
  { ClkClientWin,   MODKEY,     Button3,   resizemouse,    {0} },
  { ClkTagBar,      0,          Button1,   view,           {0} },
  { ClkTagBar,      0,          Button3,   toggleview,     {0} },
  { ClkTagBar,      MODKEY,     Button1,   tag,            {0} },
  { ClkTagBar,      MODKEY,     Button3,   toggletag,      {0} },
};

/* vim: set cc= : */
