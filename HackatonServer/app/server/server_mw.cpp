#include "server_mw.h"
#include "ui_server_mw.h"

#include <QDir>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <xl_reader.h>
#include <QInputDialog>
#include <pfactory/pfactory.h>
#include "table_list_widget.h"
#include <xl_to_json_converter.h>

ServerMw::ServerMw(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::ServerMw)
{
  ui->setupUi(this);
  connect( ui->importFromXl,    &QAction::triggered,
           this,                &ServerMw::importXl );
  initilizeHttp();
}

ServerMw::~ServerMw()
{
  delete ui;
}

void ServerMw::importXl()
{
  auto path = QFileDialog::getOpenFileName( this
                                            , tr ( "Выберите файл для импорта" )
                                            , QDir::homePath()
                                            , tr ( "Таблицы Excel (*.xlsx *.xl *.xlsm *.xlsb)" ) );
  if ( path.isEmpty() ) return;

  try {
      pf::PFactoryExp::inst()->add<xl::XlReader>( "xl::XlReader" );
  } catch (...) { }

  try {
      pf::PFactoryExp::inst()->add<xl::XlToJsonConverter>( "xl::XlToJsonConverter" );
  } catch (...) { }

  try {
    auto reader = std::shared_ptr<xl::XlReader> (
          pf::PFactoryExp::inst()->create<xl::XlReader>() );
    QString error;
    if ( reader->open( path, &error ) ) {
      TableListWidget d ( reader );
      if ( d.exec() == QDialog::Accepted ) {
        using Converter = xl::XlToJsonConverter;
        using ConverterP = std::shared_ptr<Converter>;

        auto directory = QDir::fromNativeSeparators( QCoreApplication::applicationDirPath() + "/db/import" );

        try {
          auto converter = ConverterP ( pf::PFactoryExp::inst()->create<Converter>() );
          for ( auto &name: d.selectedTables() ) {
            auto task = converter->start( path, name, directory );
            connect( task.get(),    &xl::XlToJsonConverterTask::finished,
                     [this, task, name, path]() {
              ui->log->append( tr ( "Закончен разбор %1 листа %2 -> %3" )
                               .arg( path )
                               .arg( name )
                               .arg( task->status() ? tr ( "успешно" ) : tr ( "ошибка" ) ));
            });

            ui->log->append( tr ( "Начат разбор %1 листа %2" )
                             .arg( path ).arg( name ) );
            ui->tasks->add( task );
          }
        } catch (...) {
          QMessageBox::critical( this
                                 , tr ( "Критическая ошибка" )
                                 , tr ( "Не удалось создать модуль импорта." )
                                 , tr ( "Ок" ) );
        }
      }
      reader->close();
    } else {
      QMessageBox::warning( this
                             , tr ( "Ошибка" )
                             , tr ( "Не удалось открыть файл: %1." ).arg( error )
                             , tr ( "Ок" ) );
    }
  } catch (...) {
  QMessageBox::critical( this
                         , tr ( "Критическая ошибка" )
                         , tr ( "Не удалось открыть файл. Файл или модуль загрузки поврежден." )
                         , tr ( "Ок" ) );

  }
}

void ServerMw::initilizeHttp()
{
  const QString listenerSettingPath = QDir::fromNativeSeparators(
        QCoreApplication::applicationDirPath() + "/http.ini" );
  if ( !QFile ( listenerSettingPath ).exists() ) {
      QFile out ( listenerSettingPath );
      if ( out.open( QIODevice::WriteOnly ) ) {
        out.write( "[listener]\n"
                   ";host=192.168.0.100\n"
                   "port=8080\n"
                   "minThreads=4\n"
                   "maxThreads=100\n"
                   "cleanupInterval=60000\n"
                   "readTimeout=60000\n"
                   "maxRequestSize=16000\n"
                   "maxMultiPartSize=10000000" );
        out.close();
      }
  }

  request = std::make_shared<Request>();
  auto setting = new QSettings( "http_my_her.conf"
                                , QSettings::Format::NativeFormat );
  setting->setValue( "port", 8080 );
  setting->setValue( "minThreads", 4 );
  setting->setValue( "maxThreads", 100 );
  setting->setValue( "cleanupInterval", 60000 );
  setting->setValue( "readTimeout", 60000 );
  setting->setValue( "maxRequestSize", 16000 );
  setting->setValue( "maxMultiPartSize", 10000000 );
  listener = std::make_shared<Listener>( setting, request.get() );
  listener->close();
  listener->listen();
}
