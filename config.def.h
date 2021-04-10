/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu Mono:size=14" };
static const char dmenufont[]       = "Ubuntu Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#668800";
static const char col_orange[]	    = "#F5C211";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_cyan },
	[SchemeSel]  = { col_gray4, col_cyan, col_orange },
};

static const char *tags[] = { "1", "2", "3" };
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "TTT",      bstack },
	{ "[C]",      centeredmaster },
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
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */


	TAGKEYS(			XK_F1,		0)
	TAGKEYS(			XK_F2,		1)
	TAGKEYS(			XK_F3,		2)
	TAGKEYS(			XK_F4,		3)

	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

		
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY,			XK_m,		setlayout,	{.v = &layouts[1]} },
 	{ MODKEY,			XK_f,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY|ShiftMask,		XK_m,		setlayout,	{.v = &layouts[4]} },
	/*

	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} },
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} },

	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} },
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} },
*/
	{ MODKEY,			XK_j,      focusstack,     {.i = +1 } }, 	
	{ MODKEY,			XK_Tab,      focusstack,     {.i = +1 } }, 	
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	{ MODKEY,			XK_h,		setmfact,       {.f = -0.05} }, 	
	{ MODKEY,			XK_l,		setmfact,       {.f = +0.05} },

	{ MODKEY,			XK_b,		togglebar,	{0} },

	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY|ShiftMask,		XK_q,		quit,		{0} },

	{ MODKEY,			XK_e,		spawn,          SHCMD("emoji") },
	{ MODKEY,			XK_n,		spawn,          SHCMD("nautilus") },
	{ MODKEY,			XK_r,		spawn,          SHCMD("rofi -show run") },
	{ MODKEY,			XK_s,		spawn,		SHCMD("snip") },
	{ MODKEY,			XK_v,		spawn,		SHCMD("clipmenu") },
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY,			XK_y,		spawn,		SHCMD("passmenu") },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

