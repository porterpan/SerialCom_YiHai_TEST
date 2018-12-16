
// SerialCommunicationTestDlg.h : 头文件
//
#include "SerialPort.h"
#pragma once


// CSerialCommunicationTestDlg 对话框
class CSerialCommunicationTestDlg : public CDialogEx
{
// 构造
public:
	CSerialCommunicationTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALCOMMUNICATIONTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG OnComm(WPARAM ch, LPARAM port);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	CSerialPort m_SerialPort;
	BOOL  m_bSerialPortOpened; //标志串口是否打开
	BOOL  m_bPublihTask; //标志任务是否发布
	CButton m_CommOpenClose;
	CString m_EditCW;
	CComboBox m_CommPort;
	unsigned int m_PortNo;
	CComboBox m_CommBaud;

	CString m_CarNum;//IDC_EDIT_CarNum-车牌号
	CString m_FinshNum;//IDC_EDIT_FinshNum-当前流水线完成数量
	CString m_ResidualNum;//IDC_EDIT_ResidualNum-当前流水线剩余提单数量
	CString m_Amount;//IDC_EDIT_Amount-当前流水线需要提单的总数量
	CString m_TimeRemain;// IDC_EDIT_TimeRemain-当前流水线还需多长时间完成提单
	CString m_ALL_StatusDiplay;//IDC_EDIT_ALL_StatusDiplay- 所有流水线运行状态
	CComboBox m_material;//IDC_COMBO_MATERIAL-物料类型
	CComboBox m_AssemblyLine;//发布任务的流水线号
	CButton m_Task;
	CComboBox m_AssemblyCheck;//查询流水线数据
	CString PushTask_List;//发布任务的清单信息数据汇总

	unsigned int m_BaudNo;
	afx_msg void OnBnClickedButtonSendtest();
	afx_msg void OnBnClickedCheckHex();
	int FlagHex;   //16进制显示与ASCII显示标志位，1--16进制显示  0--ASCII显示
	afx_msg void OnBnClickedButtonEmptycw();
	afx_msg void OnCbnSelchanageComboCommport();
	// 接收到的数据放到此字符串中用于显示
	CString edit_recv;
	int FlagHex_Send;  //16进制发送与ASCII发送标志位，1--16进制发送  0--ASCII发送
	afx_msg void OnBnClickedCheckHexSend();
	int String2Hex(CString str, CByteArray &senddata);
	char ConvertHexChar(char ch);
	// 发送新行标志位，1--发送回车  0--不发送回车
	BOOL flag_sendnewline;
	afx_msg void OnBnClickedCheckNewLine();
	afx_msg void OnBnClickedButtonOpenFile();
	// 打开的文件
	CString filepath;
	char rxbuf[20000];
	int last_num,cur_num,rx_num;
	afx_msg void OnBnClickedButtonClrSend();
	afx_msg void OnEnChangeEditOpenFile();
	afx_msg void OnBnClickedButtonSendFile();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeComboBaud();
	afx_msg void OnBnClickedButtonTask();
	afx_msg void OnCbnSelchangeComboAssembly();
//	afx_msg void OnCbnSelchangeComboCheck();
	afx_msg void OnCbnSelchangeComboCheck();
};
