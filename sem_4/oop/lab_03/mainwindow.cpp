#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Commands/Camera/CameraCommand.h"
#include "Commands/Load/LoadCommand.h"
#include "Commands/Model/ModelCommand.h"
#include "Commands/Scene/SceneCommand.h"
#include "Exceptions/BaseException.h"
#include "Factories/Draw/Creators/DrawerCreator.h"
#include "ID/ID.h"
#include "Managers/ManagerSolution.h"

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTimer>
#include <QtMath>
#include <filesystem>

namespace
{
    constexpr const char *kCamera = "Камера";
    constexpr const char *kCarcass = "Каркас";
    constexpr const char *kComposite = "Композит";

    QString format_center(const Point &c)
    {
        return "(" + QString::number(c.get_x()) + "; " + QString::number(c.get_y()) + "; "
               + QString::number(c.get_z()) + ")";
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), _objects(0), _active_camera_id(0)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->loadModelBtn, &QPushButton::clicked, this, &MainWindow::handle_load_model);
    connect(ui->applyShiftBtn, &QPushButton::clicked, this, &MainWindow::handle_apply_shift);
    connect(ui->applyRotateBtn, &QPushButton::clicked, this, &MainWindow::handle_apply_rotate);
    connect(ui->applyScaleBtn, &QPushButton::clicked, this, &MainWindow::handle_apply_scale);
    connect(ui->createCameraBtn, &QPushButton::clicked, this, &MainWindow::handle_create_camera);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this,
            &MainWindow::handle_table_context_menu);

    QTimer::singleShot(0, this, &MainWindow::initial_setup);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initial_setup()
{
    create_scene();

    try
    {
        std::shared_ptr<BaseCommand> add_cam = std::make_shared<AddCameraCommand>(DefaultCameraID);
        _facade.execute(add_cam);

        std::shared_ptr<BaseCommand> set_active = std::make_shared<SetCameraCommand>(_objects);
        _facade.execute(set_active);

        Point center;
        std::shared_ptr<BaseCommand> get_center =
            std::make_shared<GetCenterModelCommand>(_objects, center);
        _facade.execute(get_center);

        _active_camera_id = _objects;
        insert_row(_objects++, "Камера 1", center, kCamera);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::create_scene()
{
    const int w = ui->graphicsView->width();
    const int h = ui->graphicsView->height();

    _scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene{ 0, 0, qreal(w), qreal(h), this },
                                             [](QGraphicsScene *) {});
    _scene->setSceneRect(QRect{ 0, 0, w, h });
    _scene->setBackgroundBrush(QColor::fromRgb(39, 40, 41));

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(_scene.get());

    auto drawer = QtDrawerCreator::create(_scene);
    auto draw_manager = ManagerSolution::get_draw_manager();
    draw_manager->set_drawer(drawer);
}

void MainWindow::insert_row(size_t obj_id, const QString &name, const Point &center, const QString &type)
{
    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem{ QString::number(obj_id) });
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem{ name });
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem{ format_center(center) });
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem{ type });
}

void MainWindow::update_center(int row, const Point &center)
{
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem{ format_center(center) });
}

void MainWindow::refresh_selected()
{
    _selected_rows.clear();
    for (auto *item : ui->tableWidget->selectedItems())
        if (item->column() == 0)
            _selected_rows.push_back(item->row());
}

size_t MainWindow::row_obj_id(int row) const
{
    return ui->tableWidget->item(row, 0)->text().toULong();
}

QString MainWindow::row_type(int row) const
{
    return ui->tableWidget->item(row, 3)->text();
}

void MainWindow::handle_load_model()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Открыть файл", "", "Текстовые файлы (*.txt);;CSV файлы (*.csv)");
    if (path.isEmpty())
        return;

    auto repr = static_cast<ModelRepresentationID>(ui->modelReprList->currentIndex());
    Point center;

    try
    {
        std::shared_ptr<BaseCommand> load =
            std::make_shared<BoneLoadCommand>(repr, path.toStdString());
        _facade.execute(load);

        std::shared_ptr<BaseCommand> draw = std::make_shared<DrawSceneCommand>();
        _facade.execute(draw);

        std::shared_ptr<BaseCommand> get_center =
            std::make_shared<GetCenterModelCommand>(_objects, center);
        _facade.execute(get_center);

        const auto name = QString::fromStdString(std::filesystem::path(path.toStdString()).filename());
        insert_row(_objects++, name, center, kCarcass);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_create_camera()
{
    try
    {
        std::shared_ptr<BaseCommand> add =
            std::make_shared<AddCameraCommand>(DefaultCameraID);
        _facade.execute(add);

        Point center;
        std::shared_ptr<BaseCommand> get_center =
            std::make_shared<GetCenterModelCommand>(_objects, center);
        _facade.execute(get_center);

        insert_row(_objects++, "Камера", center, kCamera);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_apply_shift()
{
    MoveData data{ ui->dxOffsetInput->value(), ui->dyOffsetInput->value(),
                   ui->dzOffsetInput->value() };
    refresh_selected();
    Point new_center;

    try
    {
        for (const auto row : _selected_rows)
        {
            const size_t obj_id = row_obj_id(row);
            std::shared_ptr<BaseCommand> move;
            if (row_type(row) == kCamera)
                move = std::make_shared<MoveCameraCommand>(obj_id, data);
            else
                move = std::make_shared<MoveModelCommand>(obj_id, data);
            _facade.execute(move);

            std::shared_ptr<BaseCommand> get_center =
                std::make_shared<GetCenterModelCommand>(obj_id, new_center);
            _facade.execute(get_center);
            update_center(row, new_center);
        }

        std::shared_ptr<BaseCommand> draw = std::make_shared<DrawSceneCommand>();
        _facade.execute(draw);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_apply_rotate()
{
    const double ax = qDegreesToRadians(ui->angleXRotate->value());
    const double ay = qDegreesToRadians(ui->angleYRotate->value());
    const double az = qDegreesToRadians(ui->angleZRotate->value());
    const Point center{ ui->centerXRotate->value(), ui->centerYRotate->value(),
                        ui->centerZRotate->value() };

    RotateData data{ ax, ay, az, center };
    refresh_selected();
    Point new_center;

    try
    {
        for (const auto row : _selected_rows)
        {
            const size_t obj_id = row_obj_id(row);
            std::shared_ptr<BaseCommand> rotate;
            if (row_type(row) == kCamera)
                rotate = std::make_shared<RotateCameraCommand>(obj_id, data);
            else
                rotate = std::make_shared<RotateModelCommand>(obj_id, data);
            _facade.execute(rotate);

            std::shared_ptr<BaseCommand> get_center =
                std::make_shared<GetCenterModelCommand>(obj_id, new_center);
            _facade.execute(get_center);
            update_center(row, new_center);
        }

        std::shared_ptr<BaseCommand> draw = std::make_shared<DrawSceneCommand>();
        _facade.execute(draw);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_apply_scale()
{
    const Point center{ ui->centerXScale->value(), ui->centerYScale->value(),
                        ui->centerZScale->value() };
    ScaleData data{ ui->kXScale->value(), ui->kYScale->value(), ui->kZScale->value(), center };
    refresh_selected();
    Point new_center;

    try
    {
        for (const auto row : _selected_rows)
        {
            if (row_type(row) == kCamera)
                continue;

            const size_t obj_id = row_obj_id(row);
            std::shared_ptr<BaseCommand> scale =
                std::make_shared<ScaleModelCommand>(obj_id, data);
            _facade.execute(scale);

            std::shared_ptr<BaseCommand> get_center =
                std::make_shared<GetCenterModelCommand>(obj_id, new_center);
            _facade.execute(get_center);
            update_center(row, new_center);
        }

        std::shared_ptr<BaseCommand> draw = std::make_shared<DrawSceneCommand>();
        _facade.execute(draw);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_table_context_menu(const QPoint &pos)
{
    refresh_selected();
    if (_selected_rows.empty())
        return;

    QMenu menu(this);
    menu.setTitle("Выбрать действие");
    QAction *del = menu.addAction("Удалить");
    connect(del, &QAction::triggered, this, &MainWindow::handle_delete_action);

    if (_selected_rows.size() > 1)
    {
        QAction *compose = menu.addAction("Создать композит");
        connect(compose, &QAction::triggered, this, &MainWindow::handle_compose_action);
    }
    else if (row_type(_selected_rows[0]) == kCamera)
    {
        QAction *set_active = menu.addAction("Установить активной");
        connect(set_active, &QAction::triggered, this, &MainWindow::handle_set_active_camera_action);
    }

    menu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::handle_delete_action()
{
    try
    {
        std::vector<int> rows = { _selected_rows.begin(), _selected_rows.end() };
        std::sort(rows.begin(), rows.end(), std::greater<int>());

        for (const auto row : rows)
        {
            const size_t obj_id = row_obj_id(row);
            const auto type = row_type(row);

            if (type == kCamera && obj_id == _active_camera_id)
            {
                QMessageBox::warning(this, "Предупреждение",
                                     "Невозможно удалить активную камеру.");
                continue;
            }

            std::shared_ptr<BaseCommand> remove;
            if (type == kCamera)
                remove = std::make_shared<RemoveCameraCommand>(obj_id);
            else
                remove = std::make_shared<RemoveModelCommand>(obj_id);
            _facade.execute(remove);

            ui->tableWidget->removeRow(row);
        }

        std::shared_ptr<BaseCommand> draw = std::make_shared<DrawSceneCommand>();
        _facade.execute(draw);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_compose_action()
{
    try
    {
        std::vector<size_t> obj_ids;
        for (const auto row : _selected_rows)
            obj_ids.push_back(row_obj_id(row));

        std::shared_ptr<BaseCommand> compose = std::make_shared<ComposeCommand>(obj_ids);
        _facade.execute(compose);

        Point center;
        std::shared_ptr<BaseCommand> get_center =
            std::make_shared<GetCenterModelCommand>(_objects, center);
        _facade.execute(get_center);

        insert_row(_objects++, "Композит", center, kComposite);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::handle_set_active_camera_action()
{
    try
    {
        const size_t obj_id = row_obj_id(_selected_rows[0]);
        std::shared_ptr<BaseCommand> set =
            std::make_shared<SetCameraCommand>(obj_id);
        _facade.execute(set);
        _active_camera_id = obj_id;

        std::shared_ptr<BaseCommand> draw = std::make_shared<DrawSceneCommand>();
        _facade.execute(draw);
    }
    catch (const BaseException &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}
