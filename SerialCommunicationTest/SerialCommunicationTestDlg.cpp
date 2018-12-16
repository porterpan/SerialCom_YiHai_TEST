
// SerialCommunicationTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialCommunicationTest.h"
#include "SerialCommunicationTestDlg.h"
#include "afxdialogex.h"
#include "SerialPort.h"
#include <AFXPRIV.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSerialCommunicationTestDlg 对话框



CSerialCommunicationTestDlg::CSerialCommunicationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALCOMMUNICATIONTEST_DIALOG, pParent)
	, m_EditCW(_T(""))
	, FlagHex(0)
	, m_PortNo(1)
	, m_BaudNo(115200)
	, edit_recv(_T(""))
	, FlagHex_Send(0)
	, flag_sendnewline(FALSE)
	, filepath(_T(""))
	, cur_num(0)
	, last_num(0)
	, m_bSerialPortOpened(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialCommunicationTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CW, m_EditCW);
	DDX_Control(pDX, IDC_BUTTON_Open, m_CommOpenClose);
	DDX_Control(pDX, IDC_COMBO_CommPort, m_CommPort);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_CommBaud);
	DDX_Text(pDX, IDC_EDIT_RECV, edit_recv);
	DDX_Check(pDX, IDC_CHECK_NEW_LINE, flag_sendnewline);
	DDX_Text(pDX, IDC_EDIT_OPEN_FILE, filepath);

	DDX_Control(pDX, IDC_COMBO_ASSEMBLY, m_AssemblyLine);
	DDX_Control(pDX, IDC_COMBO_MATERIAL, m_material);
	DDX_Control(pDX, IDC_COMBO_Check, m_AssemblyCheck);

	DDX_Text(pDX, IDC_EDIT_CarNum, m_CarNum);
	DDX_Text(pDX, IDC_EDIT_FinshNum, m_FinshNum);
	DDX_Text(pDX, IDC_EDIT_ResidualNum, m_ResidualNum);
	DDX_Text(pDX, IDC_EDIT_Amount, m_Amount);
	DDX_Text(pDX, IDC_EDIT_TimeRemain, m_TimeRemain);
	DDX_Text(pDX, IDC_EDIT_ALL_StatusDiplay, m_ALL_StatusDiplay);
	DDX_Control(pDX, IDC_BUTTON_TASK, m_Task);
	
}

BEGIN_MESSAGE_MAP(CSerialCommunicationTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Open, &CSerialCommunicationTestDlg::OnBnClickedButtonOpen)
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
	ON_BN_CLICKED(IDC_BUTTON_SendTest, &CSerialCommunicationTestDlg::OnBnClickedButtonSendtest)
	ON_BN_CLICKED(IDC_CHECK_Hex, &CSerialCommunicationTestDlg::OnBnClickedCheckHex)
	ON_BN_CLICKED(IDC_BUTTON_EmptyCW, &CSerialCommunicationTestDlg::OnBnClickedButtonEmptycw)
	ON_CBN_SELCHANGE(IDC_COMBO_CommPort, &CSerialCommunicationTestDlg::OnCbnSelchanageComboCommport)
	ON_BN_CLICKED(IDC_CHECK_HEX_SEND, &CSerialCommunicationTestDlg::OnBnClickedCheckHexSend)
	ON_BN_CLICKED(IDC_CHECK_NEW_LINE, &CSerialCommunicationTestDlg::OnBnClickedCheckNewLine)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CSerialCommunicationTestDlg::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_CLR_SEND, &CSerialCommunicationTestDlg::OnBnClickedButtonClrSend)
	ON_EN_CHANGE(IDC_EDIT_OPEN_FILE, &CSerialCommunicationTestDlg::OnEnChangeEditOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_SEND_FILE, &CSerialCommunicationTestDlg::OnBnClickedButtonSendFile)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &CSerialCommunicationTestDlg::OnCbnSelchangeComboBaud)
	ON_BN_CLICKED(IDC_BUTTON_TASK, &CSerialCommunicationTestDlg::OnBnClickedButtonTask)
	ON_CBN_SELCHANGE(IDC_COMBO_ASSEMBLY, &CSerialCommunicationTestDlg::OnCbnSelchangeComboAssembly)
//	ON_CBN_SELCHANGE(IDC_COMBO_Check, &CSerialCommunicationTestDlg::OnCbnSelchangeComboCheck)
ON_CBN_SELCHANGE(IDC_COMBO_Check, &CSerialCommunicationTestDlg::OnCbnSelchangeComboCheck)
END_MESSAGE_MAP()


// CSerialCommunicationTestDlg 消息处理程序

BOOL CSerialCommunicationTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	HKEY RegKey;
	CString strtemp;
	int nCount = 0;
	CString subKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");

	if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, NULL, KEY_QUERY_VALUE, &RegKey) == ERROR_SUCCESS)
	{
		edit_recv += "注册表打开成功\r\n";
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		while (true)
		{
			wchar_t ValueName[_MAX_PATH];
			unsigned char ValueData[_MAX_PATH];
			DWORD nValueSize = _MAX_PATH;
			DWORD nDataSize = _MAX_PATH;
			DWORD nType;

			if (::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			edit_recv += ValueName;
			edit_recv += " = ";
			strtemp.Format(_T("%s"), ValueData);
			edit_recv += strtemp;
			edit_recv += "\r\n";
			nCount++;
			m_CommPort.AddString(strtemp);
		}
		m_CommPort.SetCurSel(0);
	}
	edit_recv += "nCount = ";
	strtemp.Format(_T("%d"), nCount);
	edit_recv += strtemp;
	edit_recv += "\r\n";
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
	::RegCloseKey(RegKey);

	m_CommBaud.AddString(_T("1200"));
	m_CommBaud.AddString(_T("2400"));
	m_CommBaud.AddString(_T("4800"));
	m_CommBaud.AddString(_T("9600"));
	m_CommBaud.AddString(_T("14400"));
	m_CommBaud.AddString(_T("19200"));
	m_CommBaud.AddString(_T("38400"));
	m_CommBaud.AddString(_T("43000"));
	m_CommBaud.AddString(_T("57600"));
	m_CommBaud.AddString(_T("76800"));
	m_CommBaud.AddString(_T("115200"));
	m_CommBaud.AddString(_T("128000"));
	m_CommBaud.AddString(_T("230400"));
	m_CommBaud.AddString(_T("256000"));
	m_CommBaud.AddString(_T("460800"));
	m_CommBaud.AddString(_T("921600"));
	m_CommBaud.AddString(_T("1382400"));

	m_CommBaud.SetCurSel(10);

	m_AssemblyLine.AddString(_T("一号线"));
	m_AssemblyLine.AddString(_T("二号线"));
	m_AssemblyLine.AddString(_T("三号线"));
	m_AssemblyLine.AddString(_T("四号线"));
	m_AssemblyLine.AddString(_T("五号线"));
	m_AssemblyLine.SetCurSel(0);

	m_AssemblyCheck.AddString(_T("一号线"));
	m_AssemblyCheck.AddString(_T("二号线"));
	m_AssemblyCheck.AddString(_T("三号线"));
	m_AssemblyCheck.AddString(_T("四号线"));
	m_AssemblyCheck.AddString(_T("五号线"));

	m_material.AddString(_T("一级豆粕65KG"));
	m_material.AddString(_T("二级豆粕50KG"));
	m_material.AddString(_T("三级豆粕100KG"));
	m_material.AddString(_T("四级豆粕30KG"));
	m_material.AddString(_T("五级豆粕40KG"));
	m_material.SetCurSel(0);

	SetDlgItemText(IDC_EDIT_CarNum, L"请发布任务");
	SetDlgItemText(IDC_EDIT_FinshNum, L"请发布任务");
	SetDlgItemText(IDC_EDIT_ResidualNum, L"请发布任务");
	SetDlgItemText(IDC_EDIT_Amount, L"请发布任务");
	SetDlgItemText(IDC_EDIT_TimeRemain, L"已结束");
	SetDlgItemText(IDC_EDIT_ALL_StatusDiplay, L"无正在工作的流水线");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSerialCommunicationTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSerialCommunicationTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSerialCommunicationTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialCommunicationTestDlg::OnBnClickedButtonOpen()
{
	CString strtemp;
	BOOL Isclosed = FALSE;
	if (m_bSerialPortOpened == 0)
	{
		if (m_PortNo)
		{
			m_bSerialPortOpened = m_SerialPort.InitPort(this,
				m_PortNo,
				m_BaudNo,
				'N',
				8,
				1,
				EV_RXCHAR | EV_CTS,
				65536,
				1000,
				1000,
				1000,
				1000,
				1000);
			m_bSerialPortOpened = m_bSerialPortOpened && m_SerialPort.StartMonitoring();
			if (m_bSerialPortOpened)
			{
				edit_recv += "COM";
				strtemp.Format(_T("%u"), m_PortNo);
				edit_recv += strtemp;
				edit_recv += "已打开，波特率115200\r\n";
				SetDlgItemText(IDC_EDIT_RECV, edit_recv);
				cur_num = 0;
				last_num = 0;
				memset(rxbuf, 0, 20000);
				rx_num = 0;
				m_CommOpenClose.SetWindowText(_T("关闭串口"));
			}
			else
			{
				edit_recv += "串口不存在或被占用，打开串口失败！\r\n";
				SetDlgItemText(IDC_EDIT_RECV, edit_recv);
			}
		}
		else
		{
			edit_recv += "请先选择串口\r\n";
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		}
	}
	else
	{
		Isclosed = m_SerialPort.StopMonitoring();
		if (Isclosed)
		{
			m_SerialPort.ClosePort();
			edit_recv += "串口已关闭\r\n";
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
			m_bSerialPortOpened = FALSE;
			m_CommOpenClose.SetWindowText(_T("打开串口"));
		}
		else
		{
			edit_recv += "串口未成功关闭\r\n";
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		}
	}

}



int CSerialCommunicationTestDlg::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	senddata.SetSize(len / 2);
	for (int i = 0; i < len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdata = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}
//这是一个将字符转换为相应的十六进制值的函数
//好多C语言书上都可以找到
//功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
char CSerialCommunicationTestDlg::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}

void CSerialCommunicationTestDlg::OnBnClickedButtonSendtest()
{
	// TODO: 在此添加控件通知处理程序代码
	CByteArray hexdata;
	CString strtemp;
	if (m_bSerialPortOpened)
	{
		if (FlagHex_Send)    //16进制发送
		{
			GetDlgItemText(IDC_EDIT_CW, m_EditCW);
			int len = String2Hex(m_EditCW, hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
			if (flag_sendnewline)
			{
				hexdata.Add(0x0d);      //添加回车换行
				hexdata.Add(0x0a);
			}
			m_SerialPort.WriteToPort((char*)&hexdata[0]);
		}
		else     //ascii发送
		{
			GetDlgItemText(IDC_EDIT_CW, m_EditCW);
			if (flag_sendnewline)
			{
				strtemp = "\r\n";     //添加回车换行
				m_EditCW += strtemp;
			}

			m_SerialPort.WriteToPort(m_EditCW);
		}
	}
}

LONG CSerialCommunicationTestDlg::OnComm(WPARAM ch, LPARAM port)
{
	//m_EditCW += "串口收到数据\r\n";
	CString strtemp;
	if (FlagHex)
	{
		strtemp.Format(_T("%.2x "), (BYTE)ch);
		edit_recv += strtemp;
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
	}
	else
	{
		last_num = cur_num;
		rxbuf[rx_num++] += (char)ch;
		if(rx_num ==1)
			SetTimer(1, 2, NULL);  //2ms进入定时器回调函数
		

		/*buf [i++]+= (char)ch;
		if (buf[i - 2] == 0x0d && buf[i-1] == 0x0a)
		{
			buf[i - 2] = 0;
			buf[i-1] = 0;
			edit_recv += buf;
			i = 0;
			memset(buf,0,20000);
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		}	*/
	}
	
	return 0;
}




void CSerialCommunicationTestDlg::OnBnClickedCheckHex()
{
	// TODO: 在此添加控件通知处理程序代码
	CString edit_data;
	CString strtemp;
	LPCSTR b;
	int i;
	if (IsDlgButtonChecked(IDC_CHECK_Hex) == BST_CHECKED)
	{
		
		GetDlgItemText(IDC_EDIT_RECV, edit_data);
		edit_recv.Empty();
		USES_CONVERSION;
		b = T2A(edit_data.GetBuffer(edit_data.GetLength()));
		for (i = 0; i < edit_data.GetLength(); i++)
		{
			strtemp.Format(_T("%.2x "), (BYTE)b[i]);
			edit_recv += strtemp;
		}
		
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		
		FlagHex = 1;
	}
	else
	{
		edit_recv.Empty();
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		FlagHex = 0;
	}		
}


void CSerialCommunicationTestDlg::OnBnClickedButtonEmptycw()
{
	// TODO: 在此添加控件通知处理程序代码
	edit_recv.Empty();
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
}


void CSerialCommunicationTestDlg::OnCbnSelchanageComboCommport()
{
	// TODO: 在此添加控件通知处理程序代码
	int Index;
	CString strCBText;
	Index = m_CommPort.GetCurSel();
	m_CommPort.GetLBText(Index, strCBText);
	edit_recv += strCBText;
	strCBText.Delete(0, 3);
	/*edit_recv += strCBText;*/
	m_PortNo = atoi((LPSTR)(LPCTSTR)strCBText);
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
}


void CSerialCommunicationTestDlg::OnBnClickedCheckHexSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString edit_data;
	CString strtemp;
	LPCSTR b;
	int i;
	if (IsDlgButtonChecked(IDC_CHECK_HEX_SEND) == BST_CHECKED)
	{
		FlagHex_Send = 1;
		GetDlgItemText(IDC_EDIT_CW, edit_data);
		m_EditCW.Empty();
		USES_CONVERSION;
		b = T2A(edit_data.GetBuffer(edit_data.GetLength()));
		for (i = 0; i < edit_data.GetLength(); i++)
		{
			strtemp.Format(_T("%.2x "), (BYTE)b[i]);
			m_EditCW += strtemp;
		}
		SetDlgItemText(IDC_EDIT_CW, m_EditCW);

	}
	else
	{
		FlagHex_Send = 0;
	}
}


void CSerialCommunicationTestDlg::OnBnClickedCheckNewLine()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK_NEW_LINE) == BST_CHECKED)
	{
		flag_sendnewline = 1;
	}
	else
	{
		flag_sendnewline = 0;
	}
}


void CSerialCommunicationTestDlg::OnBnClickedButtonOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isOpen = TRUE;     //是否打开(否则为保存)  
	CString defaultDir = L"文档";   //默认打开的文件路径  
	CString fileName = L"";         //默认打开的文件名  
	CString filter = L"Text Files (*.TXT)|*.txt|HEX (*.hex)|*.hex|BIN (*.bin)|*.bin|C (*.c;*.c++)|*.c;*.c++|ASM (*.s)|*.s|header (*.h)|*.h|All Files (*.*)|*.*|";  //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result ==IDOK) {
		filepath = openFileDlg.GetPathName();
	}
	CWnd::SetDlgItemTextW(IDC_EDIT_OPEN_FILE, filepath);
}


void CSerialCommunicationTestDlg::OnBnClickedButtonClrSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditCW.Empty();
	SetDlgItemText(IDC_EDIT_CW, m_EditCW);
}


void CSerialCommunicationTestDlg::OnEnChangeEditOpenFile()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSerialCommunicationTestDlg::OnBnClickedButtonSendFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile file;
	//打开文件

	if (!file.Open(filepath, CFile::modeRead))

	{

		::AfxMessageBox(_T("文件打开失败。"));

		return;

	}

	//读文件
	DWORD len;
	len = file.GetLength();
	/*CEdit* pBoxOne;*/
	char *pReadData = new char[len + 5]; // 分配内存
	
	file.Read(pReadData, len);                                       //  这里保存的读取文件的数据
	pReadData[len] = 0;
	pReadData[len + 1] = 0;
	pReadData[len + 2] = 0;
	pReadData[len + 3] = 0;
	pReadData[len+4] = 0;
	/*pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
	::SetWindowTextA(pBoxOne->m_hWnd, pReadData); */ //强制作为ASCII码输出

	/*CString strText = _T("");

	while (file.ReadString(strText))
		edit_recv += strText;
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);  *///以UNICODE码输出
	
	//关闭文件

	file.Close();

	CByteArray hexdata;
	char *strtemp;
	if (m_bSerialPortOpened)
	{
		if (FlagHex_Send)    //16进制发送
		{
			int len = String2Hex((CString)pReadData, hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
			if (flag_sendnewline)
			{
				hexdata.Add(0x0d);      //添加回车换行
				hexdata.Add(0x0a);
			}
			m_SerialPort.WriteToPort((char*)&hexdata[0]);
		}
		else     //ascii发送
		{
			if (flag_sendnewline)
			{
				strtemp = "\r\n";     //添加回车换行
				(CString)pReadData += strtemp;
			}
			m_SerialPort.WriteToPort(pReadData);
		}
	}

}

void CSerialCommunicationTestDlg::OnTimer(UINT nIDEvent)
{
	cur_num++;
	if(cur_num>(last_num+3))
	{
		rxbuf[rx_num] = 0;
		edit_recv += rxbuf;
		rx_num = 0;
		memset(rxbuf, 0, 20000);
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		cur_num = 0;
		last_num = 0;
		KillTimer(1);
	}
	
}



void CSerialCommunicationTestDlg::OnCbnSelchangeComboBaud()
{
	// TODO: 在此添加控件通知处理程序代码
	int Index;
	CString strCBText;
	Index = m_CommBaud.GetCurSel();
	m_CommBaud.GetLBText(Index, strCBText);
	edit_recv += strCBText;
	m_BaudNo = atoi((LPSTR)(LPCTSTR)strCBText);
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
}


void CSerialCommunicationTestDlg::OnBnClickedButtonTask()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_bPublihTask == 0)
	{		
		int Index;
		CString AssemblyLine;
		Index = m_AssemblyLine.GetCurSel();

		switch (Index)
		{
			case 0://0号流水线

				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
		//if ()
		//{
		//	GetDlgItemText(IDC_EDIT_CW, m_CarNum);
		//	
		//}

			if (m_bPublihTask==0)//如果接收到正确的从机上报响应贞数据则表示任务发布成功
			{
				m_bPublihTask = 1;//任务发布成功
				m_Task.SetWindowText(_T("结束任务"));
				
			}
			else
			{
				m_Task.SetWindowText(_T("发布任务"));
				m_bPublihTask = 0;//任务发布失败
			
			}
	}
	else if(m_bPublihTask==1)
	{
		m_Task.SetWindowText(_T("发布任务"));
		m_bPublihTask = 0;
	}
}


void CSerialCommunicationTestDlg::OnCbnSelchangeComboAssembly()
{
	// TODO: 在此添加控件通知处理程序代码


}

void CSerialCommunicationTestDlg::OnCbnSelchangeComboCheck()
{
	// TODO: 在此添加控件通知处理程序代码


}
