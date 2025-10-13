#include "../include/utils.h"

uint8_t checkParity(uint8_t byte)
{
    uint8_t bitmark = 0x01;
    uint8_t count = 0;
    for (int i = 0;i < 8; ++i)     
    {
        if(byte & bitmark){         //byte:     0b01100000
            count++;                //bitmark:  0b00000001
        }
        byte >>=1 ;   //Dịch sang phải 1 bit để so sánh bit kế tiếp                 
    }
    return (!(count % 2));
}

uint8_t reverseBits(uint8_t byte)
{
    uint8_t bitmark = 0x80;
    uint8_t newbyte = 0;
    for(int i =0; i< 8; ++i)
    {
        if(byte & bitmark)
        {                                 
            newbyte |= (1<<i);        //byte:       0b01100000
        }                             //bitmask:    0b10000000
        byte <<= 1;   //Dịch sang trái 1 bit để so sánh bit kế tiếp
    }
    return newbyte;
}

void pointerDemo(Door* doors)
{
    //Kiểm tra con trỏ có lưu giá trị địa chỉ của mảng 4 cửa không 
    if (doors == NULL)
    {
      printf("Khong co mang 4 cua de thao tac");
      exit(0);
    }

     //Tạo con trỏ cấp 1 trỏ đến đầu mảng 4 cửa
    Door *getDoor = doors; 

    //Tạo con trỏ cấp 2 trỏ vào địa chỉ cấp 1 để quản lý địa chỉ của từng cửa 
    Door **ptpDoor = &getDoor; 
    printf("\nThao tac advanced pointer\n\n");
    for (int i = 0;i < num_doors; ++i)
    {
        printf("Door %d status: %s and %s\n", i+1 , (*ptpDoor)->statusUnion.status.isOpen ? "Open" : "Close",
        (*ptpDoor)->statusUnion.status.isLocked ? "Lock" : "Unlock");
        (*ptpDoor) += 1; //Tăng giá trị địa chỉ để đến địa chỉ cửa tiếp theo 
    }

    //Khai báo mảng thô chứa dữ liệu cần đóng gói của 4 cửa 
    uint8_t FramePacked[num_doors] = {0};
    
    //Tạo con trỏ cấp 1 có kiểu dữ liệu là void trỏ đến địa chỉ của mảng thô 
    void *ptrFrame = &FramePacked;
    printf("\n");
    for (int i = 0 ;i <num_doors; ++i)
    {
        /*Copy từng byte dữ liệu của từng cửa gán vào con trỏ void sau đó ép kiểu con trỏ 
        void theo kiểu dữ liệu của mảng thô cần đóng gói*/
        ((uint8_t *)ptrFrame)[i] = doors[i].statusUnion.byte;
        printf("Pack frame of the Door %d:  %02X\n", i+1, FramePacked[i]);
    }

    printf("\n");
    //Tạo 1 con trỏ hằng gắn giá trị con trỏ void sau đó ép kiểu con trỏ void để đọc gói dữ liệu cho an toàn 
    const uint8_t* FrameUnpacked = (const uint8_t *)ptrFrame;
    for(int i=0; i < num_doors; ++i)
    {
        //Đọc gói dữ liệu của từng cửa
        printf("Unpack frame of the Door %d:  %02X\n", i+1, FrameUnpacked[i]);  
    }
    
    printf("\nPack frame of the Door before changing\n");
    //Tạo 1 hằng con trỏ được đặt với tên có chức năng thay đổi giá trị gói dữ liệu trỏ đến địa chỉ mảng thô rồi ép kiểu tương ứng 
    uint8_t *const changeFramePacked = (uint8_t *const)&FramePacked;
    for (int i = 0 ;i <num_doors; ++i)
    {
        //Đọc gói dữ liệu trước khi thay đổi giá trị
        printf("Door %d:  %02X\n", i+1, changeFramePacked[i]);
    }

    //Thay đổi giá trị gói dữ liệu cửa 2 và cửa 3
    changeFramePacked[1] = 0x01;
    changeFramePacked[2] = 0x11;
    printf("\nPack frame of the Door after changing \n");
    //
    for (int i = 0 ;i <num_doors; ++i)
    {
        //Đọc gói dữ liệu sau khi thay đổi giá trị 
        printf("Door %d:  %02X\n", i+1, changeFramePacked[i]);
    }
}