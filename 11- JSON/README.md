# Bài 11: JSON
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
  

#### - Tạo một biến là JSON
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
#### - Các hàm parse phân tích dữ liệu trong JSON
- Hàm `parse_json` có chức năng xác định kiểu dữ liệu trong một chuỗi JSON để vào các hàm parse tương ứng với kiểu dữ liệu đó để phân tích và xử lí. Đối với kiểu dữ liệu như mảng các phần tử có thể có nhiều kiểu dữ liệu khác nhau và object có nhiều cặp key và value, giá trị value sẽ có nhiều kiểu dữ liệu khác nhau nên khi vào các kiểu dữ liệu như mảng và object sẽ tiếp tục đệ quy gọi hàm `parse_json` để xác định kiểu dữ liệu bên trong để phân tích. 

```
JsonValue *parse_json(const char **json) { 
    skip_whitespace(json);
    switch (**json) {
        case 'n':
            return parse_null(json); //return nullif there is no json string is existed
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        default:
            if (isdigit(**json) || **json == '-') { 

                return parse_number(json);
            } else {
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}
```
- Dưới đây là các hàm parse trong JSON của nhiều kiểu dữ liệu khác nhau các hàm có chức năng phân tích và lấy kiểu dữ liệu và giá trị truyền vào. Trong JSON nó sẽ bao gồm nhiều kiểu dữ liệu là NULL, boolean, number, string, array, object. Các tham số truyền vào trong các hàm này đều là con trỏ cấp 2 bởi vì nếu truyền tham số vào là con trỏ cấp 1 sau khi lưu và tăng giá trị địa chỉ thì sau khi hàm kết thúc biến con trỏ cấp 1 sẽ bị thu hồi vùng nhớ đi lúc đó giá trị địa chỉ không còn nữa, việc dùng con trỏ cấp 2 khi thực hiện tăng giá trị địa chỉ là nó sẽ tăng giá trị địa chỉ của con trỏ gốc, cho dù biến con trỏ cấp 2 bị thu hồi đi khi hàm kết thúc thì giá trị địa chỉ của con trỏ gốc đã tăng rồi. Đối với các hàm parse của kiểu dữ liệu null, boolean, number, string thì cấp phát động để lưu kiểu dữ liệu và lưu giá trị thì sẽ dùng malloc, đối với array và object thì nó sẽ phụ thuộc vào bao nhiêu phần tử trong mảng và bao nhiêu cặp key và value trong 1 đối tượng nên sẽ linh động hơn trong việc cấp phát động nên sẽ dùng realloc. 

```
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
#### - Hàm hiển thị giá trị sau khi phân tích và giải phóng chuỗi JSON  
- Hàm `test` có chức năng hiển thị giá trị chuỗi json sau khi đã phân tích chuỗi thông qua hàm `parsejson`. Đối với kiểu dữ liệu trong chuỗi JSON như là string, boolean, hoặc là number sẽ trực tiếp gọi hàm `printf` để in ra giá trị, còn đối với kiểu dữ liệu như là array và object sẽ xác định bao nhiêu phần tử trong mảng hoặc bao nhiêu cặp key và value để lần lượt in ra bấy nhiêu giá trị phần tử trong mảng hoặc là bấy nhiêu cặp key và value.
```
void test(JsonValue* json_value){
    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;

        for (size_t i = 0; i < num_fields; ++i) {

            char* key = json_value->value.object.keys[i];
            JsonValue* value = &json_value->value.object.values[i];

            JsonType type = (int)(json_value->value.object.values[i].type);


            if(type == JSON_STRING){
                printf("%s: %s\n", key, value->value.string);
            }

            else if(type == JSON_NUMBER){
                printf("%s: %.1f\n", key, value->value.number);
            }

            else if(type == JSON_BOOLEAN){
                printf("%s: %s\n", key, value->value.boolean ? "True":"False");
            }

            else if(type == JSON_OBJECT){
                printf("%s: \n", key);
                test(value);
            }

            else if(type == JSON_ARRAY){
                printf("%s: ", key);
                for (size_t i = 0; i < value->value.array.count; i++)
                {
                   test(value->value.array.values + i);
                } 
                printf("\n");
            }
        }
     
    }
    else 
    {
            if(json_value->type == JSON_STRING){
                printf("%s ", json_value->value.string);
            }

            else if(json_value->type == JSON_NUMBER){
                printf("%.1f ", json_value->value.number);
            }

            else if(json_value->type == JSON_BOOLEAN){
                printf("%s ", json_value->value.boolean ? "True":"False");
            }

            else if(json_value->type == JSON_OBJECT){
                printf("%s: \n", *(json_value->value.object.keys));
                test(json_value->value.object.values);
                           
            }
            
            else if(json_value->type == JSON_ARRAY){
                for (size_t i = 0; i < json_value->value.array.count; i++)
                {
                   test(json_value->value.array.values + i);
                } 
                printf("\n");
            }
            else if (json_value->type ==JSON_NULL){
                printf("null ");
            }
    }

}
```
- Hàm `free_json_value` giải phóng bộ nhớ sau khi dùng để cấp phát để lưu trữ dữ liệu sau khi phân tích và xử lí chuỗi JSON. Đối với kiểu dữ liệu trong chuỗi JSON như là string sẽ trực tiếp gọi hàm `free` để giải phóng, còn đối với kiểu dữ liệu như là array và object sẽ xác định bao nhiêu phần tử trong mảng hoặc bao nhiêu cặp key và value để lần lượt giải phóng bấy nhiêu vùng nhớ dùng để lưu trữ giá trị phần tử trong mảng hoặc là các cặp key và value.
```
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }
    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;
        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;
        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;
        default:
            break;
    }
}
```
#### - Ứng dụng:
- So với struct thì khi dùng JSON để lưu trữ danh sách thông tin người dùng, danh sách đăng ký học viên, danh sách nơi ở hộ gia đình, dữ liệu trao đổi trong hệ thống IOT...  thì ưu điểm của JSON sẽ tiết kiệm bộ nhớ không gây lãng phí bộ nhớ hơn bởi vì nếu dùng struct để lưu trữ danh sách thì nếu lấy thông tin người dùng thì sẽ có một số thông tin sẽ để trống bởi vì một số lí do là chưa có thông tin ,người dùng không biết hoặc là người dùng không muốn nhập vào lúc đó khi dùng struct đã cấp phát dữ liệu những thành viên các thông tin trống này không dùng để lưu dữ liệu nào cả gây ra lãng phí bộ nhớ.    
- Dùng JSON sẽ linh hoạt hơn trong dữ liệu mạng, kích thước lớn, có sự thay đổi kích thước đối với một gói dữ liệu nào đó hoặc là phần tử bên trong dữ liệu đó. Dùng struct sẽ ứng dụng trong thiết bị có memory thấp, tốc độ nhanh giao tiếp giữa thiết bị và ngoại vi.  
