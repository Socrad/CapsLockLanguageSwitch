# CapsLockLanguageSwitch

## English

### Overview
CapsLockLanguageSwitch is a utility that enhances the remote desktop experience for macOS users accessing Windows systems via apps like Parsec. macOS users are accustomed to using the CapsLock key for Korean-English input switching, but on Windows, CapsLock toggles uppercase/lowercase letters, leading to frequent input errors. This tool intercepts CapsLock key presses and sends a Korean-English toggle key signal to the Windows system, mimicking macOS behavior.

Written in C++, this application is built using CMake and runs in the Windows system tray. It provides a context menu (right-click on the tray icon) to enable/disable the functionality, set the app to launch on Windows startup, or exit the application.

### Features
- Converts CapsLock key presses to Korean-English input toggle on Windows.
- System tray integration with a context menu for:
  - Enabling/disabling the functionality.
  - Setting the app to run on Windows startup.
  - Exiting the application.
- Lightweight and efficient, built with C++ and CMake.

### Installation
**The following is executed on a Windows desktop.**
1. Download `CapsLockLanguageSwitcher.exe` from the [Releases page](https://github.com/Socrad/CapsLockLanguageSwitch/releases).
2. Run the executable to start the application.
3. The app will appear in the system tray.

### Or build from source code: 
**The following is executed on a Windows desktop.**

1. **Prerequisites**:
   - Windows 10 or later.
   - CMake 3.10 or higher.
   - A C++ compiler (e.g., MSVC, MinGW).
2. **Clone the repository**:
   ```bash
   git clone https://github.com/Socrad/CapsLockLanguageSwitch.git
   cd CapsLockLanguageSwitch
   ```
3. **Build the application**:

   **Using MSVC (Visual Studio)**:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
   **Using MinGW**:
   ```bash
   mkdir build && cd build
   cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake
   cmake --build .
   ```

4. **Run the application**:
   - Navigate to the build directory and run the generated executable (e.g., `CapsLockLanguageSwitcher.exe`).
   - The app will appear in the system tray.

### Usage
1. Launch `CapsLockLanguageSwitcher.exe`.
2. The app runs in the system tray (bottom-right corner of the Windows taskbar).
3. Right-click the tray icon to access the menu:
   - **Enable/Disable**: Toggle the CapsLock Switch functionality.
   - **Run at Startup**: Add or remove the app from Windows startup.
   - **Exit**: Close the application.
4. Press CapsLock to toggle Korean-English input while using a remote Windows desktop from a MacBook.

### License
This project is licensed under the [MIT License](LICENSE).

---

## 한국어

### 개요
CapsLockLanguageSwitch는 맥북에서 Parsec 등의 앱을 통해 Windows 데스크탑에 원격 접속할 때 CapsLock 키를 한영 전환 키로 사용하는 문제를 해결하는 유틸리티입니다. 맥 OS에서는 CapsLock 키로 한영 전환을 하지만, Windows에서는 CapsLock이 대소문자 전환을 하므로, 맥북 사용자가 Windows에서 한영 전환을 위해 CapsLock을 누르는 실수가 빈번히 발생합니다. 이 도구는 CapsLock 키 입력을 가로채어 Windows에서 한영 전환 키 신호를 보내, 맥 OS와 유사한 경험을 제공합니다.

C++로 작성되었으며, CMake로 빌드됩니다. 앱 실행 시 Windows 시스템 트레이에 아이콘이 표시되며, 아이콘을 우클릭하면 기능 활성/비활성, Windows 시작 시 자동 실행 설정, 앱 종료 옵션이 포함된 메뉴가 표시됩니다.

### 기능
- CapsLock 키를 Windows에서 한영 전환 키로 변환.
- 시스템 트레이 아이콘에서 다음 메뉴 제공:
  - 기능 활성/비활성 토글.
  - Windows 시작 시 앱 자동 실행 설정.
  - 앱 종료.
- 가볍고 효율적인 C++ 구현, CMake 빌드 지원.

### 설치
**Windows 데스크톱에서 실행합니다.**
1. [Releases 페이지](https://github.com/Socrad/CapsLockLanguageSwitch/releases)에서 `CapsLockLanguageSwitcher.exe`를 다운로드.
2. 실행 파일을 실행하여 앱을 시작.
3. 앱은 시스템 트레이에 표시됩니다.

### 또는 소스코드로 빌드 : 
**Windows 데스크톱에서 실행합니다.**

1. **준비물**:
   - Windows 10 이��.
   - CMake 3.10 이상.
   - C++ 컴파일러 (예: MSVC, MinGW).
2. **레포지토리 클론**:
   ```bash
   git clone https://github.com/Socrad/CapsLockLanguageSwitch.git
   cd CapsLockLanguageSwitch
   ```
3. **앱 빌드**:

   **MSVC (Visual Studio) 사용 시**:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
   **MinGW 사용 시**:
   ```bash
   mkdir build && cd build
   cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake
   cmake --build .
   ```
4. **앱 실행**:
   - 빌드 디렉토리에서 생성된 실행 파일(예: `CapsLockLanguageSwitcher.exe`)을 실행.
   - 시스템 트레이에 앱 아이콘이 표시됨.

### 사용법
1. `CapsLockLanguageSwitcher.exe`를 실행.
2. Windows 작업 표시줄 오른쪽 하단의 시스템 트레이에서 앱 아이콘 확인.
3. 아이콘을 우클릭하여 메뉴에 접근:
   - **활성/비활성**: CapsLockSwitch 기능 켜기/끄기.
   - **시작 시 실행**: Windows 부팅 시 앱 자동 실행 설정/해제.
   - **종료**: 앱 종료.
4. 맥북에서 Windows 원격 데스크탑 사용 중 CapsLock 키를 눌러 한영 전환.

### 라이선스
이 프로젝트는 [MIT 라이선스](LICENSE) 하에 배포됩니다.
