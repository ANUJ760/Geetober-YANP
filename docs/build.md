# Building and Packaging YANP

This document provides instructions for configuring, building, testing, and packaging **YANP (Yet Another Notepad)** across Linux, Windows, and macOS.

---

## 1. Prerequisites

### All Platforms
- **CMake:** Version 3.16 or later (3.20+ recommended for CMake Presets).
- **C++20 Compiler:**
  - Linux: GCC 11+ or Clang 13+
  - Windows: MSVC 2019+ (Visual Studio 2022 recommended) or MinGW-w64 with GCC 11+
  - macOS: Apple Clang 13+ (Xcode 13+)
- **Qt 6 Framework:**
  - `Qt6::Core`
  - `Qt6::Gui`
  - `Qt6::Widgets`
  - `Qt6::PrintSupport`
  - `Qt6::Test` (for test suite)

---

## 2. Building on Linux

### Install Dependencies
On Fedora / RHEL / CentOS Stream:
```bash
sudo dnf install gcc-c++ cmake ninja-build qt6-qtbase-devel
```

On Ubuntu / Debian:
```bash
sudo apt update
sudo apt install build-essential cmake ninja-build qt6-base-dev qt6-base-dev-tools
```

### Configure and Build
```bash
# Using CMake directly
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Or using CMake presets
cmake --preset release
cmake --build --preset release
```

### Running Tests
```bash
ctest --test-dir build --output-on-failure
```

### Packaging on Linux
To install or package into a local directory:
```bash
DESTDIR=package cmake --install build
```
You can generate AppImage or Flatpak distributions using standard Qt6 runtimes.

---

## 3. Building on Windows

### Environment Setup
1. Install **Visual Studio 2022** with the **Desktop development with C++** workload.
2. Install **Qt 6** using the Qt Online Installer (MSVC 2022 64-bit component) or via `vcpkg`:
   ```cmd
   vcpkg install qtbase:x64-windows
   ```
3. Ensure CMake is in your system `PATH`.

### Configure and Build
Open "x64 Native Tools Command Prompt for VS 2022":
```cmd
cmake -B build -S . -DCMAKE_PREFIX_PATH="C:\Qt\6.x.x\msvc2022_64"
cmake --build build --config Release
```

### Running Tests
```cmd
ctest --test-dir build -C Release --output-on-failure
```

### Windows Deployment
Use `windeployqt` to bundle required Qt DLLs:
```cmd
windeployqt build\Release\YANP.exe
```

---

## 4. Building on macOS

### Environment Setup
1. Install **Xcode** and command line tools:
   ```bash
   xcode-select --install
   ```
2. Install Qt 6 via Homebrew or official installer:
   ```bash
   brew install qt@6 cmake
   ```

### Configure and Build
```bash
cmake -B build -S . -DCMAKE_PREFIX_PATH="$(brew --prefix qt@6)" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
This produces `build/YANP.app`.

### Running Tests
```bash
ctest --test-dir build --output-on-failure
```

### macOS Deployment
Use `macdeployqt` to package dependencies into the application bundle:
```bash
macdeployqt build/YANP.app -dmg
```
For signing and notarization:
```bash
codesign --deep --force --verify --verbose --sign "Developer ID Application: Your Name" build/YANP.app
xcrun notarytool submit build/YANP.dmg --keychain-profile "notary-profile" --wait
```
