#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>
#include "main.h"

// Khởi tạo các hằng số tối đa cho độc giả, sách, phiếu mượn/ trả sách
#define Max_Readers 100		// Số lượng tối đa độc giả
#define Max_Books 100			// Số lượng tối đa sách
#define Max_Bookslips 100	// Số lượng tối đa phiếu mượn/ trả sách

// Khởi tạo biến toàn cục cho độc giả (Reader)
int reader_code[Max_Readers];										// Mã độc giả
char reader_name[Max_Readers][100];							// Họ và tên độc giả
char reader_id[Max_Readers][13];									// CMND độc giả
char reader_birthday[Max_Readers][11];						// Ngày tháng năm sinh của độc giả
char reader_gender[Max_Readers][10];							// Giới tính độc giả
char reader_email[Max_Readers][100];							// Email độc giả
char reader_address[Max_Readers][100];						// Địa chỉ độc giả
char reader_create_date_card[Max_Readers][11];			// Ngày lập thẻ của độc giả
char reader_expired_date_card[Max_Readers][11];		// Ngày hết hạn thẻ của độc giả

// Khởi tạo biến toàn cục cho sách (Book)
int book_ISBN[Max_Books];											// Mã sách
char book_title[Max_Books][100];								// Tên sách
char book_author[Max_Books][100];							// Tác giả
char book_pulisher[Max_Books][100];							// Nhà xuất bản
int book_year[Max_Books];											// Năm xuất bản
char book_category[Max_Books][100];							// Thể loại
int book_price[Max_Books];											// Giá sách
int book_quantity[Max_Books];										// Số lượng sách

// Khởi tạo biến toàn cục cho phiếu mượn/ trả sách (Bookslip)
int slip_reader_code[Max_Bookslips];							// Mã độc giả mượn sách
char slip_borrow_date[Max_Bookslips][11];					// Ngày mượn sách
char slip_expected_return_date[Max_Bookslips][11];	// Ngày trả sách dự kiến
int slip_borrow_ISBN[Max_Bookslips];						// ISBN mượn trong phiếu
char slip_actual_return_date[Max_Bookslips][11];		// Ngày trả thực tế

// Khởi tạo tổng số lượng độc giả, sách
int reader_count = 0;				// Tổng số lượng độc giả
int book_count = 0;					// Tổng số lượng sách
int book_borrow_count = 0;	// Tổng số lượng  sách được mượn
int slip_count = 0;					// Tổng số lượng phiếu mượn

// Hàm xóa màn hình 
void clear_screen() 
{
#ifdef _WIN32
    system("cls");
#endif
}
// Hàm Menu chức năng chính
void display_menu()
{
    char input;
    system("cls");
    printf("CHƯƠNG TRÌNH QUẢN LÍ THƯ VIỆN \n");
    printf("1. Quản Lí Độc Giả.\n");
    printf("2. Quản Lí Sách.\n");
    printf("3. Lập Phiếu Mượn Sách.\n");
    printf("4. Lập Phiếu Trả Sách.\n");
    printf("5. Các Thống Kê Cơ Bản.\n");
    printf("0. Thoát Khỏi Chương Trình.\n");
    printf("Nhập Lựa Chọn Của Bạn: ");
}

// Hàm Menu chức năng quản lí độc giả
void reader_management()
{
    char input;
    do
    {
        system("cls");
        printf("QUẢN LÍ ĐỘC GIẢ \n");
        printf("a. Xem Danh Sách Độc Giả Trong Thư Viện.\n");
        printf("b. Thêm Độc Giả.\n");
        printf("c. Chỉnh Sửa Thông Tin Một Độc Giả.\n");
        printf("d. Xóa Thông Tin Một Độc Giả.\n");
        printf("e. Tìm Kiếm Độc Giả Theo CMND.\n");
        printf("f. Tìm Kiếm Sách Theo Họ Tên.\n");
        printf("0. Quay về Menu Chính.\n");
        printf("Nhập Lựa Chọn Của Bạn: ");

        if (scanf_s(" %c", &input, 1) != 1)
        {
            printf("Đầu vào không hợp lệ. Quay lại Menu chính.\n");
            // Xóa bộ đệm bàn phím sau khi nhập lỗi
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');
        system("cls");
        switch (tolower(input))
        {
        case 'a':
            show_list_reader();
            system("pause");
            break;
        case 'b':
            add_reader();
            system("pause");
            break;
        case 'c':
            edit_reader_by_code();
            system("pause");
            break;
        case 'd':
            delete_reader();
            system("pause");
            break;
        case 'e':
            find_reader_by_id();
            system("pause");
            break;
        case 'f':
            search_book_by_reader_name();
            system("pause");
            break;
        case '0':
            break;
        }
        if (input != '0')
        {
            printf("\n\n(Nhấn Enter để tiếp tục...)\n\n");
            getchar();
        }
    }
    while (input != '0');
}

// Hàm Menu chức năng quản lí sách
void book_management()
{
    char input;
    do
    {
        system("cls");
        printf("QUẢN LÍ SÁCH \n");
        printf("a. Xem Danh Sách Các Sách Trong Thư Viện.\n");
        printf("b. Thêm Sách.\n");
        printf("c. Chỉnh Sửa Thông Tin Một Quyển Sách.\n");
        printf("d. Xóa Thông Tin Sách.\n");
        printf("e. Tìm Kiếm Sách Theo ISBN.\n");
        printf("f. Tìm Kiếm Sách Theo Tên Sách.\n");
        printf("0. Quay Về Menu Chính.\n");
        printf("Nhập Lựa Chọn Của Bạn: ");

        if (scanf_s(" %c", &input, 1) != 1) {
            printf("Đầu vào không hợp lệ. Quay lại Menu chính.\n");
            // Xóa bộ đệm bàn phím sau khi nhập lỗi
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');
        system("cls");
        switch (tolower(input))
        {
        case 'a':
            show_list_book();
            system("pause");
            break;
        case 'b':
            add_book();
            system("pause");
            break;
        case 'c':
            edit_book_by_ISBN();
            system("pause");
            break;
        case 'd':
            delete_book();
            system("pause");
            break;
        case 'e':
            find_book_by_ISBN();
            system("pause");
            break;
        case 'f':
            find_book_by_title();
            system("pause");
            break;
        case '0':
            break;
        }
        if (input != '0')
        {
            printf("\n\n(Nhấn Enter để tiếp tục...)\n\n");
            getchar();
        }
    } 
    while (input != '0');
}

// Hàm Menu chức năng các thống kê cơ bản
void basic_statistic()
{
    char input;
    do
    {
        system("cls");
        printf("CÁC THỐNG KÊ CƠ BẢN \n");
        printf("a. Thống Kê Số Lượng Sách Trong Thư Viện.\n");
        printf("b. Thống Kê Số Lượng Sách Theo Thể Loại.\n");
        printf("c. Thống Kê Số Lượng Độc Giả.\n");
        printf("d. Thống Kê Số Lượng Độc Giả theo Giới Tính.\n");
        printf("e. Thống Kê Số Sách Đang Được Mượn.\n");
        printf("f. Thống Kê Danh Sách Độc Giả Bị Trễ Hạn.\n");
        printf("0. Quay Về Menu Chính.\n");
        printf("Nhập Lựa Chọn Của Bạn: ");

        if (scanf_s(" %c", &input, 1) != 1) {
            printf("Đầu vào không hợp lệ. Quay lại Menu chính.\n");
            // Xóa bộ đệm bàn phím sau khi nhập lỗi
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');
        system("cls");
        switch (tolower(input))
        {
        case 'a':
            statistic_total_books();
            system("pause");
            break;
        case 'b':
            statistic_book_by_category();
            system("pause");
            break;
        case 'c':
            statistic_total_readers();
            system("pause");
            break;
        case 'd':
            statistic_reader_by_gender();
            system("pause");
            break;
        case 'e':
            statistic_books_on_loan();
            system("pause");
            break;
        case 'f':
            statistic_late_return_reader();
            system("pause");
            break;
        case '0':

            break;
        }
    } 
    while (input != '0');
}

// Hàm thực hiện chức năng chương trình
void main()
{
    system("chcp 65001 >nul");
    int choice;
    do
    {
        display_menu();
        if (scanf_s("%d", &choice) != 1)
        {
            printf("Đầu vào không phải là số. Vui lòng nhập lại.\n");
            // Xóa bộ đệm bàn phím để tránh vòng lặp vô hạn
            while (getchar() != '\n');
            choice = -1; // Đặt giá trị không hợp lệ
            continue;
        }
        while (getchar() != '\n');
        switch (choice)
        {
        case 1:
            system("cls");
            reader_management();
            break;
        case 2:
            system("cls");
            book_management();
            break;
        case 3:
            system("cls");
            create_borrow_slip();
            system("pause");
            break;
        case 4:
            system("cls");
            create_return_slip();
            system("pause");
            break;
        case 5:
            system("cls");
            basic_statistic();
            break;
        case 0:
            printf("\nĐã thoát chương trình. Tạm biệt!\n");
            break;
        }
        if (choice != 0)
            continue;
    }
    while (choice != 0);
}
