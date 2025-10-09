<div align="center">

# 🏠 Home Repair Manager

![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge\&logo=c\&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge\&logo=windows\&logoColor=white)
![UTF-8](https://img.shields.io/badge/Encoding-UTF--8-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**ระบบจัดการข้อมูลการซ่อมแซมบ้านผ่าน CLI พร้อมรองรับภาษาไทย UTF-8 เต็มรูปแบบ**

[คุณสมบัติ](#-คุณสมบัติหลัก) • [การติดตั้ง](#-การติดตั้ง) • [วิธีใช้งาน](#-วิธีใช้งาน) • [การทดสอบ](#-การทดสอบ) • [โครงสร้าง](#-โครงสร้างโปรเจกต์)

</div>

---

## 🔗 ลิงก์ที่เกี่ยวข้อง

* **GitHub:** [https://github.com/yod2803/Final_Project](https://github.com/yod2803/Final_Project)
* **License:** MIT

---

## 🌟 คุณสมบัติหลัก

* เพิ่ม/ค้นหา/ลบข้อมูลการซ่อมแซมบ้านจากไฟล์ CSV
* รองรับการใช้งานภาษาไทย (UTF-8)
* ตรวจสอบความถูกต้องของวันที่และข้อมูล
* รองรับ Unit Test และ E2E Test
* ป้องกัน CSV Injection และ Error ในการบันทึกไฟล์

---

## 🔧 การติดตั้งและการคอมไพล์

```bash
git clone https://github.com/yod2803/Final_Project.git
cd Final_Project
gcc -DBUILD_MAIN -o repair.exe repair.c
gcc -o unit_test.exe unit_test.c repair.c
gcc -o e2e_test.exe e2e_test.c repair.c
```

---

## 🚀 วิธีใช้งาน
### กรณีใช้ cmd 
```bash
repair.exe
```
### กรณีใช้ power shell
```bash
./repair.exe
```


**เมนูหลัก:**

```
=== 🏠 Home Repair Manager ===
1. แสดงข้อมูลทั้งหมด
2. เพิ่มข้อมูลใหม่
3. ค้นหา (ชื่อ/ที่อยู่)
4. ลบข้อมูล
0. ออกโปรแกรม
```

---

## 🧪 การทดสอบ

### Unit Test

```bash
./unit_test.exe
```

### E2E Test

```bash
./e2e_test.exe
```

---

## 🗂️ โครงสร้างโปรเจกต์

```
Final_Project/
├── repair.c          # โค้ดหลัก
├── unit_test.c       # ทดสอบหน่วยย่อย
├── e2e_test.c        # ทดสอบระบบเต็มรูปแบบ
├── repairs.csv       # ไฟล์ข้อมูล
└── README.md         # เอกสารโปรเจกต์
```

---

## 📖 License

โครงการนี้เผยแพร่ภายใต้สัญญาอนุญาต **MIT License**.

---

<div align="center">

### 🌟 หากโปรเจกต์นี้มีประโยชน์ อย่าลืมกด Star ⭐ บน GitHub!

**Made with ❤️ in Thailand**

</div>
