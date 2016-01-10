#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "Gui.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

void j1Scene::mapPreparation(const char* mapName)
{
	if (App->map->Load(mapName) == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

}


// Called before the first frame
bool j1Scene::Start()
{
	mapPreparation("iso2.tmx");

	debug_tex = App->tex->Load("maps/path2.png");
	Gui* window = App->gui->CreateImage({0, 512, 483, 512});
	window->Center();
	window->draggable = true;
	window->interactive = true;
	window->cut_childs = false;

	title = App->gui->CreateLabel("Value: ?.??");
	title->parent = window;
	title->Center();
	iPoint p = title->GetLocalPos();
	title->SetLocalPos(p.x, 50);

	// EXERCISE 5
	bar = App->gui->CreateHScrollBar({0, 11, 307, 11}, {805, 318, 26, 15}, {0, 0, -0, 0}, {0, 0});
	bar->parent = window;
	bar->Center();
	p = bar->GetLocalPos();
	bar->SetLocalPos(p.x, 150);
	bar->interactive = true;
	bar->can_focus = true;
	bar->SetListener(this);

	// EXERCISE 6
	GuiHScrollBar* bar2 = App->gui->CreateHScrollBar({0, 11, 307, 11}, {805, 318, 26, 15}, {-5, 0, -10, 0}, {0, -2});
	bar2->parent = window;
	bar2->Center();
	bar2->interactive = true;
	bar2->can_focus = true;


	int offsetSide = 6;
	uint height;
	uint width;
	App->win->GetWindowSize(width, height);

	rectangle consoleBox = {0,0,width,250};
	rectangle dot = { 300, 11, 20, 20 };
	iPoint parsPos = {-8,13 };
	blackBackground = App->tex->Load("textures/GUI/consoleBlackWindowAlpha.png");
	console = App->gui->CreateConsole("Command me",consoleBox, dot, parsPos, offsetSide, blackBackground, 128);


	//CVARS
	speed = new fCVar(200.0f);




	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	
	// -------
	
	//if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		//App->LoadGame("save_game.xml");

	//if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		//App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(speed->GetValueToFloat() * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(speed->GetValueToFloat() * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(speed->GetValueToFloat() * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(speed->GetValueToFloat()* dt);

	App->map->Draw();
	
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}
	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == true)
		console->ConsoleOnOff();

	if (quit)
		ret = quitNow();


	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::quitNow()
{
	return false;
}

void j1Scene::quitFlag()
{
	quit = true;
}
// Called when UI event is raised
void j1Scene::OnGui(Gui* ui, GuiEvents event)
{

/*Normal Button coords are {0,111,229,69} - hover state
Bright Button coords are {410,169,229,69} - click state
Dark Button coords are {645,165,229,69} - normal state
*/
	// EXERCISE 5
	if(ui == bar && event == GuiEvents::value_changed)
	{
		char n[20];
		sprintf_s(n, 20, "Value: %0.2f", bar->GetValue());
		title->SetText(n);
	}
}


void j1Scene::changeSpeed(p2SString& value)
{
	speed->SetValueToFloat(value);
}