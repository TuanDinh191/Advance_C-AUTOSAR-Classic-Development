# Bài 10: Linked List 
#### 1. Đặt vấn đề 
- Để thực hiện thao tác xóa hoặc thêm phần tử bất ký phần tử nào trong mảng ta sẽ thực hiện những bước như sau:
- Đối với việc xóa 1 phần tử bất kỳ trong mảng qua những bước như là:
`+` B1: Đầu tiên ta phải gán giá trị tại phần tử muốn xóa là ký tự NULL `\0`.

`+` B2: Dịch bên trái với số lượng byte phụ thuộc vào kiểu dữ liệu của mảng đó, tổng số lượng phần tử và vị trí của phần tử đó bị xóa trong mảng ( ví dụ một mảng có 5 phần tử có kiểu dữ liệu là int sẽ dịch sang trái 1 lần là 4 byte và vị trí phần tử muốn xóa là phần tử thứ 2 thì sẽ dịch sang trái tổng cộng là 3 lần (12 byte)).

`+` B3: Dùng realloc để giới hạn thu hẹp lại tổng số lượng phần tử trong mảng, thu hồi vùng nhớ phần tử cuối cùng.
- Đối với việc thêm 1 phần tử bất kỳ trong mảng qua những bước như là:

`+` B1: Do việc thêm phần tử trong mảng sẽ tăng kích thước của mảng đó nên đầu tiên sẽ dùng relloc để cấp phát vùng nhớ tức là thêm 1 phần tử váo cuối mảng.

`+` B2: Dịch bên phải với số lượng byte phụ thuộc vào kiểu dữ liệu của mảng đó, tổng số lượng phần tử và vị trí phần tử đó muốn được thêm vào trong mảng ( ví dụ một mảng có 6 phần tử có kiểu dữ liệu là double sẽ dịch sang phải 1 lần là 8 byte và vị trí phần tử muốn thêm vào là phần tử thứ 3 thì sẽ dịch sang phải tổng cộng là 4 lần (32 byte)).

`+` B3: Gán giá trị tại phần tử muốn thêm vào là ký tự NULL `\0` sau đó sẽ gán giá trị mong muốn thêm tại vị trí phần tử đó.

- Có thể thấy việc xóa hoặc thêm 1 phần tử trong mảng đều trải qua những bước như trong các bước thì bước mà sẽ tốn nhiều thời gian nhất sẽ là bước dịch sang trái hoặc phải các byte, đối với mảng chứa ít 
phần tử việc thực hiện xóa hoặc thêm 1 phần tử sẽ chưa ảnh hưởng đến tốc độ xử lí nhưng đối với một mảng chứa số lượng lớn ví dụ cỡ 10000 phần tử khi thực hiện dich byte cho việc thêm hoặc xóa 1 phần tử sẽ phải dịch đi 9999 lần tiêu tốn rất nhiều thời gian, lúc này tốc độ xử lý chương trình sẽ chậm lại đi. Để khắc phục vấn đề này ta sẽ dùng một cấu trúc dữ liệu là Linked List.

#### 2. Linked list:
#### - Định nghĩa:
- Linked List (Danh sách liên kết) là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu, trong mảng thì các thành phần được gọi là phần tử nhưng trong linked list được gọi là nút (nodes).
- Một nút trong linked list sẽ có chứa 2 thành phần:

`+` Value: Giá trị dữ liệu giống như phần tử trong mảng.

`+` Con trỏ: Dùng để trỏ đến địa chỉ node tiếp theo.

- Chính vì đặc điểm của linked list là mỗi node có thành phần thứ 2 là con trỏ có thể trỏ đến địa chỉ node tiếp theo nên nó có thể liên kết với nhau tạo thành 1 danh sách liên kết. Khác với mảng thì các phần tử trong mảng đều có địa chỉ liền kề với nhau và cố định nhưng đối với linked list thì các nút (node) có thể có địa chỉ khác nhau chính vì thế việc thêm xóa 1 node trong linked list sẽ dễ dàng, linh hoạt, tốc độ chương trình xử lí sẽ nhanh hơn so với mảng. 
#### - Tạo một 1 node trong chương trình:
-  Trong lập trình C sẽ không có thư viện hỗ trợ một kiểu dữ liệu như node trong danh sách liên kết. Để tạo ra 1 node ta sẽ dùng struct để lưu các thành phần của 1 node.
```
typedef struct Node 
{
    struct Node *next; 
    int val;
}Node;
``` 
- Để khởi tạo 1 node trong linked list ta sẽ dùng hàm như sau:
```
Node *CreateNode(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->val = val;
    return node;
}
```
Dùng trong chương trình chính ta phải khởi tạo 1 con trỏ trỏ về địa chỉ trả về từ hàm khới tạo Node. Để liên kết node tiếp theo ta sẽ dùng con trỏ Next trỏ đến địa chỉ node tiếp theo.
```
int main()
{
    //Tạo 2 node trong danh sách liên kết
    Node *node1 = CreateNode(5);
    Node *node2 = CreateNode(12);

    //Liên kết node 1 với node 2
    node1->next = node2;
}
```
#### - Hàm kiểm tra có 1 node trong danh sách liên kết
- Hàm trả về giá trị true hoặc false nếu không có node nào trong danh sách liên kết.
```
bool empty(Node *head)
{
    return (head == NULL);
}
```
#### - Các hàm thêm 1 node vào trong danh sách liên kết
- Hàm `push_front` có chức năng thêm 1 node vào đầu danh sách liên kết. Để thêm 1 node vào cuối danh sách liên kết ta sẽ tạo ra 1 node sau đó sẽ kiểm tra danh sách liên kết có 1 node nào chưa nếu chưa sẽ lấy node vừa tạo ra sẽ là node đầu tiên trong danh sách liên kết, nếu có rồi thì cập nhật con trỏ next vừa mới tạo ra trỏ tới node đầu tiên của danh sách liên kết và thay đổi con trỏ gốc của danh sách liên kết trỏ tới node đầu tiên vừa cập nhật. 

```
void push_front(Node **head, int value)
{
    // tạo node mới
    Node *node = CreateNode(value);

    // cập nhật node đầu nếu danh sách rỗng
    if (empty(*head))
    {
        *head = node;
        return;
    }
    // cập nhật node đầu của list
    node->next = *head;
    *head = node;
}

```
- Hàm `push_back` có chức năng thêm 1 node vào cuối danh sách liên kết. Để thêm 1 node vào cuối danh sách liên kết ta sẽ tạo ra 1 node sau đó sẽ kiểm tra danh sách liên kết có 1 node nào chưa nếu chưa sẽ lấy node vừa tạo ra sẽ là node đầu tiên trong danh sách liên kết, nếu có rồi sẽ lần lượt kiểm tra con trỏ Next của mỗi node, nếu node nào có thành phần thứ 2 con trỏ Next chứa giá trị NULL tức là đã dến node cuối danh sách liên kết bắt đầu liên kết với node vừa tạo ra.
```
void push_back(Node **head, int value)
{
    // tạo node mới
    Node *node = CreateNode(value);

    // kiểm tra và cập nhật node đầu nếu danh sách rỗng
    if (empty(*head))
    {
        *head = node;
        return;
    }

    // gán địa chỉ node đầu
    Node *current = *head;

    // duyệt cho đến khi gặp node cuối
    while (current->next != NULL)
    {
        current = current->next;
    }

    // cập nhật node cuối
    current->next = node;
}
```
- Hàm `insert` có chức năng thêm 1 node vào vị trí bất kỳ trong danh sách liên kết. Nếu node thêm vào là vị trí đầu tiên trong danh sách liên kết sẽ dùng hàm `push_front` để thêm vào đầu danh sách liên kết, nếu vị trí node thêm vào là cuối danh sách liên kết thì dùng hàm `push_back`. Nếu không phải là vị trí đầu hoặc cuối danh sách để thêm vào thì ta sẽ tạo 1 node rồi kiểm tra điều kiện của `index` để đến được node (Node A) trước 1 node so với node (Node B) được thêm vào, sau đó lấy giá trị con trỏ next của node A để gán con trỏ next cho Node B lúc này Node B đã liên kết được với node tiếp theo, node tiếp theo con trỏ Node A bây giờ là Node B cập nhật lại giá trị con trỏ next Node A trỏ đến địa chỉ của con trỏ Node B.     
```
void insert(Node **head, int value, int position)
{
    // xủ lý chèn ở đầu list
    if (position <= 0)            push_front(head, value);
    // xử lý chèn ở cuối list
    else if (position >= size(*head) - 1) push_back(head, value);
    // xủ lý chèn ở các vị trí còn lại
    else
    {
        Node *new_node = CreateNode(value);

        Node *current = *head;
        int index = 0;

        // duyệt đến vị trí trước node cần thêm 
        while (index < position - 1)
        {
            current = current->next;
            index++;
        }
        // cập nhật node mới tại vị trí insert
        new_node->next = current->next;
        current->next = new_node;
    }
}
```
#### - Các hàm xóa node trong danh sách liên kết 
- Hàm `pop_front` có chức năng xóa 1 node ở đầu danh sách liên kết. Để thực hiện xóa 1 node thì đầu tiên sẽ kiểm tra xem danh sách liên kết có node nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Trường hợp danh sách liên kết có 1 node thì để xóa node bằng cách giải phóng vùng nhớ của node đó sau đó cập nhật con trỏ gốc danh sách liên kết tới giá trị NULL lúc này danh sách liên kết đã rỗng, trường hợp danh sách liên kết có 2 node trở lên thì phải cập nhật con trỏ gốc của danh sách liên kết trỏ tới node thứ 2 rồi sau đó thì để xóa node sẽ giải phóng vùng nhớ node đầu tiên của danh sách liên kết, bắt buộc phải theo thứ tự này bởi vì nếu xóa node đầu tiên danh sách liên kết thì sẽ không có giá trị địa chỉ của node thứ 2 để cập nhật con trỏ gốc của danh sách liên kết mà sở dĩ node đầu tiên có thành phần thứ 2 trỏ tới địa chỉ node thứ 2. 
```
void pop_front(Node **head)
{
    if (empty(*head))            
    {                           
        printf("empty list\n"); 
        return;                 
    }

    Node *current = *head;
   
    //trường hợp chỉ có 1 node
    if (current->next == NULL)
    {
        free(current);  //xóa node duy nhất của list
        *head = NULL;   //cập nhật con trỏ gốc của list
        return;
    }
    //trường hợp có 2 node trở lên
    *head = (*head)->next; //cập nhật node đầu mới của list trước khi xóa 
    free(current);         //xóa node đã lưu
}
```
- Hàm `pop_back` có chức năng xóa 1 node ở cuối danh sách liên kết. Để thực hiện xóa node sẽ kiểm tra xem danh sách liên kết có node nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Trường hợp danh sách liên kết có 1 node thì để xóa node bằng cách giải phóng vùng nhớ của node đó sau đó cập nhật con trỏ gốc danh sách liên kết tới giá trị NULL lúc này danh sách liên kết đã rỗng, trường hợp danh sách liên kết có 2 node trở lên sẽ tìm kiếm node cuối cùng danh sách liên kết bằng cách kiểm tra node mà có node (node A) trước node (node B) có giá trị con trỏ Next là NULL rồi giải phóng vùng nhớ node B tức là đã xóa được node cuối danh sách liên kết rồi cập nhật con trỏ Next của node A là giá trị NULL để biến node A là node cuối cùng của danh sách liên kết.  
```
void pop_back(Node **head)
{
    // nếu danh sách rỗng thì dừng xử lý
    if (empty(*head))            
    {                           
        printf("empty list\n"); 
        return;                 
    }
    Node *current = *head;

    // xử lý nếu chỉ có 1 node
    if (current->next == NULL)
    {
        free(current); // giải phóng node đầu do current đang trỏ tới
        *head = NULL;  // cập nhật con trỏ đầu list
        return;
    }

    // xử lý nếu có 2 node trở lên
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    Node *last_node = current->next; // lưu node cuối
    free(last_node);                 // giải phóng node cuối cũ
    current->next = NULL;            // cập nhật node cuối mới
}
```   
- Hàm `erase` có chức năng xóa 1 node ở vị trí bất kỳ trong danh sách liên kết. Để thực hiện xóa node sẽ kiểm tra xem danh sách liên kết có node nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Trường hợp xóa 1 node ở đầu danh sách liên kết thì sẽ thực thi hàm `pop_front`, trường hợp xóa 1 node ở cuối danh sách liên kết thì sẽ thực thi hàm `pop_back`. Nếu không phải là vị trí node đầu hoặc cuối danh sách để xóa sẽ kiểm tra điều kiện của `index` để đến được node (Node A) trước 1 node so với node (Node B) được xóa, sau đó lấy giá trị con trỏ next của Node B gán cho giá trị con trỏ next của Node A rồi mới thu hồi vùng nhớ node B, lúc này node B đã được xóa node A đã liên kết với node kế tiếp của node B.  

```
void erase(Node **head, int position)
{
    if (empty(*head))            
    {                           
        printf("empty list\n"); 
        return;                 
    }

    //xóa node đầu nếu vị trí <= 0
    if (position <= 0)                      pop_front(head);
    
    //xóa node cuối nếu vị trí >= số node lưu trữ trong list
    else if (position >= size(*head) - 1)   pop_back(head);
    else
    {
        Node *current = *head;
        int index = 0;

        //duyệt đến vị trí trước node cần xóa
        while (index < position - 1)
        {
            current = current->next;
            index++;
        }

        // lưu trữ node cần xóa
        Node *temp = current->next;

        // cập nhật node hiện tại trỏ đến địa chỉ sau node cần xóa
        current->next = current->next->next;

        // xóa node đã lưu
        free(temp);
    }
}
```
- Hàm `clear` có chức năng xóa tất cả các node trong danh sách liên kết. Để thực hiện xóa node sẽ kiểm tra xem danh sách liên kết có node nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Trường hợp có 1 node trở lên thì để xóa lần lượt các node từ đầu danh sách liên kết đến cuối danh sách liên kết trước tiên phải cập nhật con trỏ gốc của danh sách liên kết đến địa chỉ node tiếp theo rồi sau đó mới thực hiện xóa node bằng cách thu hồi vùng nhớ việc này lặp lại cho tới khi con trỏ gốc của danh sách trỏ tới giá trị NULL tức là đã xóa tất cả các node trong danh sách liên kết.   
```
void clear(Node **head)
{
    if (empty(*head))            
    {                           
        printf("empty list\n"); 
        return;                 
    }
    Node *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}
```
#### - Các hàm lấy giá trị value của 1 node trong danh sách liên kết  
- Hàm `front` có chức năng lấy giá trị value của node đầu tiên trong danh sách liên kết. Để thực hiện lấy giá trị ta sẽ kiểm tra xem danh sách liên kết nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Nếu có ta sẽ thực hiện lấy giá trị value của node đầu danh sách liên kết thông qua con trỏ gốc của danh sách liên kết.
```
int front(Node *head)
{
    if (empty(head))            
    {                           
        printf("empty list\n"); 
        return 0;                 
    }
    return head->val;
}
```
- Hàm `back`có chức năng lấy giá trị value của node cuối danh sách liên kết. Để thực hiện lấy giá trị ta sẽ kiểm tra xem danh sách liên kết nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Nếu có ta lần lượt tìm kiếm node cuối danh sách bằng cách kiểm tra con trỏ Next của mỗi node có bằng NULL hay không khi tìm được rồi lấy giá trị value tại node đó.   
```
int back(Node *head)
{
    if (empty(head))            
    {                           
        printf("empty list\n"); 
        return 0;                 
    }
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    return current->val;
}

```

- Hàm `get` có chức năng lấy giá trị value 1 node tại vị trí bất kỳ trong danh sách liên kết. Để thực hiện lấy giá trị value sẽ kiểm tra xem danh sách liên kết có node nào không nếu không sẽ đưa ra thông báo là danh sách liên kết rỗng. Trường hợp lấy giá trị value ở đầu danh sách liên kết thì sẽ thực thi hàm `front`, trường hợp lấy giá trị value ở cuối danh sách liên kết sẽ thực thi hàm `back`. Nếu không phải là vị trí node đầu hoặc cuối danh sách để lấy giá trị value sẽ kiểm tra điều kiện của `index` để đến được node đúng vị trí sau đó lấy giá trị value tại node đó.  
```
int get(Node *head, int pos)
{

    if (empty(head))            
    {                           
        printf("empty list\n"); 
        return 0;                 
    }

    // trả về node đầu nếu pos là giá trị âm
    if (pos <= 0) return front(head);

    // trả về node cuối nếu pos > vị trí cuối list
    else if (pos >=  size(head) - 1) return back(head);

    // trả về node tương ứng với giá trị pos
    else
    {
        Node *current = head;
        int index = 0;

        // duyệt đến khi gặp node ở vị trí pos tương ứng
        while (index < pos)
        {
            current = current->next;
            index++;
        }
        return current->val;
    }
}
```