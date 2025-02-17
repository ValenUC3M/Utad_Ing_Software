#include "renderEngine.h"
#include "manager.h"
#include "entity.h"
#include "renderComponent.h"


RenderEngine* RenderEngine::instance = nullptr;


RenderEngine* RenderEngine::getInstance()
{
	// if not created already then create it
	if (instance == nullptr) {instance = new RenderEngine();}
	return instance;
}


void RenderEngine::RenderSetUp() {
	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}


void RenderEngine::TexturesSetting() {
	// Load textures
	GetSprite()->setTexbkg(CORE_LoadPNG("data/circle-bkg-128.png", true));
	GetSprite()->setTexsmallball(CORE_LoadPNG("data/tyrian_ball.png", false));
}


void RenderEngine::RenderObjects(){

	// Render background
	for (int i = 0; i <= SCR_WIDTH / 128; i++) 
	{
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) 
		{
			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), GetSprite()->getTexbkg());
		}
	}

	// get manager for balls render and timer data getters
	Manager* manager = Manager::getInstance();

	std::vector<Entity*> entities = manager->getEntities();

	// for every ball render it using its location and radius values
	for (Entity* entity : entities) 
	{
		RenderComponent * renderComponent = entity->FindComponent<RenderComponent>();
		renderComponent->Slot();
	}
}


void RenderEngine::RenderText() 
{
	Manager* manager = Manager::getInstance();
	// get timer
	Timer* m_timer = manager->getTimer();
	// Text
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), "HELLO WORLD");

	// Time Passed
	char currentTimeString[50] = { 0 };
	snprintf(currentTimeString, 50, "TIME:%f", m_timer->GetTotalTime());
	FONT_DrawString(vec2(SCR_WIDTH - 128, SCR_HEIGHT - 16), currentTimeString);

	// Frames per second
	char fpsString[50] = { 0 };
	snprintf(fpsString, 50, "FPS:%f", 1 / m_timer->GetTime_fps());
	FONT_DrawString(vec2(0, SCR_HEIGHT - 16), fpsString);

	// Time Passed (game logic only)
	char tickString[50] = { 0 };
	snprintf(tickString, 50, "TICK:%f", m_timer->GetTotalFrameTime());
	FONT_DrawString(vec2(SCR_WIDTH - 128, SCR_HEIGHT - 40), tickString);
}

Sprite* RenderEngine::GetSprite() { return &sprite; }



GLuint Sprite::getTexbkg() { return texbkg; }

GLuint Sprite::getTexsmallball() { return texsmallball; }

void Sprite::setTexbkg(GLuint Texbkg) { texbkg = Texbkg; }

void Sprite::setTexsmallball(GLuint Texsmallball) { texsmallball = Texsmallball; }