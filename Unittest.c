#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "repair_manager.h"

// ==== Helper ====
void wait_enter() {
    printf("กด Enter เพื่อทำการทดสอบถัดไป...\n");
    while (getchar() != '\n');
}

// ==== Tests ====
void test_trim_spaces()
{
    printf("\n[TEST] trim_spaces() ...\n");
    char s1[] = "   hello world   ";
    trim_spaces(s1);
    assert(strcmp(s1, "hello world") == 0);

    char s2[] = "";
    trim_spaces(s2);
    assert(strcmp(s2, "") == 0);

    printf("✅ trim_spaces() ผ่านทั้งหมด\n");
    wait_enter();
}

void test_iequals()
{
    printf("\n[TEST] iequals() ...\n");
    assert(iequals("Test", "test"));
    assert(iequals("HELLO", "hello"));
    assert(!iequals("abc", "abcd"));
    printf("✅ iequals() ผ่านทั้งหมด\n");
    wait_enter();
}

void test_icontains()
{
    printf("\n[TEST] icontains() ...\n");
    assert(icontains("Bangkok", "kok"));
    assert(icontains("HomeRepair", "home"));
    assert(!icontains("FixCar", "house"));
    printf("✅ icontains() ผ่านทั้งหมด\n");
    wait_enter();
}

void test_is_leap_year()
{
    printf("\n[TEST] is_leap_year() ...\n");
    assert(is_leap_year(2000));
    assert(!is_leap_year(1900));
    assert(is_leap_year(2024));
    assert(!is_leap_year(2025));
    printf("✅ is_leap_year() ผ่านทั้งหมด\n");
    wait_enter();
}

void test_max_days_in_month()
{
    printf("\n[TEST] max_days_in_month() ...\n");
    assert(max_days_in_month(2024, 2) == 29);
    assert(max_days_in_month(2023, 2) == 28);
    assert(max_days_in_month(2023, 4) == 30);
    assert(max_days_in_month(2023, 7) == 31);
    printf("✅ max_days_in_month() ผ่านทั้งหมด\n");
    wait_enter();
}

void test_validate_and_normalize_date()
{
    printf("\n[TEST] validate_and_normalize_date() ...\n");
    char buf[32];
    assert(validate_and_normalize_date("2025-10-09", buf, sizeof(buf)));
    assert(strcmp(buf, "2025-10-09") == 0);

    assert(!validate_and_normalize_date("2025-13-01", buf, sizeof(buf))); // เดือนเกิน
    assert(!validate_and_normalize_date("2025-02-30", buf, sizeof(buf))); // วันเกิน
    assert(!validate_and_normalize_date("abc", buf, sizeof(buf)));        // ไม่ใช่เลข
    printf("✅ validate_and_normalize_date() ผ่านทั้งหมด\n");
    wait_enter();
}

// ==== Run All ====
void Run_units()
{
    printf("=== เริ่มการทดสอบ Unit Tests ===\n");
    test_trim_spaces();
    test_iequals();
    test_icontains();
    test_is_leap_year();
    test_max_days_in_month();
    test_validate_and_normalize_date();
    printf("\n🎉 ✅ การทดสอบทั้งหมดผ่านเรียบร้อยแล้ว!\n");
}

// ==== Main สำหรับรัน test ====

