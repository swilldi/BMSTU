//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_COMPOSITE_H
#define LAB_03_COMPOSITE_H

#include "Component/BaseObject.h"

class Composite final: public BaseObject
{
public:
    Composite() = default;
    explicit Composite(const mapObjects &objects);

    iterator begin() override;
    iterator end() override;

    const_iterator begin() const override;
    const_iterator end() const override;

    std::shared_ptr<BaseObject> get_object(const size_t id) const override;
    void add(std::shared_ptr<BaseObject> object) override;
    void remove(size_t id) noexcept override;
    void accept(std::shared_ptr<BaseVisitor> visitor) override;

    Point get_center() const noexcept override;

    bool is_composite() const noexcept override;
    bool is_visible() const noexcept override;

private:
    mapObjects _objects;
    size_t _count;
};

#endif //LAB_03_COMPOSITE_H