#ifndef CLASS_MYEVENTHANDLER
#define CLASS_MYEVENTHANDLER

#include <nctl/Array.h>
#include <ncine/IAppEventHandler.h>
#include <ncine/IInputEventHandler.h>
#include <nctl/UniquePtr.h>

namespace ncine {

	class AppConfiguration;
	class SceneNode;
	class Texture;
	class Sprite;

}

namespace nc = ncine;

/// My nCine event handler
class MyEventHandler :
    public nc::IAppEventHandler,
    public nc::IInputEventHandler
{
  public:
	void onPreInit(nc::AppConfiguration &config) override;

	void onInit() override;

	void onFrameStart() override;

	void onKeyReleased(const nc::KeyboardEvent &event) override;
private:
	nctl::UniquePtr<nc::Texture> cube_TEX;
	nctl::UniquePtr<nc::Sprite>cube_SPR;

	nctl::UniquePtr<nc::Texture> fire1_TEX;
	nctl::UniquePtr<nc::Sprite>fire1_SPR;

	nctl::UniquePtr<nc::Texture> fire2_TEX;
	nctl::UniquePtr<nc::Sprite> fire2_SPR;

	nctl::Array<nctl::UniquePtr<nc::Texture>> MaxPointTexture;
	nctl::Array<nctl::UniquePtr<nc::Sprite>> MaxPointSprite;

};

#endif
