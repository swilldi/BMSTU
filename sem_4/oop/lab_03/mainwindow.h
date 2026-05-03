#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Component/SceneObject/Model/Point/Point.h"
#include "Facade/Facade.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QString>
#include <memory>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handle_load_model();
    void handle_apply_shift();
    void handle_apply_rotate();
    void handle_apply_scale();
    void handle_create_camera();
    void handle_table_context_menu(const QPoint &pos);
    void handle_delete_action();
    void handle_compose_action();
    void handle_set_active_camera_action();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QGraphicsScene> _scene;
    Facade _facade;

    size_t _objects;
    size_t _active_camera_id;
    std::vector<size_t> _selected_rows;

    void initial_setup();
    void create_scene();
    void insert_row(size_t obj_id, const QString &name, const Point &center, const QString &type);
    void update_center(int row, const Point &center);
    void refresh_selected();
    size_t row_obj_id(int row) const;
    QString row_type(int row) const;
};

#endif // MAINWINDOW_H
