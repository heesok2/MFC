# Google Test

Welcome to **Google Test**, GoogleTest framework!

## �÷���

* Window 10 Pro x64 KR
* Visual Studio Professional 2017
* Debug|Release, win32|x64

## ���̺귯�� ����
1. [Google Test](https://github.com/google/googletest) ���� �ҽ��� �޾ƿ´�. 
2. CMake ���� �Ͽ� Visual Studio 2017 Debug|Release, win32|x64 ������Ʈ�� �����Ѵ�. - Runtime Library /MD �ɼ��� ����ϱ� ���ؼ��� BUILD_SHARED_LIBS �ɼ��� �����ϰ� ������Ʈ�� �����ؾ� �Ѵ�. -
3. ������Ʈ ���� �� �ʿ��� LIB/DLL/Header �� �����Ѵ�. 
* include : Google Test local ����� > googletest > include 
* lib : ������Ʈ > lib > Debug|Release > gtest.lib, gtest_main.lib
* dll : ������Ʈ > bin > Debug|Release > gtest.dll, gtest_main.dll

## �׽�Ʈ ������Ʈ ����
1. MFC ��� ������Ʈ�� �����. - MFC ��ȭ���� ��� ������Ʈ ���� -
2. ������Ʈ �Ӽ� > include ��ο� ���̺귯������ ������ include ��θ� �����Ѵ�.
3. ������Ʈ �Ӽ� > lib ��ο� ���̺귯������ ������ lib ��θ� �����Ѵ�. 
4. ������Ʈ �Ӽ� > lib �� gtest.lib, gtest_main.lib (Debug �� ��� *d.lib �� �̸��� �����ؾ� �Ѵ�.) �� �߰��Ѵ�. 
5. ������Ʈ ���� > bin > Debug|Release �� ���̺귯������ ������ dll �� �߰��Ѵ�. 
6. Google Test �ʱ�ȭ �� �׽�Ʈ �ڵ� �ۼ�

~~~cpp
#include <gtest\gtest.h>

int _tmain(int argc, TCHAR* argv[]) // MFC �� ��� App::InitInstance �� �߰�
{
    ::testing::InitGoogleTest(&argc, argv);
    int nResult = RUN_ALL_TEST();
    return nResult;
}
~~~

## ����
1. Google Test �� �����ϸ� �޸� ���� �߻��� �� �ִ�. - ������Ʈ ���� �Ҹ� ������ ���� �߻��� �� ������, �ڼ��� ������ Google Test �� ������ �����ϸ� �ȴ�. -
2. Google Test ������ ���õ� ������ [Document](https://github.com/google/googletest/blob/master/googletest/docs/primer.md) �� �����ϸ� �ȴ�.
3. MFC �� ��� ���� DLL �� ���� ������ �߻� �ÿ� ������Ʈ �Ӽ� > C/C++ > ��ó���⿡ GTEST_LINKED_AS_SHARED_LIBRARY=1 �� �Է��ϸ� ������ �������. Google Test �ɼǰ� ���õ� ������ Document �� �����ϸ� �ȴ�. 

