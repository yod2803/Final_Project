นี่คือ **README.md** ที่ปรับปรุงให้สวยงามและครบถ้วนกว่าเดิม:

---

```markdown
<div align="center">

# 🏠 Home Repair Manager

![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![UTF-8](https://img.shields.io/badge/Encoding-UTF--8-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**ระบบจัดการข้อมูลการซ่อมแซมบ้านผ่าน CLI พร้อมรองรับภาษาไทย UTF-8 เต็มรูปแบบ**

[คุณสมบัติ](#-คุณสมบัติหลัก) • [การติดตั้ง](#-การติดตั้ง) • [วิธีใช้งาน](#-วิธีใช้งาน) • [การทดสอบ](#-การทดสอบ) • [โครงสร้าง](#-โครงสร้างโปรเจกต์)

</div>

---

## 📖 สารบัญ

- [🎯 ภาพรวม](#-ภาพรวม)
- [✨ คุณสมบัติหลัก](#-คุณสมบัติหลัก)
- [🔧 ความต้องการของระบบ](#-ความต้องการของระบบ)
- [📥 การติดตั้ง](#-การติดตั้ง)
- [🔨 การคอมไพล์](#-การคอมไพล์)
- [🚀 วิธีใช้งาน](#-วิธีใช้งาน)
- [🧪 การทดสอบ](#-การทดสอบ)
- [📁 โครงสร้างโปรเจกต์](#-โครงสร้างโปรเจกต์)
- [💡 รายละเอียดทางเทคนิค](#-รายละเอียดทางเทคนิค)
- [❓ แก้ปัญหาที่พบบ่อย](#-แก้ปัญหาที่พบบ่อย)
- [🤝 การมีส่วนร่วม](#-การมีส่วนร่วม)
- [📜 License](#-license)

---

## 🎯 ภาพรวม

**Home Repair Manager** เป็นโปรแกรมจัดการข้อมูลการซ่อมแซมบ้านที่พัฒนาด้วยภาษา C โดยมีจุดเด่นในการรองรับ **ภาษาไทย UTF-8** อย่างสมบูรณ์บน Windows Console

โปรแกรมจัดเก็บข้อมูลในรูปแบบ **CSV** ทำให้สามารถนำไปใช้งานต่อกับ Excel หรือ Google Sheets ได้ง่าย พร้อมทั้งมีระบบ **Unit Test** และ **E2E Test** ที่ครบถ้วนเพื่อความน่าเชื่อถือ

### 🎯 วัตถุประสงค์
- จัดการข้อมูลการซ่อมแซมบ้านอย่างเป็นระบบ
- เก็บบันทึกชื่อเจ้าของ ที่อยู่ รายละเอียด และวันที่ซ่อม
- ค้นหาและแก้ไขข้อมูลได้รวดเร็ว
- รองรับการใช้งานจริงด้วยการตรวจสอบข้อมูลที่เข้มงวด

---

## ✨ คุณสมบัติหลัก

<table>
<tr>
<td width="50%">

### 🔧 ฟังก์ชันหลัก
- ✅ **เพิ่มข้อมูล** - บันทึกรายละเอียดการซ่อมแซม
- 🔍 **ค้นหาข้อมูล** - ค้นหาด้วยชื่อหรือที่อยู่
- 📋 **แสดงทั้งหมด** - ดูรายการซ่อมแซมทั้งหมด
- 🗑️ **ลบข้อมูล** - ลบด้วยชื่อเจ้าของ

</td>
<td width="50%">

### 🌐 เทคโนโลยี
- 🇹🇭 **รองรับภาษาไทย** ด้วย UTF-8
- 📊 **CSV Storage** เปิดได้ด้วย Excel
- 🧪 **Testing Suite** Unit + E2E Tests
- 🔒 **Data Validation** ตรวจสอบวันที่และ CSV Injection

</td>
</tr>
</table>

### 🎨 ฟีเจอร์พิเศษ

| ฟีเจอร์ | รายละเอียด |
|---------|-----------|
| **UTF-8 Input** | ใช้ `ReadConsoleW()` และ `WideCharToMultiByte()` สำหรับ Windows |
| **Date Validation** | ตรวจสอบวันที่รวมถึง Leap Year อัตโนมัติ |
| **CSV Protection** | ป้องกัน CSV Injection โดยห้ามใช้เครื่องหมาย `,` |
| **Case-Insensitive Search** | ค้นหาไม่สนตัวพิมพ์เล็ก/ใหญ่ |
| **Auto File Creation** | สร้างไฟล์ CSV พร้อม header อัตโนมัติ |

---

## 🔧 ความต้องการของระบบ

### ✅ ซอฟต์แวร์ที่จำเป็น

```
ระบบปฏิบัติการ: Windows 10/11
Compiler: GCC (MinGW-w64 แนะนำ)
Terminal: PowerShell หรือ Windows Terminal
Encoding: UTF-8 Support
```

### 📦 การติดตั้ง GCC

#### วิธีที่ 1: ใช้ Chocolatey (แนะนำ)
```
# ติดตั้ง Chocolatey ก่อน (หากยังไม่มี)
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# ติดตั้ง MinGW
choco install mingw -y
```

#### วิธีที่ 2: ดาวน์โหลดจากเว็บไซต์
1. ดาวน์โหลดจาก [MinGW-w64](https://www.mingw-w64.org/)
2. ติดตั้งและเพิ่ม `bin` folder ลง PATH
3. Restart Terminal

### 🔍 ตรวจสอบการติดตั้ง
```
gcc --version
```

**ผลลัพธ์ที่คาดหวัง:**
```
gcc (MinGW-W64 x86_64-ucrt-posix-seh) 13.2.0
Copyright (C) 2023 Free Software Foundation, Inc.
```

---

## 📥 การติดตั้ง

### 1️⃣ Clone Repository
```
git clone https://github.com/yod2803/Final_Project.git
cd Final_Project
```

### 2️⃣ ตรวจสอบไฟล์
```
dir
```

**โครงสร้างที่ควรเห็น:**
```
📦 Final_Project/
├── 📄 repair.c           # โค้ดหลัก
├── 📄 unit_test.c        # Unit Tests
├── 📄 e2e_test.c         # E2E Tests
└── 📄 README.md          # เอกสารนี้
```

---

## 🔨 การคอมไพล์

### 🎯 คอมไพล์โปรแกรมหลัก
```
gcc -DBUILD_MAIN -o repair.exe repair.c
```

### 🧪 คอมไพล์ Unit Tests
```
gcc -o unit_test.exe unit_test.c repair.c
```

### 🔄 คอมไพล์ E2E Tests
```
gcc -o e2e_test.exe e2e_test.c repair.c
```

### ⚡ คอมไพล์ทั้งหมดพร้อมกัน (PowerShell)
```
# สร้างสคริปต์ build.ps1
@"
Write-Host "🔨 Compiling Home Repair Manager..." -ForegroundColor Cyan

Write-Host "`n[1/3] Building main program..." -ForegroundColor Yellow
gcc -DBUILD_MAIN -o repair.exe repair.c
if ($LASTEXITCODE -eq 0) { Write-Host "✅ repair.exe compiled successfully!" -ForegroundColor Green }

Write-Host "`n[2/3] Building unit tests..." -ForegroundColor Yellow
gcc -o unit_test.exe unit_test.c repair.c
if ($LASTEXITCODE -eq 0) { Write-Host "✅ unit_test.exe compiled successfully!" -ForegroundColor Green }

Write-Host "`n[3/3] Building E2E tests..." -ForegroundColor Yellow
gcc -o e2e_test.exe e2e_test.c repair.c
if ($LASTEXITCODE -eq 0) { Write-Host "✅ e2e_test.exe compiled successfully!" -ForegroundColor Green }

Write-Host "`n🎉 All programs compiled successfully!" -ForegroundColor Cyan
"@ | Out-File -Encoding UTF8 build.ps1

# รันสคริปต์
.\build.ps1
```

---

## 🚀 วิธีใช้งาน

### ▶️ เริ่มโปรแกรม
```
./repair.exe
```

### 🎛️ เมนูหลัก

```
=== 🏠 Home Repair Manager ===
1. แสดงข้อมูลทั้งหมด
2. เพิ่มข้อมูลใหม่
3. ค้นหา (ชื่อ/ที่อยู่)
4. ลบข้อมูล
0. ออกโปรแกรม
เลือก: _
```

---

## 📚 คู่มือการใช้งานแต่ละฟังก์ชัน

### 1️⃣ เพิ่มข้อมูลใหม่

```
เลือก: 2

ชื่อเจ้าของ: สมชาย ใจดี
ที่อยู่: 123 ถนนสุขุมวิท แขวงคลองเตย เขตคลองเตย กรุงเทพฯ
รายละเอียดซ่อม: ซ่อมหลังคารั่ว เปลี่ยนกระเบื้องใหม่
วันที่เริ่ม (YYYY-MM-DD): 2025-10-09
✅ เพิ่มข้อมูลเรียบร้อยแล้ว!
```

**📋 หมายเหตุ:**
- วันที่ต้องอยู่ในรูปแบบ `YYYY-MM-DD` เท่านั้น
- ห้ามใช้เครื่องหมาย `,` ในข้อมูล
- ระบบจะตรวจสอบวันที่อัตโนมัติ (รวมถึง Leap Year)

---

### 2️⃣ ค้นหาข้อมูล

```
เลือก: 3

ค้นหาคำ (ชื่อเจ้าของ หรือ ที่อยู่): สมชาย

ชื่อเจ้าของ           | ที่อยู่                              | รายละเอียดซ่อม              | วันที่เริ่ม
----------------------------------------------------------------------------------------------------
สมชาย ใจดี            | 123 ถนนสุขุมวิท                      | ซ่อมหลังคารั่ว              | 2025-10-09

พบทั้งหมด 1 รายการ
```

**🔍 คุณสมบัติการค้นหา:**
- ไม่สนตัวพิมพ์เล็ก/ใหญ่ (Case-Insensitive)
- ค้นหาแบบ Partial Match (เช่น "สมชาย" จะตรงกับ "สมชาย ใจดี")
- ค้นหาทั้งชื่อเจ้าของและที่อยู่

---

### 3️⃣ แสดงข้อมูลทั้งหมด

```
เลือก: 1

ชื่อเจ้าของ           | ที่อยู่                              | รายละเอียดซ่อม              | วันที่เริ่ม
----------------------------------------------------------------------------------------------------
สมชาย ใจดี            | 123 ถนนสุขุมวิท                      | ซ่อมหลังคารั่ว              | 2025-10-09
สมหญิง ศรีสวัสดิ์      | 456 ถนนพระราม 4                      | ซ่อมท่อประปา                | 2025-10-10
อนันต์ คำดี           | 789 ถนนเพชรบุรี                      | ทาสีบ้าน                     | 2025-10-11
```

---

### 4️⃣ ลบข้อมูล

```
เลือก: 4

ป้อนชื่อเจ้าของที่ต้องการลบ: สมชาย
🗑️  ลบ: สมชาย ใจดี
✅ ลบข้อมูลเรียบร้อย 1 รายการ
```

**⚠️ คำเตือน:**
- การลบข้อมูลจะลบทันทีไม่สามารถกู้คืนได้
- หากมีหลายรายการที่ตรงกัน จะลบทั้งหมด
- แสดงรายชื่อที่ถูกลบก่อนดำเนินการ

---

## 🧪 การทดสอบ

### 🔬 Unit Tests

```
./unit_test.exe
```

**ผลลัพธ์:**
```
========== Running Unit Tests ==========
Testing utf8_strlen...
✅ utf8_strlen: PASSED
Testing trim_spaces...
✅ trim_spaces: PASSED
Testing validate_and_normalize_date...
✅ validate_and_normalize_date: PASSED
Testing is_leap_year...
✅ is_leap_year: PASSED
Testing max_days_in_month...
✅ max_days_in_month: PASSED
Testing utf8_icontains...
✅ utf8_icontains: PASSED
Testing has_comma...
✅ has_comma: PASSED

✅ All Unit Tests PASSED!
========================================
```

### 🔄 E2E Tests

```
./e2e_test.exe
```

**ผลลัพธ์:**
```
=== เริ่มการทดสอบ E2E ===
✅ สร้างไฟล์ CSV ใหม่เรียบร้อย
✅ เพิ่มข้อมูลจำลองแล้ว

📋 แสดงข้อมูลทั้งหมด:
[แสดงข้อมูล 3 รายการ]

🔍 ทดสอบค้นหาคำว่า 'Alice'
✅ พบ Alice จำนวน 1 รายการ

🛠️ ทดสอบอัปเดตวันที่ของ John Doe
✅ อัปเดตวันที่ของ John Doe เป็น 2025-12-31 เรียบร้อย

🗑️ ทดสอบลบข้อมูลของ Alice
✅ ลบข้อมูลของ Alice แล้ว 1 รายการ

📄 ตรวจสอบไฟล์หลังการทดสอบ:
[แสดงข้อมูลที่เหลือ]

=== ✅ การทดสอบ E2E เสร็จสิ้น ===
```

---

## 📁 โครงสร้างโปรเจกต์

```
📦 Final_Project/
│
├── 📄 repair.c                 # โค้ดหลักของโปรแกรม
│   ├── ⚙️ UTF-8 Utilities     # ฟังก์ชันจัดการ UTF-8
│   ├── 📅 Date Validation      # ตรวจสอบวันที่
│   ├── 📊 CSV Functions        # อ่าน/เขียน CSV
│   └── 🎯 Core Operations      # CRUD Operations
│
├── 📄 unit_test.c              # Unit Tests
│   ├── 🧪 Test utf8_strlen()
│   ├── 🧪 Test trim_spaces()
│   ├── 🧪 Test date_validation()
│   ├── 🧪 Test leap_year()
│   ├── 🧪 Test search_functions()
│   └── 🧪 Test csv_validation()
│
├── 📄 e2e_test.c               # End-to-End Tests
│   ├── 🔄 Test Add Record
│   ├── 🔄 Test Search
│   ├── 🔄 Test Update
│   ├── 🔄 Test Delete
│   └── 🔄 Test Full Workflow
│
├── 📄 repairs.csv              # ไฟล์ข้อมูล (สร้างอัตโนมัติ)
├── 📄 README.md                # เอกสารนี้
│
└── 🔧 Compiled Binaries
    ├── repair.exe              # โปรแกรมหลัก
    ├── unit_test.exe           # Unit Test Runner
    └── e2e_test.exe            # E2E Test Runner
```

### 📊 ตัวอย่างไฟล์ repairs.csv

```
ownername,address,RepairDetails,RepairStartDate
สมชาย ใจดี,123 ถนนสุขุมวิท แขวงคลองเตย เขตคลองเตย กรุงเทพฯ,ซ่อมหลังคารั่ว เปลี่ยนกระเบื้องใหม่,2025-10-09
สมหญิง ศรีสวัสดิ์,456 ถนนพระราม 4 แขวงปทุมวัน เขตปทุมวัน กรุงเทพฯ,ซ่อมท่อประปารั่ว,2025-10-10
อนันต์ คำดี,789 ถนนเพชรบุรี แขวงมักกะสัน เขตราชเทวี กรุงเทพฯ,ทาสีบ้านใหม่,2025-10-11
```

---

## 💡 รายละเอียดทางเทคนิค

### 🔐 UTF-8 Input Handling (Windows)

```
#ifdef _WIN32
int read_utf8_line(char *buffer, int size) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    WCHAR wbuf[MAX];
    DWORD read = 0;
    
    // อ่าน UTF-16 จาก Windows Console
    ReadConsoleW(hStdin, wbuf, MAX - 1, &read, NULL);
    
    // ลบ newline characters
    while (read > 0 && (wbuf[read-1] == L'\r' || wbuf[read-1] == L'\n')) {
        wbuf[--read] = 0;
    }
    
    // แปลง UTF-16 เป็น UTF-8
    int bytes = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, 
                                     buffer, size, NULL, NULL);
    return bytes > 0;
}
#endif
```

**💬 คำอธิบาย:**
1. Windows Console ใช้ UTF-16 เป็น encoding หลัก
2. `ReadConsoleW()` อ่านข้อมูลเป็น Wide Characters (UTF-16)
3. `WideCharToMultiByte()` แปลงเป็น UTF-8 สำหรับจัดเก็บ

---

### 📅 Date Validation System

```
int validate_and_normalize_date(const char *in, char *buff, size_t buffsz) {
    int y, m, d;
    char tmp;[1]
    
    // คัดลอกและลบช่องว่าง
    strncpy(tmp, in, sizeof(tmp) - 1);
    trim_spaces(tmp);
    
    // แยกวัน เดือน ปี
    if (sscanf(tmp, "%d-%d-%d", &y, &m, &d) != 3) return 0;
    
    // ตรวจสอบเดือน (1-12)
    if (m < 1 || m > 12) return 0;
    
    // ตรวจสอบวัน (รวมถึง Leap Year)
    if (d < 1 || d > max_days_in_month(y, m)) return 0;
    
    // Normalize เป็น YYYY-MM-DD
    snprintf(buff, buffsz, "%04d-%02d-%02d", y, m, d);
    return 1;
}
```

**✅ การตรวจสอบ:**
- รูปแบบวันที่ต้องเป็น `YYYY-MM-DD`
- เดือนต้องอยู่ระหว่าง 1-12
- วันต้องถูกต้องตามเดือน (เช่น กุมภาพันธ์ 29 วัน ต้องเป็นปีอธิกสุรทิน)
- Normalize วันที่ให้มี leading zeros (เช่น `2025-1-9` → `2025-01-09`)

---

### 🔒 CSV Injection Protection

```
int has_comma(const char *s) {
    return s && strchr(s, ',') != NULL;
}

// ตรวจสอบก่อนบันทึก
if (has_comma(r.owner) || has_comma(r.address) || 
    has_comma(r.details) || has_comma(r.date)) {
    printf("❌ ห้ามใช้เครื่องหมายจุลภาค (,)\n");
    return;
}
```

**🛡️ ป้องกัน:**
- CSV Injection โดยการห้ามใช้ `,` ในข้อมูล
- ป้องกันการแยก column ผิดพลาด
- ทำให้ไฟล์ CSV สามารถเปิดใน Excel ได้โดยไม่มีปัญหา

---

### 🔍 Case-Insensitive Search

```
int utf8_icontains(const char *hay, const char *needle) {
    if (!hay || !needle) return 0;
    
    char hbuf, nbuf;
    
    // แปลงเป็นตัวพิมพ์เล็กทั้งหมด
    utf8_tolower_copy(hay, hbuf, sizeof(hbuf));
    utf8_tolower_copy(needle, nbuf, sizeof(nbuf));
    
    // ค้นหา
    return strstr(hbuf, nbuf) != NULL;
}
```

**🎯 ข้อดี:**
- ค้นหาได้ไม่ว่าจะพิมพ์ตัวพิมพ์เล็กหรือใหญ่
- รองรับ Partial Match (ค้นหาบางส่วน)
- ทำงานกับภาษาไทยได้ถูกต้อง

---

## ❓ แก้ปัญหาที่พบบ่อย

### 🔴 ปัญหา: ภาษาไทยแสดงเป็นอักขระแปลก ๆ

**สาเหตุ:** Console encoding ไม่ถูกต้อง

**✅ วิธีแก้:**
```
# ตั้งค่า UTF-8 ใน PowerShell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
chcp 65001

# หรือเพิ่มใน PowerShell Profile
notepad $PROFILE
# เพิ่มบรรทัดนี้:
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
```

---

### 🔴 ปัญหา: gcc command not found

**สาเหตุ:** MinGW ไม่ได้เพิ่มใน System PATH

**✅ วิธีแก้:**

**Windows 10/11:**
1. กด `Win + X` → เลือก "System"
2. คลิก "Advanced system settings"
3. คลิก "Environment Variables"
4. ใน "System variables" เลือก "Path" → คลิก "Edit"
5. คลิก "New" และเพิ่ม: `C:\mingw64\bin` (หรือตำแหน่งที่ติดตั้ง MinGW)
6. คลิก "OK" ทั้งหมด
7. **Restart Terminal**

**ตรวจสอบ:**
```
gcc --version
```

---

### 🔴 ปัญหา: ไฟล์ CSV ไม่ถูกสร้าง

**สาเหตุ:** Permission denied หรือ directory ไม่มีสิทธิ์เขียน

**✅ วิธีแก้:**

**Option 1: รันด้วย Administrator**
```
# คลิกขวาที่ PowerShell → Run as Administrator
cd C:\Users\YourName\Desktop\Final_Project
./repair.exe
```

**Option 2: เปลี่ยน Working Directory**
```
# ย้ายไปยัง directory ที่มีสิทธิ์เขียน
cd ~/Desktop
./repair.exe
```

**Option 3: ตรวจสอบ Antivirus**
- Antivirus บางตัวอาจบล็อกการสร้างไฟล์ .csv
- เพิ่ม folder โปรเจกต์ลงใน Whitelist

---

### 🔴 ปัญหา: Unit Test ล้มเหลว

**สาเหตุ:** ไฟล์ `repairs.csv` มีข้อมูลเก่าที่ขัดแย้ง

**✅ วิธีแก้:**
```
# ลบไฟล์ CSV แล้วรันใหม่
rm repairs.csv
./unit_test.exe
```

---

### 🔴 ปัญหา: การค้นหาไม่เจอข้อมูล

**สาเหตุ:** ข้อมูลมี leading/trailing spaces

**✅ วิธีแก้:**
- โปรแกรมมี `trim_spaces()` อัตโนมัติ
- หากยังไม่ได้ผล ลองดูข้อมูลจริงใน `repairs.csv`
- ตรวจสอบว่าไม่มี invisible characters

```
# ดูข้อมูลใน CSV
cat repairs.csv
# หรือ
notepad repairs.csv
```

---

### 🔴 ปัญหา: Compilation Error

**สาเหตุ:** ไฟล์ source code ไม่ครบหรือเสีย

**✅ วิธีแก้:**
```
# ตรวจสอบไฟล์ทั้งหมด
ls -la *.c

# ควรเห็น:
# repair.c
# unit_test.c
# e2e_test.c

# หากขาดไฟล์ ให้ Clone ใหม่
git clone https://github.com/yod2803/Final_Project.git
```

---

## 🤝 การมีส่วนร่วม

ยินดีรับ Contribution! โปรดทำตามขั้นตอนต่อไปนี้:

### 📝 ขั้นตอนการ Contribute

1. **Fork Repository**
   ```
   # คลิก Fork บน GitHub
   # Clone fork ของคุณ
   git clone https://github.com/YOUR_USERNAME/Final_Project.git
   cd Final_Project
   ```

2. **สร้าง Feature Branch**
   ```
   git checkout -b feature/AmazingFeature
   ```

3. **เขียนโค้ดและทดสอบ**
   ```
   # แก้ไขโค้ด
   # รัน Unit Tests
   ./unit_test.exe
   # รัน E2E Tests
   ./e2e_test.exe
   ```

4. **Commit การเปลี่ยนแปลง**
   ```
   git add .
   git commit -m "Add: AmazingFeature"
   ```

5. **Push ไปยัง Fork**
   ```
   git push origin feature/AmazingFeature
   ```

6. **สร้าง Pull Request**
   - ไปที่ GitHub repository ของคุณ
   - คลิก "New Pull Request"
   - เขียนอธิบายการเปลี่ยนแปลง

### 📜 Coding Guidelines

```
Encoding: UTF-8
Indentation: 4 spaces
Line Endings: LF (Unix style)
Comments: ภาษาไทยหรืออังกฤษก็ได้
Testing: ต้องมี Unit Test สำหรับฟังก์ชันใหม่
```

### 🎯 สิ่งที่ต้องการความช่วยเหลือ

- [ ] เพิ่มฟังก์ชันแก้ไขข้อมูล (Update)
- [ ] Export เป็น PDF หรือ Excel
- [ ] GUI Version (GTK+ หรือ Qt)
- [ ] Database Support (SQLite)
- [ ] Multi-language Support
- [ ] Backup/Restore Function

---

## 📜 License

```
MIT License

Copyright (c) 2025 Yodsapon Kaewklai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 📞 ติดต่อ

<div align="center">

**Yodsapon Kaewklai**

[![GitHub](https://img.shields.io/badge/GitHub-yod2803-181717?style=for-the-badge&logo=github)](https://github.com/yod2803)
[![Email](https://img.shields.io/badge/Email-Contact-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:your.email@example.com)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-0077B5?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/yourprofile)

**Project Link:** [https://github.com/yod2803/Final_Project](https://github.com/yod2803/Final_Project)

</div>

---

## 🙏 Acknowledgments

<table>
<tr>
<td align="center" width="33%">

### 📚 เอกสารอ้างอิง
[MinGW-w64](https://www.mingw-w64.org/)<br>
[Microsoft Docs](https://learn.microsoft.com/)<br>
[C Programming Guide](https://www.cprogramming.com/)

</td>
<td align="center" width="33%">

### 🛠️ เครื่องมือ
[Visual Studio Code](https://code.visualstudio.com/)<br>
[Git for Windows](https://git-scm.com/)<br>
[Windows Terminal](https://aka.ms/terminal)

</td>
<td align="center" width="33%">

### 💡 แรงบันดาลใจ
[Best-README-Template](https://github.com/othneildrew/Best-README-Template)<br>
[Awesome README](https://github.com/matiassingers/awesome-readme)<br>
[C Projects](https://github.com/topics/c-projects)

</td>
</tr>
</table>

---

## 📊 สถิติโปรเจกต์

<div align="center">

![GitHub repo size](https://img.shields.io/github/repo-size/yod2803/Final_Project?style=for-the-badge)
![GitHub code size](https://img.shields.io/github/languages/code-size/yod2803/Final_Project?style=for-the-badge)
![Lines of code](https://img.shields.io/tokei/lines/github/yod2803/Final_Project?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/yod2803/Final_Project?style=for-the-badge)

</div>

---

<div align="center">

### 🌟 ถ้าโปรเจกต์นี้มีประโยชน์ กรุณา Star ⭐ ให้กับ Repository นี้ด้วยนะครับ!

**Made with ❤️ and ☕ in Thailand**

[🔝 กลับไปด้านบน](#-home-repair-manager)

</div>
```

นี่คือ README.md ที่ **สมบูรณ์และสวยงาม** พร้อมใช้งานจริงสำหรับโปรเจกต์ของคุณ! 🎉

[1](https://www.deviqa.com/blog/how-to-build-e2e-test-cases/)
