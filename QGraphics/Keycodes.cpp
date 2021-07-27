#include "Keycodes.h"

modCode operator|(modCode lhs, modCode rhs)
{
	return static_cast<modCode>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

modCode operator&(modCode lhs, modCode rhs)
{
	return static_cast<modCode>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

bool operator==(modCode lhs, modCode rhs)
{
	return (static_cast<int>(lhs) & static_cast<int>(rhs)) == static_cast<int>(rhs);
}


std::map<keyAction, void(*)()> keyFuncs;
std::map<mouseAction, void(*)()> mouseFuncs;

keyAction::keyAction(keyCode K, keyState State, modCode Mod): key(K), state(State), mod(Mod)
{
}

bool operator<(keyAction lhs, keyAction rhs)
{
	if (lhs.key != rhs.key)
		return lhs.key < rhs.key;
	else if (lhs.state != rhs.state)
		return lhs.state < rhs.state;
	else
		return lhs.mod < rhs.mod;
}

void AddKeyFunc(keyCode K, keyState action, modCode mods, void(*func)())
{
	keyAction act(K,action,mods);
	keyFuncs.emplace(act, func);
}

void AddKeyFunc(keyCode K, void(*func)())
{
	AddKeyFunc(K, keyState::press, modCode::NONE, func);
}

bool operator<(mouseAction lhs, mouseAction rhs)
{
	if (lhs.button != rhs.button)
		return lhs.button < rhs.button;
	else if (lhs.state != rhs.state)
		return lhs.state < rhs.state;
	else
		return lhs.mod < rhs.mod;
}

void RemoveKeyFunc(keyCode K, keyState state, modCode mod)
{
	keyAction action(K, state, mod);
	keyFuncs.erase(action);
}

mouseAction::mouseAction(mouseCode M, keyState State, modCode Mod): button(M), state(State), mod(Mod)
{
}

void AddMouseFunc(mouseCode M, keyState action, modCode mods, void(*func)())
{
	mouseAction act(M, action, mods);
	mouseFuncs.emplace(act, func);
}

void AddMouseFunc(mouseCode M, void(*func)())
{
	AddMouseFunc(M, keyState::press, modCode::NONE, func);
}

void RemoveMouseFunc(mouseCode M, keyState state, modCode mod)
{
	mouseAction action(M, state, mod);
	mouseFuncs.erase(action);
}