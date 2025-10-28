# Bài 12: Algorithm - Binary Search Tree
#### 1. Sorting algorithm - Bubble Sort
#### - Định nghĩa:
- là một thuật toán sắp xếp nổi bọt bắng cách so sánh giá trị của 2 phần tử liền kề nhau sau đó hoán đổi vị trí để sắp xếp các phần tử lớn hơn về cuối dãy hoặc phần tử nhỏ hơn về đầu dãy.
#### - Các bước triển khai của thuật toán:
`+`B1: Duyệt phần tử trong mảng từ trái sang phải.

`+`B2: So sánh hai phần tử liền kề, nếu sắp xếp phần tử lớn hơn về cuối dãy thì phần tử trước lớn hơn phần tử sau thì hoán đổi vị trí và tương tự đối với sắp xếp phần tử nhỏ hơn.

`+`B3: Lặp lại quá trình cho đến khi không còn sự hoán đổi nào xảy ra tức là lúc này mảng đã được sắp xếp.

- Cụ thể hơn với N phần tử thì số lần duyệt mảng là N - 1, số lần so sánh ở mỗi lượt duyệt thứ i là N - i - 1, i là thứ tự duyệt.
Ví dụ: 
```
int arr[6] = {5, 3, 8, 6, 2, -3};

Vị trí phần tử :    0    1    2    3     4     5
Giá trị phần tử:    5    3    8    6     2    -3

Số phần tử N = 6
Số lần duyệt mảng = 5

Số lần so sánh cho lần duyệt thứ 0: 5                                                   
                      Vị trí phần tử :    0    1    2    3     4     5
Giá trị phần tử cho lần so sánh thứ 1:    3    5    8    6     2    -3
Giá trị phần tử cho lần so sánh thứ 2:    3    5    8    6     2    -3
Giá trị phần tử cho lần so sánh thứ 3:    3    5    6    8     2    -3
Giá trị phần tử cho lần so sánh thứ 4:    3    5    6    2     8    -3
Giá trị phần tử cho lần so sánh thứ 5:    3    5    6    2    -3     8

Số lần so sánh cho lần duyệt thứ 1: 4                                                   
                      Vị trí phần tử :    0    1    2    3     4     5
Giá trị phần tử cho lần so sánh thứ 4:    3    5    2   -3     6     8

Số lần so sánh cho lần duyệt thứ 2: 3                                                   
                      Vị trí phần tử :    0    1    2    3     4     5
Giá trị phần tử cho lần so sánh thứ 3:    3    2   -3    5     6     8

Số lần so sánh cho lần duyệt thứ 3: 2                                                   
                      Vị trí phần tử :    0    1    2    3     4     5
Giá trị phần tử cho lần so sánh thứ 3:    2   -3    3    5     6     8

Số lần so sánh cho lần duyệt thứ 4: 1                                                  
                      Vị trí phần tử :    0    1    2    3     4     5
Giá trị phần tử cho lần so sánh thứ 1:   -3    2    3    5     6     8

```
#### - Triển khai thuật toán Bubble Sort trong chương trình: 
```
void bubbleSort(int arr[], int n)
{
    for (int i=0; i<=n-2; i++)
    {
        for (int j=0; j<=n-i-2; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j]   = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }  
}
```
#### 2. Search Algorithm 
#### - Định nghĩa
- Linear Search là một thuật toán tìm kiếm tuyến tính sẽ duyệt từng phần tử trong mảng để tìm kiếm giá trị cần tìm, thì đây là thuật toán tìm kiếm đơn giản nhất. Nhưng có nhược điểm là nếu phần tử trong mảng có số lượng càng lớn thì thời gian tìm kiếm sẽ ngày càng lâu hơn. 
Cơ chế hoạt động của thuật toán Linear Search:

`+B1`: Duyệt từng phần tử trong mảng từ trái sang phải.

`+B2`: Nếu phần tử đang xét trùng với giá trị cần tìm, trả về vị trí của nó. 

`+B3`: Nếu duyệt hết mảng mà không tìm thấy, trả về kết quả không tồn tại.

- Binary Search là một thuật toán tìm kiếm nhị phân sẽ tìm kiếm bằng cách lấy giá trị ở giữa mảng để so sánh nếu không đúng sẽ tìm kiếm một giá trị ở giữa mảng của một nửa mảng còn lại để tiếp tục tìm kiếm. Thì so với linear search thì thời gian tìm kiếm đã nhanh hơn do mỗi lần tìm kiếm thì số lượng giá trị để tìm trong đó đã giảm một nữa đi. Nhưng mà để triển khai thuật toán tìm kiếm này phải triển khai thuật toán bubble sort sắp xếp phẩn tử trong mảng. 

Cơ chế hoạt động của thuật toán Binary Search:

`+B1`: Sắp xếp mảng (tăng dần hoặc giảm dần). Khởi tạo chỉ số `left` là chỉ số vị trí đầu mảng cần tìm kiếm, chỉ số `right` là chỉ số vị trí cuối mảng cần tìm kiếm có được chỉ số `left` và `right` để tìm được chỉ số vị trí giữa mảng `mid` để lấy giá trị giữa mảng thông qua chỉ số `mid`. Sau 1 lần tìm kiếm thì qua một nữa mảng còn lại để tìm kiếm cập nhật lại chỉ số `left`, `right`, `mid`. 

`+B2`: So sánh phần tử ở giữa mảng với giá trị cần tìm:

  `Trường hợp 1`: Nếu trùng -> Trả về vị trí 

  `Trường hợp 2`: Nếu nhỏ hơn -> Cập nhật chỉ số  `left = mid + 1` tiếp tục tìm trong nửa phải của mảng 

  `Trường hợp 3`: Nếu lớn hơn -> Cập nhật chỉ số `right = mid + 1` tiếp tục tìm trong nửa trái của mảng 

`+B3`: Lặp lại bước 2 cho đến khi tìm thấy phần tử hoặc nếu chỉ số `left` > `right` thì không tìm giá trị tìm kiếm trong mảng. 

Ví dụ 1: 
```
Vị trí phần tử sau khi được sắp xếp lại bằng thuật toán Bubble Sort 
int arr[9] = {11, 13, 15, 16, 18, 20, 21, 25, 30};

Vị trí phần tử :   0    1    2    3    4     5     6    7    8
Giá trị phần tử:   11   13   15   16   18    20    21   25   30

Giá trị cần tìm kiếm: 25

Lần tìm kiếm thứ 1:
Khỏi tạo chỉ số left  = 0
Khởi tạo chỉ số right = 8
Cập nhật chỉ số mid: mid = (left + right)/2 = (0+8)/2 = 4
So sánh giá trị phần tử giữa mảng arr[4] = 18. Nhỏ hơn so với giá trị tìm kiếm, cập nhật left = mid + 1 = 5.
Cập nhật mảng mới cho lần thứ 2 tìm kiếm :   

Vị trí phần tử :   5     6    7    8
Giá trị phần tử:   20    21   25   30

Lần tìm kiếm thứ 2: 
Cập nhật chỉ số left = 5 
Giữ nguyên chỉ số right = 8
Cập nhật chỉ số mid: mid = (left + right)/2 = (5+8)/2 = 6
So sánh giá trị phần tử mảng arr[6] = 21. Nhỏ hơn giá trị cần tìm kiếm, cập nhật left = mid + 1 = 7.
Cập nhật mảng mới cho lần thứ 2 tìm kiếm:

Vị trí phần tử :   7    8
Giá trị phần tử:   25   30

Lần tìm kiếm thứ 3:
Cập nhật chỉ số left = 7 
Giữ nguyên chỉ số right = 8 
Cập nhật chỉ số mid: mid = (left + right)/2 = (7+8)/2 = 7
So sánh giá trị phần tử mảng arr[7] = 25. Bằng với giá trị tìm kiếm 
```
Ví dụ 2:
```
Vị trí phần tử sau khi được sắp xếp lại bằng thuật toán Bubble Sort 
int arr[9] = {11, 13, 15, 16, 18, 20, 21, 25, 30};

Vị trí phần tử :   0    1    2    3    4     5     6    7    8
Giá trị phần tử:   11   13   15   16   18    20    21   25   30

Giá trị cần tìm kiếm: 27

Lần tìm kiếm thứ 1:
Khỏi tạo chỉ số left  = 0
Khởi tạo chỉ số right = 8
Cập nhật chỉ số mid: mid = (left + right)/2 = (0+8)/2 = 4
So sánh giá trị phần tử giữa mảng arr[4] = 18. Nhỏ hơn so với giá trị tìm kiếm, cập nhật left = mid + 1 = 5.
Cập nhật mảng mới cho lần thứ 2 tìm kiếm :   

Vị trí phần tử :   5     6    7    8
Giá trị phần tử:   20    21   25   30

Lần tìm kiếm thứ 2: 
Cập nhật chỉ số left = 5 
Giữ nguyên chỉ số right = 8
Cập nhật chỉ số mid: mid = (left + right)/2 = (5+8)/2 = 6
So sánh giá trị phần tử mảng arr[6] = 21. Nhỏ hơn giá trị cần tìm kiếm, cập nhật left = mid + 1 = 7.
Cập nhật mảng mới cho lần thứ 2 tìm kiếm:

Vị trí phần tử :   7    8
Giá trị phần tử:   25   30

Lần tìm kiếm thứ 3:
Cập nhật chỉ số left = 7 
Giữ nguyên chỉ số right = 8 
Cập nhật chỉ số mid: mid = (left + right)/2 = (7+8)/2 = 7
So sánh giá trị phần tử mảng arr[7] = 25. Nhỏ hơn giá trị cần tìm kiếm, cập nhật left = mid + 1 = 8.
Cập nhật mảng mới cho lần thứ 3 tìm kiếm:

Vị trí phần tử:   8
Giá trị phần tử:  30

Lần tìm kiếm thứ 4:
Cập nhật chỉ số left = 8
Giữ nguyên chỉ số right = 8
Cập nhật chỉ số mid: mid = (left + right)/2 = (8+8)/2 = 8
So sánh giá trị phần tử mảng arr[8] = 30 .Lớn hơn giá trị cần tìm kiếm, cập nhật right = mid - 1 = 7

Chỉ số left > right không tìm thấy giá trị cần tìm trong mảng.
```
#### - Triển khai thuật toán Binary Search trong chương trình: 
```
int BinarySearch(int* pArr,int left,int right,int search){
    if(left <= right){
        int mid = (left + right) / 2;
        if(search == pArr[mid])           return mid;
        else if(search > pArr[mid])      return BinarySearch(pArr,mid + 1,right,search);
        else                        return BinarySearch(pArr,left,mid - 1,search);
    }
   return -1;
}
```
#### - Cấu trúc dữ liệu phân cấp Tree
- Cấu trúc dữ liệu phân cấp (Tree) là một cấu trúc dữ liệu phi tuyến tính, trong đó các phần tử (được gọi là nút, hay node) được tổ chức theo một thứ bậc phân cấp. Cây là một trong những cấu trúc dữ liệu quan trọng, được sử dụng rộng rãi trong khoa học máy tính để biểu diễn các quan hệ phân cấp, tìm kiếm, sắp xếp, và lưu trữ.


- Biểu diễn cây nhị phân bằng mảng:

__+__ Gốc (root) vị trí thứ 0 của mảng.

__+__ Con trái của nút i = 2*i + 1

__+__ Con phải của nút i = 2*i + 22 

Ví dụ: 

```
int ar[] = {12, 41, 3, 14, 24, 53, 10};

Vị trí phần tử :   0    1    2    3    4     5     6   
Giá trị phần tử:   12   41   3    14   24    53    10  

Biểu diễn cây nhị phân bằng mảng:

               12 (0)
             /       \
            /         \
           /           \
        41 (1)         3 (2)
       /   \           /   \
      /     \         /     \
     /       \       /       \
  14 (3)  24 (4)   53 (5)   10 (6)

```
- Cây Tìm Kiếm Nhị Phân (BST - Binary Search Tree) là một cấu trúc dữ liệu dạng cây, trong đó:

  `+` Mỗi nút có tối đa 2 con (gọi là cây con trái và cây con phải).

  `+` Dữ liệu trong cây tuân theo quy tắc:
    
    Nút con trái chứa giá trị nhỏ hơn nút gốc.

    Nút con phải chứa giá trị lớn hơn nút gốc.

    Quy tắc này áp dụng đệ quy cho toàn bộ cây.

Cụ thể hơn:

```
              A
             /  \             B <= A <= C
            /    \            D <= B <= E
           /      \           F <= C <= G
          B        C 
         / \      /  \
        /   \    /    \
       D     E  F      G 

```
- Khi muốn triển khai thuật toán tìm kiếm nhị phân trên một danh sách liên kết thì ta phải chuyển danh sách liên kết thành một cây tìm kiếm nhị phân sau đó mới áp dụng được thuật toán tìm kiếm nhị phân.

#### - Triển khai thuật toán tìm cây tìm kiếm nhị phân trong chương trình
 - Trong lập trình C sẽ không có thư viện hỗ trợ một kiểu dữ liệu như node trong danh sách liên kết và cây nhị phân. Để tạo ra 1 node ta sẽ dùng struct để lưu các thành phần của 1 node.

Node trong danh sách liên kết:

```
typedef struct Node {
    int value;          /**< Giá trị của node */
    struct Node *next;  /**< con trỏ liên kết đến node kế tiếp*/
} Node;
```

Node trong cây nhị phân:

```
typedef struct CenterPoint {
    int value;                  /**< Giá trị của node */
    struct CenterPoint *left;   /**< con trỏ đến node con bên trái */
    struct CenterPoint *right;  /**< con trỏ đến node con bên phải*/
} CenterPoint;
```
- Hàm `add_Node` có chức năng thêm 1 node mới vào danh sách liên kết được sắp xếp tại vị trí có giá trị node từ nhỏ đến lớn để phục vụ cho việc xây câycây nhị phân tìm kiếm.
```
void add_Node(Node **head, int value) {

    /* 
        {12,3,44,10,29,30}

        head -> 3 -> 10 -> 12 -> 29 -> 30 -> 44 
    */
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    //thêm vào đầu linked list nếu empty hoặc giá trị node mới > node đầu
    if (*head == NULL || (*head)->value >= value){
        new_node->next = *head;
        *head = new_node;   
        return;
    }

    
    Node *current = *head;
    //kiểm tra cho đến khi gặp node cuối và giá trị node tiếp theo trong list lớn hơn node mới tạo
    while (current->next != NULL && (*current->next).value < value) {
        current = current->next;
    }
    //chèn node mới 
    new_node->next = current->next;
    current->next = new_node; 
}
```
- Hàm `centerPoint` được dùng lần đầu có chức năng xác định vị trí node đầu của danh sách liên kết cho chỉ số `start` và vị trí node cuối của danh sách liên kết cho chỉ số `end`. Có 2 chỉ số `start` và `end` để phục vụ hàm `buildTree` xây dựng cây nhị phân tìm kiếm. 

```
CenterPoint *centerPoint(Node *head) {
    int length = 0;
    Node *node = head;
    
    //duyệt qua list và đếm số lượng node
    while (node != NULL) {
        node = node->next;
        length++;
    }

    //trả về cấu trúc binary tree chứa các nhánh đã tạo ra
    return buildTree(head, 0, length - 1);
}
```

- Hàm `buildTree` có chức năng xây dựng một cây nhị phân tìm kiếm. Để xây 1 cây nhị phân thì đầu tiên sẽ phải kiểm tra xem có node nào trong danh sách liên kết không  khi có vị trí node đầu danh sách liên kết và cuối danh sách liên kết thì có thể tìm ra vị trí node giữa danh sách liên kết sau đó cấp phát bộ nhớ động để tạo ra một node của cây nếu node mới tạo lần đầu sẽ gọi là root có giá trị là node giữa của danh sách liên kết tạo ra 2 nhánh ra 2 node con, 1 nhánh bên trái theo một nữa bên trái danh sách liên kết và 1 nhánh bên phải theo một nữa bên phải danh sách liên kết các node này sẽ được đệ qui gọi lại hàm `buildTree` để tạo ra 2 nhánh và 2 node con mới, các node con mới này sẽ tiếp tục đệ qui lại hàm `buildTree` cho đến khi không còn điều kiện (chỉ số start > end) để tạo node và nhánh mới nữa và giá trị trả về của hàm `buildTree` được gọi lần đầu sẽ là địa chỉ root của toàn bộ cây nhị phân được xây dựng hoàn chỉnh.  

```
CenterPoint *buildTree(Node *head, int start, int end) {
    //nếu không có node nào hoặc danh sách không hợp lệ -> dừng xử lý
    if (head == NULL || start > end) {
        return NULL;
    }
    //xác định điểm giữa list
    int mid = (start + end) / 2;
    Node *node = head;
    //lặp cho đến khi gặp node giữa
    for (int i = start; i < mid; i++) {
        if (node->next == NULL) {
            break;
        }
        node = node->next;
    }

    //cấp phát bộ nhớ cho node giữa 
    CenterPoint *root = (CenterPoint *) malloc(sizeof(CenterPoint));
    root->value = node->value;
    //tạo ra các node con từ node giữa (các nhánh của cây nhị phân)
    root->left = buildTree(head, start, mid - 1); 
    root->right = buildTree(node->next, mid + 1, end);

    return root;    //trả về node của nhánh hiện tại
}
```
Hàm `binarySearchTree` là thuật toán tìm kiếm nhị phân tìm kiếm áp dụng cho một cây nhị phân để có thể áp dụng thuật toán để tìm kiếm được giá trị cần tìm thì cần phải có được toàn bộ cây nhị phân được xây dựng hoàn chỉnh từ danh sách liên kết. Nếu giá trị hiện tại của node của cây không phải là giá trị tìm kiếm, thì sẽ thực hiện phép so sánh giữa node hiện tại với giá trị tìm kiếm thì nếu lớn hơn thì sẽ tìm nhánh bên trái của cây nhị phân phía dưới node hiện tại còn nếu nhỏ hơn thì tìm biên phải của cây nhị phân phía dưới node hiện tại. Trong trường hợp đã tìm kiếm được giá trị trong cây nhị phân sẽ trả về địa chỉ của node cây nhị phân đó, trường hợp không tìm được tức là đã vào node sâu nhất của cây đó không thể vào nhánh nào khác thì sẽ trả về là `NULL`.   

```
//ham tim kiem nhi phan
CenterPoint *binarySearchTree(CenterPoint *root, int search) {
    static int loop = 0;
    loop++; 
    printf("so lan lap: %d\n", loop);
    if (root == NULL) {
        loop = 0;
        return NULL;
    }

    if (root->value == search) {
        loop = 0;
        return root;
    }

    //trường hợp tìm kếm
    if (root->value > search) {
        //tìm bên trái binary tree
        return binarySearchTree(root->left, search);
    } else {
        //tìm bên phải binary tree
        return binarySearchTree(root->right, search);
    }
}
```
#### 3. File Operation
#### - Định nghĩa
- Trong lập trình ngôn ngữ C sẽ cung cấp thư viện để thao tác với các file văn bản để đọc hoặc để ghi và nhiều thao tác khác. Các file văn bản thao tác thường là file có đuôi là .txt, csv. Những file chứa thông tin của nhiều kiểu dữ liệu chẳng hạn danh sách người ở chung cư, thông tin người dùng hoặc quản lý bãi đỗ xe ... mà khi ta thực hiện thao tác file để đọc ra để lấy dữ liệu đầu vào để phục vụ làm một chức năng nào đó, hoặc có thể ghi dữ liệu lấy từ một cảm biến hoặc muốn bổ sung vào danh sách. 
- File CSV (Comma-Separated Vales) là một loại file văn bản được sử dụng để lưu trữ và truyền tải dữ liệu có cấu trúc dưới dạng bảng, trong đó các dữ liệu của các cột được phân tách bằng dấu phẩy (,) hoặc một ký tự ngăn cách khác.

#### - Hàm mở và đóng file
- Đầu tiên để thac tác mở hoặc ghi file .... phải mở được file để thao tác file. Hàm `fopen()`phục vụ cho việc mở file 
```
    FILE *file = fopen(const char *file_name, const char *access_mode);

```
- Hàm `fopen` sẽ nhận tham số đầu vào thứ 1 là đường dần đến file `file_name`, tham số thứ 2 là chế dộ thao tác với file `access_mode`
- Chế dộ thao tác với file: 

__+__ `r`: Mở file với chế độ chỉ đọc file. Nếu mở file thành công thì trả về địa chỉ của phần tử đầu tiên trong file, nếu không thì trả về NULL.

__+__ `rb`: Mở file với chế độ chỉ đọc file theo định dạng binary. Nếu mở file thành công thì trả về địa chỉ của phần tử đầu tiên trong file, nếu không thì trả về NULL.

__+__ `w`: Mở file với chế độ ghi vào file. Nếu file đã tồn tại, thì sẽ ghi đè vào nội dung bên trong file. Nếu file chưa tồn tại thì sẽ tạo một file mới. Nếu không mở được file thì trả về NULL.

__+__ `wb`: Mở file với chế độ ghi vào file theo định dạng binary. Nếu file đã tồn tại, thì sẽ ghi đè vào nội dung bên trong file. Nếu file chưa tồn tại thì sẽ tạo một file mới. Nếu không mở được file thì trả về NULL.

__+__ `a`: Mở file với chế độ nối. Nếu mở file thành công thì trả về địa chỉ của phần tử cuối cùng trong file. Nếu file chưa tồn tại thì sẽ tạo một file mới. Nếu không mở được file thì trả về NULL.

__+__ `ab`: Mở file với chế độ nối dưới định dạng binary. Nếu mở file thành công thì trả về địa chỉ của phần tử cuối cùng trong file. Nếu file chưa tồn tại thì sẽ tạo một file mới. Nếu không mở được file thì trả về NULL.

__+__ `r+`: Mở file với chế độ đọc và ghi file. Nếu mở file thành công thì trả về địa chỉ của phần tử đầu tiên trong file, nếu không thì trả về NULL.

__+__ `rb+`: Mở file với chế độ đọc và ghi file dưới định dạng binary. Nếu mở file thành công thì trả về địa chỉ của phần tử đầu tiên trong file, nếu không thì trả về NULL.

__+__ `w+`: Mở file với chế độ ghi và đọc file. Nếu file đã tồn tại thì trả về địa chỉ của phần tử đầu tiên của file. Nếu file chưa tồn tại thì sẽ tạo một file mới.

__+__ `wb+`: Mở file với chế độ ghi và đọc file dưới định dạng binary. Nếu file đã tồn tại thì trả về địa chỉ của phần tử đầu tiên của file. Nếu file chưa tồn tại thì sẽ tạo một file mới.

__+__ `a+`: Mở file với chế độ nối và đọc file. Nếu file đã tồn tại thì trả về địa chỉ của phần tử cuối cùng của file. Nếu file chưa tồn tại thì sẽ tạo một file mới.

__+__ `ab+`: Mở file với chế độ nối và đọc file dưới định dạng binary. Nếu file đã tồn tại thì trả về địa chỉ của phần tử cuối cùng của file. Nếu file chưa tồn tại thì sẽ tạo một file mới.

- Sau khi thao tác file xong ta dùng hàm `fclose()` để đóng file lại. 

#### - Hàm đọc file 
`fscanf()`: Sử dụng chuỗi được định dạng và danh sách đối số biến để lấy đầu vào từ một File.

`fgets()`: Copy nội dung trong File vào mảng dùng để lưu trữ với tối đa số lượng phần tử của mảng hoặc tới khi gặp ký tự xuống dòng.

`fgetc()`: Lấy giá trị tại địa chỉ hiện tại của file, sau đó di chuyển tới địa chỉ tiếp theo. Kiểu trả về là char.

`fread()`: Đọc một số lượng byte được chỉ định từ File .bin.

- Triển khai đọc file trong chương trình:

```
typedef struct 
{
    char* name;
    char* address;
    char* phone;
    uint8_t age;
}Info;

Info *parse_line(char *line)
{
    // cấp phát 1 vùn nhớ tạm để lưu trữ thông tin của user hiện tại
    Info *info = (Info *)malloc(sizeof(Info));
    char *token; // con trỏ lưu trữ giá trị tạm thời

    // Parse name
    token = strtok(line, ","); // tách từng ký tự cho đến khi gặp dấu ","
    info->name = (char *)malloc(strlen(token) + 1);
    strcpy(info->name, token); // sao chép vào vùng nhớ heap

    // Parse age
    token = strtok(NULL, ",");
    info->age = (uint8_t)atoi(token);

    // Parse phone
    token = strtok(NULL, ",");
    info->phone = (char *)malloc(strlen(token) + 1);
    strcpy(info->phone, token);

    // Parse address
    token = strtok(NULL, ",");
    info->address = (char *)malloc(strlen(token) + 1);
    strcpy(info->address, token);

    return info; // trả về thông tin của user hiện tại
}

Info *readfile(char *path)
{
    char line[100];
    FILE *file = fopen(path, "r"); //path :".//database//data.csv"
    if (file == NULL)
    {
        printf("đọc file thất bại\n");
        return NULL;
    }
    // đọc và không xử lý dòng tiêu đề
    fgets(line, sizeof(line), file);
    // cấp phát vùng nhớ động
    Info *line_info = (Info *)malloc(sizeof(Info));
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // tách ra thông tin và trả kết quả về kết quả tạm thời
        Info *temp_info = parse_line(line);
        // cập nhật số lượng user
        total_user += 1;
        // điều chỉnh tăng kích thước vùng nhớ mỗi khi cập nhật thông tin user mới
        line_info = (Info *)realloc(line_info, sizeof(Info) * total_user);
        // copy vào vùng nhớ đã cáp phát
        line_info[total_user - 1] = *temp_info;
        // Xóa vùng nhớ tạm mà không giải phóng vùng nhớ cấp phát cho các thành viên bên trong
        free(temp_info);
    }
    printf("Thông tin từ file csv đã được lưu thành công vào bộ nhớ\n");
    fclose(file);
    return line_info; // trả về kết quả cuối cùng sau khi đã đọc hết thông tin của tất cả useruser
}
```
#### - Hàm ghi file 

`fprintf()`: Ghi chuỗi vào File, và có thể thêm danh sách các đối số. 

`fputs()` : Ghi chuỗi vào File.

`fputc()` : Ghi một ký tự vào File.

`fwrite()` : Ghi một số byte được chỉ định vào File .bin.

- Triển khai ghi file trong chương trình:

```
bool writefile(char* path){
    FILE* file = fopen(path,"w"); //path : ".//database//data.csv"
    if(file == NULL){
        printf("mở file thất bại\n");
        return FAIL;
    }
    fprintf(file,"ten,tuoi,so dien thoai,dia chi\n");
    fprintf(file,"Pham Cao Duy,25,0972665872,91 Pham Van Hai P3 Q Tan Binh\n");
    fprintf(file,"Trinh Tran Phuong Tuan,24,0908234588,TP Tay Ninh \n");
    fprintf(file,"Trinh Le Hoang,28,0376572677,12 Nguyen Xien Q12\n");
    fprintf(file,"Nguyen Tan Tung,21,038764589,45 Tran Binh Trong\n");
    fprintf(file,"Le Quang Nhat,26,0978278121,17 Binh Phuoc\n");
    fprintf(file,"Nguyen Huu Hung,22,0978565342,17 Q Binh Thanh\n");
    fprintf(file,"Pham Cao Duy,18,090395678,220/8 Nguyen Phuc Nguuyen P9 Q3\n");
    fprintf(file,"Dinh Anh Tuan,24,0903478211,TP Tay Ninh\n");
    fprintf(file,"Nguyen Ho Duy,17,0906733209,22/5 Binh Thuan\n");
    fprintf(file,"Pham Cao Duy,20,0376572231,18 Nguyen Thi Minh Khai Q1 TPHCM\n");
    fprintf(file,"Nguyen Thi Thanh Thuy,27,038764987,21 Nguyen Thien Thuat P12 QTan Phu\n");
    fprintf(file,"Nguyen Ho Duy,27,038764912,22 Nguyen Thien Thuat P13 Q Tan Binh\n");
    fprintf(file,"Nguyen Thi Thanh Thu,27,038764997,23 Nguyen Thien Thuat P14  Q Binh Thanh\n");
    fprintf(file,"Pham Cao Duy,27,038764912,24 Nguyen Thien Thuat P9 Q 10\n");
    fclose(file);
    printf("ghi file thành công\n");
    return SUCCESS;
}
```