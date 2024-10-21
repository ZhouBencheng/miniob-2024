//
// Created by 周奔成 on 24-10-10.
//

#pragma once

#include "src/observer/common/rc.h"
#include <iomanip>

namespace common {

inline bool is_leap_year(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline bool is_valid_date(int year, int month, int day) {
  int month_days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (year < 1900 || year > 9999 ||
      month < 1 || month > 12 ||
      day < 1 || day > month_days[month - 1]) {
      LOG_WARN("Invalid date: %d-%d-%d", year, month, day);
    return false;
  }
  if (month == 2 && day == 29 && !is_leap_year(year)) {
    LOG_WARN("Invalid date for the leap year: %d-%d-%d", year, month, day);
    return false;
  }
  return true;
}

inline RC date_from_string(const string &str, int32_t *date)
{
  int year, month, day;
  const char *s = str.c_str(); // 获取str字符串的C风格指针字符串
  int num = sscanf(s, "%d-%d-%d", &year, &month, &day);
  if (num != 3) {
    LOG_WARN("Invalid date string: %s", s);
    return RC::INVALID_ARGUMENT;
  }
  // 以下部分判断非法日期
  if (!is_valid_date(year, month, day)) {
    return RC::INVALID_ARGUMENT;
  }
  *date = year * 10000 + month * 100 + day;
  return RC::SUCCESS;
}

inline RC date_to_string(int32_t date, string &str)
{
  int  year  = date / 10000;
  int  month = date % 10000 / 100;
  int  day   = date % 100;
  LOG_DEBUG("date=%d, year=%d, month=%d, day=%d", date, year, month, day);
  stringstream ss;
  ss << year << "-" << std::setw(2) << std::setfill('0') << month << "-" << std::setw(2) << std::setfill('0') << day;
  str = ss.str();
  return RC::SUCCESS;
}

}
