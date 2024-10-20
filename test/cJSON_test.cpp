
#include "test.hpp"
#include <iostream>
#include <fstream>
#include "cJSON/cJSON.h"

using namespace std;


void cJSON_test()
{
    cout << cJSON_Version() << endl;

    // 打开JSON文件
    ifstream file("../data/test.json");
    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }

    // 读取文件内容到字符串
    string jsonString((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // 解析JSON字符串
    cJSON* root = cJSON_Parse(jsonString.c_str());
    if (root == NULL) {
        cout << "Failed to parse JSON" << endl;
        return;
    }

    // 获取JSON的具体内容
    cJSON* success = cJSON_GetObjectItem(root, "success");
    if (success != NULL && success->type == cJSON_String) {
        cout << "success: " << success->valuestring << endl;
    }

    cJSON* result = cJSON_GetObjectItem(root, "result");

    // 确保解析得到的是数组
    if (cJSON_IsArray(result)) {
        cout << "cJSON is array" << endl;

        cJSON *item = NULL;

        cJSON_ArrayForEach(item, result) {
            // 获取每个对象的"name"和"age"字段
            const cJSON *days = cJSON_GetObjectItemCaseSensitive(item, "days");
            const cJSON *week = cJSON_GetObjectItemCaseSensitive(item, "week");

            // 确保字段存在且是正确的类型
            if (cJSON_IsString(days) && (cJSON_IsString(week))) {
                std::cout << "days: " << cJSON_GetStringValue(days) << ", week: " << cJSON_GetStringValue(week) << std::endl;
            }
        }
    }

    cJSON_Delete(root);
}
