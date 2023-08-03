/* this Fredo config base on ls */


/* Constants */

#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 0;       /* horiz inner gap between windows */
static unsigned int gappiv    = 0;       /* vert inner gap between windows */
static unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
/*static char *fonts[]          = { "monospace:size=14", "JoyPixels:pixelsize=14:antialias=true:autohint=true"  };*/
static char *fonts[]          = { "monospace:size=14", "Noto Emoji:pixelsize=14:antialias=true:autohint=true"  };
static char blackcolor[]            = "#222222";
static char darckgreycolor[]        = "#444444";
static char lightgreycolor[]        = "#bbbbbb";
static char whitecolor[]            = "#eeeeee";
static char redcolor[]		    = "#E01B24";
static char greencolor[]            = "#668800";
static char orangecolor[]	    = "#F6D32D";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { lightgreycolor, blackcolor, orangecolor},
       [SchemeSel]  = { whitecolor,  greencolor,  redcolor},
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    	instance      	title			tags mask    iscentered isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     	NULL,       	NULL,			1 << 8,      0,			0,           0,         0,        -1 },
	{ TERMCLASS,   	NULL,       	NULL,			0,           0,			0,           1,         0,        -1 },
	{ NULL,       	NULL,       	"Event Tester", 0,           0,			0,           0,         1,        -1 },
	{ NULL,      	"spterm",    	NULL,			SPTAG(0),    0,			1,           1,         0,        -1 },
	{ NULL,      	"spcalc",    	NULL,			SPTAG(1),    0,			1,           1,         0,        -1 },
	{ "Yad",      	NULL,    		NULL,			0,     		 1,			1,           0,         0,        -1 },
	{ "Float",      NULL,    		NULL,			0,     		 1,			1,           1,         1,        -1 },
	{ "Galculator", NULL,   		NULL,			0,     		 1,			1,           0,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* first entry is default */
	{ "[MM]",	  deck },	
	{ "[T]",      tile },   
	{ "TTT",      bstack },
	{ "[O]",      centeredmaster },
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_Tab,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,	XK_asciicircum,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_0,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",			INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",			INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",			FLOAT,	&mfact },
		{ "gappih",			INTEGER, &gappih },
		{ "gappiv",			INTEGER, &gappiv },
		{ "gappoh",			INTEGER, &gappoh },
		{ "gappov",			INTEGER, &gappov },
		{ "swallowfloating",INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"
/* https://docs.google.com/spreadsheets/d/1HsP2AfAbIopBjZm4lew0Bs9YKmubKwEkZgyM-aI_1IM/edit#gid=1573427848  */
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)

	TAGKEYS(				XK_F1,		0)
	TAGKEYS(				XK_F2,		1)
	TAGKEYS(				XK_F3,		2)
	TAGKEYS(				XK_F4,		3)

	{ MODKEY,				XK_F5,		spawn,		SHCMD("xbacklight -dec 200;kill -44 $(pidof dwmblocks)") },
	{ MODKEY,				XK_F6,		spawn,		SHCMD("xbacklight -inc 200;kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,				XK_F2,		spawn,		SHCMD("pamixer --allow-boost -d 10; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,				XK_F3,		spawn,		SHCMD("pamixer --allow-boost -i 10; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,				XK_space,	zoom,		{0} },
	{ MODKEY,				XK_f,		togglefloating,	{0} },		
	{ MODKEY,				XK_m,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_m,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,				XK_t,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[3]} },
 	{ MODKEY,				XK_o,		setlayout,	{.v = &layouts[4]} },

	{ MODKEY,				XK_h,		setmfact,       {.f = -0.05} }, 	
	{ MODKEY,				XK_l,		setmfact,       {.f = +0.05} },
	{ MODKEY,				XK_b,		togglebar,	{0} },
	{ MODKEY,				XK_g,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_g,		defaultgaps,	{0} },
	{ MODKEY,				XK_q,		killclient,	{0} },
	{ MODKEY|ShiftMask,		XK_q,		quit,		{0} },

	//{ MODKEY,				XK_e,		spawn,          SHCMD("emoji -p") },
	//{ MODKEY|ShiftMask,		XK_e,		spawn,          SHCMD("emoji") },
	//{ MODKEY,				XK_n,		spawn,          SHCMD(TERMINAL " -e vifm") },
	//{ MODKEY|ShiftMask,		XK_n,		spawn,          SHCMD("nautilus") },
	//{ MODKEY,				XK_s,		spawn,			SHCMD("snip") },
	//{ MODKEY|ShiftMask,		XK_s,		spawn,			SHCMD("systemctl suspend") },
	//{ MODKEY,				XK_r,		spawn,          SHCMD("rofi -show drun") },
	//{ MODKEY,				XK_v,		spawn,			SHCMD("clipmenuw") },
	//{ MODKEY|ShiftMask,		XK_v,		spawn,			SHCMD("clipmenu") },
	//{ MODKEY,				XK_w,		spawn,			SHCMD("$BROWSER") },
	//{ MODKEY|ShiftMask,		XK_w,		spawn,			SHCMD("$BROWSER2") },
	//{ MODKEY,				XK_y,		spawn,			SHCMD("passmenu") },
	//{ MODKEY|ShiftMask,		XK_y,		spawn,			SHCMD("passmenu --type") },
	//{ MODKEY,				XK_Return,	spawn,		{.v = termcmd } },

	{ 0, 					XF86XK_AudioMute,			spawn,			SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },					// volume mute
	{ 0, 					XF86XK_AudioRaiseVolume,	spawn,			SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },	// volume increase
	{ 0, 					XF86XK_AudioLowerVolume,	spawn,			SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") }, // volume decrease
	{ 0, 					XF86XK_AudioPrev,			spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ 0, 					XF86XK_AudioNext,			spawn,		{.v = (const char*[]){ "mpc",  "next", NULL } } },
	{ 0, 					XF86XK_AudioPause,			spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ 0, 					XF86XK_AudioPlay,			spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ 0, 					XF86XK_AudioStop,			spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ 0, 					XF86XK_AudioRewind,			spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0, 					XF86XK_AudioForward,		spawn,		{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	
	{ 0, 					XF86XK_Launch2,				spawn,		SHCMD("rofi -show drun") },
	{ 0, 					XF86XK_Favorites,			spawn,		SHCMD("rofi -show drun") },
	{ 0, 					XF86XK_MonBrightnessDown,			spawn,		SHCMD("xbacklight -dec 200;kill -44 $(pidof dwmblocks)") },
	{ 0, 					XF86XK_MonBrightnessUp,			spawn,			SHCMD("xbacklight -inc 200;kill -44 $(pidof dwmblocks)") },

};

/* button definitions */ 
/* click can be 

ClkLtSymbol, 


ClkWinTitle, 

, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} }, // left click 
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} }, // middle click
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} }, // right click
	
	{ ClkStatusText,        0,				Button4,        sigdwmblocks,   {.i = 4} }, // mouse scroll down
	{ ClkStatusText,        0,     			Button5,        sigdwmblocks,   {.i = 5} }, // mouse scroll up

	{ ClkStatusText,        ShiftMask,		Button1,        sigdwmblocks,   {.i = 6} }, // left click + shift
	{ ClkStatusText,        ShiftMask,      Button2,        sigdwmblocks,   {.i = 7} }, // middle click + shift
	{ ClkStatusText,        ShiftMask,      Button3,        sigdwmblocks,   {.i = 8} }, // right click + shift


#endif

	// ClkWinTitle
	{ ClkWinTitle,        MODKEY,		Button1,        spawn,          SHCMD("notify-send title") },

	// ClkStatusText partie grise avec les icons
	{ ClkStatusText,        MODKEY,		Button1,        spawn,          SHCMD(TERMINAL " -e vim ~/.repo/dwm/config.h") },
	{ ClkStatusText,        MODKEY,		Button2,        spawn,          SHCMD("code ~/.repo/dwm/") },
	
	// ClkClientWin la fenetre du programe
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },

	// ClkTagBar parite 1 2 3 
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },

	// ClkRootWin ??
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

