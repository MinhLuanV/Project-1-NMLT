#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "main.h"

extern int book_count;
extern int book_ISBN[];
extern char book_category[][100];
extern int book_quantity[];
extern char book_title[][100];
extern int reader_count;
extern int reader_code[];
extern char reader_gender[][10];
extern char reader_name[][100];
extern int slip_count;
extern int slip_reader_code[100];
extern char slip_expected_return_date[100][11];
extern char slip_actual_return_date[100][11]; 

// Hàm thống kê số lượng sách trong thư viện
void statistic_total_books() 
{
    int total_book = 0;
    printf("--- THỐNG KÊ SỐ LƯỢNG SÁCH TRONG THƯ VIỆN ---\n");
    for (int i = 0; i < book_count; i++) 
    {
        // Chỉ tính sách chưa bị xóa
        if (book_ISBN[i] != 0) 
        {
            total_book += book_quantity[i];
        }
    }
    printf("Tổng Số Lượng Sách Trong Thư Viện: %d\n", total_book);
}

// Hàm thống kê số lượng sách theo thể loại
void statistic_book_by_category()
{
    char categories[100][100]; // Lưu thể loại vào danh sách duy nhất
    int count[100] = { 0 };
    int unique_category_count = 0;
    int book_available_count;

    printf("--- THỐNG KÊ SỐ LƯỢNG SÁCH THEO THỂ LOẠI ---\n");

    for (int i = 0; i < book_count; i++)
    {
        // Chỉ thống kê sách hợp lệ (chưa bị xóa) và còn sách
        if (book_ISBN[i] != 0 && book_quantity[i] > 0)
        {
            book_available_count = book_quantity[i];
            int found = 0;

            // Kiểm tra thể loại có nằm trong danh sách duy nhất chưa
            for (int j = 0; j < unique_category_count; j++)
            {
                if (strcmp(book_category[i], categories[j]) == 0)
                {
                    // Nếu có thì cộng dồn lên
                    count[j] += book_available_count;
                    found = 1;
                    break;
                }
            }
            // Nếu thể loại mới, thêm vào danh sáh duy nhất
            if (!found && unique_category_count < 100) {
                strcpy(categories[unique_category_count], book_category[i]);
                count[unique_category_count] += book_available_count;
                unique_category_count++;
            }
        }
    }

    // Thống kê số lượng sách theo thể loại
    if (unique_category_count == 0)
    {
        printf("Thư viện chưa có sách hợp lệ hoặc sách đã hết.\n");
        return;
    }
    for (int i = 0; i < unique_category_count; i++)
    {
        printf("Thể loại: %s\n", categories[i]);
        printf("Số lượng: %d\n", count[i]);
        printf("==============================================\n");
    }
    printf("\n");
}

// Hàm thống kê số lượng độc giả
void statistic_total_readers() 
{
    int total_reader = 0;
    printf("--- THỐNG KÊ SỐ LƯỢNG ĐỘC GIẢ ---\n");
    for (int i = 0; i < reader_count; i++) 
    {
        if (reader_code[i] != 0) 
        {
            total_reader++;
        }
    }
    printf("Tổng Số Lượng Độc Giả: %d\n", total_reader);
}

// Hàm thống kê số lượng độc giả theo giới tính
void statistic_reader_by_gender()
{
    int male_count = 0;
    int female_count = 0;
    printf("--- THỐNG KÊ SỐ LƯỢNG ĐỘC GIẢ THEO GIỚI TÍNH ---\n");
    for (int i = 0; i < reader_count; i++)
    {
        if (strcmp(reader_gender[i], "Nam") == 0 || strcmp(reader_gender[i], "nam") == 0)
        {
            male_count++;
        }
        else
        {
            female_count++;
        }
    }
    printf("Tổng số lượng độc giả giới tính nam: %d\n", male_count);
    printf("Tổng số lượng độc giả giới tính nữ: %d\n", female_count);
}

// Hàm thống kê số sách đang được mượn
void statistic_books_on_loan() 
{
    int total_borrow_book = 0;
    printf("--- THỐNG KÊ SỐ SÁCH ĐANG ĐƯỢC MƯỢN ---\n");
    for (int i = 0; i < slip_count; i++) 
    {
        // Phiếu đang hoạt động nếu chuỗi ngày trả thực tế là rỗng
        if (slip_actual_return_date[i][0] == '\0') 
        {
            total_borrow_book++;
        }
    }
    printf("Tổng Số Sách Đang Được Mượn: %d\n", total_borrow_book);
}

// Hàm thống kê danh sách độc giả bị trễ hạn
void statistic_late_return_reader()
{
    char current_date[11];
    int late_count = 0;
    int day_late;
    int reader_index;
    printf("--- THỐNG KÊ DANH SÁCH ĐỘC GIẢ BỊ TRỄ HẠN ---\n");
    printf("Nhập ngày hiện tại: ");
    scanf_s(" %s", current_date,11);
    for (int i = 0; i < slip_count; i++)
    {
        day_late = calculate_date_difference(slip_expected_return_date[i], current_date);
        if (day_late > 0)
        {
            late_count++;
            reader_index = find_reader_index_by_code(&slip_reader_code[i]);
            if (reader_index != -1)
            {
                printf("Mã độc giả\t\t :%03d\n", reader_code[reader_index]);
                printf("Họ tên\t\t\t :%s\n", reader_name[reader_index]);
                printf("==============================================\n");
            }
            else
            {
                printf("Không tìm thấy độc giả.\n");
            }
        }
    }
    if (late_count == 0)
    {
        printf(" Không có độc giả nào bị trễ hạn.\n");
    }
    else
    {
        printf(" Tổng cộng %d độc giả bị trễ hạn \n", late_count);
    }
}
