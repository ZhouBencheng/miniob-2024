#include "src/observer/common/rc.h"
#include "common/log/log.h"
#include "src/observer/common/type/vector_type.h"

namespace common {

bool is_float(const char *str)
{
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '.') {
            return true;
        }
    }
    return false;
}


// 初始化value.pointer_value_指向零地址，因此将该指针传入函数时需要修改该指针指向的地址，而不是修改指针指向内存的内容
RC vector_from_string(char *str, char **data, int *len, VectorType::Type *type)
{
    if (str[0] != '[' || str[strlen(str) - 1] != ']') { // 判断是否用中括号包裹
        LOG_WARN("invalid vector string format. str=%s", str);
        return RC::INVALID_ARGUMENT;
    }
    // 去掉头尾括号字符
    str[strlen(str) - 1] = '\0';
    str++;

    char *p = strtok(str, ", ");
    *len = 0;
    if (p == nullptr) { // 空向量
        LOG_INFO("empty vector element. str=%s", str);
        return RC::SUCCESS;
    }
    if (is_float(p)) { // 当前仅根据数组第一个元素判断向量是否为浮点数
        *type = VectorType::Type::FLOAT;
    } else {
        *type = VectorType::Type::INT;
    }
    char *data_temp = (char *)malloc(1010 * sizeof(int));
    while (p != nullptr) {
        if (*type == VectorType::Type::INT) {
            int *q = (int *)data_temp;
            q[*len] = atoi(p);
        } else {
            float *q = (float *)data_temp;
            q[*len] = atof(p);
        }
        p = strtok(NULL, ", ");
        (*len)++;
    }
    *data = data_temp;
    *len *= 4;
    return RC::SUCCESS;
}

RC vector_to_string(char *data, int len, VectorType::Type type, string &str)
{
    // 认为len传入的Value中的length_字节长度，因此需要除以4获取元素个数
    len /= 4;
    if (type == VectorType::Type::INT) {
        int *p = (int *)data;
        str += "[";
        for (int i = 0; i < len; i++) {
            str += std::to_string(p[i]);
            if (i != len - 1) {
                str += ",";
            }
        }
        str += "]";
    } else if (type == VectorType::Type::FLOAT) {
        float *p = (float *)data;
        str += "[";
        for (int i = 0; i < len; i++) {
            str += std::to_string(p[i]);
            if (i != len - 1) {
                str += ",";
            }
        }
        str += "]";
    } else {
        LOG_WARN("unknown vector type. type=%d", type);
        return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
}

}