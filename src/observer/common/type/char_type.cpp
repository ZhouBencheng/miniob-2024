/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"
#include "common/lang/date.h"
#include "common/lang/vector_utils.h"

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}
int CharType::like(const Value &left, const Value &right) const {
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  LOG_DEBUG("like char. left=, right=");
  return common::like_string(
      left.value_.pointer_value_, left.length_, right.value_.pointer_value_, right.length_);
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::DATES: {
      int32_t date = INT32_MAX;
      RC      rc   = common::date_from_string(val.get_string(), &date);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      result.set_date(date);
      LOG_DEBUG("cast char to date. char=%s, date=%d", val.get_string().c_str(), date);
    } break;
    case AttrType::VECTORS:{
      char *data = nullptr;
      int   len  = 0;
      RC rc = common::vector_from_string(val.value_.pointer_value_, 
                  &data, &len);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to convert string to vector. s=%s", val.value_.pointer_value_);
        return rc;
      }
      result.set_vector(data, len);
    } break;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  } else if (type == AttrType::DATES) {
    return 1;
  } else if (type == AttrType::VECTORS) {
    return 1;
  } else if (type == AttrType::FLOATS) {
    return 2;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}