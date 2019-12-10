# Google Test

Welcome to **Google Test**, GoogleTest framework!

## 플랫폼

* Window 10 Pro x64 KR
* Visual Studio Professional 2017
* Debug|Release, win32|x64

## 라이브러리 생성
1. [Google Test](https://github.com/google/googletest) 에서 소스를 받아온다. 
2. CMake 실행 하여 Visual Studio 2017 Debug|Release, win32|x64 프로젝트를 생성한다. - Runtime Library /MD 옵션을 사용하기 위해서는 BUILD_SHARED_LIBS 옵션을 선택하고 프로젝트를 생성해야 한다. -
3. 프로젝트 빌드 후 필요한 LIB/DLL/Header 를 추출한다. 
* include : Google Test local 저장소 > googletest > include 
* lib : 프로젝트 > lib > Debug|Release > gtest.lib, gtest_main.lib
* dll : 프로젝트 > bin > Debug|Release > gtest.dll, gtest_main.dll

## 테스트 프로젝트 생성
1. MFC 기반 프로젝트를 만든다. - MFC 대화상자 기반 프로젝트 생성 -
2. 프로젝트 속성 > include 경로에 라이브러리에서 추출한 include 경로를 지정한다.
3. 프로젝트 속성 > lib 경로에 라이브러리에서 추출한 lib 경로를 지정한다. 
4. 프로젝트 속성 > lib 에 gtest.lib, gtest_main.lib (Debug 의 경우 *d.lib 로 이름을 지정해야 한다.) 를 추가한다. 
5. 프로젝트 폴더 > bin > Debug|Release 에 라이브러리에서 추출한 dll 을 추가한다. 
6. Google Test 초기화 및 테스트 코드 작성

~~~cpp
#include <gtest\gtest.h>

int _tmain(int argc, TCHAR* argv[]) // MFC 의 경우 App::InitInstance 에 추가
{
    ::testing::InitGoogleTest(&argc, argv);
    int nResult = RUN_ALL_TEST();
    return nResult;
}
~~~

## 참고
1. Google Test 를 적용하면 메모리 릭이 발생할 수 있다. - 프로젝트 생성 소멸 순서에 의해 발생할 수 있으며, 자세한 사항은 Google Test 의 문서를 참고하면 된다. -
2. Google Test 문법과 관련된 사항은 [Document](https://github.com/google/googletest/blob/master/googletest/docs/primer.md) 를 참고하면 된다.
3. MFC 의 경우 공유 DLL 에 의한 에러가 발생 시에 프로젝트 속성 > C/C++ > 전처리기에 GTEST_LINKED_AS_SHARED_LIBRARY=1 를 입력하면 오류가 사라진다. Google Test 옵션과 관련된 사항은 Document 를 참고하면 된다. 

