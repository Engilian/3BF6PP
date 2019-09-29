#include <QCoreApplication>

#include <QDebug>
#include <pfactory/pfactory.h>
#include <xl_to_json_converter.h>
#include <xl_to_json_converter_task.h>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  try {
    pf::FactoryExp::inst()->add<xl::XlToJsonConverter>( "xl::XlToJsonConverter" );
  } catch (...) { }

  try {
    auto converter = pf::FactoryExp::inst()->create<xl::XlToJsonConverter>();
    auto task = converter->start(  "c:\\test.xlsx", "родившиеся", "c:\\" );
    QObject::connect ( task.get(),    &xl::XlToJsonConverterTask::finished,
                       [task]{
        qDebug() << task->status();
        QCoreApplication::exit( 0 );
    });

    QObject::connect ( task.get(),    &xl::XlToJsonConverterTask::progressChanged,
                       [task]{
        qDebug() << task->progress();
    });

    return a.exec();
  } catch (...) {
  }


  return a.exec();
}
