#ifndef REPAIR_MANAGER_H
#define REPAIR_MANAGER_H

#include <stddef.h>

#define CSV_FILE "repairs.csv"
#define MAX 256

typedef struct {
    char owner[MAX];
    char address[MAX];
    char details[MAX];
    char date[MAX];
} Repair;

/* ---------- Utility ---------- */
void trim_newline(char *s);
void trim_spaces(char *s);
int has_comma(const char *s);
int iequals(const char *a, const char *b);
int icontains(const char *hay, const char *needle);

/* ---------- Date Validation ---------- */
int is_leap_year(int y);
int max_days_in_month(int y, int m);
int validate_and_normalize_date(const char *in, char *buff, size_t buffsz);

/* ---------- CSV Operations ---------- */
int ensure_header_exists(void);
int parse_line(char *line, Repair *r);
void print_record(const Repair *r);

/* ---------- Core Features ---------- */
void show_all(void);
void add_record(void);
void search_records(void);
void update_date_by_owner(void);
void delete_by_owner(void);

void wait_enter();
void Run_E2E(void);
void Run_units();
#endif
