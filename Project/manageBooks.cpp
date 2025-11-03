#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int book_count;
extern int book_ISBN[];											
extern char book_title[][100];								
extern char book_author[][100];							
extern char book_pulisher[][100];							
extern int book_year[];											
extern char book_category[][100];							
extern int book_price[];											
extern int book_quantity[];

// Hàm xem danh sách các sách trong thư viện
void show_list_book()
{
	if (book_count == 0)
	{
		printf("Chưa có sách trong thư viện.\n");
		return;
	}
	printf("--- DANH SÁCH CÁC SÁCH TRONG THƯ VIỆN ---\n");
	for (int i = 0; i < book_count; i++)
	{
		printf("ISBN\t\t\t: %03d\n", book_ISBN[i]);
		printf("Tên sách\t\t: %s\n", book_title[i]);
		printf("Tác giả\t\t\t: %s\n", book_author[i]);
		printf("Nhà xuất bản\t\t: %s\n", book_pulisher[i]);
		printf("Năm xuất bản\t\t: %04d\n", book_year[i]);
		printf("Thể loại\t\t: %s\n", book_category[i]);
		printf("Giá sách\t\t: %d\n", book_price[i]);
		printf("Số quyển sách\t\t: %d\n", book_quantity[i]);
	}
}

// Hàm thêm sách.
void add_book()
{
	if (book_count >= 100)
	{
		printf("Số lượng đã vượt mức, không thể thêm sách.\n");
		return;
	}
	int i = book_count;
	printf("--- THÊM SÁCH ---\n");
	// Mã sách (ISBN) tự động tăng
	book_ISBN[i] = i + 1;
	printf("ISBN (mã sách): %03d\n", book_ISBN[i]);

	// Nhập tên sách
	printf("Nhập tên sách: ");
	scanf_s(" %[^\n]s", book_title[i], 100);

	//Nhập tác giả
	printf("Nhập tác giả: ");
	scanf_s(" %[^\n]s", book_author[i], 100);

	// Nhập nhà xuất bản
	printf("Nhập nhà xuất bản: ");
	scanf_s(" %[^\n]s", book_pulisher[i], 100);

	// Nhập năm xuất bản
	printf("Nhập năm xuất bản: ");
	scanf_s(" %d", &book_year[i]);
	
	// Nhập thể loại
	printf("Nhập thể loại: ");
	scanf_s(" %[^\n]s", book_category[i], 100);

	// Nhập giá sách
	printf("Nhập giá sách (đơn vị VND): ");
	scanf_s("%d", &book_price[i]);

	// Nhập số quyển sách
	printf("Nhập số quyển sách: ");
	scanf_s("%d", &book_quantity[i]);

	book_count++;
}

// Hàm tìm kiếm vị trí sách theo ISBN
int find_book_index_by_ISBN(int book_ISBN[100])
{
	int index;		// Biến thể hiện vị trí tìm được
	for (int i = 0; i < book_count; i++)
	{
		if (book_ISBN[i] != 0 )
		{
			index = i;
			return index;
		}
	}
	printf("Không tìm thấy sách");
	return -1;
}

// Hàm chỉnh sửa thông tin một quyển sách
void edit_book_by_ISBN()
{
	int ISBN_to_edit;
	if (book_count == 0)
	{
		printf("Chưa có sách nào trong thư viện");
		return;
	}
	printf("Nhập mã sách cần chỉnh sửa: ");
	scanf_s(" %03d", &ISBN_to_edit);
	int index = find_book_index_by_ISBN(&ISBN_to_edit);

	if (index == -1)
	{
		printf("Không tìm thấy sách.\n");
	}

	// Hiện thông tin sách cần chỉnh sửa
	printf("ISBN\t\t\t: %03d\n", book_ISBN[index]);
	printf("Tên sách\t\t: %s\n", book_title[index]);
	printf("Tác giả\t\t\t: %s\n", book_author[index]);
	printf("Nhà xuất bản\t\t: %s\n", book_pulisher[index]);
	printf("Năm xuất bản\t\t: %04d\n", book_year[index]);
	printf("Thể loại\t\t: %s\n", book_category[index]);
	printf("Giá sách\t\t: %d\n", book_price[index]);
	printf("Số quyển sách\t\t: %d\n", book_quantity[index]);

	// Chỉnh sửa thông tin sách đã tìm
	printf("---Nhập Lại Thông Tin Sách---\n");
	printf("Mã sách: %03d\n", book_ISBN[index]);

	// Nhập lại tên sách
	printf("Nhập tên sách mới: ");
	scanf_s(" %[^\n]s", book_title[index], 100);

	// Nhập lại tác giả
	printf("Nhập tác giả mới: ");
	scanf_s(" %[^\n]s", book_author[index], 100);

	// Nhập lại nhà xuất bản
	printf("Nhập nhà xuất bản mới: ");
	scanf_s(" %[^\n]s", book_pulisher[index], 100);

	// Nhập lại năm xuất bản
	printf("Nhập năm xuất bản mới: ");
	scanf_s(" %d", &book_year[index]);

	// Nhập lại thể loại sách
	printf("Nhập thể loại sách mới: ");
	scanf_s(" %[^\n]s", book_category[index], 100);

	// Nhập lại giá sách
	printf("Nhập giá sách mới: ");
	scanf_s(" %d", &book_price[index]);

	// Nhập lại số lượng sách
	printf("Nhập số lượng sách mới: ");
	scanf_s(" %d", &book_quantity[index]);
}

// Hàm xóa thông tin sách
void delete_book()
{
	int ISBN_to_delete;
	if (book_count == 0)
	{
		printf("Chưa có sách nào để xóa.\n");
		return;
	}

	printf("--- XÓA THÔNG TIN SÁCH ---\n");
	printf("Nhập mã sách cần xóa: ");
	scanf_s(" %03d", &ISBN_to_delete);
	int index = find_book_index_by_ISBN(&ISBN_to_delete);
	if (index == -1)
	{
		printf("Không tìm thấy sách.\n");
	}

	// Gán tình trạng sách đã xóa
	strcpy(book_title[index], "Đã Xóa");
	strcpy(book_author[index], "Đã Xóa");
	strcpy(book_pulisher[index], "Đã Xóa");
	book_year[index] = 0;
	strcpy(book_category[index], "Đã Xóa");
	book_price[index] = 0;
	book_quantity[index] = 0;

	printf("-- Đã Xóa Thành Công Sách Mã %03d ---\n", ISBN_to_delete);
}

// Hàm tìm kiếm sách theo ISBN
void find_book_by_ISBN()
{
	int ISBN_to_find;
	printf("Nhập ISBN của sách cần tìm kiếm: ");
	scanf_s(" %d", &ISBN_to_find);
	int found = 0; // Biến kiểm tra có tìm được không
	for (int i = 0; i < book_count; i++)
	{
		if (book_ISBN[i] == 0)
		{
			continue;
		}
		if (ISBN_to_find == book_ISBN[i])
		{
			printf("ISBN\t\t\t: %03d\n", book_ISBN[i]);
			printf("Tên sách\t\t: %s\n", book_title[i]);
			printf("Tác giả\t\t\t: %s\n", book_author[i]);
			printf("Nhà xuất bản\t\t: %s\n", book_pulisher[i]);
			printf("Năm xuất bản\t\t: %04d\n", book_year[i]);
			printf("Thể loại\t\t: %s\n", book_category[i]);
			printf("Giá sách\t\t: %d\n", book_price[i]);
			printf("Số quyển sách\t\t: %d\n", book_quantity[i]);
			found = 1;
			break;
		}
	}
	if (found == 0)
	{
		printf("Không tìm thấy sách.\n");
	}
}

// Hàm tìm sách theo tên sách
void find_book_by_title()
{
	char title_to_find[101];
	printf("Nhập tên sách cần tìm kiếm: ");
	scanf_s(" %[^\n]s", title_to_find, 101);
	int found = 0; // Biến kiểm tra có tìm được không
	for (int i = 0; i < book_count; i++)
	{
		if (book_ISBN[i] == 0)
		{
			continue;
		}
		if (strcmp(title_to_find, book_title[i]) == 0)
		{
			printf(" ---Thông Tin Sách Tìm Được---\n");
			printf("ISBN\t\t\t: %03d\n", book_ISBN[i]);
			printf("Tên sách\t\t: %s\n", book_title[i]);
			printf("Tác giả\t\t\t: %s\n", book_author[i]);
			printf("Nhà xuất bản\t\t: %s\n", book_pulisher[i]);
			printf("Năm xuất bản\t\t: %04d\n", book_year[i]);
			printf("Thể loại\t\t: %s\n", book_category[i]);
			printf("Giá sách\t\t: %d\n", book_price[i]);
			printf("Số quyển sách\t\t: %d\n", book_quantity[i]);
			found = 1;
			break;
		}
	}
	if (found == 0)
	{
		printf("Không tìm thấy sách.\n");
	}
}