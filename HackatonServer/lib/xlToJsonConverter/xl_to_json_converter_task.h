#ifndef XL_TO_JSON_CONVERTER_TASK_H
#define XL_TO_JSON_CONVERTER_TASK_H

#include <QObject>

namespace xl
{
  class XlTable;
  class XlToJsonConverterTask
      : public QObject
  {
    Q_OBJECT
  public:
    using Table     = XlTable;
    using TableP    = std::shared_ptr<Table>;
  protected:
    explicit XlToJsonConverterTask();
  public:
    virtual ~XlToJsonConverterTask() override;

  public:
    virtual QString tableName() const = 0;
    virtual bool status() const = 0;
    virtual bool isRunning() const = 0;
    virtual double progress() const = 0;
    virtual QString errorString() const = 0;

  public slots:
    virtual void abort() = 0;

  signals:
    void finished();
    void progressChanged();
  };
}


#endif // XL_TO_JSON_CONVERTER_TASK_H
