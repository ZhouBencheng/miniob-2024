#include "src/observer/common/rc.h"
#include "common/log/log.h"
#include "src/observer/common/type/vector_type.h"
#include <iomanip>

namespace common {

bool is_float(const char *str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '.') {
            return true;
        }
    }
    return false;
}


// 初始化value.pointer_value_指向零地址，因此将该指针传入函数时需要修改该指针指向的地址，而不是修改指针指向内存的内容
RC vector_from_string(char *str, char **data, int *len)
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
    bool is_int = !is_float(p);
    char *data_temp = (char *)malloc(1010 * sizeof(int));
    while (p != nullptr) {
        if (is_int) {
            int *q = (int *)data_temp;
            q[*len] = atoi(p);
        } else {
            float *q = (float *)data_temp;
            q[*len] = atof(p);
        }
        p = strtok(NULL, ", ");
        (*len)++;
    }
    bool *q = (bool *)data_temp;
    q[*len * 4] = is_int; // 使用最后一个字节存储bool值，表示是否为整数
    *data = data_temp;
    *len = *len * 4 + 1;  // 最后一个字节存储bool是否为null，倒数第二个字节存储是否为整数，因此需要加2
    return RC::SUCCESS;
}

// helper function 浮点数字符串最多保留两位小数，去掉末尾多余的0
string formatFloat(float value) 
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    std::string str = oss.str();
    
    // 移除末尾多余的0
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    
    // 如果最后一个字符是小数点，也移除它
    if (str.back() == '.') {
        str.pop_back();
    }
    
    return str;
}

RC vector_to_string(char *data, int len, string &str)
{
    bool is_int = *(data + len - 1); // 获取最后一个字节存储的bool值，表示是否为整数
    len         = (len - 1) / 4;     // 认为len传入的Value中的length_字节长度，因此需要减2除以4来获取元素个数
    if (is_int) {
        int *p = (int *)data;
        str += "[";
        for (int i = 0; i < len; i++) {
            str += std::to_string(p[i]);
            if (i != len - 1) {
                str += ",";
            }
        }
        str += "]";
    } else {
        float *p = (float *)data;
        str += "[";
        for (int i = 0; i < len; i++) {
            str += formatFloat(p[i]);
            if (i != len - 1) {
                str += ",";
            }
        }
        str += "]";
    }
    return RC::SUCCESS;
}

}