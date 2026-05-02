//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_CAMERAFACTORY_H
#define LAB_03_CAMERAFACTORY_H
#include "Component/SceneObject/Camera/BaseCamera.h"
#include "Component/SceneObject/Camera/Default/DefaultCamera.h"
#include "ID/ID.h"

#include <memory>


class CameraFactory {
public:
    using CreatorMap = std::map<CameraID, std::function<std::shared_ptr<BaseCamera>()>>;

    CameraFactory() = default;
    std::shared_ptr<BaseCamera> create(const CameraID &id);

private:
    const CreatorMap _map {
        { DefaultCameraID, [](){ return std::make_shared<DefaultCamera>(); }}
    };
};


#endif //LAB_03_CAMERAFACTORY_H