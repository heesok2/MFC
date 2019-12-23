# Reference

Example framework Reference.

## Shared DLL
MFC Shared dll 이며 static Link 를 이용하여 연결되어 있다.

* MYEX_LIB.dll
* MYEX_BASE.dll

## Extension DLL
MFC Shared dll 이며 Dynamic Link 를 이용하여 연결되어 있다. Extension 파일에 Dll 이 있으면 Plugin 형태로 관리된다. 

* MYEX_GTEST.dll
* MYEX_UI.dll

## Excutable FILE
* MYEX

## Library
참조한 외부 라이브러리 

* google test
* zlib/libzip
   - x86|x64 빌드에서 참조되는 Header 파일이 다르다. 반드시 로컬 경로를 다르게 정의해서 따로 빌드 해야한다.
   - libzip 을 빌드하기 위해서는 zlib 를 우선적으로 빌드 해야한다. 
   - libzip 를 CMake 를 이용하기 위해서는 zlib include/lib(debug, release) 경로를 지정해야 한다. 
   - zlib include 는 zlib 로컬 경로(서버 저장소 clone 한 위치) 를 지정 해야 한다. 
   - zlib library 는 zlib 를 build 한 경로의 bin\zlib.lib (debug 의 경우 zlibd.lib) 를 지정 해야 한다. 
   - zlib\zconf.h 는 CMake 에 의해서 자동으로 .include 확장자로 변경된다. libzip 프로젝트 빌드를 하기 위해서는 .include 확장자를 제거해야 빌드할 수 있다. 
   - libzip 를 실제 프로젝트에 적용하기 위해서는 libzip build\lib\zip.lib 와 libzip build\bin\zip.dll, zlib build\bin\zlib.dll, libzip\lib\*.c 그리고 *.h, zlib\*.c 그리고 *.h 가 필요하다.








