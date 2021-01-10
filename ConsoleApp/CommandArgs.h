#pragma once
#include <vector>

class CCommandArgs
{
public:
	CCommandArgs(const TCHAR* strCommandLine);
	CString GetExePath() const;
	CString GetArgs(UINT nIndex) const;
	SIZE_T GetArgsSize() const;
private:
	CCommandArgs();
private:	
	enum class EError
	{
		NoError,
		EError_NotFileExist,
	};
	int m_nArgsCount;
	CString m_strExePath;	//実行ファイルのパス
	std::vector<CString> m_commandArgs; // コマンドライン引数リスト
	EError m_error;
private:
	static CString GetNextArg(CString& str);
	void Init();
};

