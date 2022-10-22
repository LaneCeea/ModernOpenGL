#ifndef SCENE_ISCENE_H_
#define SCENE_ISCENE_H_

#include <string_view>

namespace scene {

class IScene {
public:
    IScene() {}
    virtual ~IScene() {}

    virtual void onUpdate(float dt) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}
    virtual inline const std::string_view& getName() = 0;
};

} // namespace scene

#endif // !SCENE_ISCENE_H_