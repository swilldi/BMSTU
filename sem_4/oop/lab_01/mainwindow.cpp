#include <iostream>
#include <QPen>
#include <QString>
#include <QFileDialog>

#include "request.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    std::cout << "Окошко настраивается" << std::endl;

    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    complete_request({ .action=LOAD, .file_name="/Users/dmitriy/test/untitled/data_3d_figures/cube_in_2d.txt" });
    draw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// === Взаимодействие с моделью ===
// Перемещение фигуры
void MainWindow::on_move_button_clicked()
{
    error_code rc = OK;

    double x = ui->move_x->value(), y = ui->move_y->value(), z = ui->move_z->value();
    std::cout << "Фигура будет сдвинута по осям:\nx: " << x << "\ny: " << y << "\nz: " << z << std::endl;

    request_t request = { .action = MOVE, .move = { x, y, z} };
    rc = complete_request(request);
    if (rc == OK)
    {
        rc = draw();
        if (rc != OK)
            error_message_box(rc);
    }
    else
    {
        error_message_box(rc);
    }
}

// Вращение фигуры
void MainWindow::on_rotate_button_clicked()
{
    double x = ui->rotate_x->value(), y = ui->rotate_y->value(), z = ui->rotate_z->value();
    std::cout << "Фигура будет повернута по осям (градусы):\nx: " << x << "\ny: " << y << "\nz: " << z << std::endl;

    error_code rc = OK;
    request_t request = { .action = ROTATE, .rotate = { x, y, z } };
    rc = complete_request(request);
    if (rc == OK)
    {
        rc = draw();
        if (rc != OK)
            error_message_box(rc);
    }
    else
    {
        error_message_box(rc);
    }
}

// Масштабирование фигуры
void MainWindow::on_scale_button_clicked()
{
    double x = ui->scale_x->value(), y = ui->scale_y->value(), z = ui->scale_z->value();
    std::cout << "Фигура будет масштабирована по осям:\nx: " << x << "\ny: " << y << "\nz: " << z << std::endl;

    error_code rc = OK;
    request_t request = { .action = SCALE, .scale = { x, y, z } };
    rc = complete_request(request);
    if (rc == OK)
    {
        rc = draw();
        if (rc != OK)
            error_message_box(rc);
    }
    else
    {
        error_message_box(rc);
    }
}


// === Загрузка/сохранение фигуры ===
// Сохранение фигуры
void MainWindow::on_save_model_button_clicked()
{
    error_code rc = OK;

    QString path = QFileDialog::getSaveFileName();
    if (path.length() == 0)
        return;

    QByteArray ba = path.toLocal8Bit();
    char *file_name = ba.data();

    std::cout << "Фигура будет сохранена в файл: " << file_name << std::endl;

    request_t request = { .action = SAVE, .file_name = file_name };
    rc = complete_request(request);
    if (rc == OK)
    {
        rc = draw();
        if (rc != OK)
            error_message_box(rc);
    }
    else
    {
        error_message_box(rc);
    }
}

//Загрузка фигуры
void MainWindow::on_load_model_button_clicked()
{
    error_code rc = OK;

    QString path = QFileDialog::getOpenFileName();
    if (path.length() == 0)
        return;

    std::cout << "Фигура будет загружена их файла: " << path.toStdString() << std::endl;

    QByteArray ba = path.toLocal8Bit();
    char *file_name = ba.data();

    request_t request = { .action = LOAD, .file_name = file_name };
    rc = complete_request(request);
    // rc = FILE_OPEN_ERR;
    if (rc == OK)
    {
        rc = draw();
        if (rc != OK)
            error_message_box(rc);
    }
    else
    {
        error_message_box(rc);
    }

}

error_code MainWindow::draw()
{
    QRectF rect = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(rect);

    draw_scene_t dc = {
        .scene = ui->graphicsView->scene(),
        .width = rect.width(),
        .height = rect.height(),
        .color = Qt::black

    };

    request_t request = {
        .action = DRAW,
        .scene = dc
    };

    error_code rc = complete_request(request);

    return rc;
}



