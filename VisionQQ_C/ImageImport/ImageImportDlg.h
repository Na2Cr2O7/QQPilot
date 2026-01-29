
// ImageImportDlg.h: 头文件
//

#pragma once


// CImageImportDlg 对话框
class CImageImportDlg : public CDialogEx
{
// 构造
public:
	CImageImportDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEIMPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeFolders();
    afx_msg void addLog(CString& Log);
	// a
	// a
	// a
	// a
	// a
	CEdit Value;
	CString Text;
	CString m_folder;
	afx_msg void OnBnClickedButton1();
	afx_msg void ThcopyFile();
	std::thread t;
	afx_msg void OnBnClickedButton2();
	CButton Log;
	CStatic Log2;
	afx_msg void OnStnClickedSe();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
