# ChronoLog

C++17 ile yazılmış, thread-safe bir logging kütüphanesi. Konsol ve dosya çıktısı, seviye filtreleme ve renkli log desteği sunar.

## Özellikler

- **4 log seviyesi:** DEBUG, INFO, WARNING, ERROR
- **Konsol + dosya çıktısı** (ayrı ayrı açılıp kapatılabilir)
- **Seviye filtreleme** — yapılandırılan eşiğin altındaki loglar yazılmaz
- **Renkli konsol çıktısı** (ANSI escape kodları)
- **Thread-safe** — `std::mutex` ile korumalı
- **Otomatik bağlam** — makrolar dosya, satır ve fonksiyon bilgisini ekler

## Mimari & Pattern'ler

| Yaklaşım | Nerede | Açıklama |
|----------|--------|----------|
| **Meyers Singleton** | `Logger::GetInstance()` | Tek global logger örneği, lazy init |
| **Macro API** | `INFO_LOG`, `DEBUG_LOG`, … | `__FILE__`, `__LINE__`, `__FUNCTION__` otomatik yakalanır |
| **Config struct** | `LoggerConfig` | Çıktı hedefleri ve minimum log seviyesi |
| **Context struct** | `LogContext` | Her log satırının taşıdığı metadata |
| **Lookup table** | `LogLevelInfo::infoArray` | Seviye → etiket + renk eşlemesi |
| **RAII** | `std::lock_guard` | Log yazımında thread güvenliği |

## Proje Yapısı

```
include/
  Logger.h          — Ana sınıf ve makrolar
  LoggerConfig.h    — Yapılandırma
  LogContext.h      — Log metadata
  LogLevelInfo.h    — Seviye tanımları
  ConsoleColor.h    — ANSI renk kodları
src/
  Logger.cpp
  ConsoleColor.cpp
main.cpp            — Örnek kullanım
```

## Derleme

**Gereksinimler:** CMake ≥ 3.17, C++17 destekleyen derleyici

```bash
./build.sh
# veya
cmake -S . -B build && cmake --build build
```

Çalıştırma:

```bash
./build/LoggerExample
```

## Kullanım

```cpp
#include "Logger.h"

int main() {
    Logger::LoggerConfig config;
    config.enableConsole = true;
    config.enableFile   = true;
    config.logFile      = "app.log";
    config.logLevel     = LogLevelInfo::LOG_LEVEL::INFO;

    auto& logger = Logger::Logger::GetInstance();
    logger.Configure(config);
    logger.OpenLogFile();

    Logger::INFO_LOG("Uygulama başladı");
    Logger::DEBUG_LOG("Bu satır INFO eşiğinde filtrelenir");
    Logger::WARNING_LOG("Dikkat");
    Logger::ERROR_LOG("Bir hata oluştu");

    return 0;
}
```

### Log formatı

```
2026-07-08 12:45:30.042 [INFO] (main@main.cpp:21) Uygulama başladı
```

Konsolda seviye etiketi renklidir; dosyaya düz metin yazılır.

## Kendi Projenize Ekleme

CMake projenize kütüphaneyi ekleyin:

```cmake
add_subdirectory(path/to/ChronoLog)
target_link_libraries(YourTarget PRIVATE Logger)
```

## Lisans

Bu proje [LICENSE](LICENSE) dosyasındaki koşullar altında dağıtılır.

---

# ChronoLog (English)

A thread-safe logging library written in C++17. Supports console and file output, level filtering, and colored logs.

## Features

- **4 log levels:** DEBUG, INFO, WARNING, ERROR
- **Console + file output** (each can be enabled independently)
- **Level filtering** — logs below the configured threshold are dropped
- **Colored console output** (ANSI escape codes)
- **Thread-safe** — protected with `std::mutex`
- **Automatic context** — macros capture file, line, and function info

## Architecture & Patterns

| Approach | Where | Description |
|----------|-------|-------------|
| **Meyers Singleton** | `Logger::GetInstance()` | Single global logger instance, lazy init |
| **Macro API** | `INFO_LOG`, `DEBUG_LOG`, … | `__FILE__`, `__LINE__`, `__FUNCTION__` captured automatically |
| **Config struct** | `LoggerConfig` | Output targets and minimum log level |
| **Context struct** | `LogContext` | Metadata carried by each log line |
| **Lookup table** | `LogLevelInfo::infoArray` | Level → label + color mapping |
| **RAII** | `std::lock_guard` | Thread safety during log writes |

## Project Structure

```
include/
  Logger.h          — Main class and macros
  LoggerConfig.h    — Configuration
  LogContext.h      — Log metadata
  LogLevelInfo.h    — Level definitions
  ConsoleColor.h    — ANSI color codes
src/
  Logger.cpp
  ConsoleColor.cpp
main.cpp            — Example usage
```

## Build

**Requirements:** CMake ≥ 3.17, C++17-capable compiler

```bash
./build.sh
# or
cmake -S . -B build && cmake --build build
```

Run:

```bash
./build/LoggerExample
```

## Usage

```cpp
#include "Logger.h"

int main() {
    Logger::LoggerConfig config;
    config.enableConsole = true;
    config.enableFile   = true;
    config.logFile      = "app.log";
    config.logLevel     = LogLevelInfo::LOG_LEVEL::INFO;

    auto& logger = Logger::Logger::GetInstance();
    logger.Configure(config);
    logger.OpenLogFile();

    Logger::INFO_LOG("Application started");
    Logger::DEBUG_LOG("This line is filtered at INFO threshold");
    Logger::WARNING_LOG("Warning");
    Logger::ERROR_LOG("An error occurred");

    return 0;
}
```

### Log format

```
2026-07-08 12:45:30.042 [INFO] (main@main.cpp:21) Application started
```

Level labels are colored in the console; plain text is written to the file.

## Adding to Your Project

Add the library to your CMake project:

```cmake
add_subdirectory(path/to/ChronoLog)
target_link_libraries(YourTarget PRIVATE Logger)
```

## License

This project is distributed under the terms in [LICENSE](LICENSE).
