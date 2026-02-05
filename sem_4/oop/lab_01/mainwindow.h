#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "error_codes.h"

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


    private:
        error_code draw();

    private slots:
        void on_move_button_clicked();
        void on_rotate_button_clicked();
        void on_scale_button_clicked();

        void on_save_model_button_clicked();
        void on_load_model_button_clicked();


    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
