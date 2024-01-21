/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int borderalpha = 9; /* border pixel of windows */
static const unsigned int baralpha = 25; /* border pixel of windows */
static const unsigned int gappx = 10;
static const unsigned int snap = 12;    /* snap pixel */
static const int showbar = 0;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"JetBrains Mono:size=16"};
static const char dmenufont[] = "JetBrains Mono:size=16";
static const char bg_norm[] = "#1E1E2E";
static const char border_norm[] = "#6C7086";
static const char color_norm[] = "#CDD6F4";
static const char color_sel[] = "#1E1E2E";
static const char bg_sel[] = "#B4BEFE";
static const char border_sel[] = "#cba6f7";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {color_norm, bg_norm, border_norm},
    [SchemeSel] = {color_sel, bg_sel, border_sel},
};

/* tagging */
static const char *tags[] = {"", "", "3", "4", "5", "6", "7", "8", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {" ", tile}, /* first entry is default */
    {"><>", NULL},  /* no layout function means floating behavior */
    {" ", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT_L Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

static const char browser[] = "chromium";
static const char alt_browser[] = "qutebrowser";
static const char editor[6] = "codium";
static const char fileManager[] = "Thunar";
/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run","-b", "-m",dmenumon, "-fn",  dmenufont, "-nb",     bg_norm,
    "-nf",       color_norm, "-sb",    bg_sel, "-sf",     color_sel, NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *editorcmd[] = {editor, NULL};
static const char *emailcmd[] = { "openmails", NULL};
static const char *browsercmd[] = {browser, NULL};
static const char *altbrowsercmd[] = {alt_browser, NULL};
static const char *fileManagercmd[] = {fileManager, NULL};
static const char *notescmd[] = {"/usr/local/bin/logseq", NULL};
static const char *incVol[] = {"/usr/local/bin/incVol", NULL};
static const char *decVol[] = {"/usr/local/bin/decVol", NULL};
static const char *muteVol[] = {"/usr/local/bin/muteVol", NULL};

static const char *incBri[] = {"/usr/local/bin/incBacklight", NULL};
static const char *decBri[] = {"/usr/local/bin/decBacklight", NULL};
static const char *screenShotCmd[] = {"/usr/local/bin/maimpick", NULL};
static const char *powerCmd[] = {"/usr/local/bin/powerpick", NULL};
static const char *screenKeyCmd[] = {"/usr/local/bin/togglescreenkey", NULL};
static const char *postmanCmd[] = {"/usr/bin/postman", NULL};
static const char *emojiCmd[] = {"/usr/local/bin/emoji", NULL};
// XF86MonBrightnessUp
static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {ALT_L | ShiftMask, XK_w, spawn, {.v = browsercmd}},
    {ALT_L | ShiftMask, XK_e, spawn, {.v = emailcmd}},
    {ALT_L | ShiftMask, XK_q, spawn, {.v = altbrowsercmd}},
    {ALT_L | ShiftMask, XK_c, spawn, {.v = editorcmd}},
    {ALT_L | ShiftMask, XK_n, spawn, {.v = notescmd}},
    {ALT_L | ShiftMask, XK_p, spawn, {.v = postmanCmd }},
    
    {ALT_L | ControlMask, XK_e, spawn, {.v = emojiCmd }},

    // XF86PowerDown
    {0, XF86XK_PowerDown, spawn, {.v = powerCmd}},
    {0, XF86XK_PowerOff, spawn, {.v = powerCmd}},

    {0, XF86XK_AudioLowerVolume, spawn, {.v = decVol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = incVol}},
    {0, XF86XK_AudioMute, spawn, {.v = muteVol}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = incBri}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = decBri}},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = screenShotCmd}},
    { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
  	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
   	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	  { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
  	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
  	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
  	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
  	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
  	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
  	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
  	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
  	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
  	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
    { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
  	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
  	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
    {MODKEY, XK_s, spawn, {.v = screenKeyCmd}},
    {MODKEY, XK_e, spawn, {.v = fileManagercmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY| ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
    /*	{ MODKEY,             XK_q,      quit,           {0} }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}}, };
