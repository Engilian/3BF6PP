/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphmodifier.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QtGui/QFontDatabase>
#include "itemsfromjson.h"
#include "graphitem.h"

#define TR(x) QApplication::translate( "app", x )

int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

int main(int argc, char **argv)
{
    //! [0]
    QApplication app(argc, argv);
    Q3DBars *widgetgraph = new Q3DBars();
    QWidget *container = QWidget::createWindowContainer(widgetgraph);
    //! [0]

    if (!widgetgraph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = widgetgraph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    //! [1]
    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    //! [1]

//    widget->setWindowTitle(TR("Average temperatures in Oulu and Helsinki, Finland (2006-2013)"));

    QComboBox *themeList = new QComboBox(widget);
    themeList->addItem(TR("1"));
    themeList->addItem(TR("2"));
    themeList->addItem(TR("3"));
    themeList->addItem(TR("4"));
    themeList->addItem(TR("5"));
    themeList->addItem(TR("6"));
    themeList->addItem(TR("7"));
    themeList->addItem(TR("8"));
    themeList->setCurrentIndex(0);

    QPushButton *labelButton = new QPushButton(widget);
    labelButton->setText(TR("Change label style"));
    labelButton->setVisible(false);

    QCheckBox *smoothCheckBox = new QCheckBox(widget);
    smoothCheckBox->setText(TR("Smooth bars"));
    smoothCheckBox->setChecked(false);
    smoothCheckBox->setVisible(false);


    QComboBox *barStyleList = new QComboBox(widget);
    barStyleList->addItem(TR("Стержень"), int(QAbstract3DSeries::MeshBar));
    barStyleList->addItem(TR("Пирамида"), int(QAbstract3DSeries::MeshPyramid));
    barStyleList->addItem(TR("Конус"), int(QAbstract3DSeries::MeshCone));
    barStyleList->addItem(TR("Цилиндр"), int(QAbstract3DSeries::MeshCylinder));
    barStyleList->setCurrentIndex(3);

    QPushButton *cameraButton = new QPushButton(widget);
    cameraButton->setText(TR("Ракурс камеры"));

    QPushButton *zoomToSelectedButton = new QPushButton(widget);
    zoomToSelectedButton->setText(TR("Зум"));

    QComboBox *selectionModeList = new QComboBox(widget);
    selectionModeList->addItem(TR("Нет"),
                               int(QAbstract3DGraph::SelectionNone));
    selectionModeList->addItem(TR("Ячейка"),
                               int(QAbstract3DGraph::SelectionItem));
    selectionModeList->addItem(TR("Строка"),
                               int(QAbstract3DGraph::SelectionRow));
    selectionModeList->addItem(TR("Ячейка и строка"),
                               int(QAbstract3DGraph::SelectionItemAndRow));
    selectionModeList->addItem(TR("Столбец"),
                               int(QAbstract3DGraph::SelectionColumn));
    selectionModeList->addItem(TR("Ячейка и столбец"),
                               int(QAbstract3DGraph::SelectionItemAndColumn));
    selectionModeList->addItem(TR("Строка и столбец"),
                               int(QAbstract3DGraph::SelectionRowAndColumn));
    selectionModeList->addItem(TR("Ячейка, строка и столбец"),
                               int(QAbstract3DGraph::SelectionItemRowAndColumn));
    selectionModeList->addItem(TR("Срез по строке"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionRow));
    selectionModeList->addItem(TR("Срез по строке и элементу"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndRow));
    selectionModeList->addItem(TR("Срез по столбцу"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionColumn));
    selectionModeList->addItem(TR("Срез по столбцу и элементу"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndColumn));

    selectionModeList->setCurrentIndex(1);

    QCheckBox *backgroundCheckBox = new QCheckBox(widget);
    backgroundCheckBox->setText(TR("Показать бэкграунд"));
    backgroundCheckBox->setChecked(false);
    backgroundCheckBox->setVisible(false);

    QCheckBox *gridCheckBox = new QCheckBox(widget);
    gridCheckBox->setText(TR("Показать сетку"));
    gridCheckBox->setChecked(true);

    QCheckBox *seriesCheckBox = new QCheckBox(widget);
    seriesCheckBox->setText(TR("Show second series"));
    seriesCheckBox->setChecked(false);
    seriesCheckBox->setVisible(false);

    QCheckBox *reverseValueAxisCheckBox = new QCheckBox(widget);
    reverseValueAxisCheckBox->setText(TR("Отразить ось"));
    reverseValueAxisCheckBox->setChecked(false);

    QCheckBox *reflectionCheckBox = new QCheckBox(widget);
    reflectionCheckBox->setText(TR("Show reflections"));
    reflectionCheckBox->setChecked(false);
    reflectionCheckBox->setVisible(false);

    //! [4]
    QSlider *rotationSliderX = new QSlider(Qt::Horizontal, widget);
    rotationSliderX->setTickInterval(30);
    rotationSliderX->setTickPosition(QSlider::TicksBelow);
    rotationSliderX->setMinimum(-180);
    rotationSliderX->setValue(0);
    rotationSliderX->setMaximum(180);
    QSlider *rotationSliderY = new QSlider(Qt::Horizontal, widget);
    rotationSliderY->setTickInterval(15);
    rotationSliderY->setTickPosition(QSlider::TicksAbove);
    rotationSliderY->setMinimum(-90);
    rotationSliderY->setValue(0);
    rotationSliderY->setMaximum(90);
    //! [4]

    QSlider *fontSizeSlider = new QSlider(Qt::Horizontal, widget);
    fontSizeSlider->setTickInterval(10);
    fontSizeSlider->setTickPosition(QSlider::TicksBelow);
    fontSizeSlider->setMinimum(1);
    fontSizeSlider->setValue(30);
    fontSizeSlider->setMaximum(100);

    QFontComboBox *fontList = new QFontComboBox(widget);
    fontList->setCurrentFont(QFont("Times New Roman"));

    QComboBox *shadowQuality = new QComboBox(widget);
    shadowQuality->addItem(TR("None"));
    shadowQuality->addItem(TR("Low"));
    shadowQuality->addItem(TR("Medium"));
    shadowQuality->addItem(TR("High"));
    shadowQuality->addItem(TR("Low Soft"));
    shadowQuality->addItem(TR("Medium Soft"));
    shadowQuality->addItem(TR("High Soft"));
    shadowQuality->setCurrentIndex(5);
    shadowQuality->setVisible(false);

    QComboBox *rangeList = new QComboBox(widget);
    rangeList->addItem(TR("2006"));
    rangeList->addItem(TR("2007"));
    rangeList->addItem(TR("2008"));
    rangeList->addItem(TR("2009"));
    rangeList->addItem(TR("2010"));
    rangeList->addItem(TR("2011"));
    rangeList->addItem(TR("2012"));
    rangeList->addItem(TR("2013"));
    rangeList->addItem(TR("Все"));
    rangeList->setCurrentIndex(8);

    QCheckBox *axisTitlesVisibleCB = new QCheckBox(widget);
    axisTitlesVisibleCB->setText(TR("Показать подписи"));
    axisTitlesVisibleCB->setChecked(true);

    QCheckBox *axisTitlesFixedCB = new QCheckBox(widget);
    axisTitlesFixedCB->setText(TR("Axis titles fixed"));
    axisTitlesFixedCB->setChecked(true);
    axisTitlesFixedCB->setVisible(false);

    QSlider *axisLabelRotationSlider = new QSlider(Qt::Horizontal, widget);
    axisLabelRotationSlider->setTickInterval(10);
    axisLabelRotationSlider->setTickPosition(QSlider::TicksBelow);
    axisLabelRotationSlider->setMinimum(0);
    axisLabelRotationSlider->setValue(30);
    axisLabelRotationSlider->setMaximum(90);

    //! [5]
    vLayout->addWidget(new QLabel(TR("Поворот по горизонтали")));
    vLayout->addWidget(rotationSliderX, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(TR("Поворот по вертикали")));
    vLayout->addWidget(rotationSliderY, 0, Qt::AlignTop);
    //! [5]
    vLayout->addWidget(labelButton, 0, Qt::AlignTop);
    vLayout->addWidget(cameraButton, 0, Qt::AlignTop);
    vLayout->addWidget(zoomToSelectedButton, 0, Qt::AlignTop);
    vLayout->addWidget(backgroundCheckBox);
    vLayout->addWidget(gridCheckBox);
    vLayout->addWidget(smoothCheckBox);
    vLayout->addWidget(reflectionCheckBox);
    vLayout->addWidget(seriesCheckBox);
    vLayout->addWidget(reverseValueAxisCheckBox);
    vLayout->addWidget(axisTitlesVisibleCB);
    vLayout->addWidget(axisTitlesFixedCB);
    vLayout->addWidget(new QLabel(TR("Отобразить данные за год")));
    vLayout->addWidget(rangeList);
    vLayout->addWidget(new QLabel(TR("Стиль колонок")));
    vLayout->addWidget(barStyleList);
    vLayout->addWidget(new QLabel(TR("Режим выбора")));
    vLayout->addWidget(selectionModeList);
    vLayout->addWidget(new QLabel(TR("Тема")));
    vLayout->addWidget(themeList);
    //vLayout->addWidget(new QLabel(TR("Adjust shadow quality")));
    vLayout->addWidget(shadowQuality);
    vLayout->addWidget(new QLabel(TR("Шрифт")));
    vLayout->addWidget(fontList);
    vLayout->addWidget(new QLabel(TR("Размер шрифта")));
    vLayout->addWidget(fontSizeSlider);
    vLayout->addWidget(new QLabel(TR("Поворот подписей")));
    vLayout->addWidget(axisLabelRotationSlider, 1, Qt::AlignTop);


    auto items = ItemsFromJson::fromJson(QString("C:/1.json"));

    QStringList lst = {"Белгородская область","Амурская область","Магаданская область","Забайкальский край","Республика Бурятия"};
    QStringList ylst ={"2000","2001","2002","2003","2004","2005","2006","2007","2008","2009","2010","2011"};
    //! [2]
    GraphModifier *modifier = new GraphModifier(widgetgraph);
    QList<GraphItem> itms;
    for (int i=0; i<lst.count();++i){
        GraphItem itm;
        itm.rowTitle = lst.at(i);
        for (int j=0; j<ylst.count();++j){
            Column c;
            c.caption = ylst.at(j);
            c.value= j * randomBetween( 0,50 );
            itm.columns.append( c );
        }
        itms.append(itm);
    }
    modifier->setTitleByX("Регионы");
    modifier->setTitleByY("Год");
    modifier->setTitleByZ("Родилось");
    modifier->setMinMax(0,20000);
    modifier->setData(items);
    //! [2]

    //! [6]
    QObject::connect(rotationSliderX, &QSlider::valueChanged, modifier, &GraphModifier::rotateX);
    QObject::connect(rotationSliderY, &QSlider::valueChanged, modifier, &GraphModifier::rotateY);
    //! [6]

    QObject::connect(labelButton, &QPushButton::clicked, modifier,
                     &GraphModifier::changeLabelBackground);
    QObject::connect(cameraButton, &QPushButton::clicked, modifier,
                     &GraphModifier::changePresetCamera);
    QObject::connect(zoomToSelectedButton, &QPushButton::clicked, modifier,
                     &GraphModifier::zoomToSelectedBar);

    QObject::connect(backgroundCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setBackgroundEnabled);
    QObject::connect(gridCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setGridEnabled);
    QObject::connect(smoothCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setSmoothBars);
    QObject::connect(seriesCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setSeriesVisibility);
    QObject::connect(reverseValueAxisCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setReverseValueAxis);
    QObject::connect(reflectionCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setReflection);

    QObject::connect(modifier, &GraphModifier::backgroundEnabledChanged,
                     backgroundCheckBox, &QCheckBox::setChecked);
    QObject::connect(modifier, &GraphModifier::gridEnabledChanged,
                     gridCheckBox, &QCheckBox::setChecked);

    QObject::connect(rangeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeRange(int)));

    QObject::connect(barStyleList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeStyle(int)));

    QObject::connect(selectionModeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeSelectionMode(int)));

    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeTheme(int)));

    QObject::connect(shadowQuality, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeShadowQuality(int)));

    QObject::connect(modifier, &GraphModifier::shadowQualityChanged, shadowQuality,
                     &QComboBox::setCurrentIndex);
    QObject::connect(widgetgraph, &Q3DBars::shadowQualityChanged, modifier,
                     &GraphModifier::shadowQualityUpdatedByVisual);

    QObject::connect(fontSizeSlider, &QSlider::valueChanged, modifier,
                     &GraphModifier::changeFontSize);
    QObject::connect(fontList, &QFontComboBox::currentFontChanged, modifier,
                     &GraphModifier::changeFont);

    QObject::connect(modifier, &GraphModifier::fontSizeChanged, fontSizeSlider,
                     &QSlider::setValue);
    QObject::connect(modifier, &GraphModifier::fontChanged, fontList,
                     &QFontComboBox::setCurrentFont);

    QObject::connect(axisTitlesVisibleCB, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setAxisTitleVisibility);
    QObject::connect(axisTitlesFixedCB, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setAxisTitleFixed);
    QObject::connect(axisLabelRotationSlider, &QSlider::valueChanged, modifier,
                     &GraphModifier::changeLabelRotation);
    //! [3]
    widget->show();
    return app.exec();
    //! [3]
}
