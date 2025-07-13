# 최소 CMake 버전 요구사항
cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(CapsLockLanguageSwitcher)

# 실행 파일 생성
# "WIN32" 키워드는 콘솔 창이 없는 GUI 애플리케이션을 만든다는 의미입니다.
add_executable(CapsLockLanguageSwitcher WIN32 main.cpp resource.rc)

# 유니코드 빌드를 위한 컴파일러 정의 추가
target_compile_definitions(CapsLockLanguageSwitcher PRIVATE UNICODE _UNICODE)

# Windows API 라이브러리 링크
# user32.lib는 창관리, 메시지, 키보드 입력 등 기본적인 UI 기능을 담고 있습니다.
target_link_libraries(CapsLockLanguageSwitcher PRIVATE user32 shell32)