#ifndef XL_TO_JSON_CONVERTER_THREAD_V1_H
#define XL_TO_JSON_CONVERTER_THREAD_V1_H

#include <atomic>
#include <QThread>

namespace xl
{
  class XlTable;
  class XlReader;
  class XlToJsonConverterTaskV1;
  class XlToJsonConverterThreadV1 final
      : public QThread
  {
    Q_OBJECT
    using Reader  = XlReader;
    using ReaderP = std::shared_ptr<Reader>;
    using Table   = XlTable;
    using TableP  = std::shared_ptr<Table>;

    XlToJsonConverterTaskV1 *event;

    QString             _error;
    std::atomic<double> _progress;
    std::atomic_bool    _status, _isRun, _isAbort;
  public:
    explicit XlToJsonConverterThreadV1(XlToJsonConverterTaskV1 *event);
    ~XlToJsonConverterThreadV1() override;

  public:
    bool status() const;
    bool isRunning() const;
    double progress() const;
    QString errorString() const;

  public slots:
    void abort();

  private:
    ReaderP createReader() const;
    QRect getRowRect(const TableP &table, const QJsonObject &tableTemplate) const;
    QRect getColumnRect(const TableP &table, const QJsonObject &tableTemplate) const;
    QJsonObject getRowObject(int row, const QRect &rowRect, const QRect &columnRect, const TableP &table, const QJsonObject &tableTamplate) const;
    QJsonObject getColumnObject(int row, int column, const QRect &columnRect, const TableP &table, const QJsonObject &tableTamplate) const;
  private slots:
    void runDo(const TableP &table, const QJsonObject &tableTemplate);
    void runDoItem(const TableP &table, const QJsonObject &tableTemplate, double progress);

  private slots:
    QStringList getAreaList(int level, int depth) const;

    // QThread interface
  protected:
    void run() override;
  };
}

#endif // XL_TO_JSON_CONVERTER_THREAD_V1_H
