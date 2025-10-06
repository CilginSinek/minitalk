# 🗣️ Minitalk

![42 School Project](https://img.shields.io/badge/42-Project-blue)
![Language](https://img.shields.io/badge/Language-C-brightgreen)
![Norminette](https://img.shields.io/badge/Norminette-Passing-success)

> *A messaging program using UNIX signals for inter-process communication*  
> *Süreçler arası iletişim için UNIX sinyalleri kullanarak bir mesajlaşma programı*

---

[🇬🇧 English](#english) | [🇹🇷 Türkçe](#turkish)

---

<a name="english"></a>
# 🇬🇧 English Version

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [How It Works](#-how-it-works)
- [Bonus Features](#-bonus-features)
- [Technical Details](#-technical-details)
- [Learning Outcomes](#-learning-outcomes)
- [Testing](#-testing)

---

## 🎯 About the Project

**Minitalk** is a project from the 42 School curriculum that teaches inter-process communication (IPC). This project aims to create a client-server architecture using UNIX signals (`SIGUSR1` and `SIGUSR2`).

### Goals
- Understand and use UNIX signals
- Practice bit manipulation
- Learn inter-process communication mechanisms
- Gain experience with client-server architecture

---

## ✨ Features

### Mandatory Features
- ✅ **Server**: Prints its PID on startup and receives messages
- ✅ **Client**: Sends string messages to the server
- ✅ **Uses only SIGUSR1 and SIGUSR2**
- ✅ **Fast and reliable communication**
- ✅ **Unicode support**

### Bonus Features
- ⭐ **Acknowledgment Mechanism**: Server confirms each bit received
- ⭐ **Character Counter**: Displays the number of characters transmitted
- ⭐ **Advanced Error Handling**: Timeout and error checks

---

## 🔧 Installation

### Requirements
- GCC compiler
- Make
- UNIX/Linux system (macOS or Linux)

### Compilation

```bash
# Compile mandatory version
make

# Compile bonus version
make bonus

# Clean
make clean      # Remove object files
make fclean     # Remove all build outputs
make re         # Recompile
```

These commands will create:
- `server` / `server_bonus`
- `client` / `client_bonus`

---

## 🚀 Usage

### 1. Start the Server

```bash
./server
```

The server will print its PID (Process ID):
```
12345
```

### 2. Send Messages with Client

```bash
./client [SERVER_PID] [MESSAGE]
```

**Example:**
```bash
./client 12345 "Hello World!"
```

### Bonus Version Usage

```bash
# Start the server
./server_bonus

# Send a message
./client_bonus 12345 "This is a test message! 🚀"
```

The bonus client will print the number of characters sent.

---

## 🔍 How It Works

### Communication Protocol

1. **Bit-Level Transmission**
   - Each character is split into 8 bits
   - Each bit is sent as a separate signal
   - `SIGUSR1` = bit 0
   - `SIGUSR2` = bit 1

2. **Character Transmission**
   ```
   Character: 'A' (ASCII 65 = 0b01000001)
   
   Bit 7 (0) → SIGUSR1
   Bit 6 (1) → SIGUSR2
   Bit 5 (0) → SIGUSR1
   Bit 4 (0) → SIGUSR1
   Bit 3 (0) → SIGUSR1
   Bit 2 (0) → SIGUSR1
   Bit 1 (0) → SIGUSR1
   Bit 0 (1) → SIGUSR2
   ```

3. **Acknowledgment Mechanism (Bonus)**
   - Server confirms each bit with `SIGUSR2`
   - Sends `SIGUSR1` when message is complete
   - Client performs timeout check (1 second)

### Flow Diagram

```
CLIENT                          SERVER
  |                               |
  |-- Connect with PID ---------→ |
  |                               |
  |-- Send bit (SIGUSR1/2) -----→ |
  |                               |
  | ←--- Acknowledge (SIGUSR2) ---|
  |                               |
  |-- Next bit ----------------→  |
  |                               |
  | ←--- Character complete ------|
  |                               |
  | ←--- Message complete (SIGUSR1)
```

---

## ⭐ Bonus Features

### 1. Acknowledgment Mechanism
After each bit transmission, the server sends a `SIGUSR2` signal to the client as confirmation. This increases reliability and prevents message loss.

### 2. Character Counter
The client prints the number of characters sent after completing message transmission:

```bash
./client_bonus 12345 "Hello"
# Server output:
Hello

# Client output:
5
```

### 3. Timeout and Error Handling
- Client waits 1 second timeout for each bit
- Program exits with error if no acknowledgment received
- This prevents hanging communications

---

## 🛠️ Technical Details

### File Structure

```
minitalk/
│
├── client.c              # Basic client implementation
├── client_bonus.c        # Bonus client (with acknowledgment)
├── server.c              # Basic server implementation
├── server_bonus.c        # Bonus server (sends acknowledgment)
├── utils.c               # Helper functions (ft_atoi, ft_putnbr, etc.)
├── minitalk.h            # Header file
├── Makefile              # Build rules
└── README.md             # This file
```

### Functions Used

#### Allowed System Functions
- `write()` - Output printing
- `signal()` / `sigaction()` - Signal management
- `sigemptyset()` / `sigaddset()` - Signal set operations
- `kill()` - Send signals
- `getpid()` - Get process ID
- `pause()` - Wait for signals
- `sleep()` / `usleep()` - Sleep
- `exit()` - Exit program

#### Custom Functions
- `ft_atoi()` - Convert string to integer
- `ft_putchar()` - Print character
- `ft_putnbr()` - Print number

### Bit Manipulation

**Extract Bit:**
```c
bit = (character >> (7 - i)) & 1;
```

**Add Bit:**
```c
character |= (sig == SIGUSR2);
character = character << 1;
```

### Signal Safety

The project uses `volatile sig_atomic_t` type for signal-safe variables:
```c
volatile sig_atomic_t g_ack_received;
```

This ensures safe communication between signal handlers and the main program.

---

## 🎓 Learning Outcomes

- 🔸 **UNIX Signals**: SIGUSR1, SIGUSR2
- 🔸 **Bit Manipulation**: Bitwise operators
- 🔸 **Process Management**: PID, fork, kill
- 🔸 **Asynchronous Programming**: Signal handlers
- 🔸 **Client-Server Architecture**: IPC design
- 🔸 **Error Handling**: Timeout, error handling
- 🔸 **Unicode Support**: Multi-byte characters

---

## 📝 Notes

- Project complies with 42 School Norm standards
- All code is memory leak-free (tested with Valgrind)
- Functions do not exceed 25 lines
- Global variables are used only in signal handlers

---

## 🏆 Testing

To test the project:

1. Open two terminal windows
2. Start the server in the first terminal
3. Send messages with the client in the second terminal
4. Try long texts, Unicode characters, and special characters

**Test Examples:**
```bash
# Simple text
./client [PID] "Hello, World!"

# Unicode characters
./client [PID] "Hello 🌍"

# Long text
./client [PID] "This is a very long test message..."

# Special characters
./client [PID] "!@#$%^&*()"
```

---

## 👤 Author

- **iduman** - 42 Istanbul

---

## � License

This project is part of the 42 Network education program.

---

## 🙏 Acknowledgments

Thanks to the 42 Istanbul community and everyone who helped me develop this project!

---

<a name="turkish"></a>
# 🇹🇷 Türkçe Versiyon

## �📋 İçindekiler

- [Proje Hakkında](#-proje-hakkında)
- [Özellikler](#-özellikler)
- [Kurulum](#-kurulum)
- [Kullanım](#-kullanım)
- [Nasıl Çalışır](#-nasıl-çalışır)
- [Bonus Özellikler](#-bonus-özellikler)
- [Teknik Detaylar](#-teknik-detaylar)
- [Öğrenilen Kavramlar](#-öğrenilen-kavramlar)
- [Test Etme](#-test-etme)

---

## 🎯 Proje Hakkında

**Minitalk**, 42 School müfredatının bir parçası olan ve süreçler arası iletişim (IPC) konusunu öğreten bir projedir. Bu proje, UNIX sinyalleri (`SIGUSR1` ve `SIGUSR2`) kullanarak bir istemci-sunucu mimarisi oluşturmayı amaçlar.

### Amaç
- UNIX sinyallerini anlamak ve kullanmak
- Bit manipülasyonu pratiği yapmak
- Süreçler arası iletişim mekanizmalarını öğrenmek
- İstemci-sunucu mimarisi deneyimi kazanmak

---

## ✨ Özellikler

### Temel Özellikler (Mandatory)
- ✅ **Server**: Başlatıldığında PID'sini yazdırır ve mesajları alır
- ✅ **Client**: Server'a string mesajlar gönderir
- ✅ **Sadece SIGUSR1 ve SIGUSR2 kullanımı**
- ✅ **Hızlı ve güvenilir iletişim**
- ✅ **Unicode desteği**

### Bonus Özellikler
- ⭐ **Onay Mekanizması**: Her bit için server'dan onay
- ⭐ **Karakter Sayacı**: İletilen karakter sayısını gösterir
- ⭐ **Gelişmiş Hata Yönetimi**: Timeout ve hata kontrolleri

---

## 🔧 Kurulum

### Gereksinimler
- GCC derleyicisi
- Make
- UNIX/Linux sistemi (macOS veya Linux)

### Derleme

```bash
# Temel sürümü derlemek için
make

# Bonus sürümü derlemek için
make bonus

# Temizlik
make clean      # Object dosyalarını sil
make fclean     # Tüm derleme çıktılarını sil
make re         # Yeniden derle
```

Bu komutlar şu dosyaları oluşturacaktır:
- `server` / `server_bonus`
- `client` / `client_bonus`

---

## 🚀 Kullanım

### 1. Server'ı Başlatma

```bash
./server
```

Server başlatıldığında PID'sini (Process ID) ekrana yazdıracaktır:
```
12345
```

### 2. Client ile Mesaj Gönderme

```bash
./client [SERVER_PID] [MESSAGE]
```

**Örnek:**
```bash
./client 12345 "Merhaba Dünya!"
```

### Bonus Sürüm Kullanımı

```bash
# Server'ı başlat
./server_bonus

# Client ile mesaj gönder
./client_bonus 12345 "Bu bir test mesajıdır! 🚀"
```

Bonus sürümde client, gönderilen karakter sayısını ekrana yazdıracaktır.

---

## 🔍 Nasıl Çalışır

### İletişim Protokolü

1. **Bit Seviyesinde İletim**
   - Her karakter 8 bite ayrılır
   - Her bit ayrı bir sinyal olarak gönderilir
   - `SIGUSR1` = bit 0
   - `SIGUSR2` = bit 1

2. **Karakter Gönderimi**
   ```
   Karakter: 'A' (ASCII 65 = 0b01000001)
   
   Bit 7 (0) → SIGUSR1
   Bit 6 (1) → SIGUSR2
   Bit 5 (0) → SIGUSR1
   Bit 4 (0) → SIGUSR1
   Bit 3 (0) → SIGUSR1
   Bit 2 (0) → SIGUSR1
   Bit 1 (0) → SIGUSR1
   Bit 0 (1) → SIGUSR2
   ```

3. **Onay Mekanizması (Bonus)**
   - Server her biti aldığında `SIGUSR2` ile onaylar
   - Mesaj tamamlandığında `SIGUSR1` gönderir
   - Client, onay beklerken timeout kontrolü yapar (1 saniye)

### Akış Diyagramı

```
CLIENT                          SERVER
  |                               |
  |-- PID ile bağlan -----------→ |
  |                               |
  |-- Bit gönder (SIGUSR1/2) ---→ |
  |                               |
  | ←--- Onay (SIGUSR2) ----------|
  |                               |
  |-- Sonraki bit -------------→  |
  |                               |
  | ←--- Karakter tamamlandı -----|
  |                               |
  | ←--- Mesaj tamamlandı (SIGUSR1)
```

---

## ⭐ Bonus Özellikler

### 1. Onay Mekanizması
Her bit iletiminden sonra server, client'a `SIGUSR2` sinyali göndererek alındı onayı verir. Bu, güvenilirliği artırır ve mesaj kaybını önler.

### 2. Karakter Sayacı
Client, mesaj iletimini tamamladıktan sonra gönderilen karakter sayısını ekrana yazdırır:

```bash
./client_bonus 12345 "Hello"
# Server çıktısı:
Hello

# Client çıktısı:
5
```

### 3. Timeout ve Hata Yönetimi
- Client, her bit için 1 saniye timeout süresi bekler
- Onay alınmazsa program hata ile sonlanır
- Bu, askıda kalan iletişimleri önler

---

## 🛠️ Teknik Detaylar

### Dosya Yapısı

```
minitalk/
│
├── client.c              # Temel client implementasyonu
├── client_bonus.c        # Bonus client (onay mekanizmalı)
├── server.c              # Temel server implementasyonu
├── server_bonus.c        # Bonus server (onay gönderimli)
├── utils.c               # Yardımcı fonksiyonlar (ft_atoi, ft_putnbr, vb.)
├── minitalk.h            # Header dosyası
├── Makefile              # Derleme kuralları
└── README.md             # Bu dosya
```

### Kullanılan Fonksiyonlar

#### İzin Verilen Sistem Fonksiyonları
- `write()` - Çıktı yazdırma
- `signal()` / `sigaction()` - Sinyal yönetimi
- `sigemptyset()` / `sigaddset()` - Sinyal set işlemleri
- `kill()` - Sinyal gönderme
- `getpid()` - Process ID alma
- `pause()` - Sinyal bekleme
- `sleep()` / `usleep()` - Bekleme
- `exit()` - Program sonlandırma

#### Özel Fonksiyonlar
- `ft_atoi()` - String'i integer'a çevirme
- `ft_putchar()` - Karakter yazdırma
- `ft_putnbr()` - Sayı yazdırma

### Bit Manipülasyonu

**Bit Çıkarma:**
```c
bit = (character >> (7 - i)) & 1;
```

**Bit Ekleme:**
```c
character |= (sig == SIGUSR2);
character = character << 1;
```

### Sinyal Güvenliği

Proje, `volatile sig_atomic_t` tipini kullanarak sinyal güvenli değişkenler tanımlar:
```c
volatile sig_atomic_t g_ack_received;
```

Bu, sinyal işleyicileri ve ana program arasında güvenli iletişim sağlar.

---

## 🎓 Öğrenilen Kavramlar

- 🔸 **UNIX Sinyalleri**: SIGUSR1, SIGUSR2
- 🔸 **Bit Manipülasyonu**: Bitwise operatörler
- 🔸 **Süreç Yönetimi**: PID, fork, kill
- 🔸 **Asenkron Programlama**: Sinyal işleyiciler
- 🔸 **İstemci-Sunucu Mimarisi**: IPC tasarımı
- 🔸 **Hata Yönetimi**: Timeout, error handling
- 🔸 **Unicode Desteği**: Çok baytlı karakterler

---

## 📝 Notlar

- Proje 42 School Norm kurallarına uygun olarak yazılmıştır
- Tüm kod bellek sızıntısından arındırılmıştır (Valgrind ile test edilmiştir)
- Fonksiyonlar 25 satırı geçmemektedir
- Global değişkenler yalnızca sinyal işleyicilerde kullanılmıştır

---

## 🏆 Test Etme

Projeyi test etmek için:

1. İki terminal penceresi açın
2. Birinci terminalde server'ı başlatın
3. İkinci terminalde client ile mesajlar gönderin
4. Uzun metinler, Unicode karakterler ve özel karakterler deneyin

**Test Örnekleri:**
```bash
# Basit metin
./client [PID] "Hello, World!"

# Unicode karakterler
./client [PID] "Merhaba 🌍"

# Uzun metin
./client [PID] "Bu çok uzun bir test mesajıdır..."

# Özel karakterler
./client [PID] "!@#$%^&*()"
```

---

## 👤 Yazar

- **iduman** - 42 İstanbul

---

## 📄 Lisans

Bu proje 42 Network eğitim programının bir parçasıdır.

---

## 🙏 Teşekkürler

42 İstanbul topluluğuna ve bu projeyi geliştirmeme yardımcı olan herkese teşekkürler!

---

**Note / Not**: This project is for educational purposes and is part of the 42 School curriculum. 🚀  
**Bu proje eğitim amaçlıdır ve 42 School müfredatının bir parçasıdır. 🚀**
