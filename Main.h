#ifndef CLASS_MYEVENTHANDLER
#define CLASS_MYEVENTHANDLER

#include <ncine/IAppEventHandler.h>
#include <ncine/IInputEventHandler.h>
#include <nctl/UniquePtr.h>
#include <nctl/Array.h>

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
	nctl::UniquePtr<nc::Texture> cubeTexture_;
	nctl::UniquePtr<nc::Sprite>cubeSprites_;

	nctl::UniquePtr<nc::Texture> fire1Texture_;
	nctl::UniquePtr<nc::Sprite>fire1Sprite_;

	nctl::UniquePtr<nc::Texture> fire2Texture_;
	nctl::UniquePtr<nc::Sprite> fire2Sprites_;

	nctl::Array<nctl::UniquePtr<nc::Texture>> MaxPointTexture_;
	nctl::Array<nctl::UniquePtr<nc::Sprite>> MaxPointSprite_;

};

#endif
