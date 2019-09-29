#ifndef XL_AX_READER_H
#define XL_AX_READER_H

#include <QAxObject>
#include <xl_reader.h>

class XlAxReader final
    : public xl::XlReader
{
  Q_OBJECT
public:
  using QAxObjectP  = std::shared_ptr<QAxObject>;
  QAxObjectP  _excel, _workbooks, _workbook, _sheets;
  TableList   _tables;
public:
  explicit XlAxReader();
  ~XlAxReader() override;

  // XlReader interface
public:
  bool isOpen() const override;
  TableP table(int index) const override;
  TableP table(const QString &name) const override;
  TableList tables() const override;
  int count() const override;

public slots:
  bool open(const QString &path, QString *error) override;
  void close() override;
};

#endif // XL_AX_READER_H
