#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiLabel;
class GuiHScrollBar;
class GuiConsole;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Called when UI event is raised
	void OnGui(Gui* ui, GuiEvents event);

	bool quitNow();
	void quitFlag();

	void mapPreparation(const char* mapName);

public:
	GuiConsole* console;
	bool quit = false;
private:
	SDL_Texture* debug_tex;
	SDL_Texture* blackBackground;

	GuiHScrollBar* bar;
	GuiLabel* title;
	
};

#endif // __j1SCENE_H__