//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "ModelReader.h"

ModelReader::ModelReader(std::shared_ptr<BaseModelReaderImpl> impl) : _impl(impl) {}

std::shared_ptr<std::vector<Point>> ModelReader::read_points()
{
    return _impl->read_points();
}

std::shared_ptr<std::vector<Edge> > ModelReader::read_edges()
{
    return _impl->read_edges();
}
