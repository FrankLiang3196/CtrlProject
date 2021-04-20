
// CtrlProjectDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CtrlProject.h"
#include "CtrlProjectDlg.h"
#include "afxdialogex.h"
#include "usb7660.H"
#include "resource.h"
#include <algorithm>

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


// CMyCtrlProjectDlg 对话框



CMyCtrlProjectDlg::CMyCtrlProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCtrlProject_DIALOG, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 将数组m_nzValues的元素都初始化为0   
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);
	memset(m_trueValues, 0, sizeof(int) * POINT_COUNT);
	
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CMyCtrlProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDCANCEL, m_picDraw);

	DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);
	DDX_Control(pDX, IDC_COMBO8, step_combo);
}

BEGIN_MESSAGE_MAP(CMyCtrlProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyCtrlProjectDlg::OnBnClickedOk)
//	ON_LBN_SELCHANGE(IDC_LIST1, &CMyCtrlProjectDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDCANCEL, &CMyCtrlProjectDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT4, &CMyCtrlProjectDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyCtrlProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyCtrlProjectDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMyCtrlProjectDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMyCtrlProjectDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_RADIO1, &CMyCtrlProjectDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMyCtrlProjectDlg::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT12, &CMyCtrlProjectDlg::OnEnChangeEdit12)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyCtrlProjectDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyCtrlProjectDlg 消息处理程序

BOOL CMyCtrlProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.   

   // IDM_ABOUTBOX must be in the system command range.   
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

	// Set the icon for this dialog.  The framework does this automatically   
	//  when the application's main window is not a dialog   
	SetIcon(m_hIcon, TRUE);         // Set big icon   
	SetIcon(m_hIcon, FALSE);        // Set small icon   

	// TODO: Add extra initialization here

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, NULL);
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//选上

	TS = 10; 	//设定定时器时间, 单位ms

	CString tempStr;
	tempStr.Format(_T("请设置参数"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数



	return TRUE;  // return TRUE  unless you set the focus to a control   
}

void CMyCtrlProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyCtrlProjectDlg::OnPaint()
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
HCURSOR CMyCtrlProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyCtrlProjectDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString str1, str2;
	GetDlgItemText(IDC_EDIT1, str1);
	str2 = str1;
	SetDlgItemText(IDC_EDIT2, str2);//设置对话框项的文字

}


void CMyCtrlProjectDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMyCtrlProjectDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnCancel();
}


void CMyCtrlProjectDlg::DrawWave(CDC *pDC, CRect &rectPicture)
{
	float fDeltaX;     // x轴相邻两个绘图点的坐标距离   
	float fDeltaY;     // y轴每个逻辑单位对应的坐标值   
	int nX;      // 在连线时用于存储绘图点的横坐标   
	int nY;      // 在连线时用于存储绘图点的纵坐标  
	int nYtrue;
	CPen newPen;       // 用于创建新画笔   
	CPen newPentrue;   // 用于创建理想图像画笔
	CPen *pOldPen;     // 用于存放旧画笔   
	CBrush newBrush;   // 用于创建新画刷   
	CBrush *pOldBrush; // 用于存放旧画刷   

	// 计算fDeltaX和fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 250;

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	pDC->Rectangle(rectPicture);
	// 恢复旧画刷   
	pDC->SelectObject(pOldBrush);
	// 删除新画刷   
	newBrush.DeleteObject();

	// 创建实心画笔，粗度为1，颜色为绿色   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	newPentrue.CreatePen(PS_SOLID, 1, RGB(255,0,0));
	// 选择新画笔，并将旧画笔的指针保存到pOldPen   
	pOldPen = pDC->SelectObject(&newPen);
	// 将当前点移动到绘图控件窗口的左下角，以此为波形的起始点   
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	// 计算m_nzValues数组中每个点对应的坐标位置，并依次连接，最终形成曲线   
	for (int i = 0; i < POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);
		pDC->LineTo(nX, nY);
	}
	pOldPen = pDC->SelectObject(&newPen);
	newPen.DeleteObject();//返回值作图
	// 恢复旧画笔   
	pOldPen = pDC->SelectObject(&newPentrue);
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	for (int i = 0; i < POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nYtrue = rectPicture.bottom - (int)(m_trueValues[i] * fDeltaY);
		pDC->LineTo(nX, nYtrue);
	}
	// 恢复旧画笔   
	pDC->SelectObject(pOldPen);
	// 删除新画笔   
	newPentrue.DeleteObject();//理论值画图

}


void CMyCtrlProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default   
	CRect rectPicture;
	if (signal == 1)//阶跃信号
	{
		count += 1;
		t += (TS / 1000);

		CString tempStr;
		renVal = (float)ZT7660_AIonce(1, 0, 21, 2, 0, 0, 0, 0, 0, 0, 0) / 40;//对指定通道进行单次数据采集

		if (count == 1 && abs(renVal) < 10) flag = true; //此时为标准阶跃测试

		int ifstep = step_combo.GetCurSel(); //判断是高电平还是低电平
		float stepVal;
		stepVal = ifstep * stepvalue;

		if (abs(renVal - stepVal) > 0.1 * stepVal)
		{
			integral = 0; // 在0-0.9stepVal时不要积分环节
			//可以在0-0.9stepVal时增大Kp
		}

		Error1 = (stepVal - renVal);//Calculate E(k)
		integral = Error1 + integral;//积分环节

		if (isMAX(Error1, Error2, Error3)) {
			//if (flag && !flag1) {
			//	sigma = abs(Error1) / stepvalue * 100;
			//	tempStr.Format(_T("%.2f"), sigma);//进行字符串的转换
			//	SetDlgItemText(IDC_EDIT11, tempStr);//输出超调量
			//	tp = t;
			//	tempStr.Format(_T("%.2f"), tp);//进行字符串的转换
			//	SetDlgItemText(IDC_EDIT12, tempStr);//输出上升时间
			//	flag1 = !flag1; //不再执行此程序 1表示已经打印过了
			//}
		      if (flag && isStable(Error2) && !flag2) {

				int max_i = findMAX(m_nzValues);

				sigma = (m_nzValues[max_i] - stepvalue) / stepvalue * 100;
				if (sigma < 0) sigma = 0;
				tempStr.Format(_T("%.2f"), sigma);//进行字符串的转换
				SetDlgItemText(IDC_EDIT11, tempStr);//输出超调量

				ts = t;
				tempStr.Format(_T("%.2f"), ts);//进行字符串的转换
				SetDlgItemText(IDC_EDIT13, tempStr);//打印稳定时间

				tp = ts - (POINT_COUNT - max_i - 1) * 5 * TS / 1000;
				tempStr.Format(_T("%.2f"), tp);//进行字符串的转换
				SetDlgItemText(IDC_EDIT12, tempStr);//输出峰值时间

				flag2 = !flag2;
				tempStr.Format(_T("系统已稳定"));
				SetDlgItemText(IDC_EDIT14, tempStr);
			}
			else if (isAuto && isStable(Error2) && count > 500) Stop(); //如果在自动调试PID阶段，满足此条件时停止计时器
		}

		float p = Error1 - Error2;
		Error3 = Error2;
		Error2 = Error1;//Calculate E(k-1)      

		Output = 40 * (Kp * Error1 + Ki * integral + Kd * p);//PID
		if (Output > 0) Output = Output + 2500;
		else Output = Output - 2500; //对返回时添加一个系数平衡

		ZT7660_AOonce(1, 1, 6, Output);//指定某通道模拟量输出一次

		//每隔50步输出一次参数
		if (count % 50 == 0) {
			tempStr.Format(_T("%.2f"), renVal);
			SetDlgItemText(IDC_EDIT5, tempStr);//输出当前位移量
			tempStr.Format(_T("%.2f"), stepVal);
			SetDlgItemText(IDC_EDIT4, tempStr); //输出位移量参考值
			tempStr.Format(_T("%.2f"), Error1);
			SetDlgItemText(IDC_EDIT6, tempStr);//输出位移差
			tempStr.Format(_T("%.2f"), Output);
			SetDlgItemText(IDC_EDIT10, tempStr);//输出电压
		}

		//将图形绘制在界面上(5步打印一次图像)
		if (count % 5 == 0) {
			for (int i = 0; i < POINT_COUNT - 1; i++)
			{
				m_nzValues[i] = m_nzValues[i + 1];
				m_trueValues[i] = m_trueValues[i + 1];
			}
			m_nzValues[POINT_COUNT - 1] = renVal;
			m_trueValues[POINT_COUNT - 1] = stepVal;

			// 绘制波形图   
			m_picDraw.GetClientRect(&rectPicture);
			DrawWave(m_picDraw.GetDC(), rectPicture);

			//绘制原函数
			m_picDraw.GetClientRect(&rectPicture);
			DrawWave(m_picDraw.GetDC(), rectPicture);
		}

	}
	else {
		count += 1;
		CString tempStr;
		feedback = 125.0 + peakvalue * sin(frequency*6.28*t);
		t += 1.8 * (TS/1000);
		renVal = ZT7660_AIonce(1, 0, 21, 2, 0, 0, 0, 0, 0, 0, 0) / 40;

		Error1 = feedback - renVal;//Calculate E(k)
		integral = Error1 + integral;//积分环节

		float p = Error1 - Error2;
		Error2 = Error1;//Calculate E(k-1)		

		Output = 40 * (Kp*Error1 + Ki * integral + Kd * p);

		// 设置死区范围为正负2500
		if (Output > 0) Output = Output + 2500;
		else Output = 1.3 * (Output - 2500);

		ZT7660_AOonce(1, 1, 6, Output);

		//每隔50步输出一次参数
		if (count % 50 == 0) {
			tempStr.Format(_T("%.2f"), renVal);
			SetDlgItemText(IDC_EDIT5, tempStr);//输出当前位移量
			tempStr.Format(_T("%.2f"), feedback);
			SetDlgItemText(IDC_EDIT4, tempStr);//输出位移量参考值
			tempStr.Format(_T("%.2f"), Error1);
			SetDlgItemText(IDC_EDIT6, tempStr);//输出位移差
			tempStr.Format(_T("%.2f"), Output);
			SetDlgItemText(IDC_EDIT10, tempStr);//输出电压
		}

		//将图形绘制在界面上(5步打印一次图像)
		if (count % 5 == 0) {
			for (int i = 0; i < POINT_COUNT - 1; i++)
			{
				m_nzValues[i] = m_nzValues[i + 1];
				m_trueValues[i] = m_trueValues[i + 1];
			}
			m_nzValues[POINT_COUNT - 1] = renVal;
			m_trueValues[POINT_COUNT - 1] = feedback;

			// 绘制波形图   
			m_picDraw.GetClientRect(&rectPicture);
			DrawWave(m_picDraw.GetDC(), rectPicture);

			//绘制原函数
			m_picDraw.GetClientRect(&rectPicture);
			DrawWave(m_picDraw.GetDC(), rectPicture);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMyCtrlProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here   

	// 关闭定时器   
	//KillTimer(1);
}

void CMyCtrlProjectDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	//TODO:  在此添加控件通知处理程序代码
	
}


void CMyCtrlProjectDlg::OnBnClickedButton1() //开始波形对话框
{
	// TODO: 在此添加控件通知处理程序代码
	int   iRadioButton;
	Kp = 0;
	Ki = 0;
	Kd = 0;

	Initialization();
	CString str_kp, str_ki, str_kd, str_step, str_peak, strf;
	GetDlgItemText(IDC_EDIT1, str_kp);
	GetDlgItemText(IDC_EDIT2, str_ki);
	GetDlgItemText(IDC_EDIT3, str_kd);
	GetDlgItemText(IDC_EDIT7, str_step);
	GetDlgItemText(IDC_EDIT8, str_peak);
	GetDlgItem(IDC_EDIT9)->GetWindowText(strf);

	iRadioButton = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2);
	if (iRadioButton == IDC_RADIO1)   //若选中控件1
	{
		//MessageBox("Click   Button1"); 
		signal = 1;
	}
	if (iRadioButton == IDC_RADIO2)   //若选中控件2
	{
		// MessageBox("Click   Button2");
		signal = 2;
	}
	Kp = _ttof(str_kp);
	Ki = _ttof(str_ki);
	Kd = _ttof(str_kd);
	stepvalue = _ttof(str_step);
	frequency = _ttof(strf);
	peakvalue = _ttof(str_peak);

	if (ZT7660_OpenDevice(1) != 0) 
		AfxMessageBox(_T("fail!"));

	CString tempStr;
	tempStr.Format(_T("正在控制..."));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数

	SetTimer(1, TS, NULL);
}


void CMyCtrlProjectDlg::OnBnClickedButton2()
{
	Stop();
}


void CMyCtrlProjectDlg::Stop()
{
	ZT7660_CloseDevice(1);
	//exit(0);
	Invalidate(1);

	CString tempStr;
	tempStr.Format(_T("已停止"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数

	KillTimer(1);
}

void CMyCtrlProjectDlg::Initialization()
{
	t = 0;//初始化时间
	count = 0;//初始化循环数
	flag = false;
	flag1 = false;
	flag2 = false;
	Error1 = 0;//(E(k))
	Error2 = 0;//(E(k-1))
	Error3 = 0;//(E(k-2))
	integral = 0;//E(k)求和
	Output = 0;//输出电平大小
	feedback = 0;//正弦的理论值
	ts = 0;//稳定时间
	tp = 0;//峰值时间
	//sigma = 0;//超调量
	renVal = 0;//当前位移值
	peakvalue = 0; //正弦信号理论幅值
	frequency = 0; //正弦信号理论频率
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);
	memset(m_trueValues, 0, sizeof(int) * POINT_COUNT);
}

void CMyCtrlProjectDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	

}


void CMyCtrlProjectDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMyCtrlProjectDlg::OnBnClickedRadio1()
{
	CString tempStr;
	tempStr.Format(_T("已选择阶跃信号"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数
}


void CMyCtrlProjectDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tempStr;
	tempStr.Format(_T("已选择正弦信号"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数
}


bool CMyCtrlProjectDlg::isMAX(float Error1, float Error2, float Error3)
{
	// TODO: 在此添加控件通知处理程序代码
	if ((Error2 < Error1 && Error2 < Error3) || (Error2 > Error3 && Error2 > Error1)) return true;
	else return false;
}

int CMyCtrlProjectDlg::findMAX(float nums[])
{
	// TODO: 在此添加控件通知处理程序代码
	float maxVal = 0;
	int maxIndex = 0;
	for (int i = 0; i < POINT_COUNT; ++i) {
		if (nums[i] > maxVal) {
			maxVal = nums[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

bool CMyCtrlProjectDlg::isStable(float Error)
{
	if (abs(Error) < 0.02 * stepvalue + 0.001) return true;
	else return false;
}

//void CMyCtrlProjectDlg::Print_PID() //打印PID
//{
//	CString tempStr;
//	tempStr.Format(_T("%.2f"), Kp);//进行字符串的转换
//	SetDlgItemText(IDC_EDIT1, tempStr);
//	tempStr.Format(_T("%.2f"), Ki);//进行字符串的转换
//	SetDlgItemText(IDC_EDIT2, tempStr);
//	tempStr.Format(_T("%.2f"), Kd);//进行字符串的转换
//	SetDlgItemText(IDC_EDIT3, tempStr);
//}

//void CMyCtrlProjectDlg::Print_sigma() //打印超调量和上升时间以及稳定时间
//{
//	CString tempStr;
//	if (isMAX() && flag == 1 && flag1 == 1)
//	{
//		sigma = abs(Error1) / stepvalue;
//		tempStr.Format(_T("%.2f"), sigma);//进行字符串的转换
//		SetDlgItemText(IDC_EDIT11, tempStr);//超调量
//		tempStr.Format(_T("%.2f"), t);//进行字符串的转换
//		SetDlgItemText(IDC_EDIT12, tempStr);//上升时间
//		flag1 = 0; //不再执行此程序 0表示已经打印过了
//	}
//	if (flag == 1 && flag2 == 1 && isStable())
//	{
//		tempStr.Format(_T("%.2f"), t);//进行字符串的转换
//		SetDlgItemText(IDC_EDIT13, tempStr);//打印稳定时间
//		flag2 = 0;
//	}
//}
void CMyCtrlProjectDlg::auto_PID()
{
	isAuto = true;
	Initialization();

	Kp = 0;
	Ki = 0;
	Kd = 0;

	CString tempStr;
	tempStr.Format(_T("正在调节比例系数"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数
	auto_P();
	auto_I();
	isAuto = false;
}

void CMyCtrlProjectDlg::auto_P() {
	Kp = 1;
	CString tempStr;
	while (sigma < 0.05) {
		stepvalue = 100;
		SetTimer(1, TS, NULL);

		tempStr.Format(_T("%.2f"), Kp);
		SetDlgItemText(IDC_EDIT1, tempStr);//输出当前比例系数

		Initialization();
		Kp += 0.5;
		stepvalue = 0;
		SetTimer(1, TS, NULL);
		Initialization();
	}
	while (sigma > 0) {
		stepvalue = 100;
		SetTimer(1, TS, NULL);

		tempStr.Format(_T("%.2f"), Kp);
		SetDlgItemText(IDC_EDIT1, tempStr);//输出当前比例系数

		Initialization();
		Kp -= 0.05;
		SetTimer(1, TS, NULL);
		Initialization();
	}
	Kp *= 0.65;

	tempStr.Format(_T("比例系数调节完成"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数
}
void CMyCtrlProjectDlg::auto_I() {
	Ki = 0.05;
	CString tempStr;
	while (sigma < 0.05) {  
		stepvalue = 100;
		SetTimer(1, TS, NULL);
		
		tempStr.Format(_T("%.2f"), Ki);
		SetDlgItemText(IDC_EDIT2, tempStr);//输出当前比例系数

		Initialization();
		Ki -= 0.005;
		stepvalue = 0;
		SetTimer(1, TS, NULL);
		Initialization();
	}
	while (sigma > 0) {
		stepvalue = 100;
		SetTimer(1, TS, NULL);

		tempStr.Format(_T("%.2f"), Ki);
		SetDlgItemText(IDC_EDIT2, tempStr);//输出当前比例系数

		Initialization();
		Ki += 0.001;
		SetTimer(1, TS, NULL);
		Initialization();
	}
	Ki *= 1.5;

	tempStr.Format(_T("比例系数调节完成"));
	SetDlgItemText(IDC_EDIT14, tempStr);//输出当前比例系数
}




void CMyCtrlProjectDlg::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMyCtrlProjectDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	auto_PID();
}
