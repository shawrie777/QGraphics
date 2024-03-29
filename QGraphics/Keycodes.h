#pragma once
#include <map>

enum class keyCode
{
SPACE        =      32,
APOSTROPHE   =      39,  /* ' */
COMMA        =      44,  /* , */
MINUS        =      45,  /* - */
PERIOD       =      46,  /* . */
SLASH        =      47,  /* / */
ZERO         =      48,
ONE          =      49,
TWO          =      50,
THREE        =      51,
FOUR         =      52,
FIVE         =      53,
SIX          =      54,
SEVEN        =      55,
EIGHT        =      56,
NINE         =      57,
SEMICOLON    =      59,  /* ; */
EQUAL        =      61,  /* = */
A            =      65,
B            =      66,
C            =      67,
D            =      68,
E            =      69,
F            =      70,
G            =      71,
H            =      72,
I            =      73,
J            =      74,
K            =      75,
L            =      76,
M            =      77,
N            =      78,
O            =      79,
P            =      80,
Q            =      81,
R            =      82,
S            =      83,
T            =      84,
U            =      85,
V            =      86,
W            =      87,
X            =      88,
Y            =      89,
Z            =      90,
LEFT_BRACKET =      91,  /* [ */
BACKSLASH    =      92,  /* \ */
RIGHT_BRACKET=      93,  /* ] */
GRAVE_ACCENT =      96,  /* ` */
WORLD_1      =      161, /* non-US #1 */
WORLD_2      =      162, /* non-US #2 */


ESCAPE       =      256,
ENTER        =      257,
TAB          =      258,
BACKSPACE    =      259,
INSERT       =      260,
DELETE       =      261,
RIGHT        =      262,
LEFT         =      263,
DOWN         =      264,
UP           =      265,
PAGE_UP      =      266,
PAGE_DOWN    =      267,
HOME         =      268,
END          =      269,
CAPS_LOCK    =      280,
SCROLL_LOCK  =      281,
NUM_LOCK     =      282,
PRINT_SCREEN =      283,
PAUSE        =      284,
F1           =      290,
F2           =      291,
F3           =      292,
F4           =      293,
F5           =      294,
F6           =      295,
F7           =      296,
F8           =      297,
F9           =      298,
F10          =      299,
F11          =      300,
F12          =      301,
F13          =      302,
F14          =      303,
F15          =      304,
F16          =      305,
F17          =      306,
F18          =      307,
F19          =      308,
F20          =      309,
F21          =      310,
F22          =      311,
F23          =      312,
F24          =      313,
F25          =      314,
KP_0         =      320,
KP_1         =      321,
KP_2         =      322,
KP_3         =      323,
KP_4         =      324,
KP_5         =      325,
KP_6         =      326,
KP_7         =      327,
KP_8         =      328,
KP_9         =      329,
KP_DECIMAL   =      330,
KP_DIVIDE    =      331,
KP_MULTIPLY  =      332,
KP_SUBTRACT  =      333,
KP_ADD       =      334,
KP_ENTER     =      335,
KP_EQUAL     =      336,
LEFT_SHIFT   =      340,
LEFT_CONTROL =      341,
LEFT_ALT     =      342,
LEFT_SUPER   =      343,
RIGHT_SHIFT  =      344,
RIGHT_CONTROL=      345,
RIGHT_ALT    =      346,
RIGHT_SUPER  =      347,
MENU         =      348
};

enum class modCode {
	NONE	  = 0X0000,
	SHIFT     = 0X0001,
	CONTROL   = 0X0002,
	ALT       = 0X0004,
	SUPER     = 0X0008,
	CAPS      = 0X0010,
	NUMLOCK   = 0X0020
};

//allows multiple modifier keys to be used in combination
modCode operator|(modCode lhs, modCode rhs);
//allows any of a group of modifier keys to be used
modCode operator&(modCode lhs, modCode rhs);
//checks if modCodes are equal
bool operator==(modCode lhs, modCode rhs);

enum class mouseCode {
	LEFT     = 0,
	RIGHT    = 1,
	MIDDLE   = 2,
	BUTTON4  = 3,
	BUTTON5  = 4,
	BUTTON6  = 5,
	BUTTON7  = 6,
	BUTTON8  = 7,
};

enum class keyState
{
	release,
	press
};

struct keyAction
{
	keyCode key;
	keyState state;
	modCode mod;

	keyAction(keyCode K, keyState State, modCode Mod);
};

//allows comparing of key actions
//this is simply to allow mapping to determine a 'correct' order to list them in
bool operator<(keyAction lhs, keyAction rhs);

struct mouseAction
{
	mouseCode button;
	keyState state;
	modCode mod;

	mouseAction(mouseCode M, keyState State, modCode Mod);
};

//allows comparing of mouse actions
//this is simply to allow mapping to determine a 'correct' order to list them in
bool operator<(mouseAction lhs, mouseAction rhs);

extern std::map<keyAction, void(*)()> keyFuncs;
extern std::map<mouseAction, void(*)()> mouseFuncs;

//add a global function to a specific key action using a function pointer
//note the function must have no parameters and return void
void AddKeyFunc(keyCode K, keyState action, modCode mods, void(*func)());
//add a global function to a specific key action using a function pointer
//note the function must have no parameters and return void
//the keystate will be press and there will be no mod keys
void AddKeyFunc(keyCode K, void(*func)());
//remove a global key function from the list
void RemoveKeyFunc(keyCode K, keyState state = keyState::press, modCode mod = modCode::NONE);

//add a global function to a specific mouse action using a function pointer
//note the function must have no parameters and return void
void AddMouseFunc(mouseCode M, keyState action, modCode mods, void(*func)());
//add a global function to a specific mouse action using a function pointer
//note the function must have no parameters and return void
//the keystate will be press and there will be no mod keys
void AddMouseFunc(mouseCode M, void(*func)());
//remove a global mouse function from the list
void RemoveMouseFunc(mouseCode M, keyState state = keyState::press, modCode mod = modCode::NONE);