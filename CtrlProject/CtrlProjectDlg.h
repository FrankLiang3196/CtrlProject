 
// CtrlProjectDlg.h: 头文件
//


#define POINT_COUNT 100 


// CMyCtrlProjectDlg 对话框
class CMyCtrlProjectDlg : public CDialogEx
{
// 构造
public:
	CMyCtrlProjectDlg(CWnd* pParent = nullptr);	// 标准构造函数
	int m_nzValues[POINT_COUNT];
	int m_trueValues[POINT_COUNT];
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCtrlProject_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	//定义变量储存PID的值
	float Kp;
	float Ki;
	float Kd;
	//我们自己添加的变量
	float stepvalue; // 定义阶跃响应的幅值
	float peakvalue = 0; //正弦信号理论幅值
	float frequency = 0; //正弦信号理论频率
	float TS; // 周期

	//可能不需要
	float Error1;//(E(k))
	float Error2;//(E(k-1))
	float Error3;//(E(k-2))
	float integral;//E(k)求和
	float Output;//输出电平大小
	float feedback;
	float t;
	float sigma;
	float velocity;
	float renVal;//当前位移值
	float lastVal;//上次位移值
	float interval;

	int flag; //用于判断是否为正常阶跃
	int flag1;//用于判断是否打印过超调量和上升时间
	int flag2;//用于判断是否打印过稳定时间
	int flag3;
	int signal;//阶跃1；正弦2；
	CStatic m_picDraw;


	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedCancel();
	
	void DrawWave(CDC* pDC, CRect& rectPicture);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CComboBox step_combo;
	afx_msg void OnCbnSelchangeCombo8();
	afx_msg void OnBnClickedButton3();

	afx_msg bool ReturnToInitial();
	afx_msg void OnEnChangeEdit14();

	bool isMAX();
	bool isStable();
	void Print_PID();
	void Print_sigma();
	void auto_PID();
	void Stop();
};
