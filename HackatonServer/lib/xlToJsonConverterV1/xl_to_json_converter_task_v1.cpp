#include "xl_to_json_converter_task_v1.h"
using namespace xl;

#include "xl_to_json_converter_thread_v1.h"

XlToJsonConverterTaskV1::XlToJsonConverterTaskV1(const QString &xlFile, const QString &tableName, const QString &outDir)
  : xl::XlToJsonConverterTask ()
  , _xlFile ( xlFile )
  , _tableName ( tableName )
  , _outDir ( outDir )
  , handler ( std::make_shared<Handler>( this ) )
{
  handler->start();
}

XlToJsonConverterTaskV1::~XlToJsonConverterTaskV1()
{
  if ( isRunning() )
    handler->abort();

  handler.reset();
}

QString XlToJsonConverterTaskV1::tableName() const
{
  return _tableName;
}

bool xl::XlToJsonConverterTaskV1::status() const
{
  return handler->status();
}

bool xl::XlToJsonConverterTaskV1::isRunning() const
{
  return handler->isRunning();
}

double xl::XlToJsonConverterTaskV1::progress() const
{
  return handler->progress();
}

QString xl::XlToJsonConverterTaskV1::errorString() const
{
  return handler->errorString();
}

void xl::XlToJsonConverterTaskV1::abort()
{
  return handler->abort();
}
