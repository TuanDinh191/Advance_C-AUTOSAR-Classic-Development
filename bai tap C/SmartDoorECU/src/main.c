#include <stdio.h>
#include "../include/door.h"
#include "../include/can_frame.h"
#include "../include/utils.h"

/*
 * Chức năng chính:
 * - Khởi tạo mảng 4 cửa, gán actuator (Door_Init)
 * - Vòng lặp menu cho phép:
 *    + Xem trạng thái cửa: truy cập statusUnion/status/byte
 *    + Thao tác actuator: gọi open/close/lock/unlock
 *    + Packing trạng thái vào frame: packDoorStatus
 *    + Unpacking frame: unpackDoorStatus
 *    + Kiểm tra parity, đảo bit: checkParity, reverseBits
 *    + Thao tác advanced pointer: pointerDemo
 *    + In log kết quả ra màn hình
 */

void show_menu()
{
   printf("\n=========== User Menu Interface ==========\n");
   printf("***AVAILABLE OPTION***\n");
   printf("1. Xem trang thai tat ca cua\n");
   printf("2. Dieu khien cua\n");
   printf("3. Packing\\Upackaging trang thai vao frame\n");
   printf("4. Kiem tra parity, dao bit\n");
   printf("5. Thao tac advanced pointer\n");
   printf("6. Thoat\n");
   printf("===========================\n");
   printf("Xin vui long chon: ");
}

/**
 * @brief Xem trạng thái của 4 cửa 
 * @param doors  Mảng 4 cửa nguồn
 */
void DoorStatus(Door* doors);

/**
 * @brief Chọn 1 cửa trong 4 cửa để thao tác actuator để cập nhật trạng thái cửa
 * @param doors  Mảng 4 cửa nguồn
 */
void DoorUpdate(Door* doors);

/**
 * @brief Đóng gói, gỡ gói frame dữ liệu.
 * @param doors  Mảng 4 cửa nguồn
 * @param frame  Con trỏ tới frame đích
 */
void Pack_Unpackframe(Door* doors, CANFrame_t* frame);

/**
 * @brief Chọn 1 cửa trong 4 cửa để kiểm tra parity hoặc đảo bit.
 * @param doors  Mảng 4 cửa nguồn
 */
void CheckParity_ReverseBit(Door *doors);

int main()
{
  //Khởi tạo mảng quản lý 4 cửa
  Door doors[num_doors] = {0};

  //Khởi tạo frame chứa gói dữ liệu 
  CANFrame_t Canframe = {0};
   
  //Khởi tạo trạng thái mặc định ban đầu của 4 cửa
  for (int i= 0; i <num_doors; ++i)
  {
    Door_Init(&doors[i],openDoor,closeDoor,lockDoor,unlockDoor);
  }

  int choice = 0;
  while (choice != 6)
  {
    show_menu();
    scanf("%d", &choice);
    getchar();
    //Menu tương tác với người dùng
    switch (choice)
    {
      case 1: DoorStatus(doors);                  break;
      case 2: DoorUpdate(doors);                  break;
      case 3: Pack_Unpackframe(doors, &Canframe); break;
      case 4: CheckParity_ReverseBit(doors);      break;
      case 5: pointerDemo(doors);                 break;
      case 6: break;
      default: printf("Tuy chon khong hop le vui long chon lai");
    }
  }
  printf("Da thoat khoi Menu\n");
  return 0;
}

void DoorStatus(Door *doors)
{
  printf("\nTrang thai tat ca cac cua\n");
  for(int i = 0;i < num_doors; ++i)
  {
    printf("Door %d Framebyte: %02X  Status: %s and %s\n", i+1, doors[i].statusUnion.byte, doors[i].statusUnion.status.isOpen ?  "Open" : "Close",
    doors[i].statusUnion.status.isLocked ? "Lock" : "Unlock");
  }
}

void DoorUpdate(Door *doors)
{
  int door_num, choice;
  select:
  printf("Vui long chon 1 trong 4 cua tu 1 den 4 de cap nhat trang thai: ");
  scanf("%d",&door_num);
  getchar();
  if (door_num < 0 || door_num > 4)
  {
    printf("Oto chi co 4 cua khong co cua so %d vui long chon lai\n",door_num);
    goto select;
  }

  select2:
  printf("\nVui long chon trang thai de cap nhat:\n1. Mo cua\n\
2. Dong cua\n3. Khoa cua\n4. Mo khoa cua\nChon trang thai: ");
  scanf("%d",&choice);
  switch (choice)
  {
    case 1: openDoor(&doors[door_num-1]);     break;
    case 2: closeDoor(&doors[door_num-1]);    break;
    case 3: lockDoor(&doors[door_num-1]);     break;
    case 4: unlockDoor(&doors[door_num-1]);   break;
    default: 
      printf("Tuy chon khong hop le vui long chon lai\n");
      goto select2;
  }

}

void Pack_Unpackframe(Door* doors, CANFrame_t* frame)
{
  int choice;
  select:
  printf("Vui long chon cach thuc xu li voi frame du lieu:\n\
1. Dong goi frame du lieu\n2. Go goi frame du lieu\nChon cach xu li: ");
  scanf("%d",&choice);
  getchar();
  switch (choice)
  {
    case 1: packDoorStatus(doors, frame);     break;
    case 2: unpackDoorStatus(frame, doors);   break;
    default: 
      printf("Tuy chon khong hop le vui long chon lai\n");
      goto select;
  }
}

void CheckParity_ReverseBit(Door* doors)
{
  int door_num, choice;
  select:
  printf("Vui long chon 1 trong 4 cua tu 1 den 4 de kiem tra parity hoac dao bit: ");
  scanf("%d",&door_num);
  getchar();
  if (door_num < 0 || door_num > 4)
  {
    printf("Oto chi co 4 cua khong co cua so %d vui long chon lai\n",door_num);
    goto select;
  }

  select2:
  printf("\nVui long chon kiem tra bang Parity hoac Dao bit :\n1. Parity Bit\n\
2. Dao Bit\nChon phuong thuc kiem tra: ");
  scanf("%d",&choice);
  switch (choice)
  {
    case 1: printf("\nParity Bit cua Door %d la so %s\n", door_num, checkParity(doors[door_num-1].statusUnion.byte) ? "chan" : "le");       break;
    case 2: printf("\nGia tri Dao Bit cua Door %d la %u\n", door_num, reverseBits(doors[door_num-1].statusUnion.byte));                     break;
    default: 
      printf("Tuy chon khong hop le vui long chon lai\n");
      goto select2;
  } 
}
