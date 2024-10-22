#pragma once


namespace common {

// helper function 判断当前字符串是否为浮点数(是否存在'.'字符)
bool is_float(const char *str);
/**
 * @brief 将字符串解析为向量
 * @param str  字符串
 * @param data (out)指向向量元素第一个字节的指针
 * @param len  (out)向量元素个数
 */
RC vector_from_string(char *str, char **data, int *len);

RC vector_to_string(char *data, int len, string &str);

}