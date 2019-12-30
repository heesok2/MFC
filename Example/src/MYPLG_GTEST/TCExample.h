#pragma once

class CDocBase;
namespace mytest
{
	class TCExample : public ::testing::Test
	{
	protected:
		virtual void SetUp() override;
		virtual void TearDown() override;

	protected:
		CDocBase* m_pMyDoc;

	};
}

