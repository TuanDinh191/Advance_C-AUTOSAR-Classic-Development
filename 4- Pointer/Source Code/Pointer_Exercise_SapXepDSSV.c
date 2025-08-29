#include <stdio.h>
#include <string.h>

typedef struct {
   char ten[50];    // 48 bytes + 2bytes + 2 padding  
   float diemTrungBinh; // 4 bytes
   int id; //4 bytes
} SinhVien;

typedef struct {
    char ten[50];   
    float diemTrungBinh;
    int id;
    char hocluc[20];
}SinhVien2;

int stringCompare(const char *str1, const char *str2) {
   while (*str1  && (*str1 == *str2)) { //'\0' = 0   
       str1++;
       str2++;
   }
   return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}


// Hàm so sánh theo tên
int compareByName(const void *a, const void *b) {
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   return stringCompare(sv1->ten, sv2->ten);
}

// int compareByName(const SinhVien *a, const SinhVien *b) {
//    const SinhVien *sv1 = a;
//    const SinhVien *sv2 = b;
//    return stringCompare(sv1->ten, sv2->ten);
// }

// Hàm so sánh theo điểm trung bình
int compareByDiemTrungBinh(const void *a, const void *b) {
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   if (sv1->diemTrungBinh > sv2->diemTrungBinh)
   {
       return 1;
   }
  
   return 0;
}

// Hàm so sánh theo ID
int compareByID(const void *a, const void *b) {
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   return sv1->id - sv2->id;
}

// Hàm sắp xếp chung
void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *)) {
   int i, j;
   SinhVien temp;
   //Thuật toán sắp xếp nổi bọt của các phần tử trong mảng có kiểu dữ liệu là Sinhvien 
   for (i = 0; i < size-1; i++)    
       for (j = i+1; j < size; j++)
           if (compareFunc(array+i, array+j)>0) {
               temp = array[i];
               array[i] = array[j];
               array[j] = temp;
           }
}

// void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *)) {
//    int i, j;
//    SinhVien temp;
//    for (i = 0; i < size-1; i++)    
//        for (j = i+1; j < size; j++)
//            if (compareFunc(array+i, array+j)>0) {
//                temp = array[i];
//                array[i] = array[j];
//                array[j] = temp;
//            }
// }

void display(SinhVien *array, size_t size) {
   for (size_t i = 0; i < size; i++) {
       printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
   }
   printf("\n");
}

void sort2(SinhVien2 array[], size_t size, int (*compareFunc)(const void *, const void *)) {
   int i, j;
   SinhVien2 temp;
   for (i = 0; i < size-1; i++)    
       for (j = i+1; j < size; j++)
           if (compareFunc(array+i, array+j)>0) {
               temp = array[i];
               array[i] = array[j];
               array[j] = temp;
           }
}

void display2(SinhVien2 *array, size_t size) {
   for (size_t i = 0; i < size; i++) {
       printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
   }
   printf("\n");
}

int main() {
   SinhVien danhSachSV[] = {
       {  
           .ten = "γHoang",  //γHoang
           .diemTrungBinh = 7.5,
           .id = 100
       },
       {
           .ten = "ΓTuan",  //ΓTuan
           .diemTrungBinh = 4.5,
           .id = 101
       },
       {
           .ten = "Vy",
           .diemTrungBinh = 6.8,
           .id = 102
       },
       {  
           .ten = "Ngan",
           .diemTrungBinh = 5.6,
           .id = 10
       },
   };

   SinhVien2 danhSachSv2[]=  {
       {   
           .ten = "Trung", 
           .diemTrungBinh = 3.5,       
           .id = 100,
           .hocluc = "Kha"
           
       },
       {
           .ten = "Binh",
           .diemTrungBinh = 9.5,
           .id = 112,
           .hocluc = "Gioi"
       },
       {
           .ten = "Vu",
           .diemTrungBinh = 8.5,
           .id = 121,
           .hocluc = "Gioi"
       },
       
   };
   size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);

   // Sắp xếp theo tên
   sort(danhSachSV, size, compareByName);
   display(danhSachSV, size);

   size_t size2 =  sizeof(danhSachSv2)/ sizeof(danhSachSv2[0]);
   
   // Sắp xếp theo tên
    sort2(danhSachSv2, size2, compareByName);
    display2(danhSachSv2, size2);

   // Sắp xếp theo điểm trung bình
    sort(danhSachSV, size, compareByDiemTrungBinh);

    display(danhSachSV, size);

    // // Sắp xếp theo ID
    sort(danhSachSV, size, compareByID);
    display(danhSachSV, size);

   return 0;
}

