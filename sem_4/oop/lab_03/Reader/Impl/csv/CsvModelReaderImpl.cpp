//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "CsvModelReaderImpl.h"

#include "Exceptions/Model/ModelException.h"

#include <sstream>

CsvModelReaderImpl::CsvModelReaderImpl(const std::string &filename) : BaseModelReaderImpl(filename) { }

std::shared_ptr<std::vector<Point> > CsvModelReaderImpl::read_points()
{
    std::vector<Point> points;
    std::string line;
    double x, y, z;
    char sep;

    _file.clear();
    _file.seekg(0, std::ios::beg);

    std::getline(_file, line);  // пропуск заголовка
    while (std::getline(_file, line))
    {
        if (line.empty())
            continue;

        std::istringstream s(line);
        if (s >> x >> sep >> y >> sep >> z)
            points.emplace_back(x, y, z);
        else
            break;
    }

    if (points.empty())
        throw ModelInvalidPointCountException();

    return std::make_shared<std::vector<Point>>(points);
}

std::shared_ptr<std::vector<Edge> > CsvModelReaderImpl::read_edges()
{
    std::vector<Edge> edges;
    std::string line;
    size_t id_1, id_2;
    char sep;

    _file.clear();
    _file.seekg(0, std::ios::beg);

    while (std::getline(_file, line))
    {
        std::istringstream iss(line);
        double x, y, z;
        if (!(iss >> x >> sep >> y >> sep >> z))
            break;
    }

    do
    {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        if (iss >> id_1 >> sep >> id_2)
            edges.emplace_back(id_1, id_2);
    } while (std::getline(_file, line));

    return std::make_shared<std::vector<Edge>>(edges);
}
