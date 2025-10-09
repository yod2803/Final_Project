#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

#define MAX 256

extern int utf8_strlen(const char *s);
extern void trim_spaces(char *s);
extern int validate_and_normalize_date(const char *in, char *buff, size_t buffsz);
extern int is_leap_year(int y);
extern int max_days_in_month(int y, int m);
extern int utf8_icontains(const char *hay, const char *needle);
extern int has_comma(const char *s);

void test_utf8_strlen(void) {
    printf("Testing utf8_strlen...\n");
    assert(utf8_strlen("") == 0);
    assert(utf8_strlen("abc") == 3);
    assert(utf8_strlen("สวัสดี") == 6);
    assert(utf8_strlen("Hello สวัสดี") == 12);
    printf("✅ utf8_strlen: PASSED\n");
}

void test_trim_spaces(void) {
    printf("Testing trim_spaces...\n");
    char str1[MAX] = "  hello  ";
    trim_spaces(str1);
    assert(strcmp(str1, "hello") == 0);
    
    char str2[MAX] = "test";
    trim_spaces(str2);
    assert(strcmp(str2, "test") == 0);
    
    char str3[MAX] = "  สมชาย  ";
    trim_spaces(str3);
    assert(strcmp(str3, "สมชาย") == 0);
    
    char str4[MAX] = "   ";
    trim_spaces(str4);
    assert(strcmp(str4, "") == 0);
    printf("✅ trim_spaces: PASSED\n");
}

void test_validate_date(void) {
    printf("Testing validate_and_normalize_date...\n");
    char buff[MAX];
    
    assert(validate_and_normalize_date("2025-10-09", buff, sizeof(buff)) == 1);
    assert(strcmp(buff, "2025-10-09") == 0);
    
    assert(validate_and_normalize_date("2025-13-01", buff, sizeof(buff)) == 0);
    assert(validate_and_normalize_date("2025-02-30", buff, sizeof(buff)) == 0);
    assert(validate_and_normalize_date("2024-02-29", buff, sizeof(buff)) == 1);
    assert(validate_and_normalize_date("2025-02-29", buff, sizeof(buff)) == 0);
    
    assert(validate_and_normalize_date("2025-1-9", buff, sizeof(buff)) == 1);
    assert(strcmp(buff, "2025-01-09") == 0);
    printf("✅ validate_and_normalize_date: PASSED\n");
}

void test_is_leap_year(void) {
    printf("Testing is_leap_year...\n");
    assert(is_leap_year(2000) == 1);
    assert(is_leap_year(2024) == 1);
    assert(is_leap_year(2025) == 0);
    assert(is_leap_year(1900) == 0);
    assert(is_leap_year(2400) == 1);
    printf("✅ is_leap_year: PASSED\n");
}

void test_max_days_in_month(void) {
    printf("Testing max_days_in_month...\n");
    assert(max_days_in_month(2025, 1) == 31);
    assert(max_days_in_month(2025, 2) == 28);
    assert(max_days_in_month(2024, 2) == 29);
    assert(max_days_in_month(2025, 4) == 30);
    assert(max_days_in_month(2025, 12) == 31);
    printf("✅ max_days_in_month: PASSED\n");
}

void test_utf8_icontains(void) {
    printf("Testing utf8_icontains...\n");
    assert(utf8_icontains("สมชาย ใจดี", "สมชาย") == 1);
    assert(utf8_icontains("Hello World", "world") == 1);
    assert(utf8_icontains("Hello World", "xyz") == 0);
    assert(utf8_icontains("12 ถนนสุขสันต์", "ถนน") == 1);
    printf("✅ utf8_icontains: PASSED\n");
}

void test_has_comma(void) {
    printf("Testing has_comma...\n");
    assert(has_comma("hello,world") == 1);
    assert(has_comma("hello world") == 0);
    assert(has_comma("สมชาย,ใจดี") == 1);
    assert(has_comma("") == 0);
    printf("✅ has_comma: PASSED\n");
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    
    printf("\n========== Running Unit Tests ==========\n");
    test_utf8_strlen();
    test_trim_spaces();
    test_validate_date();
    test_is_leap_year();
    test_max_days_in_month();
    test_utf8_icontains();
    test_has_comma();
    printf("\n✅ All Unit Tests PASSED!\n");
    printf("========================================\n");
    
    return 0;
}
