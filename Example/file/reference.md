# Reference

Example framework Reference.

## Shared DLL
MFC Shared dll �̸� static Link �� �̿��Ͽ� ����Ǿ� �ִ�.

* MYEX_LIB.dll
* MYEX_BASE.dll

## Extension DLL
MFC Shared dll �̸� Dynamic Link �� �̿��Ͽ� ����Ǿ� �ִ�. Extension ���Ͽ� Dll �� ������ Plugin ���·� �����ȴ�. 

* MYEX_GTEST.dll
* MYEX_UI.dll

## Excutable FILE
* MYEX

## Library
������ �ܺ� ���̺귯�� 

* google test
* zlib/libzip
   - x86|x64 ���忡�� �����Ǵ� Header ������ �ٸ���. �ݵ�� ���� ��θ� �ٸ��� �����ؼ� ���� ���� �ؾ��Ѵ�.
   - libzip �� �����ϱ� ���ؼ��� zlib �� �켱������ ���� �ؾ��Ѵ�. 
   - libzip �� CMake �� �̿��ϱ� ���ؼ��� zlib include/lib(debug, release) ��θ� �����ؾ� �Ѵ�. 
   - zlib include �� zlib ���� ���(���� ����� clone �� ��ġ) �� ���� �ؾ� �Ѵ�. 
   - zlib library �� zlib �� build �� ����� bin\zlib.lib (debug �� ��� zlibd.lib) �� ���� �ؾ� �Ѵ�. 
   - zlib\zconf.h �� CMake �� ���ؼ� �ڵ����� .include Ȯ���ڷ� ����ȴ�. libzip ������Ʈ ���带 �ϱ� ���ؼ��� .include Ȯ���ڸ� �����ؾ� ������ �� �ִ�. 
   - libzip �� ���� ������Ʈ�� �����ϱ� ���ؼ��� libzip build\lib\zip.lib �� libzip build\bin\zip.dll, zlib build\bin\zlib.dll, libzip\lib\*.c �׸��� *.h, zlib\*.c �׸��� *.h �� �ʿ��ϴ�.








