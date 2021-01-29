/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const int gappx              = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "hack nerd font:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "hack nerd font:pixelsize=14:antialias=true:autohint=true" ;
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#3A3A3A";
static const char col_gray3[]       = "#f9f5d7";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#458588";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "F1", "F2", "F3", "F4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-b" , "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray1, NULL };
static const char *clipmenucmd[] = { "clipmenu", "-b" , "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray1 , NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "nextprevtag.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_slash,  spawn,          {.v = clipmenucmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    { MODKEY,                       XK_Right,  view_adjacent,  {.i = +1 } },
	{ MODKEY,                       XK_Left,   view_adjacent,  {.i = -1 } },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("=")},
	{ MODKEY,                       XK_r,      spawn,          SHCMD("st repoManager")},
	{ MODKEY,                       XK_u,      spawn,          SHCMD("st syu")},
	{ MODKEY,                       XK_a,      spawn,          SHCMD("connectAukey")},
	{ MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("disconnectAukey")},
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("st ranger")},
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("st translate")},
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("st ncmpcpp")},
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("firefox")},
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("discord")},
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("powerButton")},
	{ 0,                XF86XK_AudioPlay,      spawn,          SHCMD("mpc toggle")},
	{ 0,                XF86XK_AudioNext,      spawn,          SHCMD("mpc next")},
	{ 0,                XF86XK_AudioPrev,      spawn,          SHCMD("mpc prev")},
	{ ShiftMask, XF86XK_AudioRaiseVolume,      spawn,          SHCMD("mpc volume +5") },
	{ ShiftMask, XF86XK_AudioLowerVolume,      spawn,          SHCMD("mpc volume -5") },			
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          SHCMD("amixer set Master 5%+ && bar_signal_volume") },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          SHCMD("amixer set Master 5%- && bar_signal_volume") },			
    { 0,                XF86XK_AudioMute,      spawn,          SHCMD("amixer set Master toggle && bar_signal_volume") },
	{ 0,             XF86XK_AudioMicMute,      spawn,          SHCMD("amixer set Capture toggle && bar_signal_microphone") },	
    { 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight +5 && bar_signal_brightness") },
    { 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -5 && bar_signal_brightness") },
    { 0,               XF86XK_Calculator,      spawn,          SHCMD("=") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_F1,                     9)
	TAGKEYS(                        XK_F2,                     10)
	TAGKEYS(                        XK_F3,                     11)
	TAGKEYS(                        XK_F4,                     12)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        spawn,          SHCMD("bar_signal_all")},
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

