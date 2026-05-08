//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_CSVMODELREADERIMPL_H
#define LAB_03_CSVMODELREADERIMPL_H
#include "Reader/Impl/BaseModelReaderImpl.h"


class CsvModelReaderImpl : public BaseModelReaderImpl
{
public:
    CsvModelReaderImpl() = delete;
    CsvModelReaderImpl(const std::string &filename);
    virtual ~CsvModelReaderImpl() override = default;

    std::shared_ptr<std::vector<Point>> read_points() override;
    std::shared_ptr<std::vector<Edge>> read_edges() override;
};


#endif //LAB_03_CSVMODELREADERIMPL_H