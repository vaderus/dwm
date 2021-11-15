/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 15;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 5;       /* horizontal padding of bar */
static const char *fonts[]          = { "Source Code Pro Medium:style=Medium:size=9:antialias=true:autohint=true" ,"FontAwesome:style=Regular:size=10", "JoyPixels:size=9"};
static const char dmenufont[]       = "SourceCodePro:size=9:antialias=true:autohint=true";

static const char col_gray1[]    = "#000000";
static const char col_gray2[]    = "#ff0000";
static const char col_gray3[]    = "#bbbbbb";
static const char col_gray4[]    = "#eeeeee";
static const char col_cyan[]     = "#252525";
static const char col_backuo[]   = "#005577";
static const char *colors[][3]   = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_cyan, col_gray4  },
};

/* tagging */
//static const char *tags[] = { "", "", "", "", "", "", };
static const char *tags[] = { "1", "2", "3", "4", "5", "6",};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class			 instance  title              tags mask  isfloating  isterminal  noswallow  monitor */
	{ "librewolf",                   NULL,      NULL,              1 << 4,       0,           0,          0,           -1 },
	{ "Vieb",                   	 NULL,      NULL,              1 << 4,       0,           0,          0,           -1 },
	{ "Gimp",                        NULL,      NULL,              1 << 6,       0,           0,          0,           -1 },
	{ "discord",                     NULL,      NULL,              1 << 3,       0,           0,          0,           -1 },
	{ "Steam",                       NULL,      NULL,              1 << 5,       0,           0,          0,           -1 },
	{ "st",                          NULL,      NULL,              0,            0,           1,          0,           -1 },
	{ NULL,                          NULL,      "Event Tester",    0,            0,           0,          1,           -1 },
	{ "Pavucontrol",                 NULL,      NULL,		0,            1,           0,          1,           -1 },
	{ "st",                 	NULL,       "ncpamixer",	0,            1,           1,          1,           -1 },
	{ "st",                 	NULL,       "ncmpcpp",		0,            1,           1,          1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[empilhado]=",      tile },    /* first entry is default */
	{ ">flutuante<",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|Mod1Mask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	// CUSTOM KEYS:
	/* general applications */
	{ MODKEY|ShiftMask,             XK_Escape, spawn,  	   SHCMD("doas poweroff")}, 
	{ MODKEY|Mod1Mask,	        XK_r,	   spawn,  	   SHCMD("st ranger")}, 
	{ MODKEY|Mod1Mask,		XK_b,	   spawn,  	   SHCMD("st btop --utf-force")},
	{ MODKEY|Mod1Mask,             	XK_w, 	   spawn,          SHCMD("vieb")},
	{ MODKEY|Mod1Mask,             	XK_k, 	   spawn,          SHCMD("keepassxc")},
	{ MODKEY|Mod1Mask,             	XK_d, 	   spawn,          SHCMD("discord")},
	{ MODKEY|Mod1Mask,             	XK_s, 	   spawn,          SHCMD("steam")}, 
	/* print */
	{ 0,             		XK_Print,  spawn,          SHCMD("scrot -e 'xclip -selection clipboard -t image/png -i $f' /home/gabriel/mídia/ims/scrot/%b%d::%H%M%S.png")},
	{ ShiftMask,	                XK_Print,  spawn,          SHCMD("scrot -s -e 'xclip -selection clipboard -t image/png -i $f' /home/gabriel/mídia/ims/scrot/%b%d::%H%M%S.png")},
	/* audio control */
	{ MODKEY|Mod1Mask,             	XK_m, 	   spawn,          SHCMD("st ncpamixer")}, 
	{ MODKEY,			XK_bracketleft,spawn,  	   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +20%")}, 
	{ MODKEY,			XK_bracketright,spawn,     SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -20%")}, 
	{ MODKEY,			XK_slash,  spawn,  	   SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle")}, 
	/* mpd control etc... */
	{ 0,			        0x1008ff81,spawn,  	   SHCMD("st ncmpcpp")},
	{ 0,				0x1008ff13,spawn,  	   SHCMD("mpc volume +10")}, 
	{ 0,				0x1008ff11,spawn, 	   SHCMD("mpc volume -10")}, 
	{ 0,			        0x1008ff14,spawn,  	   SHCMD("mpc toggle") },
	{ 0,			        0x1008ff16,spawn,  	   SHCMD("mpc prev") },
	{ 0,			        0x1008ff17,spawn,  	   SHCMD("mpc next") },
	{ 0,			        0x1008ff15,spawn,  	   SHCMD("mpd --kill && mpc stop") },

	//DEFAULT KEYS
	{ MODKEY,                      	XK_b,      togglebar,      {0} },
	{ MODKEY,	              	XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|Mod1Mask,             	XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|Mod1Mask,             		XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|Mod1Mask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|Mod1Mask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|Mod1Mask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|Mod1Mask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY,			XK_q,      quit,	   {0} },
	{ MODKEY,			XK_q,      spawn,	   SHCMD("doas killall amdgpu-fan mpd pipewire pipewire-pulse picom") },
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

