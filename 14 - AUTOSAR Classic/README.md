# Bài 14: Autosar Classic 
#### 1. Đặt vấn đề 
- Hệ thống ô tô trước đây trang bị ít tính năng chỉ phục vụ cho chức năng cơ bản để đi lại vì thế sẽ dùng số lượng ECU trang bị cho ô tô không có nhiều đối với ngày nay thì hệ thống ô tô không thuần túy là phương tiện đi lại nữa mà lại được trang bị nhiều tính năng thông minh và tiện nghi được tính hợp vào ví dụ như là kết nối mạng, giao diện tương tác người dùng, hệ thống giải trí, ... chính vì lí do này mà số lượng ecu được trang bị cho ô tô sẽ được tăng đáng kể mà mỗi ecu sẽ phục vụ cho chức năng khác nhau, tùy vào ứng dụng, tốc độ xử lí cũng như là hiệu suất của mỗi ECU mà mỗi ECU sẽ được thực thi trên những con MCU khác nhau. Chính vì vậy sẽ có những team sẽ phối hợp với nhau để phát triển hệ thống phần mềm trong ô tô khi dự án của mỗi nhóm hoàn thành thì mỗi team sẽ phải thống nhất với nhau với các dự án phát triển cho nhiều ECU thành một hệ thống hoàn chỉnh. Vấn đề sinh ra lúc này là mỗi team sẽ có tiêu chuẩn, hướng phát triển, triển khai phần mềm khác nhau khi mà gộp các mã nguồn dự án các ECU thành một hệ thống thì sẽ xảy ra xung đột với nhau.
- Đối với mã nguồn của một dự án hệ thống ô tô khi được triển khai trên 1 file duy nhất và khi chương trình chạy tuần tự sẽ không thể xử lý nhiều chức năng cùng một lúc, không đảm bảo độ ổn định và độ tin cậy khi vận hành ở điều kiện môi trường thực tế do bị tác động yếu tố bên ngoài như nhiệt độ, nhiễu, rung .... , và không thể sử dùng lại mã nguồn của dự án do phụ thuộc vào phần cứng khi phần cứng thay đổi thì phần mềm cũng thay đổi theo lúc này phải viết lại phần mềm mới sẽ làm tăng chi phí và thời gian phát triển, quản lý lỗi và bảo trì phức tạp, khó khăn và thiếu linh hoạt trong việc phát triển nâng cấp hệ thống, lí do nữa là chương trình viết cho MCU hãng này không thể dùng cho MCU hãng khác. 
- Để giải quyết những vấn đề trên cần phải phát triển công cụ, nền tảng tiêu chuẩn chung tổng quát để chuẩn hóa cho phần mềm nhúng nói chung cũng như ngành automotive để đảm bảo các team khi mà triển khai chức năng cho từng ECU để đi đúng hướng, tránh bị sai sót, bị mơ hồ vấn đề cần giải quyết, đảm bảo hỗ trợ đa tác vụ, tách biệt vai trò software và hardware khi dó hardware có thể chạy trên những cái software khác và ngược lại software có thể chạy trên nhiều phần cứng khác nhau, dễ quản lý và bảo trì nâng cấp phần mềm, có khả năng tái sử dụng phần mềm, dễ dàng thay đổi để tương thích các dòng MCU khác nhau. Các công ty thuộc lĩnh vực ô tô, automotive đã phát triển cái tiêu chuẩn chung để giải quyết vấn đề trên chính là tiêu chuẩn AUTOSAR. 
#### 2. AUTOSAR 
#### - Định nghĩa: 
- AUTOSAR (AUTomotive Open System ARchitecture) là một tiêu chuẩn toàn cầu cho phát triển phần mềm ô tô với mục tiêu là chuẩn hóa kiến trúc phần mềm cho các hệ thống điều khiển điện tử (ECU) trong ô tô, nhằm tăng tính khả chuyển, khả mở rộng và giảm chi phí phát triển. AUTOSAR cũng cung cấp một cái tiêu chuẩn xây dựng hệ điều hành trong hệ thống ô tô để quản lý, điều phối các tác vụ chức năng trong ô tô. 
- Dựa vào tiêu chuẩn AUTOSAR và hệ điều hành (Os) sẽ tạo ra hệ điều hành OS cho AUTOSAR để làm được những tiêu chí: 

__+__ Quản lý các tác vụ và mức ưu tiên giữa chúng.

__+__ Đảm bảo hệ thống hoạt động theo thời gian thực.

__+__ Cung cấp các cơ chế Alarm, Event, Resource giúp đồng bộ và bảo vệ chia sẽ dữ liệu giữa các tác vụ.  

#### - Phân lớp trong AUTOSAR:
- AUTOSAR định nghĩa 1 kiến trúc phân lớp được thiết kế để xử lý và trừu tượng hóa các hoạt động khác nhau của mã nguồn. Từ đó giúp đội nhóm  dễ dàng quản lý và phát triển dự án theo hướng module hóa và linh hoạt trong việc tích hợp với bất kỳ module từ các nhóm phát triển khác

 <p align = "center">
 <img width="1601" height="798" alt="image" src="https://github.com/user-attachments/assets/5ecdf825-661e-483d-8aca-aa42e98174b8" />

- AUTOSAR sẽ có 3 lớp chính:
  
__+__ ASW (Application Layer): Là lớp nằm trên cùng thì lớp này sẽ triển khai phần mềm ứng dụng cụ thể ở trên ô tô chứa các khối chức năng cụ thể, khối phần mềm ứng dụng (Software Component - SWC) để cụ thể hóa hành vi của 1 chiếc xe. (Ví dụ: điều khiển động cơ, hệ thống phanh, túi khí, cảnh báo, vv…) tức là mỗi SWC thực hiện 1 chức năng cụ thể trong hệ thống ECU. SWC chỉ quan tâm đến logic (tính toán số học, khởi động như thế nào), các SWC có thể giao tiếp với nhau và giao tiếp với phần cứng thông qua RTE.

__+__ RTE (Runtime Environment): Lớp nằm giữa là lớp môi trường thực thi giúp lớp application có các SWC giao tiếp với nhau và lớp application có thể giao tiếp lớp bên dưới BSW thông qua giao diện trừu tượng để tách biệt lớp application với lớp bên dưới là lớp phần mềm cơ bản (BSW), điều này giúp các SWCs có thể sử dụng dịch vụ hoặc điều khiển phần cứng một cách dễ dàng. 

__+__ BSW (Basic Software): Đảm bảo lớp application giao tiếp độc lập với phần cứng hỗ trợ các SWC hoạt động trên phần cứng, BSW chứa lớp dịch vụ (Service Layer) chứa các dịch vụ như:

System Services: Nơi triển khai hệ điều hành cho hệ thống ô tô.

DCM: Cung cấp dịch vụ hệ thống chuẩn đoán xử lí lỗi.

DEM: Dùng để lưu trữ sự kiện chuẩn đoán lỗi.

Crypto Services: Dịch vụ mã hóa trao đổi dữ liệu giữa các ECU, giữa các hệ thống ô tô.
 
Memory service: Dịch vụ quản lý bộ nhớ

Off Board Communication Services: Dịch vụ truyền thông dữ liệu giữa các ECU không có thông qua ngoại vi điều khiển MCU ví dụ CAN, LIN, SPI, I2C hoặc UART... được dùng để kết nối thiết bị bên ngoài để hỗ trợ truyền thông dữ liệu giữa các ECU

Communicaton Services:  Dịch vụ truyền thông dữ liệu giữa các ECU  dựa trên các ngoại vi mà vi điều khiển MCU có CAN, LIN, SPI, I2C .... 

I/O HardWare Abstraction: Lớp trừu tượng cấu hình input/ output trên các chân vi điều khiển thao tác với phần cứng.

Complex Drivers: Tương tác hoặc giao tiếp với thiết bị bên ngoài không có theo chuẩn AUTOSAR.

__+__ Ngoài ra BSW còn chứa 2 lớp nữa là:

ECU Abstraction, Hardware Abstraction Layer: Trừu tượng hóa việc tương tác với MCU, cung cấp API độc lập với MCU.

MCAL (Microcontroller Abstraction Layer): Phát triển các drivers trên MCU, cung cấp API để đọc ghi thao tác ở ngoại vi trên vi điều khiển giao tiếp trực tiếp với phần cứng cung cấp giao diện trừu tượng cho lớp trên sử dụng là lớp ECU Abstraction. 

#### - Phân loại trong AUTOSAR
- Trong AUTOSAR sẽ chia ra 2 loại là:
  
__+__ AUTOSAR Classic: Đóng vai trò phần khung sườn, điều phối và vận hành những phần cốt lỗi của 1 chiếc xe, cung cấp tiêu chuẩn để phát triển tính năng cơ bản, những phần mềm cơ bản 1 chiếc ô tô phải có như điều khiển tốc độ, điều khiển mômen xoắn, kiểm soát dòng điện điện áp, chế độ lái,.... 

__+__ AUTOSAR Adaptive: Cung cấp tiêu chuẩn để phát triển tính năng nâng cao trên xe những nhiệm vụ xử lý thông minh như lái tự động, né tránh vật cản, cập nhật phần mềm từ xa OTA, thiết kế giao diện tương tác cung cấp tính năng giải trí trên xe ô tô....
