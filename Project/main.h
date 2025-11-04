// Hàm tính ngày hết hạn của độc giả
void calculatate_expire_date_card(char create_date[100], char expire_date[100]);

// Hàm xem danh sách độc giả trong thư viện
void show_list_reader();

// Hàm thêm độc giả
void add_reader();

// Hàm tìm vị trí của độc giả theo mã độc giả
int find_reader_index_by_code(int input_code);

// Hàm chỉnh sửa thông tin một độc giả
void edit_reader_by_code();

// Hàm xóa thông tin độc giả
void delete_reader();

// Hàm tìm kiếm độc giả theo CMND
void find_reader_by_id();

// Hàm tìm sách theo họ tên
void search_book_by_reader_name();

// Hàm xem danh sách các sách trong thư viện
void show_list_book();

// Hàm thêm sách
void add_book();

//Hàm tìm kiếm vị trí sách theo ISBN
int find_book_index_by_ISBN(int input_isbn);

// Hàm chỉnh sửa thông tin một quyển sách
void edit_book_by_ISBN();

// Hàm xóa thông tin sách
void delete_book();

// Hàm tìm kiếm sách theo ISBN
void find_book_by_ISBN();

// Hàm tìm sách theo tên sách
void find_book_by_title();


// Hàm tính ngày trả sách dự kiến
void calculate_expect_return_date(char slip_borrow_date[], char slip_expected_return_date[]);


// Hàm lập phiếu mượn sách
void create_borrow_slip();

// Hàm kiểm tra năm nhuận
int is_leap(int year);

// Tính tổng số ngày thực tế
long date_to_absolute_days(int d, int m, int y);

// Hàm tính tổng số ngày chênh lệch
int calculate_date_difference(char expected_date[], char actual_date[]);

// Hàm lập phiếu trả sách
void create_return_slip();

// Hàm thống kê số lượng sách trong thư viện
void statistic_total_books();

// Hàm thống kê số lượng sách theo thể loại
void statistic_book_by_category();

// Hàm thống kê số lượng độc giả
void statistic_total_readers();

// Hàm thống kê số lượng độc giả theo giới tính
void statistic_reader_by_gender();

// Hàm thống kê số sách đang được mượn
void statistic_books_on_loan();

// Hàm thống kê danh sách độc giả bị trễ hạn
void statistic_late_return_reader();