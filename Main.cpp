#include "nCineStaticArrayExample.h"

#include <ncine/Application.h>
#include <ncine/AppConfiguration.h>
#include <ncine/FileSystem.h> 
#include <ncine/imgui.h>
#include <math.h>
#include <ncine/SceneNode.h>
#include <ncine/Sprite.h>
#include <ncine/Texture.h>

const char* Texture2File = "C:\\Users\\Utilizzatore\\Desktop\\ncine\\ncline\\Test-data\\data\\fire2.png";
const char* Earth = "C:\\Users\\Utilizzatore\\Desktop\\ncine\\ncline\\Test-data\\data\\Earth.png";
const char* Sun = "C:\\Users\\Utilizzatore\\Desktop\\ncine\\ncline\\Test-data\\data\\Sun.png";
const char* maxPoint = "C:\\Users\\Utilizzatore\\Desktop\\ncine\\ncline\\Test-data\\data\\cubo.png";

nctl::UniquePtr<nc::IAppEventHandler> createAppEventHandler()
{
	return nctl::makeUnique<MyEventHandler>();
}

void MyEventHandler::onPreInit(nc::AppConfiguration& config)
{
#if defined(__ANDROID__)
	config.dataPath() = "asset::";
#elif defined(__EMSCRIPTEN__)
	config.dataPath() = "/";
#else
#ifdef PACKAGE_DEFAULT_DATA_DIR
	config.dataPath() = PACKAGE_DEFAULT_DATA_DIR;
#else
	config.dataPath() = "data/";
#endif
#endif

	config.windowTitle = "nCineStaticArray";
	config.windowIconFilename = "icon48.png";
}

void MyEventHandler::onInit()
{	
	cube_TEX = nctl::makeUnique<nc::Texture>(Earth);
	cube_SPR = nctl::makeUnique<nc::Sprite>(&nc::theApplication().rootNode(), cube_TEX.get());
	cube_SPR->setLayer(1);

	fire1_TEX = nctl::makeUnique<nc::Texture>(Sun);
	fire1_SPR = nctl::makeUnique<nc::Sprite>(&nc::theApplication().rootNode(), fire1_TEX.get());
	fire1_SPR->setPosition(nc::theApplication().width() / 2, nc::theApplication().height() / 2);

	fire2_TEX = nctl::makeUnique<nc::Texture>(Texture2File);
	fire2_SPR = nctl::makeUnique<nc::Sprite>(&nc::theApplication().rootNode(), fire2_TEX.get());
	fire2_SPR->setPosition(1280, nc::theApplication().height() / 2);
	fire2_SPR->setScale(0.7f);

	MaxPointTexture.pushBack(nctl::makeUnique<nc::Texture>(maxPoint));

	for (int i = 0; i < 4; i++)
	{
		MaxPointSprite.pushBack(nctl::makeUnique<nc::Sprite>(&nc::theApplication().rootNode(), MaxPointTexture[i % MaxPointTexture.size()].get()));
		MaxPointSprite[i]->setScale(0.3f);
		MaxPointSprite[i]->setColorF(255.f, 255.f, 255.f, 0.6f);
	}

}

void MyEventHandler::onFrameStart()
{
	static float time = 0.f;
	time += nc::theApplication().interval();
	
	static float w = nc::theApplication().width();
	static float h = nc::theApplication().height();
	
	static float w_ = 0.3f;
	static float h_ = 0.4f;

	float width = w * 0.5f + w * w_;
	float height = h * 0.5f + h * h_;
	float focalCenter = width / 2 - height / 2;

	float CenterY = nc::theApplication().height() / 2;
	float CenterX = nc::theApplication().width() / 2;

	static bool inverseMovement = false;
	static bool debugOverlay = false;

	if (ImGui::Begin("Properties"))
	{
		if (ImGui::TreeNode("Ellipse"))
		{
			ImGui::InputFloat("X axis", &w_);
			ImGui::InputFloat("Y axis", &h_);
			ImGui::Checkbox("Inverse movement", &inverseMovement);

			ImGui::TreePop();
		}

		if (ImGui::Checkbox("Debug Overlay", &debugOverlay))
		{
			fire2_SPR->setColor(nc::Color::White);
		}
		else if(!debugOverlay)
			fire2_SPR->setColorF(0.f, 0.f, 0.f, 0.f);
	}

	if (inverseMovement)
	{
		cube_SPR->setPosition(w * 0.5f + w * w_ * sinf(-time), h * 0.5f + h * h_ * cosf(-time));
	}
	else if(!inverseMovement)
		cube_SPR->setPosition(w * 0.5f + w * w_ * sinf(time), h * 0.5f + h * h_ * cosf(time));

	if ( w * w_ > h * h_)
	{
		fire1_SPR->setPosition(CenterX - focalCenter, CenterY );
		fire2_SPR->setPosition(CenterX + focalCenter, CenterY);
	}
	else if (w * w_ < h * h_)
	{
		fire1_SPR->setPosition(CenterX, CenterY + focalCenter);
		fire2_SPR->setPosition(CenterX, CenterY - focalCenter);

	}

	MaxPointSprite[0]->setPosition(CenterX, height );
	MaxPointSprite[1]->setPosition(width, CenterY);
	MaxPointSprite[2]->setPosition(CenterX, h * 0.5f + h * -h_);
	MaxPointSprite[3]->setPosition(w * 0.5f + w * -w_, CenterY);
}

void MyEventHandler::onKeyReleased(const nc::KeyboardEvent &event)
{
	if (event.sym == nc::KeySym::ESCAPE)
		ncine::theApplication().quit();
}
