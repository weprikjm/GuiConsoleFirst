#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_mouse.h"

#define NUM_MOUSE_BUTTONS 5

struct SDL_Rect;

enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class j1Input : public j1Module
{

public:

	j1Input();

	// Destructor
	virtual ~j1Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(j1EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	void StartTextInput(SDL_Rect* rect = NULL);
	void EndTextInput();
	const char* GetTextInput(int& cursor, int& selection) const;
	void FlushTextInput();

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard = nullptr;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x = 0;
	int			mouse_motion_y = 0;
	int			mouse_x = 0;
	int			mouse_y = 0;
	// Text Input
	bool		text_input;
	p2SString	last_text_input;
	int			cursor_text_input;
	int			selection_text_input;
};

#endif // __j1INPUT_H__