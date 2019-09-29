#include "widgetgrapth.h"
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

#include "graphitem.h"
#include "itemsfromjson.h"

const QString GET_LIST{ "get_list" };
const QString GET_DATA{ "get_data" };
const QString ID{"id"};
const QString DATA{"data"};
const QString TYPE_COMMAND{"type"};
const QString NAME{"name"};

WidgetGrapth::WidgetGrapth(QWidget *parent) :QWidget(parent)
{
  setWindowTitle( tr ( "Модуль отрисовки графиков" ) );
  list.setMinimumWidth( 350 );
}

void WidgetGrapth::initInterface()
{
    Q3DBars *widgetgraph = new Q3DBars();
    QWidget *container = QWidget::createWindowContainer(widgetgraph);

    QSize screenSize = widgetgraph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(&list);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    QComboBox *themeList = new QComboBox(this);
    themeList->addItem(tr("1"));
    themeList->addItem(tr("2"));
    themeList->addItem(tr("3"));
    themeList->addItem(tr("4"));
    themeList->addItem(tr("5"));
    themeList->addItem(tr("6"));
    themeList->addItem(tr("7"));
    themeList->addItem(tr("8"));
    themeList->setCurrentIndex(2);

    QPushButton *labelButton = new QPushButton(this);
    labelButton->setText(tr("Change label style"));
    labelButton->setVisible(false);

    QCheckBox *smoothCheckBox = new QCheckBox(this);
    smoothCheckBox->setText(tr("Smooth bars"));
    smoothCheckBox->setChecked(false);
    smoothCheckBox->setVisible(false);


    QComboBox *barStyleList = new QComboBox(this);
    barStyleList->addItem(tr("Стержень"), int(QAbstract3DSeries::MeshBar));
    barStyleList->addItem(tr("Пирамида"), int(QAbstract3DSeries::MeshPyramid));
    barStyleList->addItem(tr("Конус"), int(QAbstract3DSeries::MeshCone));
    barStyleList->addItem(tr("Цилиндр"), int(QAbstract3DSeries::MeshCylinder));
    barStyleList->setCurrentIndex(3);

    QPushButton *cameraButton = new QPushButton(this);
    cameraButton->setText(tr("Ракурс камеры"));

    QPushButton *zoomToSelectedButton = new QPushButton(this);
    zoomToSelectedButton->setText(tr("Зум"));

    QComboBox *selectionModeList = new QComboBox(this);
    selectionModeList->addItem(tr("Нет"),
                               int(QAbstract3DGraph::SelectionNone));
    selectionModeList->addItem(tr("Ячейка"),
                               int(QAbstract3DGraph::SelectionItem));
    selectionModeList->addItem(tr("Строка"),
                               int(QAbstract3DGraph::SelectionRow));
    selectionModeList->addItem(tr("Ячейка и строка"),
                               int(QAbstract3DGraph::SelectionItemAndRow));
    selectionModeList->addItem(tr("Столбец"),
                               int(QAbstract3DGraph::SelectionColumn));
    selectionModeList->addItem(tr("Ячейка и столбец"),
                               int(QAbstract3DGraph::SelectionItemAndColumn));
    selectionModeList->addItem(tr("Строка и столбец"),
                               int(QAbstract3DGraph::SelectionRowAndColumn));
    selectionModeList->addItem(tr("Ячейка, строка и столбец"),
                               int(QAbstract3DGraph::SelectionItemRowAndColumn));
    selectionModeList->addItem(tr("Срез по строке"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionRow));
    selectionModeList->addItem(tr("Срез по строке и элементу"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndRow));
    selectionModeList->addItem(tr("Срез по столбцу"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionColumn));
    selectionModeList->addItem(tr("Срез по столбцу и элементу"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndColumn));

    selectionModeList->setCurrentIndex(1);

    QCheckBox *backgroundCheckBox = new QCheckBox(this);
    backgroundCheckBox->setText(tr("Показать бэкграунд"));
    backgroundCheckBox->setChecked(false);
    backgroundCheckBox->setVisible(false);

    QCheckBox *gridCheckBox = new QCheckBox(this);
    gridCheckBox->setText(tr("Показать сетку"));
    gridCheckBox->setChecked(true);

    QCheckBox *seriesCheckBox = new QCheckBox(this);
    seriesCheckBox->setText(tr("Show second series"));
    seriesCheckBox->setChecked(false);
    seriesCheckBox->setVisible(false);

    QCheckBox *reverseValueAxisCheckBox = new QCheckBox(this);
    reverseValueAxisCheckBox->setText(tr("Отразить ось"));
    reverseValueAxisCheckBox->setChecked(false);

    QCheckBox *reflectionCheckBox = new QCheckBox(this);
    reflectionCheckBox->setText(tr("Show reflections"));
    reflectionCheckBox->setChecked(false);
    reflectionCheckBox->setVisible(false);

    //! [4]
    QSlider *rotationSliderX = new QSlider(Qt::Horizontal, this);
    rotationSliderX->setTickInterval(30);
    rotationSliderX->setTickPosition(QSlider::TicksBelow);
    rotationSliderX->setMinimum(-180);
    rotationSliderX->setValue(0);
    rotationSliderX->setMaximum(180);
    QSlider *rotationSliderY = new QSlider(Qt::Horizontal, this);
    rotationSliderY->setTickInterval(15);
    rotationSliderY->setTickPosition(QSlider::TicksAbove);
    rotationSliderY->setMinimum(-90);
    rotationSliderY->setValue(0);
    rotationSliderY->setMaximum(90);
    //! [4]

    QSlider *fontSizeSlider = new QSlider(Qt::Horizontal, this);
    fontSizeSlider->setTickInterval(10);
    fontSizeSlider->setTickPosition(QSlider::TicksBelow);
    fontSizeSlider->setMinimum(1);
    fontSizeSlider->setValue(30);
    fontSizeSlider->setMaximum(100);

    QFontComboBox *fontList = new QFontComboBox(this);
    fontList->setCurrentFont(QFont("Times New Roman"));

    QComboBox *shadowQuality = new QComboBox(this);
    shadowQuality->addItem(tr("None"));
    shadowQuality->addItem(tr("Low"));
    shadowQuality->addItem(tr("Medium"));
    shadowQuality->addItem(tr("High"));
    shadowQuality->addItem(tr("Low Soft"));
    shadowQuality->addItem(tr("Medium Soft"));
    shadowQuality->addItem(tr("High Soft"));
    shadowQuality->setCurrentIndex(5);
    shadowQuality->setVisible(false);

    rangeList = new QComboBox(this);
    rangeListByY = new QComboBox(this);

    QCheckBox *axisTitlesVisibleCB = new QCheckBox(this);
    axisTitlesVisibleCB->setText(tr("Показать подписи"));
    axisTitlesVisibleCB->setChecked(true);

    QCheckBox *axisTitlesFixedCB = new QCheckBox(this);
    axisTitlesFixedCB->setText(tr("Axis titles fixed"));
    axisTitlesFixedCB->setChecked(true);
    axisTitlesFixedCB->setVisible(false);

    QSlider *axisLabelRotationSlider = new QSlider(Qt::Horizontal, this);
    axisLabelRotationSlider->setTickInterval(10);
    axisLabelRotationSlider->setTickPosition(QSlider::TicksBelow);
    axisLabelRotationSlider->setMinimum(0);
    axisLabelRotationSlider->setValue(30);
    axisLabelRotationSlider->setMaximum(90);

    //! [5]
    vLayout->addWidget(new QLabel(tr("Поворот по горизонтали")));
    vLayout->addWidget(rotationSliderX, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(tr("Поворот по вертикали")));
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
    vLayout->addWidget(new QLabel(tr("Отобразить данные за год")));
    vLayout->addWidget(rangeList);
    vLayout->addWidget(new QLabel(tr("Дополнительный фильтр")));
    vLayout->addWidget(rangeListByY);
    vLayout->addWidget(new QLabel(tr("Стиль колонок")));
    vLayout->addWidget(barStyleList);
    vLayout->addWidget(new QLabel(tr("Режим выбора")));
    vLayout->addWidget(selectionModeList);
    vLayout->addWidget(new QLabel(tr("Тема")));
    vLayout->addWidget(themeList);
    //vLayout->addWidget(new QLabel(tr("Adjust shadow quality")));
    vLayout->addWidget(shadowQuality);
    vLayout->addWidget(new QLabel(tr("Шрифт")));
    vLayout->addWidget(fontList);
    vLayout->addWidget(new QLabel(tr("Размер шрифта")));
    vLayout->addWidget(fontSizeSlider);
    vLayout->addWidget(new QLabel(tr("Поворот подписей")));
    vLayout->addWidget(axisLabelRotationSlider, 1, Qt::AlignTop);

    fontSizeSlider->setValue(fontSizeSlider->value()+10);

    modifier = new GraphModifier(widgetgraph);
    modifier->setTitleByX("Регионы");
    modifier->setTitleByY("Год");
    modifier->setTitleByZ("");
    modifier->changeTheme(2);
    modifier->changeFontSize(fontSizeSlider->value());
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

    QObject::connect(rangeListByY, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeRangeByY(int)));

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

    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &WidgetGrapth::onReply);

    QObject::connect(&list, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(onSelectGraph(QListWidgetItem *)));


    QJsonObject outData;
    outData[ TYPE_COMMAND ] = GET_LIST;
    QNetworkRequest request ( QUrl("http://192.168.43.28:8080/response" ) );
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager.post( request, QJsonDocument( outData ).toJson() );

    list.setWordWrap(true);
}

#include "graphitem.h"

void WidgetGrapth::setJsonData(const QString &filePath)
{
    auto items = ItemsFromJson::fromJson(filePath);

    rangeList->clear();
    rangeListByY->clear();
    for (auto i : items ){
        rangeListByY->addItem(i.rowTitle);
    }

    rangeListByY->addItem("Все");

    if ( !items.empty()){
        auto values = items[0].columns;
        for (Column i : values){
            rangeList->addItem(i.caption);
        }

    }
    rangeList->addItem(tr("Все"));

    modifier->setData(items);

    rangeList->setCurrentIndex(rangeList->count()-1);

//    this->setWindowTitle(ItemsFromJson::tableTitle);
}

void WidgetGrapth::setJsonData(const QByteArray &data)
{
    auto items = ItemsFromJson::fromJson(data);

    rangeList->clear();
    rangeListByY->clear();

    for (auto i : items ){
        rangeListByY->addItem(i.rowTitle);
    }

    rangeListByY->addItem("Все");

    if ( !items.empty()){
        auto values = items[0].columns;
        for (Column i : values){
            rangeList->addItem(i.caption);
        }

    }
    rangeList->addItem(tr("Все"));

    modifier->setData(items);

    if ( rangeList->count() != 0 )
      rangeList->setCurrentIndex(rangeList->count()-1);
//    this->setWindowTitle(ItemsFromJson::tableTitle);
//    rangeListByY->currentIndexChanged( rangeListByY->currentIndex() );
//    rangeListByY->setCurrentIndex( rangeListByY->count() - 1 );
}

void WidgetGrapth::onReply(QNetworkReply *reply)
{

   auto data = reply->readAll();
   QJsonParseError error;
   auto obj = QJsonDocument::fromJson( data, &error ).object();
   if ( error.error == QJsonParseError::NoError ) {
       //w.setJsonData(obj.toJson());
       qDebug() << "type" <<obj.value("type");
       if (obj.value(TYPE_COMMAND)==GET_LIST){
           auto lst = obj.value(DATA).toArray();
           qDebug() << "coutn" << lst.count();

           for (auto it =0; it < lst.count(); ++it ) {
               list.addItem(lst[it].toObject().value("name").toString());
               listId.append(lst[it].toObject().value("id").toString());
//               qDebug() << "id" << lst[it].toObject().value("id");
//               qDebug() << "name" << lst[it].toObject().value("name");
//               qDebug() << "**************";
           }
       }
       if (obj.value(TYPE_COMMAND)==GET_DATA){
            qDebug( )<<"Get graph";
            setJsonData( data );
       }

   } else {
       qDebug() << "Error reply" << data;
   }
}

void WidgetGrapth::onSelectGraph(QListWidgetItem *)
{
    QJsonObject outData;
    outData[ TYPE_COMMAND ] = GET_DATA;
    outData[ID]=listId[list.currentRow()];
    setWindowTitle( list.currentItem()->text() );
    QNetworkRequest request ( QUrl("http://192.168.43.28:8080/response" ) );
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager.post( request, QJsonDocument( outData ).toJson() );
    qDebug() << "select" << listId[list.currentRow()];
}
