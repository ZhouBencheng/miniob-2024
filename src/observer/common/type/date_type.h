//
// Created by 周奔成 on 24-10-9.
//

#pragma once

#include "common/type/data_type.h"

/**
 * @brief 日期类型，在底层用int32_t存储
 * @ingroup DataType
 */
class DateType : public DataType
{
public:
  DateType(): DataType(AttrType::DATES) {}
  virtual ~DateType() {}

  int compare(const Value &left, const Value &right) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  RC to_string(const Value &val, string &result) const override;
};
