#include "common/type/attr_type.h"
#include "common/value.h"
#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/lang/vector_utils.h"
#include "common/lang/comparator.h"

int VectorType::compare(const Value &left_prev, const Value &right_prev) const
{
    // 检查左右类型是否为向量并转换
    Value left;
    Value right;
    if (left_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(left_prev, AttrType::VECTORS, left);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast left value to vector type failed. %s", strrc(rc));
            return INT32_MAX;
        }
    } else {
        left = left_prev;
    }
    if (right_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(right_prev, AttrType::VECTORS, right);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast right value to vector type failed. %s", strrc(rc));
            return INT32_MAX;
        }
    } else {
        right = right_prev;
    }

    int left_len  = (left.length()  - 1) / 4;
    int right_len = (right.length() - 1) / 4;
    bool left_is_int  = left.is_int_vector();
    bool right_is_int = right.is_int_vector();
    int i = 0;
    // 无法知道vector的类型，所以需要分别处理int和float
    if (left_is_int && right_is_int) {
        int *p = (int *)left.get_vector();
        int *q = (int *)right.get_vector();
        while (i < left_len && i < right_len) {
            if (p[i] != q[i]) {
                return common::compare_int((void*)&p[i], (void*)&q[i]);
            }
            i++;
        }
    } else if (!left_is_int && right_is_int) {
        float *p = (float *)left.get_vector();
        int   *q = (int *)right.get_vector();
        while (i < left_len && i < right_len) {
            float q_val = (float)q[i];
            if (p[i] != q_val) {
                return common::compare_float((void*)&p[i], (void*)&q_val);
            }
            i++;
        }
    } else if (left_is_int && !right_is_int) {
        int   *p = (int *)left.get_vector();
        float *q = (float *)right.get_vector();
        while (i < left_len && i < right_len) {
            float p_val = (float)p[i];
            if (p_val != q[i]) {
                return common::compare_float((void*)&p_val, (void*)&q[i]);
            }
            i++;
        }
    } else {
        float *p = (float *)left.get_vector();
        float *q = (float *)right.get_vector();
        while (i < left_len && i < right_len) {
            if (p[i] != q[i]) {
                return common::compare_float((void*)&p[i], (void*)&q[i]);
            }
            i++;
        }
    }
    return common::compare_int((void*)&left_len, (void*)&right_len);
}

RC VectorType::add(const Value &left_prev, const Value &right_prev, Value &result) const
{
    // 检查左右类型是否为向量并转换
    Value left;
    Value right;
    if (left_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(left_prev, AttrType::VECTORS, left);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast left value to vector type failed. %s", strrc(rc));
            return rc;
        }
    } else {
        left = left_prev;
    }
    if (right_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(right_prev, AttrType::VECTORS, right);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast right value to vector type failed. %s", strrc(rc));
            return rc;
        }
    } else {
        right = right_prev;
    }
    bool left_is_int  = left.is_int_vector();
    bool right_is_int = right.is_int_vector();
    int left_len  = (left.length()  - 1) / 4;
    int right_len = (right.length() - 1) / 4;
    if (left_len != right_len) {
        LOG_WARN("left and right vector length mismatch. left_len=%d, right_len=%d", left_len, right_len);
        return RC::INVALID_ARGUMENT;
    }
    char *result_data = new char[left.length()];
    if (left_is_int && right_is_int) {
        int *p = (int *)left.get_vector();
        int *q = (int *)right.get_vector();
        int *r = (int *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] + q[i];
        }
        result_data[left.length() - 1] = true;
    } else if (!left_is_int && right_is_int) {
        float *p = (float *)left.get_vector();
        int   *q = (int *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] + (float)q[i];
        }
        result_data[left.length() - 1] = false;
    } else if (left_is_int && !right_is_int) {
        int   *p = (int *)left.get_vector();
        float *q = (float *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = (float)p[i] + q[i];
        }
        result_data[left.length() - 1] = false;
    } else {
        float *p = (float *)left.get_vector();
        float *q = (float *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] + q[i];
        }
        result_data[left.length() - 1] = false;
    }
    result.set_vector(result_data, left.length());
    delete[] result_data;
    return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left_prev, const Value &right_prev, Value &result) const
{
    // 检查左右类型是否为向量并转换
    Value left;
    Value right;
    if (left_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(left_prev, AttrType::VECTORS, left);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast left value to vector type failed. %s", strrc(rc));
            return rc;
        }
    } else {
        left = left_prev;
    }
    if (right_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(right_prev, AttrType::VECTORS, right);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast right value to vector type failed. %s", strrc(rc));
            return rc;
        }
    } else {
        right = right_prev;
    }

    bool left_is_int  = left.is_int_vector();
    bool right_is_int = right.is_int_vector();
    int left_len  = (left.length()  - 1) / 4;
    int right_len = (right.length() - 1) / 4;
    if (left_len != right_len) {
        LOG_WARN("left and right vector length mismatch. left_len=%d, right_len=%d", left_len, right_len);
        return RC::INVALID_ARGUMENT;
    }
    char *result_data = new char[left.length()];
    if (left_is_int && right_is_int) {
        int *p = (int *)left.get_vector();
        int *q = (int *)right.get_vector();
        int *r = (int *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] - q[i];
        }
        result_data[left.length() - 1] = true;
    } else if (!left_is_int && right_is_int) {
        float *p = (float *)left.get_vector();
        int   *q = (int *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] - (float)q[i];
        }
        result_data[left.length() - 1] = false;
    } else if (left_is_int && !right_is_int) {
        int   *p = (int *)left.get_vector();
        float *q = (float *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = (float)p[i] - q[i];
        }
        result_data[left.length() - 1] = false;
    } else {
        float *p = (float *)left.get_vector();
        float *q = (float *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] - q[i];
        }
        result_data[left.length() - 1] = false;
    }
    result.set_vector(result_data, left.length());
    delete[] result_data;
    return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left_prev, const Value &right_prev, Value &result) const
{
    // 检查左右类型是否为向量并转换
    Value left;
    Value right;
    if (left_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(left_prev, AttrType::VECTORS, left);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast left value to vector type failed. %s", strrc(rc));
            return rc;
        }
    } else {
        left = left_prev;
    }
    if (right_prev.attr_type() != AttrType::VECTORS) {
        RC rc = Value::cast_to(right_prev, AttrType::VECTORS, right);
        if (OB_FAIL(rc)) {
            LOG_WARN("cast right value to vector type failed. %s", strrc(rc));
            return rc;
        }
    } else {
        right = right_prev;
    }

    bool left_is_int  = left.is_int_vector();
    bool right_is_int = right.is_int_vector();
    int left_len  = (left.length()  - 1) / 4;
    int right_len = (right.length() - 1) / 4;
    if (left_len != right_len) {
        LOG_WARN("left and right vector length mismatch. left_len=%d, right_len=%d", left_len, right_len);
        return RC::INVALID_ARGUMENT;
    }
    char *result_data = new char[left.length()];
    if (left_is_int && right_is_int) {
        int *p = (int *)left.get_vector();
        int *q = (int *)right.get_vector();
        int *r = (int *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] * q[i];
        }
        result_data[left.length() - 1] = true;
    } else if (!left_is_int && right_is_int) {
        float *p = (float *)left.get_vector();
        int   *q = (int *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] * (float)q[i];
        }
        result_data[left.length() - 1] = false;
    } else if (left_is_int && !right_is_int) {
        int   *p = (int *)left.get_vector();
        float *q = (float *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = (float)p[i] * q[i];
        }
        result_data[left.length() - 1] = false;
    } else {
        float *p = (float *)left.get_vector();
        float *q = (float *)right.get_vector();
        float *r = (float *)result_data;
        for (int i = 0; i < left_len; i++) {
            r[i] = p[i] * q[i];
        }
        result_data[left.length() - 1] = false;
    }
    result.set_vector(result_data, left.length());
    delete[] result_data;
    return RC::SUCCESS;
}

RC VectorType::vector_aggregation(const Value &val, Value &result) const
{
    bool is_int = val.is_int_vector();
    int len = (val.length() - 1) / 4;
    if (is_int) {
        int *p = (int *)val.get_vector();
        int result_val = 0;
        for (int i = 0; i < len; i++) {
            result_val += p[i];
        }
        result.set_int(result_val);
    } else {
        float *p = (float *)val.get_vector();
        float result_val = 0;
        for (int i = 0; i < len; i++) {
            result_val += p[i];
        }
        result.set_float(result_val);
    }
    return RC::SUCCESS;
}

RC VectorType::to_string(const Value &val, string &result) const
{
    common::vector_to_string(val.value_.pointer_value_, val.length(), result);
    return RC::SUCCESS;
}