#ifndef XL_TO_JSON_CONVERTER_TASK_V1_H
#define XL_TO_JSON_CONVERTER_TASK_V1_H

#include <xl_to_json_converter_task.h>

namespace xl
{
  class XlToJsonConverterThreadV1;
  class XlToJsonConverterTaskV1 final
      : public xl::XlToJsonConverterTask
  {
    Q_OBJECT
    using Handler   = XlToJsonConverterThreadV1;
    using HandlerP  = std::shared_ptr<Handler>;

    const QString _xlFile;
    const QString _tableName;
    const QString _outDir;

    HandlerP handler;
    friend class XlToJsonConverterThreadV1;
  public:
    explicit XlToJsonConverterTaskV1(const QString &xlFile
                                     , const QString &tableName
                                     , const QString &outDir);
    ~XlToJsonConverterTaskV1() override;

    // XlToJsonConverterTask interface
  public:
    QString tableName() const override;
    bool status() const override;
    bool isRunning() const override;
    double progress() const override;
    QString errorString() const override;

  public slots:
    void abort() override;
  };
}


#endif // XL_TO_JSON_CONVERTER_TASK_V1_H
