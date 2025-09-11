#include <stdio.h>
#include <string.h> // strncpy()
//#include <ctype.h>  // isdigit(),isspace()
#include <stdlib.h> // strtod()

//hàm bỏ qua ký tự khoảng trắng
// void skipSpace(const char **c)
// {
//     while (isspace(**c))
//     {
//         (*c)++;     //lặp qua địa chỉ của từng ký tự khoảng trắng 
//     }
// }
//hàm phân tách chuỗi 
void parseString(const char **pbuff, char *name)
{
    (*pbuff)++;                 // bỏ qua ký tự '\"' để bắt đầu phân tích ký tự đầu của chuỗi con
    const char *start = *pbuff; // lưu địa chỉ của ký tự hiện của chuỗi mà buffer đang trỏ tới
    const char *end = start;    // dùng để xác định độ dài chuỗi sau này

    while (*end != '\0' && *end != '\"')
    {
        end++;              //lặp địa chỉ của từng ký tự để xác định chuỗi con cần phân tích
    }

    int len = end - start;     //tính độ dài của chuỗi đã phân tích
    strncpy(name, start, len); //sao chép số lượng ký tự bằng với len tính từ vị trí start 
    name[len] = '\0';          //thêm ký tự kết thúc để đảm bảo đúng chuẩn 1 chuỗi ký tự
    *pbuff = ++end;            //cập nhật con trỏ đến vị trí mới để tiếp tục phân tích chuỗi
}
//hàm phân tách ký tự số 
void parseNumber(const char **pbuff, int *number)
{
    (*pbuff)++;                    // bỏ qua ký tự ':'
    *number = 0;                  //khởi tạo giá trị = 0 để cộng dồn giá trị số vào
    while(**pbuff != '\0' && **pbuff != '\"') 
    {
        *number = *number * 10 + (**pbuff - '0'); //chuyển ký tự số sang kiểu int và cộng dồn vào giá trị vào 
       (*pbuff)++;                  //cập nhật con trỏ đến vị trí mới để phân tích ký tự số tiếp theo 
    }
}

void main()
{

    const char *buffer = "\"temperature\":23"
                          "\"humidity\":45"     
                          "\"Speed\":12"    
                           "\"Light\":89";
    int value = 0;
    char sensor_name[30];
    while(*buffer != '\0'){
        switch (*buffer)
        {
        //xử lý phân tách chuõi
        case '\"':
            parseString(&buffer, sensor_name);
            printf("%s\t",sensor_name);
            break;
        //xử lý phân tách ký tự số
        case ':':
            parseNumber(&buffer, &value);
            printf("%d\n",value);
            break;
        //xử lý bỏ qua các ký tự còn lại
        default:
            buffer++;\
            break;
        }
    }
}