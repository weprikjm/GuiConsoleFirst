#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2Point.h"

class Gui;
class GuiImage;
class GuiLabel; 
class GuiInputText;
class GuiHScrollBar;
class GuiConsole;

struct SDL_Texture;

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	GuiImage* CreateImage(const char* filename);
	GuiImage* CreateImage(const rectangle& atlas_section);
	GuiLabel* CreateLabel(const char* text);
	GuiInputText* CreateInput(const rectangle& section, const char* default_text, uint width, const iPoint& offset = {0, 0});
	GuiInputText* CreateInputConsole(const rectangle& section, const char* default_text, uint width, const iPoint& offset = { 0, 0 });
	GuiHScrollBar* CreateHScrollBar(const rectangle& bar, const rectangle& thumb, const rectangle& bar_offset = {0, 0,0,0}, const iPoint& thumb_margins = {0, 0});
	GuiConsole* CreateConsole(const char* default_text, const rectangle& defaultBox, const rectangle& dotBox, iPoint frameWorkPosOffset, int letterSizeNext, SDL_Texture* blackBackground, float alpha);
	
	const Gui* FindMouseHover() const;
	const SDL_Texture* GetAtlas() const;

private:

	bool debug = false;
	p2List<Gui*> elements;
	const Gui* focus = nullptr;
	SDL_Texture* atlas = nullptr;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__