//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_ID_H
#define LAB_03_ID_H

#include <cstddef>

enum DirectorID: size_t
{
    BoneDirectorID = 0,
};

enum ReaderID: size_t
{
    BoneReaderID = 0,
};

enum ModelRepresentation: size_t
{
    ListRepresentationID = 0,
    MatrixRepresentationID,
};

enum CameraID: size_t
{
    DefaultCameraID = 0
};

#endif //LAB_03_ID_H
