#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "main.h"

extern int reader_count;
extern int reader_code[];
extern char reader_name[][100];
char reader_id[][13];									
char reader_birthday[][11];						
char reader_gender[][10];							
char reader_email[][100];							
char reader_address[][100];						
char reader_create_date_card[][11];			
char reader_expired_date_card[][11];
extern int slip_count;
extern int slip_reader_code[100];
extern int slip_borrow_ISBN[100];
extern char slip_actual_return_date[100][11];
extern int book_count; 
extern int book_ISBN[];
extern char book_title[][100];
extern char book_author[][100];
extern char book_pulisher[][100];
extern int book_year[];
extern char book_category[][100];
extern int book_price[];
extern int book_quantity[];

// Hàm tính ngày hết hạn của độc giả
void calculatate_expire_date_card(char reader_create_date_card[100], char reader_expired_date_card[100]) //Truyền vào mảng ngày lập thẻ và mảng ngày hết hạn của thẻ
{
	int day, month, year;
	int expire_year;

	// Chuyển định dạng ngày lập thẻ từ char sang int để thực hiện phép tính
	sscanf_s(reader_create_date_card, "%d/%d/%d", &day, &month, &year);
	if (strcmp(reader_create_date_card, "Đã Xóa") == 0)
	{
		strcpy(reader_expired_date_card, "Đã Xóa");
	}
	else
	{
		expire_year = year + 4;
		sprintf(reader_expired_date_card, "%02d/%02d/%04d", day, month, expire_year);
	}
	// Chuyển định dạng ngày hết hạn sau khi tính toán thành kiểu char và gán vào mảng ngày hết hạn
	//sprintf(reader_expired_date_card, "%02d/%02d/%04d", day, month, expire_year);
}

// Hàm xem danh sách độc giả trong thư viện
void show_list_reader()
{
	char temp_expire_date[11];

	if (reader_count == 0)
	{
		printf("Chưa có độc giả.\n");
		return;
	}
	printf("--- DANH SÁCH ĐỘC GIẢ ---\n");
	for (int i = 0; i < reader_count; i++)
	{
		if (reader_code[i] == 0)
		{
			continue; // Bỏ qua độc giả bằng 0 (hoặc đã bị xóa)
		}
		calculatate_expire_date_card(reader_create_date_card[i], temp_expire_date);
		printf("Mã độc giả\t\t: %03d\n", reader_code[i]);
		printf("Họ tên\t\t\t: %s\n", reader_name[i]);
		printf("CMND\t\t\t: %s\n", reader_id[i]);
		printf("Ngày sinh\t\t: %s\n", reader_birthday[i]);
		printf("Giới tính\t\t: %s\n", reader_gender[i]);
		printf("Email\t\t\t: %s\n", reader_email[i]);
		printf("Địa chỉ\t\t\t: %s\n", reader_address[i]);
		printf("Ngày lập thẻ\t\t: %s\n", reader_create_date_card[i]);
		printf("Ngày hết hạn\t\t: %s\n", temp_expire_date);
		printf("==============================================\n");
	}
}

//Hàm thêm độc giả
void add_reader()
{
	if (reader_count >= 100)
	{
		printf("Số lượng đã vượt mức, không thể thêm độc giả.\n");
		return;
	}
	int i = reader_count;
	printf("--- THÊM ĐỘC GIẢ---\n");

	// Mã độc giả tự động tăng
	reader_code[i] = i + 1;
	printf("Mã độc giả: %03d\n", reader_code[i]);

	// Nhập họ tên
	printf("Nhập họ tên: ");
	scanf_s(" %[^\n]s", reader_name[i], 100);

	// Nhập CMND
	printf("Nhập CMND: ");
	scanf_s(" %s", reader_id[i], 13);

	// Nhập ngày tháng năm sinh
	printf("Nhập ngày tháng năm sinh: ");
	scanf_s(" %s", reader_birthday[i], 11);

	// Nhập giới tính
	printf("Nhập giới tính: ");
	scanf_s(" %s", reader_gender[i], 10);

	// Nhập email
	printf("Nhập email: ");
	scanf_s(" %s", reader_email[i], 100);

	// Nhập địa chỉ
	printf("Nhập địa chỉ: ");
	scanf_s(" %[^\n]s", reader_address[i], 100);

	// Nhập ngày lập thẻ
	printf("Nhập ngày lập thẻ: ");
	scanf_s(" %s", reader_create_date_card[i], 11);

	// Ngày hết hạn 
	calculatate_expire_date_card(reader_create_date_card[i], reader_expired_date_card[i]);
	printf("Ngày hết hạn: %s\n", reader_expired_date_card[i]);

	reader_count++;
}

// Hàm tìm vị trí của độc giả theo mã độc giả
int find_reader_index_by_code(int reader_code[100])
{
	int index;		// Biến thể hiện vị trí tìm được
	for (int i = 0; i < reader_count; i++)
	{
		if (reader_code[i] != 0)
		{
			index = i;
			return index;
		}
	}
	printf("Không tìm thấy độc giả");
	return -1;
}

// Hàm chỉnh sửa thông tin một độc giả
void edit_reader_by_code()
{
	int code_to_edit;
	if (reader_count == 0)
	{
		printf("Chưa có độc giả nào trong thư viện");
		return;
	}
	printf("Nhập mã độc giả cần chỉnh sửa: ");
	scanf_s(" %03d", &code_to_edit);
	int index = find_reader_index_by_code(&code_to_edit);

	if (index == -1)
	{
		printf("Không tìm thấy độc giả\n");
	}

	// Hiện thông tin độc giả cần chỉnh sửa
	printf("Mã độc giả\t\t: %03d\n", reader_code[index]);
	printf("Họ tên\t\t\t: %s\n", reader_name[index]);
	printf("CMND\t\t\t: %s\n", reader_id[index]);
	printf("Ngày sinh\t\t: %s\n", reader_birthday[index]);
	printf("Giới tính\t\t: %s\n", reader_gender[index]);
	printf("Email\t\t\t: %s\n", reader_email[index]);
	printf("Địa chỉ\t\t\t: %s\n", reader_address[index]);
	printf("Ngày lập thẻ\t\t: %s\n", reader_create_date_card[index]);
	printf("Ngày hết hạn\t\t: %s\n", reader_expired_date_card[index]);

	// Chỉnh sửa thông tin độc giả đã tìm
	printf("---Nhập Lại Thông Tin Độc Giả---\n");
	printf("Mã độc giả: %03d\n", reader_code[index]);
	
	// Nhập lại họ tên
	printf("Nhập họ tên mới mới: ");
	scanf_s(" %[^\n]s", reader_name[index], 100);

	// Nhập lại CMND
	printf("Nhập CMND mới: ");
	scanf_s(" %s", reader_id[index], 13);

	// Nhập lại ngày tháng năm sinh
	printf("Nhập ngày tháng năm sinh mới: ");
	scanf_s(" %s", reader_birthday[index], 11);

	// Nhập lại giới tính
	printf("Nhập giới tính mới: ");
	scanf_s(" %s", reader_gender[index], 10);

	// Nhập lại email
	printf("Nhập email mới: ");
	scanf_s(" %s", reader_email[index], 100);

	// Nhập lại địa chỉ
	printf("Nhập địa chỉ mới: ");
	scanf_s(" %[^\n]s", reader_address[index], 100);

	// Nhập lại ngày lập thẻ
	printf("Nhập ngày lập thẻ mới: ");
	scanf_s(" %s", reader_create_date_card[index], 11);

	// Ngày hết hạn 
	calculatate_expire_date_card(reader_create_date_card[index], reader_expired_date_card[index]);
	printf("Ngày hết hạn: %s\n", reader_expired_date_card[index]);
}

// Hàm xóa thông tin độc giả
void delete_reader()
{
	int code_to_delete;
	if (reader_count == 0)
	{
		printf("Chưa có độc giả nào để xóa.\n");
		return;
	}

	printf("--- XÓA THÔNG TIN ĐỘC GIẢ ---\n");
	printf("Nhập mã độc giả cần xóa: ");
	scanf_s(" %03d", &code_to_delete);
	int index = find_reader_index_by_code(&code_to_delete);
	if (index == -1)
	{
		printf("Không tìm thấy độc giả.\n");
	}

	// Gán thông tin độc giả đã xóa
	strcpy(reader_name[index], "Đã Xóa");
	strcpy(reader_id[index], "Đã Xóa");
	strcpy(reader_birthday[index], "Đã Xóa");
	strcpy(reader_gender[index], "Đã Xóa");
	strcpy(reader_email[index], "Đã Xóa");
	strcpy(reader_address[index], "Đã Xóa");
	strcpy(reader_create_date_card[index], "Đã Xóa");
	strcpy(reader_expired_date_card[index],"Đã Xóa");

	printf("-- Đã Xóa Thành Công Độc Giả Mã %03d ---\n", code_to_delete);
}

// Hàm tìm kiếm độc giả theo CMND
void find_reader_by_id()
{
	char id_to_find[15];
	printf("--- TÌM KIẾM ĐỘC GIẢ THEO CMND ---\n");
	printf("Nhập CMND của độc giả cần tìm kiếm: ");
	scanf_s(" %s", id_to_find, 15);
	int found = 0; // Biến kiểm tra có tìm được không
	for (int i = 0; i < reader_count; i++)
	{
		if (reader_code[i] == 0)
		{
			continue;
		}
			if (strcmp(id_to_find, reader_id[i]) == 0)
			{
				printf("--- Thông Tin Độc Giả Tìm Được Theo CMND ---\n");
				printf("Mã độc giả\t\t: %03d\n", reader_code[i]);
				printf("Họ tên\t\t\t: %s\n", reader_name[i]);
				printf("CMND\t\t\t: %s\n", reader_id[i]);
				printf("Ngày sinh\t\t: %s\n", reader_birthday[i]);
				printf("Giới tính\t\t: %s\n", reader_gender[i]);
				printf("Email\t\t\t: %s\n", reader_email[i]);
				printf("Địa chỉ\t\t\t: %s\n", reader_address[i]);
				printf("Ngày lập thẻ\t\t: %s\n", reader_create_date_card[i]);
				printf("Ngày hết hạn\t\t: %s\n", reader_expired_date_card[i]);
				found = 1;
				break;
		}
	}
	if (found == 0)
	{
		printf("Không tìm thấy độc giả.\n");
	}
}

// Hàm tìm sách theo họ tên
void search_book_by_reader_name() 
{
	char search_term[100];
	char temp_reader_name[100];
	int found_reader_code[100];
	int found_reader_count = 0;
	int found_book_count = 0;

	if (reader_count == 0 || slip_count == 0) {
		printf("Chưa có độc giả hoặc phiếu mượn nào.\n");
		return;
	}

	printf("--- TÌM KIẾM SÁCH THEO HỌ TÊN ---\n");
	printf("Nhập tên độc giả cần tìm kiếm: ");
	scanf_s(" %[^\n]s", search_term, 100);

	// Chuyển đổi chuỗi tìm kiếm sang chữ thường
	for (int i = 0; i < strlen(search_term); i++) 
	{
		search_term[i] = tolower(search_term[i]);
	}

	// Tìm mã độc giả theo tên độc giả
	for (int i = 0; i < reader_count; i++) 
	{
		if (reader_code[i] == 0)
		{
			continue;
		}

		// Tạo bản sao và chuyển tên độc giả sang chữ thường để so sánh
		strcpy(temp_reader_name, reader_name[i]);
		for (int j = 0; j < strlen(temp_reader_name); j++) 
		{
			temp_reader_name[j] = tolower(temp_reader_name[j]);
		}

		// Nếu tên độc giả chứa từ khóa tìm kiếm
		if (strstr(temp_reader_name, search_term) != NULL) 
		{
			// Lưu Mã độc giả vào mảng tạm thời
			found_reader_code[found_reader_count] = reader_code[i];
			found_reader_count++;
		}
	}

	if (found_reader_count == 0) {
		printf("Không tìm thấy độc giả nào khớp với tên '%s'.\n", search_term);
		return;
	}

	printf("Sách Đang Mượn Bởi Độc Giả\n");

	// Tìm sách đang được mượn
	int is_match = 0;
	int current_slip_reader_code = 0;
	for (int i = 0; i < slip_count; i++)
	{
		current_slip_reader_code = slip_reader_code[i];

		// Kiểm tra xem mã độc giả trong phiếu có nằm trong danh sách tìm được không
		for (int j = 0; j < found_reader_count; j++)
		{
			if (current_slip_reader_code == found_reader_code[j])
			{
				is_match = 1;
				break;
			}
		}

	// Thỏa điều kiện mã độc giả khớp với sách chưa được trả
		if (is_match && slip_actual_return_date[i][0] == '\0')
		{
			int book_isbn = slip_borrow_ISBN[i];
			int book_index = find_book_index_by_ISBN(&book_isbn);

			if (book_index != -1)
			{
				found_book_count++;

				// Hiển thị thông tin sách 
				printf("\n[%d] Sách đang được mượn:\n", found_book_count);
				printf("%-20s: %03d\n", "Mã Độc giả:", current_slip_reader_code);
				printf("%-20s: %s\n", "Tên Độc giả:", reader_name[find_reader_index_by_code(&current_slip_reader_code)]);
				printf("%-20s: %03d\n", "ISBN Sách:", book_isbn);
				printf("%-20s: %s\n", "Tên sách:", book_title[book_index]);
				printf("%-20s: %s\n", "Tác giả:", book_author[book_index]);
				printf("%-22s: %s\n", "Nhà xuất bản:", book_pulisher[book_index]);
				printf("%-22s: %d\n", "Năm xuất bản:", book_year[book_index]);
				printf("%-22s: %s\n", "Thể loại:", book_category[book_index]);
				printf("%-22s: %d\n", "Giá sách:", book_price[book_index]);
				printf("%-22s: %d\n", "Số lượng sách:", book_quantity[book_index]);
			}
		}
	}

		if (found_book_count == 0) 
	{
		printf("Không có sách nào đang được mượn bởi các độc giả này.\n");
	}
	else 
	{
		printf("Tìm Thấy  %d Sách Đang Được Mượn.\n", found_book_count);
	}
}