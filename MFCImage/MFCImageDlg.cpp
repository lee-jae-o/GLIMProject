
// MFCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCImage.h"
#include "MFCImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCImageDlg 대화 상자



CMFCImageDlg::CMFCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CMFCImageDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMFCImageDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMFCImageDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCImageDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCImageDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CMFCImageDlg 메시지 처리기

BOOL CMFCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCImageDlg::OnBnClickedBtnImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	UpdateDisplay();
}


CString g_strFileImage = _T("c:\\image\\save.bmp");
void CMFCImageDlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage);
}


void CMFCImageDlg::OnBnClickedBtnLoad()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}
	m_image.Load(g_strFileImage);

	UpdateDisplay();
}


void CMFCImageDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

}


void CMFCImageDlg::MoveRect()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nGray = rand() % 256; 
	int nRadius = 20;        
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int randX = rand() % (nWidth - nRadius * 2);
	int randY = rand() % (nHeight - nRadius * 2);

	memset(fm, 0xff, nWidth * nHeight);

	drawCircle(fm, randX, randY, nRadius, nGray);

	m_centerX = randX + nRadius; 
	m_centerY = randY + nRadius; 

	UpdateDisplay();
}


void CMFCImageDlg::OnBnClickedBtnAction()
{
	for (int i = 0; i < 5; i++) 
	{
		MoveRect();

		CString strFile;
		strFile.Format(_T("C:\\image\\image%d.jpg"), i); 
		m_image.Save(strFile);

		Sleep(200);
	}
}


BOOL CMFCImageDlg::validImagePos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}


void CMFCImageDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();


	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}


bool CMFCImageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}


void CMFCImageDlg::OnBnClickedBtnOpen()
{
	CFileDialog dlg(TRUE, _T("bmp"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		if (m_image != NULL) {
			m_image.Destroy();
		}
		m_image.Load(filePath);

		UpdateDisplay();

		CClientDC dc(this);
		CPen pen(PS_SOLID, 2, RGB(255, 0, 0)); 
		CPen* pOldPen = dc.SelectObject(&pen);

		dc.MoveTo(m_centerX - 10, m_centerY - 10);
		dc.LineTo(m_centerX + 10, m_centerY + 10);
		dc.MoveTo(m_centerX + 10, m_centerY - 10);
		dc.LineTo(m_centerX - 10, m_centerY + 10);

		CString strCoords;
		strCoords.Format(_T("(%d, %d)"), m_centerX, m_centerY);
		dc.TextOutW(m_centerX + 15, m_centerY, strCoords);

		dc.SelectObject(pOldPen); 
	}
}

