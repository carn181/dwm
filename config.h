/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"Monospace:pixelsize=12:antialias=true:autohint=true", "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[]       = "Monospace:size=10";
static char normbgcolor[]           = "#282828";
static char normbordercolor[]       = "#282828";
static char normfgcolor[]           = "#458588";
static char selfgcolor[]            = "#282828";
static char selbordercolor[]        = "#458588";
static char selbgcolor[]            = "#458588";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
        { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
        { "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
        { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
        { NULL,      NULL,     "broken",       0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "10"};
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,                       XK_q,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                             XK_f,      togglefullscr,  {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
        { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
        { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
        { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,             XK_e,      quit,           {0} },
        {0, XF86XK_AudioRaiseVolume,    spawn,     SHCMD("amixer sset Master 5%+") },
        {0, XF86XK_AudioLowerVolume,    spawn,     SHCMD("amixer sset Master 5%-") },
        {0, XF86XK_AudioMute,           spawn,     SHCMD("amixer sset Master toggle") },
        {0, XF86XK_AudioPrev,           spawn,     SHCMD("mpc next") },
        {0, XF86XK_AudioNext,           spawn,     SHCMD("mpc prev") },
        //      {0, XF86XK_MonBrightnessDown,   spawn,     SHCMD("brightness down") },
        //      {0, XF86XK_MonBrightnessUp,     spawn,     SHCMD("brightness up") },
        {0, XF86XK_AudioPlay,           spawn,     SHCMD("mpc toggle") },
        {0, XK_Print,                   spawn,     SHCMD("screeny") },
        {ControlMask,                   XK_Print,  spawn,          SHCMD("screeny -s") },
        {ControlMask, XF86XK_AudioRaiseVolume,    spawn,           SHCMD("mpc volume +5") },
        {ControlMask, XF86XK_AudioLowerVolume,    spawn,           SHCMD("mpc volume -5") },
        {MODKEY,                        XK_g,      spawn,          SHCMD("st -e gotop")},
        {MODKEY,                        XK_n,      spawn,          SHCMD("st -e iwctl")},
        {MODKEY,                        XK_p,      spawn,          SHCMD("st -e alsamixer")},
        {MODKEY,                        XK_y,      spawn,          SHCMD("search")},
        {MODKEY,                        XK_e,      spawn,          SHCMD("emojis")},
        {MODKEY|ControlMask,            XK_e,      spawn,          SHCMD("emacsclient -c")},
        {MODKEY|ShiftMask,              XK_t,      spawn,          SHCMD("st -e tremc")},
        //               {MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("qutebrowser --qt-flag ignore-gpu-blacklist --qt-flag enable-gpu-rasterization --qt-flag enable-native-gpu-memory-buffers --qt-flag num-raster-threads=4")},
//      {MODKEY|ShiftMask,              XK_b,      spawn,          SHCMD("surf-tabs")},
//      {MODKEY|ShiftMask,              XK_b,      spawn,          SHCMD("brave-browser-nightly")},
        {MODKEY|ShiftMask,              XK_b,      spawn,          SHCMD("librewolf")},
        {MODKEY|ShiftMask,              XK_m,      spawn,          SHCMD("emacsclient -c -e '(mpdel-browser-open)'")},
        {MODKEY|ControlMask|ShiftMask,  XK_t,      spawn,          SHCMD("notify-send \"Starting tf2\" && steam steam://rungameid/440")},
        {MODKEY|ControlMask,            XK_t,      spawn,          SHCMD("wallpapers")},
        {MODKEY|ControlMask,            XK_y,      spawn,          SHCMD("emacsclient -c -e '(elfeed)'")},
        {MODKEY|ControlMask,            XK_s,      spawn,          SHCMD("dmenuexit")},
        {MODKEY|ControlMask,            XK_f,      spawn,          SHCMD("st -e nnn")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
