/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;      /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 1;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"monospace:pixelsize=13:antialias=true:autohint=true",
	"Noto Color Emoji:pixelsize=12:style=regular:antialias=true:autohint=true",
	"Noto Sans CJK:pixelsize=13:style=regular:antialias=true:autohint=true"
};

/*static const char dmenufont[]       = "monospace:size=11:antialias=true:autohint=true";*/
static char normbgcolor[]           = "#091843";
static char normbordercolor[]       = "#0000b2";
static char normfgcolor[]           = "#0abdb6";
static char selfgcolor[]            = "#ffbb00";
static char selbordercolor[]        = "#0abdb6";
static char selbgcolor[]            = "#711da9";
static const char col_borderbar[]   = "#ea00d9";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = {
	">_",
	"🏫",
	"🚧",
	"🏢",
	"🛋️",
	"👫",
	"🖥️",
	"🎹",
	"🦊"
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "firefox",	 NULL,     NULL,           1 << 8,    0,          0,           0,        -1 },
	{ "Pd",			 NULL,     NULL,           1 << 7,    0,          0,           0,        -1 },
	{ "VirtualBox",	 NULL,     NULL,           1 << 6,    0,          0,           0,        -1 },
	{ "qBittorrent", NULL,     NULL,           1 << 5,    0,          0,           0,        -1 },
	{ "Bless",       NULL,     NULL,           1 << 2,    0,          0,           0,        -1 },
	{ "St",		     NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,		     NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 5;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "HHH",      grid },


	{ "TTT",      bstack },
	{ "H[]",      deck },
	{ ":::",      gaplessgrid },


	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[\\]",     dwindle },
	{ "---",      horizgrid },
/* These are not used
*	{ "|M|",      centeredmaster },
*	{ "---",      horizgrid },
*	{ ">M>",      centeredfloatingmaster },
*	{ ":::",      gaplessgrid },
*	{ "===",      bstackhoriz },
*	{ "[@]",      spiral },
	{ NULL,       NULL },*/
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
/*	"-fn", dmenufont,*/
/*	"-nb", normbgcolor,*/
/*	"-nf", normfgcolor,*/
/*	"-sb", selbgcolor,*/
/*	"-sf", selfgcolor,*/
	NULL
};
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x26", NULL };

#include "selfrestart.c"
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,           togglebar,      {0} },
	{ MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,           incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,           setmfact,       {.f = -0.025} },
	{ MODKEY,                       XK_l,           setmfact,       {.f = +0.025} },
	{ MODKEY,                       XK_v,           setcfact,       {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_v,           setcfact,       {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_d,           setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,			    XK_j,           movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,			    XK_k,           movestack,      {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_j,           incrgaps,       {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,           incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_m,           togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_m,           defaultgaps,    {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,           incrogaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_l,           incrogaps,      {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_j,           incrigaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,           incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_space,       zoom,           {0} },
	{ MODKEY,                       XK_Tab,         view,           {0} },
	{ MODKEY,                       XK_q,           killclient,     {0} },
	{ MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_c,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_f,           setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_c,           setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask|ControlMask, XK_t,           setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask|ControlMask, XK_f,           setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask|ControlMask, XK_c,           setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ControlMask,           XK_space,       setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
	{ MODKEY,                       XK_0,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,          xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ControlMask,           XK_BackSpace,   self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,		    quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
/*	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },*/
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

