#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define CSV_FILE "repairs.csv"
#define MAX 256

typedef struct {
    char owner[MAX];
    char address[MAX];
    char details[MAX];
    char date[MAX];
} Repair;

/* ---------- Utilities ---------- */
static void trim_newline(char *s) {
    if (!s) return;
    s[strcspn(s, "\r\n")] = 0;
}
static void trim_spaces(char *s) {
    if (!s) return;
    // leading
    size_t i = 0, n = strlen(s);
    while (i < n && isspace((unsigned char)s[i])) i++;
    if (i) memmove(s, s + i, n - i + 1);
    // trailing
    n = strlen(s);
    while (n > 0 && isspace((unsigned char)s[n - 1])) s[--n] = 0;
}
static int has_comma(const char *s) {
    return s && strchr(s, ',') != NULL;
}
static int iequals(const char *a, const char *b) {
    if (!a || !b) return 0;
    size_t la = strlen(a), lb = strlen(b);
    if (la != lb) return 0;
    for (size_t i = 0; i < la; i++)
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return 0;
    return 1;
}
static int icontains(const char *hay, const char *needle) {
    if (!hay || !needle) return 0;
    size_t hlen = strlen(hay), nlen = strlen(needle);
    if (nlen == 0) return 1;
    for (size_t i = 0; i + nlen <= hlen; i++) {
        size_t j = 0;
        while (j < nlen &&
               tolower((unsigned char)hay[i + j]) == tolower((unsigned char)needle[j])) j++;
        if (j == nlen) return 1;
    }
    return 0;
}

/* ---------- CSV helpers ---------- */
static int ensure_header_exists(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) {
        // create with header
        fp = fopen(CSV_FILE, "w");
        if (!fp) return 0;
        fprintf(fp, "ownername,address,RepairDetails,RepairStartDate\n");
        fclose(fp);
        return 1;
    } else {
        // check first line
        char first[1024];
        if (!fgets(first, sizeof(first), fp)) { fclose(fp); return 1; }
        fclose(fp);
        if (strncmp(first, "ownername,address,RepairDetails,RepairStartDate", 47) != 0) {
            // prepend header by rewriting (ง่ายสุด: ถ้าไม่มี header ให้สร้างใหม่ + คัดลอกเดิม)
            FILE *in = fopen(CSV_FILE, "r");
            FILE *out = fopen("tmp.csv", "w");
            if (!in || !out) { if(in) fclose(in); if(out) fclose(out); return 0; }
            fprintf(out, "ownername,address,RepairDetails,RepairStartDate\n");
            char buf[1024];
            while (fgets(buf, sizeof(buf), in)) fputs(buf, out);
            fclose(in); fclose(out);
            remove(CSV_FILE); rename("tmp.csv", CSV_FILE);
        }
        return 1;
    }
}

static int parse_line(char *line, Repair *r) {
    // คาดหวัง CSV แบบง่าย ไม่มีเครื่องหมายคำพูดครอบ
    char *p = line;
    char *tok = strtok(p, ",");
    if (!tok) return 0; strncpy(r->owner, tok, MAX - 1); r->owner[MAX - 1] = 0; trim_spaces(r->owner);

    tok = strtok(NULL, ",");
    if (!tok) return 0; strncpy(r->address, tok, MAX - 1); r->address[MAX - 1] = 0; trim_spaces(r->address);

    tok = strtok(NULL, ",");
    if (!tok) return 0; strncpy(r->details, tok, MAX - 1); r->details[MAX - 1] = 0; trim_spaces(r->details);

    tok = strtok(NULL, ",");
    if (!tok) return 0; strncpy(r->date, tok, MAX - 1); r->date[MAX - 1] = 0; trim_spaces(r->date);

    return 1;
}

static void print_record(const Repair *r) {
    printf("%s | %s | %s | %s\n", r->owner, r->address, r->details, r->date);
}

/* ---------- Features ---------- */
static void show_all(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    char line[1024];
    int lineNo = 0, shown = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0 && strncmp(line, "ownername,", 10) == 0) { lineNo++; continue; }
        Repair r;
        if (parse_line(line, &r)) {
            print_record(&r);
            shown++;
        }
        lineNo++;
    }
    fclose(fp);
    if (shown == 0) printf("ไม่มีข้อมูลให้แสดง\n");
}

static void add_record(void) {
    if (!ensure_header_exists()) { printf("สร้าง/ตรวจสอบไฟล์ไม่สำเร็จ\n"); return; }

    Repair r;
    printf("ชื่อเจ้าของ: "); if (!fgets(r.owner, MAX, stdin)) return; trim_newline(r.owner); trim_spaces(r.owner);
    printf("ที่อยู่: "); if (!fgets(r.address, MAX, stdin)) return; trim_newline(r.address); trim_spaces(r.address);
    printf("รายละเอียดซ่อม: "); if (!fgets(r.details, MAX, stdin)) return; trim_newline(r.details); trim_spaces(r.details);
    printf("วันที่เริ่ม (YYYY-MM-DD): "); if (!fgets(r.date, MAX, stdin)) return; trim_newline(r.date); trim_spaces(r.date);

    if (has_comma(r.owner) || has_comma(r.address) || has_comma(r.details) || has_comma(r.date)) {
        printf("เพิ่มไม่สำเร็จ: ห้ามมีเครื่องหมายจุลภาค (,) ในข้อมูล\n");
        return;
    }
    if (strlen(r.owner) == 0) { printf("เพิ่มไม่สำเร็จ: ชื่อเจ้าของว่าง\n"); return; }

    FILE *fp = fopen(CSV_FILE, "a");
    if (!fp) { printf("ไม่สามารถเขียนไฟล์\n"); return; }
    fprintf(fp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
    fclose(fp);
    printf("เพิ่มข้อมูลแล้ว\n");
}

static void search_records(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }

    char key[MAX];
    printf("ค้นหาคำ (ชื่อเจ้าของ หรือ ที่อยู่): ");
    if (!fgets(key, MAX, stdin)) { fclose(fp); return; }
    trim_newline(key); trim_spaces(key);

    char line[1024];
    int lineNo = 0, found = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0 && strncmp(line, "ownername,", 10) == 0) { lineNo++; continue; }
        Repair r;
        if (parse_line(line, &r)) {
            if (icontains(r.owner, key) || icontains(r.address, key)) {
                print_record(&r);
                found++;
            }
        }
        lineNo++;
    }
    fclose(fp);
    if (!found) printf("ไม่พบข้อมูลที่ตรงกับ \"%s\"\n", key);
    else printf("พบทั้งหมด %d รายการ\n", found);
}

static void update_date_by_owner(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    FILE *tmp = fopen("tmp.csv", "w");
    if (!tmp) { printf("ไม่สามารถสร้างไฟล์ชั่วคราว\n"); fclose(fp); return; }

    char owner[MAX], newDate[MAX];
    printf("ชื่อเจ้าของที่จะอัปเดต (เทียบแบบไม่สนตัวพิมพ์): ");
    if (!fgets(owner, MAX, stdin)) { fclose(fp); fclose(tmp); return; }
    trim_newline(owner); trim_spaces(owner);
    printf("วันที่ใหม่ (YYYY-MM-DD): ");
    if (!fgets(newDate, MAX, stdin)) { fclose(fp); fclose(tmp); return; }
    trim_newline(newDate); trim_spaces(newDate);

    // คัดลอก header ก่อน
    fprintf(tmp, "ownername,address,RepairDetails,RepairStartDate\n");

    char line[1024];
    int lineNo = 0, changed = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0 && strncmp(line, "ownername,", 10) == 0) { lineNo++; continue; }
        Repair r;
        if (parse_line(line, &r)) {
            if (iequals(r.owner, owner)) {
                strncpy(r.date, newDate, MAX - 1);
                r.date[MAX - 1] = 0;
                changed++;
            }
            fprintf(tmp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
        }
        lineNo++;
    }
    fclose(fp); fclose(tmp);
    remove(CSV_FILE); rename("tmp.csv", CSV_FILE);
    if (changed == 0) printf("ไม่พบชื่อ \"%s\" จึงไม่ได้อัปเดต\n", owner);
    else printf("อัปเดตแล้ว %d รายการ\n", changed);
}

static void delete_by_owner(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    FILE *tmp = fopen("tmp.csv", "w");
    if (!tmp) { printf("ไม่สามารถสร้างไฟล์ชั่วคราว\n"); fclose(fp); return; }

    char owner[MAX];
    printf("ชื่อเจ้าของที่จะลบ (เทียบแบบไม่สนตัวพิมพ์): ");
    if (!fgets(owner, MAX, stdin)) { fclose(fp); fclose(tmp); return; }
    trim_newline(owner); trim_spaces(owner);

    printf("ยืนยันลบทั้งหมดของ \"%s\" ? (y/n): ", owner);
    int ch = getchar();
    if (ch != 'y' && ch != 'Y') {
        // flush line
        while (ch != '\n' && ch != EOF) ch = getchar();
        fclose(fp); fclose(tmp); remove("tmp.csv");
        printf("ยกเลิกการลบ\n");
        return;
    }
    // flush newline
    while (ch != '\n' && ch != EOF) ch = getchar();

    // เขียน header
    fprintf(tmp, "ownername,address,RepairDetails,RepairStartDate\n");

    char line[1024];
    int lineNo = 0, deleted = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0 && strncmp(line, "ownername,", 10) == 0) { lineNo++; continue; }
        Repair r;
        if (parse_line(line, &r)) {
            if (iequals(r.owner, owner)) {
                deleted++;
            } else {
                fprintf(tmp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
            }
        }
        lineNo++;
    }
    fclose(fp); fclose(tmp);
    remove(CSV_FILE); rename("tmp.csv", CSV_FILE);
    if (deleted == 0) printf("ไม่พบชื่อ \"%s\" จึงไม่ได้ลบ\n", owner);
    else printf("ลบแล้ว %d รายการ\n", deleted);
}

/* ---------- Menu ---------- */
static void menu(void) {
    printf("\n=== Home Repair Manager ===\n");
    printf("1. แสดงข้อมูลทั้งหมด\n");
    printf("2. เพิ่มข้อมูล\n");
    printf("3. ค้นหา (ชื่อ/ที่อยู่)\n");
    printf("4. อัปเดตวันที่เริ่ม (ตามชื่อ)\n");
    printf("5. ลบข้อมูลตามชื่อ\n");
    printf("0. ออก\n");
    printf("เลือก: ");
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    ensure_header_exists();

    char buf[16];
while (1) {
    menu();
    if (!fgets(buf, sizeof(buf), stdin)) break;
    trim_newline(buf); 
    trim_spaces(buf);

    // ถ้าว่าง ให้แจ้งเตือน
    if (strlen(buf) == 0) {
        printf("กรุณาป้อนตัวเลข 0-5\n");
        continue;
    }

    // ตรวจสอบว่ามีแต่ตัวเลข
    int validNumber = 1;
    for (size_t i = 0; i < strlen(buf); i++) {
        if (!isdigit((unsigned char)buf[i])) { 
            validNumber = 0; 
            break; 
        }
    }

    if (!validNumber) {
        printf("ตัวเลือกไม่ถูกต้อง ต้องเป็นตัวเลข 0-5 เท่านั้น\n");
        continue;
    }

    int c = atoi(buf);

    if      (c == 1) show_all();
    else if (c == 2) add_record();
    else if (c == 3) search_records();
    else if (c == 4) update_date_by_owner();
    else if (c == 5) delete_by_owner();
    else if (c == 0) { 
        printf("ออกโปรแกรม\n"); 
        break; 
    }
    else {
        printf("ตัวเลือกไม่ถูกต้อง ต้องเป็น 0-5\n");
    }
}


    return 0;
}
