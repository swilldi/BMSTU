#include "error_codes.h"
#include <QMessageBox>
#include <QString>


void select_error_message(const error_code rc, QString &qmsg)
{
    switch (rc)
    {
        case FILE_OPEN_ERR:
            qmsg = QStringLiteral("Ошибка открытия файла");
            break;

        case FILE_INVALID_TYPE_DATA:
            qmsg = QStringLiteral("Некорректные данные в файле");    
            break;
        case FILE_INVALID:
            qmsg = QStringLiteral("Некорректный файл");    
            break;
        case FILE_DATA_INVALID_RANGE:
            qmsg = QStringLiteral("Количество точек/ребер в файле отрицательное или ноль");    
            break;

        case MEMORY_ERR:
            qmsg = QStringLiteral("Ошибка выделения памяти");    
            break;

        case MODEL_NOT_LOADED:
            qmsg = QStringLiteral("Модель не была загружена");    
            break;

        case DRAW_SCENE_SCENE_INVALID:
            qmsg = QStringLiteral("Некорректная сцена для отрисовки модели");    
            break;
        case DRAW_SCENE_WIDTH_INVALID_RANGE:
            qmsg = QStringLiteral("Некоррекная ширина сцены для отрисовки модели");    
            break;
        case DRAW_SCENE_HEIGHT_INVALID_RANGE:
            qmsg = QStringLiteral("Некоррекная высота сцены для отрисовки модели");    
            break;


        case EDGES_INVALID:
            qmsg = QStringLiteral("Некорректные ребра");    
            break;
        case EDGES_EMPTY:
            qmsg = QStringLiteral("Количество ребер 0");    
            break;
        case EDGES_INVALID_INDEX_RANGE:
            qmsg = QStringLiteral("Некоректный индекс точки при описании ребра");    
            break;

        case POINTS_INVALID:
            qmsg = QStringLiteral("Некорректные точки");    
            break;
        case POINTS_EMPTY:
            qmsg = QStringLiteral("Количество точек 0");    
            break;

        case ACTION_INVALID:
            qmsg = QStringLiteral("Некорректное действие");    
            break;
            
        default:
            qmsg = QStringLiteral("Конец всему, это неизвестная ошибка!!!");
            break;
    }
}

void error_message_box(const error_code rc)
{
    QString msg, title = QStringLiteral("Ошибка");
    select_error_message(rc, msg);
    QMessageBox::critical(NULL, title, msg);
}

