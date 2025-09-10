#include <stdio.h>
#include <string.h>

//Định nghĩa danh sách Sinh viên có các thành phần là tên, điểm trung bình và id
typedef struct
{
    char ten[50];
    float diemTrungBinh;
    int id;
} SinhVien;

/*Hàm so sánh chuỗi theo tên của Sinh viên có tham số truyền vào là con trỏ hằng char
để lấy được tên của sinh viên nhằm mục đích so sánh không được quyền chỉnh sửa tên 
sinh viên*/
int stringCompare(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    /*việc giải tham chiếu về kiểu const unsigned char nhằm mục đích tránh lỗi khi so sánh các ký tự có giá trị là âm 
    vì trong bảng mã ASCII tiêu chuẩn thì luôn là số dương nên khi ký tự có giá trị là số âm sẽ ép về số dương để khi thực hiện
    phép toán hiệu của hai ký tự cho ra kết quả để thực hiện hàm sort cho kết quả đúng */
    return (*(const unsigned char*)str1 - *(const unsigned char*)str2); 
}


/*Hàm so sánh theo tên của Sinh viên có tham số truyền vào là con trỏ hằng 
để lấy được tên của sinh viên nhằm mục đích so sánh không được quyền chỉnh sửa tên của 
sinh viên có kiểu dữ liệu là void nhằm mục đích cho hàm sort là một hàm so sánh tổng quảt*/
int compareByName(const void *a, const void *b)
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;
    return stringCompare(sv1->ten, sv2->ten);
}

/*Hàm so sánh theo điểm trung bình của Sinh viên có tham số truyền vào là con trỏ hằng 
để lấy được điểm trung bình của sinh viên nhằm mục đích so sánh không được quyền chỉnh sửa điểm của 
sinh viên có kiểu dữ liệu là void nhằm mục đích cho hàm sort là một hàm so sánh tổng quảt*/
int compareByDiemTrungBinh(const void *a, const void *b)
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;
    if (sv1->diemTrungBinh > sv2->diemTrungBinh) return 1;
    return 0;
}

/*Hàm so sánh theo ID của Sinh viên có tham số truyền vào là con trỏ hằng 
để lấy được ID của sinh viên nhằm mục đích so sánh không được quyền chỉnh sửa ID của 
sinh viên có kiểu dữ liệu là void nhằm mục đích cho hàm sort là một hàm so sánh tổng quảt*/
int compareByID(const void *a, const void *b)
{
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   return sv1->id - sv2->id;
}

/* Hàm sắp xếp chung dùng thuật toán nổi bọt theo thứ tự tứ thấp đến cao tùy vào yêu cầu 
sắp xếp của hàm so sánh được truyền vào, hàm sort có tham số truyền vào là con trỏ hàm
cho mục đích có thể sắp xếp danh sách sinh viên tùy vào những tiêu chí chẳng hạn 
như là sắp xếp theo id, theo tên hoặc điểm trung bình của một sinh viên mà tham số truyền
vào của một con trỏ hàm là con trỏ hằng có kiểu dữ liệu là void nhằm mục đích là cho hàm sort là một hàm 
so sánh tổng quảt hơn có nghĩa là ngoài dữ liệu có kiểu là Sinhvien nếu sau này có nâng cấp 
hàm sort thêm nữa thì mình có thể nhận kiểu dữ liệu khác nữa chẳng hạn như một kiểu dữ liệu 
Sinhvien khác có các thành phần trong đó có thể là điểm thể chất hoặc là hạnh kiểm ... để sắp
xếp theo các tiêu chí mới này*/
void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *))
{
    for (int i=0; i<size-1; i++)
    {
        for (int j=0; j<size-i-1; j++)
        {
            if (compareFunc(array+j, array+j+1)>0)
            {
                SinhVien temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }        
}

void display(SinhVien *array, size_t size)
{
   for (size_t i = 0; i < size; i++)
   {
       printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
   }
   printf("\n");
}

int main() {
    SinhVien danhSachSV[] =
    {
        {  
            .ten = "Hoang",
            .diemTrungBinh = 7.5,
            .id = 100
        },
        {
            .ten = "Tuan",
            .diemTrungBinh = 4.5,
            .id = 101
        },
        {
            .ten = "Vy",
            .diemTrungBinh = 6.8,
            .id = 102},
        {  
            .ten = "Ngan",
            .diemTrungBinh = 5.6,
            .id = 10
        },
    };

    size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);

    // Sắp xếp theo tên
    sort(danhSachSV, size, compareByName);
    display(danhSachSV, size);

    // Sắp xếp theo điểm trung bình
    sort(danhSachSV, size, compareByDiemTrungBinh);
    display(danhSachSV, size);

    // Sắp xếp theo ID
    sort(danhSachSV, size, compareByID);
    display(danhSachSV, size);

    return 0;
}
