#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repair_manager.h"




void Run_E2E(void) {
    printf("\n=== เริ่มการทดสอบ E2E ===\n");

    // ขั้นตอนที่ 1: ล้างไฟล์ CSV เดิม (เริ่มใหม่)
    FILE *fp = fopen(CSV_FILE, "w");
    if (!fp) {
        printf("❌ ไม่สามารถเปิดไฟล์ CSV เพื่อรีเซ็ต\n");
        return;
    }
    fprintf(fp, "ownername,address,RepairDetails,RepairStartDate\n");
    fclose(fp);
    printf("✅ สร้างไฟล์ CSV ใหม่เรียบร้อย\n");

    // ขั้นตอนที่ 2: เพิ่มข้อมูลจำลอง
    fp = fopen(CSV_FILE, "a");
    fprintf(fp, "John Doe,123 Main St,Fix Roof,2025-10-09\n");
    fprintf(fp, "Alice,456 Oak Ave,Paint Wall,2025-10-10\n");
    fprintf(fp, "Bob,789 Pine Rd,Replace Door,2025-10-11\n");
    fclose(fp);
    printf("✅ เพิ่มข้อมูลจำลองแล้ว\n");

    // ขั้นตอนที่ 3: แสดงข้อมูลทั้งหมด
    printf("\n📋 แสดงข้อมูลทั้งหมด:\n");
    show_all();

    // ขั้นตอนที่ 4: ค้นหาข้อมูล
    printf("\n🔍 ทดสอบค้นหาคำว่า 'Alice'\n");
    FILE *in = fopen(CSV_FILE, "r");
    if (in) fclose(in);
    // จำลอง search_records() แบบอัตโนมัติ
    {
        char key[] = "Alice";
        FILE *fp2 = fopen(CSV_FILE, "r");
        char line[1024];
        int lineNo = 0, found = 0;
        while (fgets(line, sizeof(line), fp2)) {
            if (lineNo == 0) { lineNo++; continue; }
            Repair r;
            if (parse_line(line, &r)) {
                if (icontains(r.owner, key) || icontains(r.address, key)) {
                    print_record(&r);
                    found++;
                }
            }
            lineNo++;
        }
        fclose(fp2);
        if (!found) printf("❌ ไม่พบ Alice\n");
        else printf("✅ พบ Alice จำนวน %d รายการ\n", found);
    }

    // ขั้นตอนที่ 5: ทดสอบอัปเดตวันที่
    printf("\n🛠️ ทดสอบอัปเดตวันที่ของ John Doe\n");
    FILE *fp3 = fopen(CSV_FILE, "r");
    FILE *tmp = fopen("tmp.csv", "w");
    fprintf(tmp, "ownername,address,RepairDetails,RepairStartDate\n");
    char line2[1024];
    int lineNo2 = 0;
    while (fgets(line2, sizeof(line2), fp3)) {
        if (lineNo2 == 0) { lineNo2++; continue; }
        Repair r;
        if (parse_line(line2, &r)) {
            if (iequals(r.owner, "John Doe")) strcpy(r.date, "2025-12-31");
            fprintf(tmp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
        }
        lineNo2++;
    }
    fclose(fp3);
    fclose(tmp);
    remove(CSV_FILE);
    rename("tmp.csv", CSV_FILE);
    printf("✅ อัปเดตวันที่ของ John Doe เป็น 2025-12-31 เรียบร้อย\n");

    // ขั้นตอนที่ 6: ทดสอบลบ Alice
    printf("\n🗑️ ทดสอบลบข้อมูลของ Alice\n");
    fp3 = fopen(CSV_FILE, "r");
    tmp = fopen("tmp.csv", "w");
    fprintf(tmp, "ownername,address,RepairDetails,RepairStartDate\n");
    int deleted = 0;
    while (fgets(line2, sizeof(line2), fp3)) {
        if (strncmp(line2, "ownername", 9) == 0) continue;
        Repair r;
        if (parse_line(line2, &r)) {
            if (iequals(r.owner, "Alice")) deleted++;
            else fprintf(tmp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
        }
    }
    fclose(fp3);
    fclose(tmp);
    remove(CSV_FILE);
    rename("tmp.csv", CSV_FILE);
    printf("✅ ลบข้อมูลของ Alice แล้ว %d รายการ\n", deleted);

    // ขั้นตอนที่ 7: ตรวจสอบผลสุดท้าย
    printf("\n📄 ตรวจสอบไฟล์หลังการทดสอบ:\n");
    show_all();

    printf("\n=== ✅ การทดสอบ E2E เสร็จสิ้น ===\n");

    wait_enter();
}
