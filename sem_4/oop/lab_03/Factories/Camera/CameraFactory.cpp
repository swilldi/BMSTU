//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "CameraFactory.h"

std::shared_ptr<BaseCamera> CameraFactory::create(const CameraID &id)
{
    auto it = _map.find(id);
    if (it != _map.end())
        return it->second();

    throw nullptr;
}
