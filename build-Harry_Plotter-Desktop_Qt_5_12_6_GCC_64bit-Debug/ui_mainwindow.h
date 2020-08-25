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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QLabel *warningLabel;
    QGroupBox *groupBox1;
    QSpinBox *pointsNumber;
    QLabel *label1;
    QPushButton *addFunction;
    QWidget *verticalWidget_5;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *functionLayout;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_4;
    QDoubleSpinBox *xFrom;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout2;
    QLabel *label4;
    QLabel *label6;
    QDoubleSpinBox *xTo;
    QDoubleSpinBox *yTo;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout1;
    QLabel *label3;
    QLabel *label5;
    QDoubleSpinBox *yFrom;
    QCheckBox *gridBox;
    QPushButton *resetButton;
    QPushButton *rangeButton;
    QGroupBox *groupBox2;
    QLabel *label2;
    QComboBox *styleBox;
    QPushButton *selectFile;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *fileLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1052, 835);
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
        graphicsView->setGeometry(QRect(60, 80, 690, 500));
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: #161616;\n"
"border-radius: 12px;"));
        warningLabel = new QLabel(centralwidget);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        warningLabel->setGeometry(QRect(50, 610, 691, 171));
        warningLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        groupBox1 = new QGroupBox(centralwidget);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(780, 70, 231, 261));
        pointsNumber = new QSpinBox(groupBox1);
        pointsNumber->setObjectName(QString::fromUtf8("pointsNumber"));
        pointsNumber->setGeometry(QRect(150, 230, 71, 26));
        pointsNumber->setMinimum(5);
        pointsNumber->setMaximum(1001);
        pointsNumber->setValue(101);
        label1 = new QLabel(groupBox1);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(10, 230, 131, 17));
        addFunction = new QPushButton(groupBox1);
        addFunction->setObjectName(QString::fromUtf8("addFunction"));
        addFunction->setGeometry(QRect(110, 30, 111, 25));
        addFunction->setStyleSheet(QString::fromUtf8(""));
        verticalWidget_5 = new QWidget(groupBox1);
        verticalWidget_5->setObjectName(QString::fromUtf8("verticalWidget_5"));
        verticalWidget_5->setGeometry(QRect(0, 60, 231, 171));
        verticalLayout = new QVBoxLayout(verticalWidget_5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        functionLayout = new QVBoxLayout();
        functionLayout->setObjectName(QString::fromUtf8("functionLayout"));
        functionLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        verticalLayout->addLayout(functionLayout);

        verticalSpacer = new QSpacerItem(99, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(780, 590, 231, 181));
        xFrom = new QDoubleSpinBox(groupBox_4);
        xFrom->setObjectName(QString::fromUtf8("xFrom"));
        xFrom->setEnabled(true);
        xFrom->setGeometry(QRect(10, 110, 71, 26));
        xFrom->setMinimum(-99999.990000000005239);
        xFrom->setMaximum(99999.990000000005239);
        xFrom->setValue(-3.000000000000000);
        verticalLayoutWidget_3 = new QWidget(groupBox_4);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(90, 140, 55, 31));
        verticalLayout2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
        verticalLayout2->setContentsMargins(0, 0, 0, 0);
        label4 = new QLabel(verticalLayoutWidget_3);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setLayoutDirection(Qt::LeftToRight);
        label4->setStyleSheet(QString::fromUtf8(""));
        label4->setAlignment(Qt::AlignCenter);

        verticalLayout2->addWidget(label4);

        label6 = new QLabel(verticalLayoutWidget_3);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setStyleSheet(QString::fromUtf8(""));
        label6->setPixmap(QPixmap(QString::fromUtf8(":/Files/download-divider-line-png-doub.png")));

        verticalLayout2->addWidget(label6);

        xTo = new QDoubleSpinBox(groupBox_4);
        xTo->setObjectName(QString::fromUtf8("xTo"));
        xTo->setEnabled(true);
        xTo->setGeometry(QRect(150, 110, 71, 26));
        xTo->setMinimum(-99999.990000000005239);
        xTo->setMaximum(99999.990000000005239);
        xTo->setValue(3.000000000000000);
        yTo = new QDoubleSpinBox(groupBox_4);
        yTo->setObjectName(QString::fromUtf8("yTo"));
        yTo->setEnabled(true);
        yTo->setGeometry(QRect(150, 150, 71, 26));
        yTo->setMinimum(-99999.990000000005239);
        yTo->setMaximum(99999.990000000005239);
        yTo->setValue(3.000000000000000);
        verticalLayoutWidget_2 = new QWidget(groupBox_4);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(90, 100, 55, 31));
        verticalLayout1 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
        verticalLayout1->setContentsMargins(0, 0, 0, 0);
        label3 = new QLabel(verticalLayoutWidget_2);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setLayoutDirection(Qt::LeftToRight);
        label3->setStyleSheet(QString::fromUtf8(""));
        label3->setAlignment(Qt::AlignCenter);

        verticalLayout1->addWidget(label3);

        label5 = new QLabel(verticalLayoutWidget_2);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setStyleSheet(QString::fromUtf8(""));
        label5->setPixmap(QPixmap(QString::fromUtf8(":/Files/download-divider-line-png-doub.png")));

        verticalLayout1->addWidget(label5);

        yFrom = new QDoubleSpinBox(groupBox_4);
        yFrom->setObjectName(QString::fromUtf8("yFrom"));
        yFrom->setEnabled(true);
        yFrom->setGeometry(QRect(10, 150, 71, 26));
        yFrom->setMinimum(-99999.990000000005239);
        yFrom->setMaximum(99999.990000000005239);
        yFrom->setValue(-3.000000000000000);
        gridBox = new QCheckBox(groupBox_4);
        gridBox->setObjectName(QString::fromUtf8("gridBox"));
        gridBox->setGeometry(QRect(10, 70, 92, 23));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush10(QColor(255, 255, 255, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush11(QColor(255, 255, 255, 128));
        brush11.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        QBrush brush12(QColor(119, 20, 20, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        QBrush brush13(QColor(255, 255, 255, 128));
        brush13.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush13);
#endif
        gridBox->setPalette(palette1);
        gridBox->setChecked(false);
        resetButton = new QPushButton(groupBox_4);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(150, 30, 71, 25));
        resetButton->setStyleSheet(QString::fromUtf8(""));
        rangeButton = new QPushButton(groupBox_4);
        rangeButton->setObjectName(QString::fromUtf8("rangeButton"));
        rangeButton->setGeometry(QRect(10, 30, 121, 25));
        rangeButton->setStyleSheet(QString::fromUtf8(""));
        groupBox2 = new QGroupBox(centralwidget);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(780, 340, 231, 241));
        groupBox2->setStyleSheet(QString::fromUtf8(""));
        label2 = new QLabel(groupBox2);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(50, 210, 38, 17));
        label2->setStyleSheet(QString::fromUtf8(""));
        styleBox = new QComboBox(groupBox2);
        styleBox->addItem(QString());
        styleBox->addItem(QString());
        styleBox->addItem(QString());
        styleBox->setObjectName(QString::fromUtf8("styleBox"));
        styleBox->setGeometry(QRect(100, 210, 120, 25));
        styleBox->setStyleSheet(QString::fromUtf8(""));
        selectFile = new QPushButton(groupBox2);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));
        selectFile->setGeometry(QRect(110, 30, 111, 25));
        selectFile->setStyleSheet(QString::fromUtf8(""));
        verticalWidget = new QWidget(groupBox2);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setGeometry(QRect(0, 60, 231, 151));
        verticalLayout_3 = new QVBoxLayout(verticalWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        fileLayout = new QVBoxLayout();
        fileLayout->setObjectName(QString::fromUtf8("fileLayout"));

        verticalLayout_3->addLayout(fileLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 30, 301, 41));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Files/logo1.png")));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Harry Plotter", nullptr));
        warningLabel->setText(QString());
        groupBox1->setTitle(QApplication::translate("MainWindow", "Plot function", nullptr));
        label1->setText(QApplication::translate("MainWindow", "Points for plotting:", nullptr));
        addFunction->setText(QApplication::translate("MainWindow", "Add function", nullptr));
        groupBox_4->setTitle(QString());
        label4->setText(QApplication::translate("MainWindow", "y range", nullptr));
        label6->setText(QString());
        label3->setText(QApplication::translate("MainWindow", "x range", nullptr));
        label5->setText(QString());
        gridBox->setText(QApplication::translate("MainWindow", "Show grid", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        rangeButton->setText(QApplication::translate("MainWindow", "Adjust x range", nullptr));
        groupBox2->setTitle(QApplication::translate("MainWindow", "Plot from file", nullptr));
        label2->setText(QApplication::translate("MainWindow", "Style:", nullptr));
        styleBox->setItemText(0, QApplication::translate("MainWindow", "Dots only", nullptr));
        styleBox->setItemText(1, QApplication::translate("MainWindow", "Linear interp.", nullptr));
        styleBox->setItemText(2, QApplication::translate("MainWindow", "Cubic spline", nullptr));

        selectFile->setText(QApplication::translate("MainWindow", "Select file", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
