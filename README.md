# 📂 C Projeleri Koleksiyonu (C Projects Collection)

Bu depo, C programlama dili kullanılarak geliştirilmiş algoritmik oyun projelerimi ve veri yapıları uygulamalarımı içermektedir. 

Projelerin her biri farklı teknik yeteneklere (Veri Yapıları, Dosya İşlemleri, Bellek Yönetimi) odaklanmaktadır.

---

## 🚀 Projeler

### 1. 🐍 Yılan Oyunu (Snake Game)
Klasik yılan oyununun **Veri Yapıları** kullanılarak yeniden tasarlanmış, gelişmiş bir versiyonudur.

* **Klasör:** `/YilanOyunu`
* **Kullanılan Veri Yapıları:**
    * **Bağlı Liste (Linked List):** Yılanın uzayan gövdesini dinamik olarak yönetmek için kullanılmıştır. Dizi yerine bağlı liste kullanılarak bellek verimliliği sağlanmıştır.
    * **İkili Arama Ağacı (Binary Search Tree - BST):** Oyun boyunca yenen yemeklerin koordinatları (X, Y) ve türleri bir BST üzerinde tutulur. Oyun bittiğinde bu ağaç **Recursive (Özyinelemeli)** olarak dolaşılarak raporlanır.
* **Teknik Özellikler:**
    * `windows.h` kütüphanesi ile konsol imleç yönetimi.
    * Dinamik bellek yönetimi (`malloc`, `free`).
    * Gerçek zamanlı klavye kontrolü.

### 2. 💰 Kim Milyoner Olmak İster? (Quiz Game)
Popüler bilgi yarışmasının konsol tabanlı simülasyonudur. Oyun mantığı ve dosya okuma işlemleri üzerine kuruludur.

* **Klasör:** `/MilyonerOyunu`
* **Özellikler:**
    * **Dosya İşlemleri (File I/O):** Sorular kodun içine gömülü değildir; harici bir `question.csv` veritabanından dinamik olarak okunur (`strtok` ile parsing).
    * **Oyun Mantığı:** 50/50 ve Çift Cevap (Double Dip) gibi joker hakları algoritmik olarak kodlanmıştır.
    * **Skor Kaydı:** Oyuncu kazançları `player_winnings.txt` dosyasına otomatik olarak kaydedilir ve geçmiş skorlar görüntülenebilir.

---

## 📂 Dosya Yapısı

```text
C-Projelerim/
│
├── 📂 YilanOyunu/
│   └── main.c          # Yılan oyunu kaynak kodu (Data Structures içerir)
│
├── 📂 MilyonerOyunu/
│   ├── main.c          # Milyoner oyunu kaynak kodu
│   └── question.csv    # Soru bankası dosyası
│
└── README.md           # Proje dokümantasyonu


💻 Kurulum ve Çalıştırma
Projeleri kendi bilgisayarınızda derlemek ve çalıştırmak için aşağıdaki adımları izleyebilirsiniz.

Yılan Oyunu İçin:
Bu proje windows.h kütüphanesini kullandığı için Windows işletim sisteminde çalıştırılmalıdır.
1.YilanOyunu klasörüne gidin.
2.Bir IDE (Code::Blocks, Dev-C++) veya GCC ile derleyin.
gcc main.c -o snake
./snake

Milyoner Oyunu İçin:
1.MilyonerOyunu klasörüne gidin.

2.Önemli: main.c dosyasını açın ve fopen fonksiyonundaki dosya yolunu kendi bilgisayarınızdaki question.csv konumuna göre güncelleyin.

3.Derleyip çalıştırın.
gcc main.c -o milyoner
./milyoner


👨‍💻 Geliştirici
Mine Akçakala

