#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

#define MAX 256
#define CSV_FILE "repairs.csv"

typedef struct {
    char owner[MAX];
    char address[MAX];
    char details[MAX];
    char date[MAX];
} Repair;

/* ---------- UTF-8 Utilities ---------- */
int utf8_strlen(const char *s) {
    int count = 0;
    unsigned char c;
    while ((c = (unsigned char)*s++)) {
        if ((c & 0xC0) != 0x80)
            count++;
    }
    return count;
}

static void utf8_tolower_copy(const char *src, char *dst, size_t dstsz) {
    size_t j = 0; unsigned char c;
    while (*src && j < dstsz - 1) {
        c = (unsigned char)*src;
        if (c < 128) { dst[j++] = (char)tolower(c); src++; }
        else {
            int len = 1;
            if ((c & 0xE0) == 0xC0) len = 2;
            else if ((c & 0xF0) == 0xE0) len = 3;
            else if ((c & 0xF8) == 0xF0) len = 4;
            for (int i = 0; i < len && *src && j < dstsz - 1; i++)
                dst[j++] = *src++;
        }
    }
    dst[j] = '\0';
}

int utf8_icontains(const char *hay, const char *needle) {
    if (!hay || !needle) return 0;
    char hbuf[512], nbuf[256];
    utf8_tolower_copy(hay, hbuf, sizeof(hbuf));
    utf8_tolower_copy(needle, nbuf, sizeof(nbuf));
    return strstr(hbuf, nbuf) != NULL;
}

/* ---------- Windows UTF-8 Input Fix ---------- */
#ifdef _WIN32
int read_utf8_line(char *buffer, int size) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    WCHAR wbuf[MAX];
    DWORD read = 0;
    
    if (!ReadConsoleW(hStdin, wbuf, MAX - 1, &read, NULL)) {
        return 0;
    }
    
    if (read == 0) return 0;
    
    while (read > 0 && (wbuf[read-1] == L'\r' || wbuf[read-1] == L'\n')) {
        wbuf[--read] = 0;
    }
    wbuf[read] = 0;
    
    int bytes = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, buffer, size, NULL, NULL);
    return bytes > 0;
}
#else
int read_utf8_line(char *buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        return 1;
    }
    return 0;
}
#endif

/* ---------- Utility ---------- */
void trim_newline(char *s) {
    if (!s) return;
    s[strcspn(s, "\r\n")] = 0;
}

void trim_spaces(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\t')) s[--n] = 0;
    size_t i = 0;
    while (s[i] == ' ' || s[i] == '\t') i++;
    if (i > 0) memmove(s, s + i, n - i + 1);
}

int has_comma(const char *s) {
    return s && strchr(s, ',') != NULL;
}

int icontains(const char *hay, const char *needle) {
    if (!hay || !needle) return 0;
    char hbuf[512], nbuf[256];
    for (size_t i = 0; needle[i]; ++i) nbuf[i] = tolower((unsigned char)needle[i]);
    nbuf[strlen(needle)] = '\0';
    for (size_t i = 0; hay[i]; ++i) hbuf[i] = tolower((unsigned char)hay[i]);
    hbuf[strlen(hay)] = '\0';
    return strstr(hbuf, nbuf) != NULL;
}

int iequals(const char *a, const char *b) {
    if (!a || !b) return 0;
    char abuf[MAX], bbuf[MAX];
    for (size_t i = 0; a[i]; ++i) abuf[i] = tolower((unsigned char)a[i]);
    abuf[strlen(a)] = '\0';
    for (size_t i = 0; b[i]; ++i) bbuf[i] = tolower((unsigned char)b[i]);
    bbuf[strlen(b)] = '\0';
    return strcmp(abuf, bbuf) == 0;
}

/* ---------- Date ---------- */
int is_leap_year(int y) {
    return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

int max_days_in_month(int y, int m) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return is_leap_year(y) ? 29 : 28;
        default: return 0;
    }
}

int validate_and_normalize_date(const char *in, char *buff, size_t buffsz) {
    int y, m, d; char tmp[64];
    strncpy(tmp, in, sizeof(tmp) - 1); tmp[sizeof(tmp) - 1] = 0;
    trim_spaces(tmp);
    if (sscanf(tmp, "%d-%d-%d", &y, &m, &d) != 3) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > max_days_in_month(y, m)) return 0;
    snprintf(buff, buffsz, "%04d-%02d-%02d", y, m, d);
    return 1;
}

void prompt_valid_date(const char *label, char *out, size_t outsz) {
    char line[MAX];
    while (1) {
        printf("%s (YYYY-MM-DD): ", label); fflush(stdout);
        if (!read_utf8_line(line, sizeof(line))) return;
        trim_spaces(line);
        if (validate_and_normalize_date(line, out, outsz)) return;
        printf("❌ รูปแบบวันที่ไม่ถูกต้อง\n");
    }
}

/* ---------- CSV ---------- */
int ensure_header_exists(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) {
        fp = fopen(CSV_FILE, "w");
        if (!fp) return 0;
        fprintf(fp, "ownername,address,RepairDetails,RepairStartDate\n");
        fclose(fp); return 1;
    }
    fclose(fp); return 1;
}

int parse_line(char *line, Repair *r) {
    char *tok = strtok(line, ",");
    if (!tok) return 0; strncpy(r->owner, tok, MAX - 1); r->owner[MAX-1] = '\0';
    tok = strtok(NULL, ","); if (!tok) return 0; strncpy(r->address, tok, MAX - 1); r->address[MAX-1] = '\0';
    tok = strtok(NULL, ","); if (!tok) return 0; strncpy(r->details, tok, MAX - 1); r->details[MAX-1] = '\0';
    tok = strtok(NULL, ","); if (!tok) return 0; strncpy(r->date, tok, MAX - 1); r->date[MAX-1] = '\0';
    return 1;
}

/* ---------- Display ---------- */
void print_table_header() {
    printf("\n%-20s | %-25s | %-25s | %-12s\n", "ชื่อเจ้าของ", "ที่อยู่", "รายละเอียดซ่อม", "วันที่เริ่ม");
    printf("-----------------------------------------------------------------------------------------------\n");
}

void print_record(const Repair *r) {
    printf("%-20s | %-25s | %-25s | %-12s\n", r->owner, r->address, r->details, r->date);
}

/* ---------- Core ---------- */
void show_all(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    char line[1024]; int lineNo = 0, shown = 0;
    print_table_header();
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0 && strncmp(line, "ownername,", 10) == 0) { lineNo++; continue; }
        Repair r; if (parse_line(line, &r)) { print_record(&r); shown++; }
        lineNo++;
    }
    fclose(fp);
    if (!shown) printf("ไม่มีข้อมูลให้แสดง\n");
}

void add_record(void) {
    ensure_header_exists(); Repair r;
    printf("ชื่อเจ้าของ: "); fflush(stdout);
    if (!read_utf8_line(r.owner, MAX)) return;
    trim_spaces(r.owner);
    
    printf("ที่อยู่: "); fflush(stdout);
    if (!read_utf8_line(r.address, MAX)) return;
    trim_spaces(r.address);
    
    printf("รายละเอียดซ่อม: "); fflush(stdout);
    if (!read_utf8_line(r.details, MAX)) return;
    trim_spaces(r.details);
    
    prompt_valid_date("วันที่เริ่ม", r.date, sizeof(r.date));
    
    if (has_comma(r.owner) || has_comma(r.address) || has_comma(r.details) || has_comma(r.date)) {
        printf("❌ ห้ามใช้เครื่องหมายจุลภาค (,)\n"); return;
    }
    FILE *fp = fopen(CSV_FILE, "a");
    if (!fp) { printf("ไม่สามารถเขียนไฟล์ได้\n"); return; }
    fprintf(fp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
    fclose(fp);
    printf("✅ เพิ่มข้อมูลเรียบร้อยแล้ว!\n");
}

void search_records(void) {
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    char key[MAX];
    printf("ค้นหาคำ (ชื่อเจ้าของ หรือ ที่อยู่): "); fflush(stdout);
    
    if (!read_utf8_line(key, MAX)) {
        fclose(fp);
        return;
    }
    
    trim_spaces(key);
    
    if (strlen(key) == 0) {
        printf("❌ คำค้นหาอย่าเว้นว่าง\n");
        fclose(fp);
        return;
    }
    
    char line[1024]; int lineNo = 0, found = 0;
    print_table_header();
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0 && strncmp(line, "ownername,", 10) == 0) { lineNo++; continue; }
        Repair r;
        if (parse_line(line, &r)) {
            if (utf8_icontains(r.owner, key) || utf8_icontains(r.address, key)) {
                print_record(&r); found++;
            }
        }
        lineNo++;
    }
    fclose(fp);
    if (!found) printf("\nไม่พบข้อมูลที่ตรงกับ '%s'\n", key);
    else printf("\nพบทั้งหมด %d รายการ\n", found);
}

void delete_record(void) {
    char key[MAX];
    printf("ป้อนชื่อเจ้าของที่ต้องการลบ: "); fflush(stdout);
    
    if (!read_utf8_line(key, MAX)) return;
    trim_spaces(key);
    
    if (strlen(key) == 0) {
        printf("❌ กรุณาป้อนชื่อเจ้าของ\n");
        return;
    }
    
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    
    FILE *tmp = fopen("tmp.csv", "w");
    if (!tmp) {
        printf("❌ ไม่สามารถสร้างไฟล์ชั่วคราวได้\n");
        fclose(fp);
        return;
    }
    
    fprintf(tmp, "ownername,address,RepairDetails,RepairStartDate\n");
    
    char line[1024];
    int lineNo = 0, deleted = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0) { lineNo++; continue; }
        
        Repair r;
        char lineCopy[1024];
        strcpy(lineCopy, line);
        
        if (parse_line(lineCopy, &r)) {
            if (utf8_icontains(r.owner, key)) {
                deleted++;
                printf("🗑️  ลบ: %s\n", r.owner);
            } else {
                fprintf(tmp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
            }
        }
        lineNo++;
    }
    
    fclose(fp);
    fclose(tmp);
    
    if (deleted > 0) {
        remove(CSV_FILE);
        rename("tmp.csv", CSV_FILE);
        printf("✅ ลบข้อมูลเรียบร้อย %d รายการ\n", deleted);
    } else {
        remove("tmp.csv");
        printf("❌ ไม่พบข้อมูลที่ตรงกับ '%s'\n", key);
    }
}

void edit_record(void) {
    char key[MAX];
    printf("ป้อนชื่อเจ้าของที่ต้องการแก้ไข: "); fflush(stdout);
    
    if (!read_utf8_line(key, MAX)) return;
    trim_spaces(key);
    
    if (strlen(key) == 0) {
        printf("❌ กรุณาป้อนชื่อเจ้าของ\n");
        return;
    }
    
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp) { printf("ไม่พบไฟล์ %s\n", CSV_FILE); return; }
    
    // หาข้อมูลที่ต้องการแก้ไข
    char line[1024];
    int lineNo = 0, found = 0;
    Repair foundRecord;
    
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0) { lineNo++; continue; }
        
        Repair r;
        char lineCopy[1024];
        strcpy(lineCopy, line);
        
        if (parse_line(lineCopy, &r)) {
            if (utf8_icontains(r.owner, key)) {
                foundRecord = r;
                found = 1;
                break;
            }
        }
        lineNo++;
    }
    fclose(fp);
    
    if (!found) {
        printf("❌ ไม่พบข้อมูลที่ตรงกับ '%s'\n", key);
        return;
    }
    
    // แสดงข้อมูลปัจจุบัน
    printf("\n📋 ข้อมูลปัจจุบัน:\n");
    print_table_header();
    print_record(&foundRecord);
    
    // รับข้อมูลใหม่
    Repair newRecord;
    char choice[10];
    
    printf("\nแก้ไขชื่อเจ้าของ? (y/n): "); fflush(stdout);
    read_utf8_line(choice, sizeof(choice));
    if (choice[0] == 'y' || choice[0] == 'Y') {
        printf("ชื่อเจ้าของใหม่ [%s]: ", foundRecord.owner); fflush(stdout);
        if (read_utf8_line(newRecord.owner, MAX) && strlen(newRecord.owner) > 0) {
            trim_spaces(newRecord.owner);
        } else {
            strcpy(newRecord.owner, foundRecord.owner);
        }
    } else {
        strcpy(newRecord.owner, foundRecord.owner);
    }
    
    printf("แก้ไขที่อยู่? (y/n): "); fflush(stdout);
    read_utf8_line(choice, sizeof(choice));
    if (choice[0] == 'y' || choice[0] == 'Y') {
        printf("ที่อยู่ใหม่ [%s]: ", foundRecord.address); fflush(stdout);
        if (read_utf8_line(newRecord.address, MAX) && strlen(newRecord.address) > 0) {
            trim_spaces(newRecord.address);
        } else {
            strcpy(newRecord.address, foundRecord.address);
        }
    } else {
        strcpy(newRecord.address, foundRecord.address);
    }
    
    printf("แก้ไขรายละเอียดซ่อม? (y/n): "); fflush(stdout);
    read_utf8_line(choice, sizeof(choice));
    if (choice[0] == 'y' || choice[0] == 'Y') {
        printf("รายละเอียดซ่อมใหม่ [%s]: ", foundRecord.details); fflush(stdout);
        if (read_utf8_line(newRecord.details, MAX) && strlen(newRecord.details) > 0) {
            trim_spaces(newRecord.details);
        } else {
            strcpy(newRecord.details, foundRecord.details);
        }
    } else {
        strcpy(newRecord.details, foundRecord.details);
    }
    
    printf("แก้ไขวันที่? (y/n): "); fflush(stdout);
    read_utf8_line(choice, sizeof(choice));
    if (choice[0] == 'y' || choice[0] == 'Y') {
        printf("วันที่ใหม่ [%s] ", foundRecord.date);
        prompt_valid_date("", newRecord.date, sizeof(newRecord.date));
    } else {
        strcpy(newRecord.date, foundRecord.date);
    }
    
    // ตรวจสอบ comma
    if (has_comma(newRecord.owner) || has_comma(newRecord.address) || 
        has_comma(newRecord.details) || has_comma(newRecord.date)) {
        printf("❌ ห้ามใช้เครื่องหมายจุลภาค (,)\n");
        return;
    }
    
    // เขียนข้อมูลกลับไปยังไฟล์
    fp = fopen(CSV_FILE, "r");
    FILE *tmp = fopen("tmp.csv", "w");
    if (!tmp) {
        printf("❌ ไม่สามารถสร้างไฟล์ชั่วคราวได้\n");
        fclose(fp);
        return;
    }
    
    fprintf(tmp, "ownername,address,RepairDetails,RepairStartDate\n");
    lineNo = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        if (lineNo == 0) { lineNo++; continue; }
        
        Repair r;
        char lineCopy[1024];
        strcpy(lineCopy, line);
        
        if (parse_line(lineCopy, &r)) {
            if (utf8_icontains(r.owner, key)) {
                fprintf(tmp, "%s,%s,%s,%s\n", newRecord.owner, newRecord.address, 
                        newRecord.details, newRecord.date);
            } else {
                fprintf(tmp, "%s,%s,%s,%s\n", r.owner, r.address, r.details, r.date);
            }
        }
        lineNo++;
    }
    
    fclose(fp);
    fclose(tmp);
    
    remove(CSV_FILE);
    rename("tmp.csv", CSV_FILE);
    printf("✅ แก้ไขข้อมูลเรียบร้อยแล้ว!\n");
}

#ifdef BUILD_MAIN
int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    ensure_header_exists();
    char buf[16];
    while (1) {
        printf("\n=== 🏠 Home Repair Manager ===\n");
        printf("1. แสดงข้อมูลทั้งหมด\n");
        printf("2. เพิ่มข้อมูลใหม่\n");
        printf("3. ค้นหา (ชื่อ/ที่อยู่)\n");
        printf("4. ลบข้อมูล\n");
        printf("5. แก้ไขข้อมูล\n");
        printf("0. ออกโปรแกรม\n");
        printf("เลือก: "); fflush(stdout);
        
        if (!read_utf8_line(buf, sizeof(buf))) break;
        trim_spaces(buf);
        int c = atoi(buf);
        
        if (c == 1) show_all();
        else if (c == 2) add_record();
        else if (c == 3) search_records();
        else if (c == 4) delete_record();
        else if (c == 5) edit_record();
        else if (c == 0) { printf("👋 ออกจากโปรแกรมแล้ว\n"); break; }
        else printf("❌ ตัวเลือกไม่ถูกต้อง\n");
    }
    return 0;
}
#endif
