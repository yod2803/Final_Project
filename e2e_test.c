#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX 256
#define CSV_FILE "repairs.csv"

typedef struct {
    char owner[MAX];
    char address[MAX];
    char details[MAX];
    char date[MAX];
} Repair;

extern void show_all(void);
extern int parse_line(char *line, Repair *r);
extern void print_record(const Repair *r);
extern int icontains(const char *hay, const char *needle);
extern int iequals(const char *a, const char *b);

void wait_enter(void) {
    printf("\nกด Enter เพื่อดำเนินการต่อ...");
    fflush(stdout);
    char tmp[8]; fgets(tmp, 8, stdin);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    printf("\n=== เริ่มการทดสอบ E2E ===\n");

    FILE *fp = fopen(CSV_FILE, "w");
    if (!fp) {
        printf("❌ ไม่สามารถเปิดไฟล์ CSV เพื่อรีเซ็ต\n");
        return 1;
    }
    fprintf(fp, "ownername,address,RepairDetails,RepairStartDate\n");
    fclose(fp);
    printf("✅ สร้างไฟล์ CSV ใหม่เรียบร้อย\n");

    fp = fopen(CSV_FILE, "a");
    fprintf(fp, "John Doe,123 Main St,Fix Roof,2025-10-09\n");
    fprintf(fp, "Alice,456 Oak Ave,Paint Wall,2025-10-10\n");
    fprintf(fp, "Bob,789 Pine Rd,Replace Door,2025-10-11\n");
    fclose(fp);
    printf("✅ เพิ่มข้อมูลจำลองแล้ว\n");

    printf("\n📋 แสดงข้อมูลทั้งหมด:\n");
    show_all();

    printf("\n🔍 ทดสอบค้นหาคำว่า 'Alice'\n");
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

    printf("\n📄 ตรวจสอบไฟล์หลังการทดสอบ:\n");
    show_all();

    printf("\n=== ✅ การทดสอบ E2E เสร็จสิ้น ===\n");
    wait_enter();
    return 0;
}
    