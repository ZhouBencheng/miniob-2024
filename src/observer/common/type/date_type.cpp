//
// Created by 周奔成 on 24-10-9.
//

#include "date_type.h"
#include "common/log/log.h"
#include "common/value.h"
#include "deps/common/lang/date.h"
#include "common/lang/comparator.h"
#include <iomanip>

int DateType::compare(const Value &left, const Value &right) const {
    ASSERT(left.attr_type() == AttrType::DATES, "left type is not date.");
    ASSERT(right.attr_type() == AttrType::DATES, "right type is not date.");
    int left_date = left.get_date();
    int right_date = right.get_date();
    return common::compare_int((void *)&left_date, (void *)&right_date);
}

RC DateType::set_value_from_str(Value &val, const string &data) const {
  int32_t date = INT32_MAX;
  RC rc = common::date_from_string(data, &date);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  val.set_int(date);
  val.set_type(AttrType::DATES);
  return RC::SUCCESS;
}

RC DateType::to_string(const Value &val, string &result) const {
  ASSERT(val.attr_type() == AttrType::DATES, "val type is not date.");
  return common::date_to_string(val.get_date(), result);
}
