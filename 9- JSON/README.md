# Bài 9: JSON
#### 1. JSON
#### - Định nghĩa:
- JSON (JavaScript Object Notation) là một định dạng dữ liệu được sử dụng phổ biến trên trình duyệt web có thể hỗ trợ cho nhiều ngôn ngữ lập trình, bản chất của JSON là một chuỗi bên trong nó có thể chứa nhiều kiểu dữ liệu khác nhau, có thể chứa mảng, đối tượng.
- Trong JSON có một kiểu dữ liệu mới tên là object, 1 object trong đó sẽ chữa nhiều cặp key value được ngăn cách bởi dấu phẩy. Trong object thì key sẽ là một chuối còn value là giá trị của nhiều kiểu dữ liệu khác nhau. Object trong Json có thể lồng với object tạo nên nhiều dữ liệu phức tạp.

Ví dụ:
```
char *json = “ 
{ 
  "name": "John Doe",
  "age": 30,
  "city": "New York",
  "isStudent": false,
  "grades": [85, 90, 78]
}

“
```
- Đối với mảng trong JSON thì các phần tử trong mảng đều có thể chứa nhiều kiểu dữ liệu khác nhau. Có thể chứa object, và có thể lồng mảng trong đó.

#### Tạo một biến là JSON
- Ở chương trình dưới đây để tạo một dữ liệu JSON ta sẽ dùng cấu trúc JSONValue có thành phần 1 là biến kiểu enum thành phần 2 là biến kiểu tự định nghĩa union. enum chứa tất cả danh sách các kiểu dữ liệu của một JSON mà có thể có khi đã xác định kiểu dữ liệu rồi thì union sẽ lưu giá trị vào biến tương ứng với kiểu dữ liệu đó. 
```
#include <stdio.h>
#include <stdbool.h>
/*
 * "[50.456, true, [5, "hello world"]]"
 */

typedef enum{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSONType;

typedef struct JSONValue{
    JSONType type;
    union{
        int     boolean; // 0 hoặc 1, 0 = false, 1 = true
        double  number;
        char    *string;
        struct{
            struct JSONValue *values;
            size_t count;
        } array;
        struct{
            char **keys; // ["key1", "key2", "key3"]
            struct JSONValue *values;
            size_t count;
        } object;
    } value;
} JSONValue;

int main(int argc, char const *argv[])
{
    JSONValue *json_str = (JSONValue*)malloc(sizeof(JSONValue));

    json_str->type = JSON_ARRAY;
    json_str->value.array.count = 3;
    json_str->value.array.values = (JSONValue*)malloc(json_str->value.array.count*sizeof(JSONValue));

    // phần tử 1
    json_str->value.array.values[0].type = JSON_NUMBER;
    json_str->value.array.values[0].value.number = 50.456;

    // phần tử 2
    json_str->value.array.values[1].type = JSON_BOOLEAN;
    json_str->value.array.values[1].value.boolean = true;

    // phần tử 3
    json_str->value.array.values[2].type = JSON_ARRAY;
    json_str->value.array.values[2].value.array.count = 2;
    json_str->value.array.values[2].value.array.values = (JSONValue*)malloc(json_str->value.array.values[2].value.array.count *sizeof(JSONValue));
    
     
    json_str->value.array.values[2].value.array.values[0].type = JSON_NUMBER;
    json_str->value.array.values[2].value.array.values[0].value.number = 5;

    json_str->value.array.values[2].value.array.values[1].type = JSON_STRING;
    json_str->value.array.values[2].value.array.values[1].value.string = "hello world";

    return 0;
}
```
#### Các hàm parse phân tích dữ liệu trong JSON
- Dưới đây là các hàm parse trong JSON của nhiều kiểu dữ liệu khác nhau các hàm có chức năng phân tích và lấy kiểu dữ liệu và giá trị truyền vào. Trong JSON nó sẽ bao gồm nhiều kiểu dữ liệu là NULL, boolean, number, string, array, object. Các tham số truyền vào trong các hàm này đều là con trỏ cấp 2 bởi vì nếu truyền tham số vào là con trỏ cấp 1 sau khi lưu và tăng giá trị địa chỉ thì sau khi hàm kết thúc biến con trỏ cấp 1 sẽ bị thu hồi vùng nhớ đi lúc đó giá trị địa chỉ không còn nữa, việc dùng con trỏ cấp 2 khi thực hiện tăng giá trị địa chỉ là nó sẽ tăng giá trị địa chỉ của con trỏ gốc, cho dù biến con trỏ cấp 2 bị thu hồi đi khi hàm kết thúc thì giá trị địa chỉ của con trỏ gốc đã tăng rồi. Đối với các hàm parse của kiểu dữ liệu null, boolean, number, string thì cấp phát động để lưu kiểu dữ liệu và lưu giá trị thì sẽ dùng malloc, đối với array và object thì nó sẽ phụ thuộc vào bao nhiêu phần tử trong mảng và bao nhiêu cặp key và value trong 1 đối tượng nên sẽ linh động hơn trong việc cấp phát động nên sẽ dùng realloc. 
```

JsonValue *parse_json(const char **json);

void free_json_value(JsonValue *json_value);

static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}

JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    if (strncmp(*json, "null", 4) == 0) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }
    return NULL;
}

JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } else {
        free(value);
        return NULL;
    }
    return value;
}

JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;
    double num = strtod(*json, &end);
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

JsonValue *parse_string(const char **json) {
    skip_whitespace(json);


    if (**json == '\"') {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start; // 3
            char *str = (char *) malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);
            str[length] = '\0';


            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}



JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        /*
        double arr[2] = {};
        arr[0] = 30;
        arr[1] = 70;
        */

        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json); // 70
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parse_object(const char **json) {
    skip_whitespace(json);
    if (**json == '{') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;



        while (**json != '}' && **json != '\0') {
            JsonValue *key = parse_string(json);
            if (key) {
                skip_whitespace(json);
                if (**json == ':') {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } else {
                        free_json_value(key);
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}
```