/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_7;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *rotate_group;
    QVBoxLayout *move_group;
    QLabel *move_label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *move_x_label;
    QLabel *move_y_label;
    QLabel *move_z_label;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *move_x;
    QDoubleSpinBox *move_y;
    QDoubleSpinBox *move_z;
    QPushButton *move_button;
    QLabel *rotate_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *rotate_x_label;
    QLabel *rotate_y_label;
    QLabel *rotate_z_label;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *rotate_x;
    QDoubleSpinBox *rotate_y;
    QDoubleSpinBox *rotate_z;
    QPushButton *rotate_button;
    QVBoxLayout *scale_group;
    QLabel *scale_label;
    QHBoxLayout *horizontalLayout_5;
    QLabel *scale_x_label;
    QLabel *scale_y_label;
    QLabel *scale_z_label;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *scale_x;
    QDoubleSpinBox *scale_y;
    QDoubleSpinBox *scale_z;
    QPushButton *scale_button;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QPushButton *save_model_button;
    QPushButton *load_model_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("QLabel#rotate_label, QLabel#move_label, QLabel#scale_label {\n"
"	font-size: 18px;\n"
"    background-color: rgb(90, 165, 53);\n"
"    color: black;\n"
"    border: 1px solid #555;\n"
"    border-radius: 4px;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QLabel#rotate_x_label, QLabel#rotate_y_label, QLabel#rotate_z_label,\n"
"QLabel#move_x_label, QLabel#move_y_label, QLabel#move_z_label,\n"
"QLabel#scale_x_label, QLabel#scale_y_label, QLabel#scale_z_label {\n"
"  background-color: rgb(190, 171, 255);\n"
"  color: black;\n"
"  border: 1px solid #555;\n"
"  border-radius: 4px;\n"
"  padding: 4px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_7 = new QHBoxLayout(centralwidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(0, 0));

        horizontalLayout_7->addWidget(graphicsView);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        rotate_group = new QVBoxLayout();
        rotate_group->setObjectName("rotate_group");
        move_group = new QVBoxLayout();
        move_group->setObjectName("move_group");
        move_label = new QLabel(centralwidget);
        move_label->setObjectName("move_label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(move_label->sizePolicy().hasHeightForWidth());
        move_label->setSizePolicy(sizePolicy1);
        move_label->setStyleSheet(QString::fromUtf8("F"));
        move_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        move_group->addWidget(move_label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        move_x_label = new QLabel(centralwidget);
        move_x_label->setObjectName("move_x_label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(move_x_label->sizePolicy().hasHeightForWidth());
        move_x_label->setSizePolicy(sizePolicy2);
        move_x_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(move_x_label);

        move_y_label = new QLabel(centralwidget);
        move_y_label->setObjectName("move_y_label");
        sizePolicy2.setHeightForWidth(move_y_label->sizePolicy().hasHeightForWidth());
        move_y_label->setSizePolicy(sizePolicy2);
        move_y_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(move_y_label);

        move_z_label = new QLabel(centralwidget);
        move_z_label->setObjectName("move_z_label");
        sizePolicy2.setHeightForWidth(move_z_label->sizePolicy().hasHeightForWidth());
        move_z_label->setSizePolicy(sizePolicy2);
        move_z_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(move_z_label);


        move_group->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
#ifndef Q_OS_MAC
        horizontalLayout_4->setSpacing(-1);
#endif
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, -1, -1);
        move_x = new QDoubleSpinBox(centralwidget);
        move_x->setObjectName("move_x");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(move_x->sizePolicy().hasHeightForWidth());
        move_x->setSizePolicy(sizePolicy3);
        move_x->setMinimum(-100.000000000000000);
        move_x->setMaximum(100.000000000000000);

        horizontalLayout_4->addWidget(move_x);

        move_y = new QDoubleSpinBox(centralwidget);
        move_y->setObjectName("move_y");
        move_y->setMinimum(-100.000000000000000);
        move_y->setMaximum(100.000000000000000);

        horizontalLayout_4->addWidget(move_y);

        move_z = new QDoubleSpinBox(centralwidget);
        move_z->setObjectName("move_z");
        move_z->setMinimum(-100.000000000000000);
        move_z->setMaximum(100.000000000000000);

        horizontalLayout_4->addWidget(move_z);


        move_group->addLayout(horizontalLayout_4);

        move_button = new QPushButton(centralwidget);
        move_button->setObjectName("move_button");
        sizePolicy3.setHeightForWidth(move_button->sizePolicy().hasHeightForWidth());
        move_button->setSizePolicy(sizePolicy3);

        move_group->addWidget(move_button);


        rotate_group->addLayout(move_group);

        rotate_label = new QLabel(centralwidget);
        rotate_label->setObjectName("rotate_label");
        sizePolicy2.setHeightForWidth(rotate_label->sizePolicy().hasHeightForWidth());
        rotate_label->setSizePolicy(sizePolicy2);
        rotate_label->setStyleSheet(QString::fromUtf8("F"));
        rotate_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        rotate_group->addWidget(rotate_label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        rotate_x_label = new QLabel(centralwidget);
        rotate_x_label->setObjectName("rotate_x_label");
        sizePolicy2.setHeightForWidth(rotate_x_label->sizePolicy().hasHeightForWidth());
        rotate_x_label->setSizePolicy(sizePolicy2);
        rotate_x_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(rotate_x_label);

        rotate_y_label = new QLabel(centralwidget);
        rotate_y_label->setObjectName("rotate_y_label");
        sizePolicy2.setHeightForWidth(rotate_y_label->sizePolicy().hasHeightForWidth());
        rotate_y_label->setSizePolicy(sizePolicy2);
        rotate_y_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(rotate_y_label);

        rotate_z_label = new QLabel(centralwidget);
        rotate_z_label->setObjectName("rotate_z_label");
        sizePolicy2.setHeightForWidth(rotate_z_label->sizePolicy().hasHeightForWidth());
        rotate_z_label->setSizePolicy(sizePolicy2);
        rotate_z_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(rotate_z_label);


        rotate_group->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        rotate_x = new QDoubleSpinBox(centralwidget);
        rotate_x->setObjectName("rotate_x");
        rotate_x->setMinimum(-100.000000000000000);
        rotate_x->setMaximum(100.000000000000000);

        horizontalLayout->addWidget(rotate_x);

        rotate_y = new QDoubleSpinBox(centralwidget);
        rotate_y->setObjectName("rotate_y");
        rotate_y->setMinimum(-100.000000000000000);
        rotate_y->setMaximum(100.000000000000000);

        horizontalLayout->addWidget(rotate_y);

        rotate_z = new QDoubleSpinBox(centralwidget);
        rotate_z->setObjectName("rotate_z");
        rotate_z->setMinimum(-100.000000000000000);
        rotate_z->setMaximum(100.000000000000000);

        horizontalLayout->addWidget(rotate_z);


        rotate_group->addLayout(horizontalLayout);

        rotate_button = new QPushButton(centralwidget);
        rotate_button->setObjectName("rotate_button");
        sizePolicy2.setHeightForWidth(rotate_button->sizePolicy().hasHeightForWidth());
        rotate_button->setSizePolicy(sizePolicy2);

        rotate_group->addWidget(rotate_button);


        verticalLayout_4->addLayout(rotate_group);

        scale_group = new QVBoxLayout();
        scale_group->setObjectName("scale_group");
        scale_label = new QLabel(centralwidget);
        scale_label->setObjectName("scale_label");
        sizePolicy2.setHeightForWidth(scale_label->sizePolicy().hasHeightForWidth());
        scale_label->setSizePolicy(sizePolicy2);
        scale_label->setStyleSheet(QString::fromUtf8("F"));
        scale_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        scale_group->addWidget(scale_label);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        scale_x_label = new QLabel(centralwidget);
        scale_x_label->setObjectName("scale_x_label");
        sizePolicy2.setHeightForWidth(scale_x_label->sizePolicy().hasHeightForWidth());
        scale_x_label->setSizePolicy(sizePolicy2);
        scale_x_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(scale_x_label);

        scale_y_label = new QLabel(centralwidget);
        scale_y_label->setObjectName("scale_y_label");
        sizePolicy2.setHeightForWidth(scale_y_label->sizePolicy().hasHeightForWidth());
        scale_y_label->setSizePolicy(sizePolicy2);
        scale_y_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(scale_y_label);

        scale_z_label = new QLabel(centralwidget);
        scale_z_label->setObjectName("scale_z_label");
        sizePolicy2.setHeightForWidth(scale_z_label->sizePolicy().hasHeightForWidth());
        scale_z_label->setSizePolicy(sizePolicy2);
        scale_z_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(scale_z_label);


        scale_group->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        scale_x = new QDoubleSpinBox(centralwidget);
        scale_x->setObjectName("scale_x");
        scale_x->setMinimum(-100.000000000000000);
        scale_x->setMaximum(100.000000000000000);
        scale_x->setValue(1.000000000000000);

        horizontalLayout_6->addWidget(scale_x);

        scale_y = new QDoubleSpinBox(centralwidget);
        scale_y->setObjectName("scale_y");
        scale_y->setMinimum(-100.000000000000000);
        scale_y->setMaximum(100.000000000000000);
        scale_y->setValue(1.000000000000000);

        horizontalLayout_6->addWidget(scale_y);

        scale_z = new QDoubleSpinBox(centralwidget);
        scale_z->setObjectName("scale_z");
        scale_z->setMinimum(-100.000000000000000);
        scale_z->setMaximum(100.000000000000000);
        scale_z->setValue(1.000000000000000);

        horizontalLayout_6->addWidget(scale_z);


        scale_group->addLayout(horizontalLayout_6);

        scale_button = new QPushButton(centralwidget);
        scale_button->setObjectName("scale_button");
        sizePolicy2.setHeightForWidth(scale_button->sizePolicy().hasHeightForWidth());
        scale_button->setSizePolicy(sizePolicy2);

        scale_group->addWidget(scale_button);


        verticalLayout_4->addLayout(scale_group);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        save_model_button = new QPushButton(centralwidget);
        save_model_button->setObjectName("save_model_button");

        verticalLayout->addWidget(save_model_button);

        load_model_button = new QPushButton(centralwidget);
        load_model_button->setObjectName("load_model_button");

        verticalLayout->addWidget(load_model_button);


        verticalLayout_4->addLayout(verticalLayout);


        horizontalLayout_7->addLayout(verticalLayout_4);

        horizontalLayout_7->setStretch(0, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        move_label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        move_x_label->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        move_y_label->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        move_z_label->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        move_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214", nullptr));
        rotate_label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        rotate_x_label->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        rotate_y_label->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        rotate_z_label->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        rotate_button->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        scale_label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        scale_x_label->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        scale_y_label->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        scale_z_label->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        scale_button->setText(QCoreApplication::translate("MainWindow", "\320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        save_model_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        load_model_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
