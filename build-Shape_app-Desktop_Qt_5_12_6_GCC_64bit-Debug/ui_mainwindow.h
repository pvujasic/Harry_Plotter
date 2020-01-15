/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox;
    QPushButton *selectFile;
    QLabel *label;
    QComboBox *style_comboBox;
    QGroupBox *groupBox_2;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QPushButton *drawButton;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *functionEdit1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_function;
    QPushButton *delete_function;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_5;
    QPushButton *resetButton;
    QCheckBox *gridBox;
    QLabel *warningLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1052, 624);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(51, 51, 51, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(76, 76, 76, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 63, 63, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(25, 25, 25, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(34, 34, 34, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        QBrush brush9(QColor(136, 138, 133, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        MainWindow->setPalette(palette);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(50, 50, 690, 500));
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: #161616;\n"
"border-radius: 12px;"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(780, 430, 231, 121));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        selectFile = new QPushButton(groupBox);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));
        selectFile->setGeometry(QRect(10, 40, 91, 25));
        selectFile->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 80, 38, 17));
        label->setStyleSheet(QString::fromUtf8(""));
        style_comboBox = new QComboBox(groupBox);
        style_comboBox->addItem(QString());
        style_comboBox->addItem(QString());
        style_comboBox->addItem(QString());
        style_comboBox->setObjectName(QString::fromUtf8("style_comboBox"));
        style_comboBox->setGeometry(QRect(110, 80, 116, 25));
        style_comboBox->setStyleSheet(QString::fromUtf8(""));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(780, 50, 231, 331));
        doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(10, 250, 71, 26));
        doubleSpinBox->setMinimum(-99999.990000000005239);
        doubleSpinBox->setMaximum(99999.990000000005239);
        doubleSpinBox->setValue(-1.000000000000000);
        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(150, 250, 71, 26));
        doubleSpinBox_2->setMinimum(-99999.990000000005239);
        doubleSpinBox_2->setMaximum(99999.990000000005239);
        doubleSpinBox_2->setValue(1.000000000000000);
        drawButton = new QPushButton(groupBox_2);
        drawButton->setObjectName(QString::fromUtf8("drawButton"));
        drawButton->setGeometry(QRect(10, 290, 91, 25));
        drawButton->setStyleSheet(QString::fromUtf8(""));
        formLayoutWidget = new QWidget(groupBox_2);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 30, 212, 201));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QPalette palette1;
        QBrush brush10(QColor(245, 210, 93, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush10);
        QBrush brush11(QColor(117, 117, 117, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush11);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush10);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush10);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush11);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush11);
        QBrush brush12(QColor(78, 154, 6, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::LinkVisited, brush12);
        QBrush brush13(QColor(0, 0, 0, 128));
        brush13.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush13);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush12);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush13);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush12);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush13);
#endif
        label_4->setPalette(palette1);
        label_4->setStyleSheet(QString::fromUtf8("color: #f5d25d;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        functionEdit1 = new QLineEdit(formLayoutWidget);
        functionEdit1->setObjectName(QString::fromUtf8("functionEdit1"));
        functionEdit1->setStyleSheet(QString::fromUtf8("color: #f5d25d;\n"
"background-color: #1C1C1C;\n"
""));
        functionEdit1->setReadOnly(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, functionEdit1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        add_function = new QPushButton(formLayoutWidget);
        add_function->setObjectName(QString::fromUtf8("add_function"));
        add_function->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(add_function);

        delete_function = new QPushButton(formLayoutWidget);
        delete_function->setObjectName(QString::fromUtf8("delete_function"));
        delete_function->setEnabled(false);
        delete_function->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(delete_function);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_2);

        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(90, 240, 52, 31));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/Files/download-divider-line-png-doub.png")));

        verticalLayout->addWidget(label_5);

        resetButton = new QPushButton(groupBox_2);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(130, 290, 91, 25));
        resetButton->setStyleSheet(QString::fromUtf8(""));
        gridBox = new QCheckBox(centralwidget);
        gridBox->setObjectName(QString::fromUtf8("gridBox"));
        gridBox->setGeometry(QRect(920, 400, 92, 23));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush14(QColor(255, 255, 255, 128));
        brush14.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush14);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush15(QColor(255, 255, 255, 128));
        brush15.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush15);
#endif
        QBrush brush16(QColor(119, 20, 20, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush16);
        QBrush brush17(QColor(255, 255, 255, 128));
        brush17.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush17);
#endif
        gridBox->setPalette(palette2);
        gridBox->setChecked(false);
        warningLabel = new QLabel(centralwidget);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        warningLabel->setGeometry(QRect(50, 560, 691, 17));
        warningLabel->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1052, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Function manager", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Draw from file", nullptr));
        selectFile->setText(QApplication::translate("MainWindow", "Select file", nullptr));
        label->setText(QApplication::translate("MainWindow", "Style:", nullptr));
        style_comboBox->setItemText(0, QApplication::translate("MainWindow", "Dots only", nullptr));
        style_comboBox->setItemText(1, QApplication::translate("MainWindow", "Linear interp.", nullptr));
        style_comboBox->setItemText(2, QApplication::translate("MainWindow", "Cubic spline", nullptr));

        groupBox_2->setTitle(QApplication::translate("MainWindow", "Draw function", nullptr));
        drawButton->setText(QApplication::translate("MainWindow", "Draw", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "f(x) =", nullptr));
        functionEdit1->setText(QString());
        add_function->setText(QApplication::translate("MainWindow", "Add", nullptr));
        delete_function->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "range", nullptr));
        label_5->setText(QString());
        resetButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        gridBox->setText(QApplication::translate("MainWindow", "Show grid", nullptr));
        warningLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
