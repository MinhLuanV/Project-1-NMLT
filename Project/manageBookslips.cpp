#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "main.h"

extern int book_borrow_count;
extern int reader_count;
extern int book_count;
extern int slip_count;
extern int reader_code[];
extern char reader_name[][100];
extern char reader_expired_date_card[][11];
extern int book_ISBN[];
extern int book_quantity[];
extern char book_title[][100];
extern int slip_reader_code[];							
extern char slip_borrow_date[][11];
extern char slip_expected_return_date[][11];
extern int slip_borrow_ISBN[];
extern char slip_actual_return_date[][11];

// Hàm tính ngày trả sách dự kiến
void calculate_expect_return_date(char slip_borrow_date[], char slip_expected_return_date[])
{
	int day, month, year;
	// Chuyển định dạng ngày mượn sách từ char sang int để thực hiện phép tính
	sscanf_s(slip_borrow_date, "%d/%d/%d", &day, &month, &year);
	int add_day, next_month, next_year;
	int DayInMonth;
	switch (month)
	{
	case 1: case 3: case 5:case 7:case 8: case 10: case 12:
		DayInMonth = 31;
		break;
	case 4: case 6: case 9: case 11:
		DayInMonth = 30;
		break;
	case 2:
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			DayInMonth = 29;
		}
		else
		{
			DayInMonth = 28;
		}
		break;
	}
	add_day = day + 7;
	next_month = month;
	next_year = year;

	if (add_day > DayInMonth)
	{
		add_day = add_day - DayInMonth;
		next_month = month + 1;

		if (next_month > 12)
		{
			next_month = 1;
			next_year = year + 1;
		}
	}
		// Chuyển định dạng ngày hết hạn sau khi tính toán thành kiểu char và gán vào mảng ngày hết hạn
		sprintf(slip_expected_return_date, "%02d/%02d/%04d", add_day, next_month, next_year);
}

// Hàm lập phiếu mượn sách
void create_borrow_slip()
{
	int input_reader_code;
	int reader_index;
	char borrow_date[11];
	char expected_return_date[11];
	char choice_continue;
	int current_slip_index;

	// Kiểm tra điều kiện phiếu mượn
	if (reader_count == 0 || book_count == 0)
	{
		printf("Thư viện chưa có độc giả hoặc sách.\n");
		return;
	}

	if (slip_count >= 100)
	{
		printf("Đã đủ số lượng phiếu mượn.\n");
	}

	printf("--- LẬP PHIẾU MƯỢN SÁCH ---\n");

	// Nhập và xác nhận độc giả
	printf("Nhập mã độc giả để lập phiếu: ");
	scanf_s(" %d", &input_reader_code);

	reader_index = find_reader_index_by_code(&input_reader_code);

	if (reader_index == -1 || reader_code[reader_index] == 0) 
	{
		printf("Không tìm thấy độc giả hoặc độc giả đã bị xóa.\n");
		return;
	}
	printf("Độc giả hợp lệ: %s\n", reader_name[reader_index]);

	// Nhập ngày mượn
	printf("Nhập Ngày Mượn: ");
	scanf_s(" %s", borrow_date, 11);

	// Tính ngày trả dự kiến 
	calculate_expect_return_date(borrow_date, expected_return_date);
	printf("Ngày trả dự kiến: %s\n", expected_return_date);

	current_slip_index = slip_count;
	slip_reader_code[current_slip_index] = input_reader_code;
	strcpy(slip_borrow_date[current_slip_index], borrow_date);
	strcpy(slip_expected_return_date[current_slip_index], expected_return_date);
	slip_count++;

	// Mượn sách
	printf("--- DANH SÁCH SÁCH MƯỢN ---\n");

	do {
		int input_isbn;
		int book_index;

		printf("\nNhập ISBN của sách muốn mượn: ");
		scanf_s(" %d", &input_isbn);

		book_index = find_book_index_by_ISBN(&input_isbn);

		if (book_index == -1 || book_ISBN[book_index] == 0) {
			printf("Không tìm thấy sách với ISBN này.\n");
		}
		else if (book_quantity[book_index] <= 0) {
			printf("Sách '%s' đã hết, không thể mượn.\n", book_title[book_index]);
		}
		else {

			book_quantity[book_index]--;
			
			printf("Đã mượn sách ISBN %03d. Số lượng sách còn lại: %d\n", input_isbn, book_quantity[book_index]);
		}

		// Thêm sách mượn
		printf("Bạn có muốn mượn thêm sách không? (y/n): ");
		scanf_s(" %c", &choice_continue, 1);

	} while (choice_continue == 'y' || choice_continue == 'Y');

	printf("Đã Lập Phiếu Mượn Sách Thành Công.\n");
}

// Hàm tính tổng số ngày tính từ 01/01/0000 đến ngày thực tế
int is_leap(int year) // Hàm kiểm tra năm nhuận
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Tính tổng số ngày thực tế
long date_to_absolute_days(int d, int m, int y) // Truyền tham số ngày, tháng, năm
{
	long days = 0;

	// Số ngày trong các tháng (bắt đầu từ tháng 1)
	int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Tổng số ngày theo năm
	for (int i = 1; i < y; i++) 
	{
		days += 365;
		if (is_leap(i)) {
			days++; // Cộng thêm 1 ngày cho năm nhuận
		}
	}

	// Tổng số ngày theo tháng
	for (int i = 1; i < m; i++) 
	{
		days += month_days[i];
	}

	// Xử lý năm nhuận cho tháng 2 trong năm hiện tại (nếu đã qua tháng 2)
	if (m > 2 && is_leap(y)) 
	{
		days++;
	}
	days += d;
	return days;
}

// Hàm tính tổng số ngày chênh lệch
int calculate_date_difference(char expected_date[], char actual_date[]) {
	int d1, m1, y1; // Ngày dự kiến
	int d2, m2, y2; // Ngày thực tế

	// Phân tích cú pháp ngày dự kiến
	if (sscanf_s(expected_date, "%d/%d/%d", &d1, &m1, &y1, 11) != 3) 
	{
		return 0;
	}

	// Phân tích cú pháp ngày thực tế
	if (sscanf_s(actual_date, "%d/%d/%d", &d2, &m2, &y2, 11) != 3) 
	{
		return 0;
	}

	// Chuyển đổi cả hai ngày sang số ngày tuyệt đối
	long expected_days = date_to_absolute_days(d1, m1, y1);
	long actual_days = date_to_absolute_days(d2, m2, y2);

	// Tính số ngày chênh lệch 
	long difference = actual_days - expected_days;

	// Tính số ngày trễ 
	if (difference > 0) 
	{
		return (int)difference;
	}
	else {
		return 0;
	}
}

 // Hàm lập phiếu trả sách
void create_return_slip() {
	int input_reader_code;
	int input_isbn;
	int slip_index = -1;
	int book_index = -1;
	char actual_return_date[11];
	int days_late = 0;
	long fine = 0; // Tiền phạt

	if (slip_count == 0) {
		printf("Chưa có phiếu mượn nào để trả.\n");
		return;
	}

	printf("--- LẬP PHIẾU TRẢ SÁCH ---\n");

	// Nhập thông tin để tìm kiếm phiếu mượn đang hoạt động
	printf("Nhập Mã độc giả: ");
	scanf_s(" %d", &input_reader_code);
	printf("Nhập ISBN của sách cần trả: ");
	scanf_s(" %d", &input_isbn);

	// Tìm kiếm phiếu mượn đang hoạt động (chưa trả)
	slip_index = -1; 

	for (int i = 0; i < slip_count; i++) {
		// Tìm phiếu khớp Mã ĐG, khớp ISBN, và CHƯA có ngày trả thực tế (đã trả)
		if (slip_reader_code[i] == input_reader_code && 
			slip_borrow_ISBN[i] == input_isbn && 
			slip_actual_return_date[i][0] == '\0') // Kiểm tra chuỗi rỗng
		{
			slip_index = i;
			break;
		}
	}

	if (slip_index == -1) {
		printf("Không tìm thấy phiếu mượn sách.\n");
		return;
	}

	// Nhập Ngày Trả Thực Tế
	printf("Nhập Ngày Trả Thực Tế: ");
	scanf_s(" %s", actual_return_date, 11);

	// Tìm kiếm sách để cập nhật số lượng
	book_index = find_book_index_by_ISBN(&input_isbn);

	if (book_index == -1 || book_ISBN[book_index] == 0) {
		printf("Không tìm thấy thông tin sách trong thư viện, không thể tăng số lượng.\n");
	}
	else {
		book_quantity[book_index]++;
		printf("Đã tăng số lượng sách ISBN %03d lên 1.\n", input_isbn);
	}

	// Cập nhật Ngày Trả Thực Tế vào phiếu mượn
	strcpy(slip_actual_return_date[slip_index], actual_return_date);

	// Tính toán tiền phạt
	// Cần hàm calculate_date_difference(ngày dự kiến, ngày thực tế)
	days_late = calculate_date_difference(slip_expected_return_date[slip_index], actual_return_date);

	if (days_late > 0) {
		fine = days_late * 5000;
		printf("--- Đóng Phạt Quá Hạn---\n");
		printf("Ngày trả dự kiến: %s\n", slip_expected_return_date[slip_index]);
		printf("Trễ %d ngày. Tiền phạt: %ld VND\n", days_late, fine);
	}
	else {
		printf("Trả sách đúng hạn.\n");
	}

	printf("Đã Lập Phiếu Trả Sách Thành Công.\n");
}