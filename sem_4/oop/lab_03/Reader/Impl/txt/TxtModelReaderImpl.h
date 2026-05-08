//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_TXTMODELREADERIMPL_H
#define LAB_03_TXTMODELREADERIMPL_H
#include "Reader/Impl/BaseModelReaderImpl.h"


class TxtModelReaderImpl : public BaseModelReaderImpl
{
public:
    TxtModelReaderImpl() = delete;
    TxtModelReaderImpl(const std::string &filename);
    virtual ~TxtModelReaderImpl() override = default;

    std::shared_ptr<std::vector<Point>> read_points() override;
    std::shared_ptr<std::vector<Edge>> read_edges() override;
};


#endif //LAB_03_TXTMODELREADERIMPL_H