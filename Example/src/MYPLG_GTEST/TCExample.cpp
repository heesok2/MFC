#include "pch.h"
#include "TCExample.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\Module.h"

using namespace mytest;
using namespace mydb;

void TCExample::SetUp()
{
	auto pWnd = AfxGetMainWnd();
	if (pWnd != nullptr && IsWindow(pWnd->GetSafeHwnd()))
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
		{
			auto pFrameWnd = reinterpret_cast<CMDIFrameWnd*>(pWnd);
			auto pChildWnd = pFrameWnd->MDIGetActive();
			if (pChildWnd != nullptr && IsWindow(pChildWnd->GetSafeHwnd()))
			{
				auto pDoc = pChildWnd->GetActiveDocument();
				if (pDoc != nullptr)
					m_pMyDoc = reinterpret_cast<CDocBase*>(pDoc);			
			}
		}
	}
}

void TCExample::TearDown()
{
}

TEST_F(TCExample, ExistPackage)
{
	EXPECT_TRUE(m_pMyDoc != nullptr);

	auto pPackage = m_pMyDoc->GetPackage();
	EXPECT_TRUE(pPackage != nullptr);
}

TEST_F(TCExample, ExistModule)
{
	if (m_pMyDoc != nullptr)
	{
		auto pPackage = m_pMyDoc->GetPackage();
		auto pos = pPackage->GetHeader();
		while (pos != pPackage->GetEnd())
		{
			auto pModule = pPackage->Get(pos);

			EXPECT_TRUE(pModule != nullptr);
			ASSERT_TRUE(pModule->GetType() == pos->first);

			pPackage->Next(pos);
		}
	}	
}