#ifndef __GUI_H__
#define __GUI_H__

#include "p2Point.h"
#include "p2List.h"
#include "p2DynArray.h"

#define CURSOR_WIDTH 2

enum GuiEvents
{
	listening_ends,
	mouse_enters,
	mouse_leaves,
	mouse_lclick_down,
	mouse_lclick_up,
	mouse_rclick_down,
	mouse_rclick_up,
	gain_focus,
	lost_focus,
	input_changed,
	input_submit,
	value_changed
};

enum GuiTypes
{
	unknown,
	image,
	label,
	button,
	hscrollbar,
	console
};

// ---------------------------------------------------
class Gui
{
public:
	Gui();
	virtual ~Gui()
	{}

	virtual void Draw() const
	{}
	virtual void DebugDraw() const;
	virtual void Update(const Gui* mouse_hover, const Gui* focus)
	{}
	void CheckInput(const Gui* mouse_hover, const Gui* focus);
	void SetLocalPos(int x, int y);
	void Center();
	rectangle GetScreenRect() const;
	rectangle GetLocalRect() const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	void SetListener(j1Module* module);
	
protected:
	void SetSize(int w, int h);

public:
	bool draggable = false;
	bool interactive = false;
	bool cut_childs = false;
	bool can_focus = false;
	Gui* parent = nullptr;
protected:
	GuiTypes type = GuiTypes::unknown;
	j1Module* listener = nullptr;
	bool have_focus = false;
private:
	bool mouse_inside = false;
	rectangle rect;
};

// ---------------------------------------------------
class GuiImage : public Gui
{
public:
	GuiImage(const SDL_Texture* texture);
	GuiImage(const SDL_Texture* texture, const rectangle& section);
	~GuiImage();

	void SetSection(const rectangle& section);
	void Draw() const;

private:

	rectangle section;
	const SDL_Texture* texture = nullptr;
};

// ---------------------------------------------------
class GuiLabel : public Gui
{
public:
	GuiLabel(const char* text);
	~GuiLabel();

	void TextReplace(const char* text);
	void SetText(const char* text);
	void EraseText();
	const SDL_Texture* GetTexture() const;
	void Draw() const;

private:

	SDL_Texture* texture = nullptr;
};

class GuiInputText : public Gui
{
public:
	GuiInputText(const char* default_text, uint width, const SDL_Texture* texture, const rectangle& section, const iPoint& offset = {0, 0});
	~GuiInputText();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void UpdateConsole(const Gui* mouse_hover, const Gui* focus);
	p2SString& GetText();
	void Draw() const;
	void ResetInput();
public:
	bool isVisible = false;

private:
	
	GuiLabel text;
	GuiImage image;
	p2SString input;
	iPoint cursor_coords = {0, 0};
	int last_cursor = 0;
	bool had_focus = false;
};

// EXERCISE 1
class GuiHScrollBar : public Gui
{
public:
	GuiHScrollBar(const rectangle& bar, const rectangle& offset, const rectangle& thumb, iPoint margins);
	~GuiHScrollBar();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw() const;
	float GetValue() const;

private:

	GuiImage bar;
	GuiImage thumb;
	iPoint margins;
	int min_x = 0;
	int max_x = 0;
	int thumb_pos = 0;
};

class GuiConsole : public Gui
{
public:
	GuiConsole(const char* default_text, const rectangle defaultBox, const rectangle dotBox, const iPoint frameWorkPosOffset, int letterSize, SDL_Texture* texture, int alpha);
	void ActivateConsole();
	void TurnOffConsole();
	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw() const;
	bool ConsoleOnOff();
	bool CheckCommand(p2SString& possibleCommand);
	GuiInputText* GetInput() const;
	void ResetInput();
	void Endline();
	void listCommands();

public:
	void LogConsole(const char* string);
private:
	bool isVisible = false;
	float alpha = 1;
	iPoint parsePos;
	int letterSize;
	rectangle backgrundBlack;

	bool had_focus;
	p2SString input;
	int last_cursor = 0;

	iPoint cursor_coords = { 0, 0 };

	GuiInputText* InputConsole;
	GuiImage* blackBackground;

	SDL_Texture* texture;
	void ChooseMethod(p2List<string>& commandSplitted);
	

	string pastTextStr;
	GuiLabel* pastText;
	iPoint positionPastText;
	
	//Handling Input Commands
public:
	p2List<string> commandSplitted;
	p2List<string> commandList;
	
};



#endif // __GUI_H__
