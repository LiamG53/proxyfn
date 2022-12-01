#include "SDK.h"
#include "../../../../../../Downloads/MinHook.h"
#pragma comment(lib, "minhook.lib")


//#include "custom_runtimes.h"

typedef int (WINAPI* LPFN_MBA)(DWORD);
static LPFN_MBA NiggerKeyState;


bool ShowMenu = true;

int Menu_AimBoneInt = 0;
Vector3 udbox;
Vector3 udboxA;

std::vector<uint64_t> radarPawns;
std::vector<PVOID> boatPawns;

void RadarRange(float* x, float* y, float range)
{
	if (fabs((*x)) > range || fabs((*y)) > range)
	{
		if ((*y) > (*x))
		{
			if ((*y) > -(*x))
			{
				(*x) = range * (*x) / (*y);
				(*y) = range;
			}
			else
			{
				(*y) = -range * (*y) / (*x);
				(*x) = -range;
			}
		}
		else
		{
			if ((*y) > -(*x))
			{
				(*y) = range * (*y) / (*x);
				(*x) = range;
			}
			else
			{
				(*x) = -range * (*x) / (*y);
				(*y) = -range;
			}
		}
	}
}
void CalcRadarPoint(Vector3 vOrigin, int& screenx, int& screeny)
{
	Vector3 vAngle = Vector3{ CamRot.x, CamRot.y, CamRot.z };
	FLOAT fYaw = read<FLOAT>(PlayerController + 0x190);
	float dx = vOrigin.x - CamLoc.x;
	float dy = vOrigin.y - CamLoc.y;

	FLOAT cY = cos(fYaw * (3.1415926 / 180.0f));
	FLOAT sY = sin(fYaw * (3.1415926 / 180.0f));



	Vector3 RetRadar;
	float fsin_yaw = sinf(fYaw);
	float fminus_cos_yaw = -cosf(fYaw);

	float x = dy * fminus_cos_yaw + dx * fsin_yaw;
	x = -x;
	float y = dx * fminus_cos_yaw - dy * fsin_yaw;

	float range = (float)Settings::MaxESPDistance;

	RadarRange(&x, &y, range);

	ImVec2 DrawPos = ImGui::GetCursorScreenPos();
	ImVec2 DrawSize = ImGui::GetContentRegionAvail();

	int rad_x = (int)DrawPos.x;
	int rad_y = (int)DrawPos.y;

	float r_siz_x = DrawSize.x;
	float r_siz_y = DrawSize.y;


	int x_max = (int)r_siz_x + rad_x - 5;
	int y_max = (int)r_siz_y + rad_y - 5;

	screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
	screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

	if (screenx > x_max)
		screenx = x_max;

	if (screenx < rad_x)
		screenx = rad_x;

	if (screeny > y_max)
		screeny = y_max;

	if (screeny < rad_y)
		screeny = rad_y;
}

void renderRadar() {
	for (auto pawn : radarPawns) {
		auto player = pawn;

		int screenx = 0;
		int screeny = 0;

		float Color_R = 255 / 255.f;
		float Color_G = 128 / 255.f;
		float Color_B = 0 / 255.f;



		ImDrawList* Draw = ImGui::GetOverlayDrawList();

		//FVector viewPoint = { 0 };
		//if (IsTargetVisible(pawn)) {
		//	Color_R = 128 / 255.f;
		//	Color_G = 224 / 255.f;
		//	Color_B = 0 / 255.f;
		//}
		Draw->AddRectFilled(ImVec2((float)screenx, (float)screeny),
			ImVec2((float)screenx + 5, (float)screeny + 5),
			ImColor(Color_R, Color_G, Color_B));
	}

}
namespace Draw
{
	typedef struct
	{
		DWORD R;
		DWORD G;
		DWORD B;
		DWORD A;
	}RGBA;

	class RBGAColr
	{
	public:
		RGBA red = { 255,0,0,255 };
		RGBA Magenta = { 255,0,255,255 };
		RGBA yellow = { 255,255,0,255 };
		RGBA grayblue = { 128,128,255,255 };
		RGBA green = { 128,224,0,255 };
		RGBA darkgreen = { 0,224,128,255 };
		RGBA brown = { 192,96,0,255 };
		RGBA pink = { 255,168,255,255 };
		RGBA DarkYellow = { 216,216,0,255 };
		RGBA SilverWhite = { 236,236,236,255 };
		RGBA purple = { 144,0,255,255 };
		RGBA Navy = { 88,48,224,255 };
		RGBA skyblue = { 0,136,255,255 };
		RGBA graygreen = { 128,160,128,255 };
		RGBA blue = { 0,96,192,255 };
		RGBA orange = { 255,128,0,255 };
		RGBA peachred = { 255,80,128,255 };
		RGBA reds = { 255,128,192,255 };
		RGBA darkgray = { 96,96,96,255 };
		RGBA Navys = { 0,0,128,255 };
		RGBA darkgreens = { 0,128,0,255 };
		RGBA darkblue = { 0,128,128,255 };
		RGBA redbrown = { 128,0,0,255 };
		RGBA purplered = { 128,0,128,255 };
		RGBA greens = { 0,255,0,255 };
		RGBA envy = { 0,255,255,255 };
		RGBA black = { 0,0,0,255 };
		RGBA gray = { 128,128,128,255 };
		RGBA white = { 255,255,255,255 };
		RGBA blues = { 30,144,255,255 };
		RGBA lightblue = { 135,206,250,160 };
		RGBA Scarlet = { 220, 20, 60, 160 };
		RGBA white_ = { 255,255,255,200 };
		RGBA gray_ = { 128,128,128,200 };
		RGBA black_ = { 0,0,0,200 };
		RGBA red_ = { 255,0,0,200 };
		RGBA Magenta_ = { 255,0,255,200 };
		RGBA yellow_ = { 255,255,0,200 };
		RGBA grayblue_ = { 128,128,255,200 };
		RGBA green_ = { 128,224,0,200 };
		RGBA darkgreen_ = { 0,224,128,200 };
		RGBA brown_ = { 192,96,0,200 };
		RGBA pink_ = { 255,168,255,200 };
		RGBA darkyellow_ = { 216,216,0,200 };
		RGBA silverwhite_ = { 236,236,236,200 };
		RGBA purple_ = { 144,0,255,200 };
		RGBA Blue_ = { 88,48,224,200 };
		RGBA skyblue_ = { 0,136,255,200 };
		RGBA graygreen_ = { 128,160,128,200 };
		RGBA blue_ = { 0,96,192,200 };
		RGBA orange_ = { 255,128,0,200 };
		RGBA pinks_ = { 255,80,128,200 };
		RGBA Fuhong_ = { 255,128,192,200 };
		RGBA darkgray_ = { 96,96,96,200 };
		RGBA Navy_ = { 0,0,128,200 };
		RGBA darkgreens_ = { 0,128,0,200 };
		RGBA darkblue_ = { 0,128,128,200 };
		RGBA redbrown_ = { 128,0,0,200 };
		RGBA purplered_ = { 128,0,128,200 };
		RGBA greens_ = { 0,255,0,200 };
		RGBA envy_ = { 0,255,255,200 };
		RGBA glassblack = { 0, 0, 0, 160 };
		RGBA GlassBlue = { 65,105,225,80 };
		RGBA glassyellow = { 255,255,0,160 };
		RGBA glass = { 200,200,200,60 };
		RGBA Plum = { 221,160,221,160 };
		RGBA neongreen = { 0, 255, 229,0 };

	};
	RBGAColr Color;

	std::string string_To_UTF8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}
	// Drawings for custom menus + Toggle Button's / Checkboxes ETC
	void RegularRGBText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void ShadowRGBText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 2), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 240)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 2), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 240)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void OutlinedRBGText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 30 / 30.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 30 / 30.0)), utf_8_2.c_str());
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void RegularText(int x, int y, RGBA* color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
	}
	void NeonRBGText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y - 1), ImColor(64, 255, 0), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 1), ImColor(64, 255, 0), utf_8_2.c_str());
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	}
	void BackgroundRBGOutline(int x, int y, int w, int h, ImColor color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0, thickness);
	}
	void BackgroundOutline(int x, int y, int w, int h, RGBA* color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
	}
	void TitleBar(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
	}
	void TitleBarGraident(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), (color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0), 0, 0);
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), (color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0), 0, 0);
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), (color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0), 0, 0);
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), (color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0), 0, 0);
	}
	void BackgroundLowOpacity(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 0.20f)), 0);
	}

	void BackgroundLowRounded(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 0.20f)), 6);
	}

	void BackgroundRBGGradient(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void BackgroundFilledRBG(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void SelectedFilled(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 0.40f)), 0, 0);
	}

	void BackgroundFilled(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 1.00f)), 0);
	}

	void BackgroundFilledRound(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 1.00f)), 6);
	}

	void BackgroundGradient(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 1.00f)), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, 1.00f)), 0, 0);
	}
	void RoundedRect(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(color), 2);
	}
}

static const char* AimBone_TypeItems[]{
	"   Head",
	"   Neck",
	"   Dick",
};


static const char* ESP_Box_TypeItems[]{
	"   Box",
	"   Cornered",
	"   3D Box"
};


float color_red = 1.;
float color_green = 0;
float color_blue = 0;
float color_random = 0.0;
float color_speed = -10.0;





void ColorChange()
{
	static float Color[3];
	static DWORD Tickcount = 0;
	static DWORD Tickcheck = 0;
	ImGui::ColorConvertRGBtoHSV(color_red, color_green, color_blue, Color[0], Color[1], Color[2]);
	if (GetTickCount() - Tickcount >= 1)
	{
		if (Tickcheck != Tickcount)
		{
			Color[0] += 0.001f * color_speed;
			Tickcheck = Tickcount;
		}
		Tickcount = GetTickCount();
	}
	if (Color[0] < 0.0f) Color[0] += 1.0f;
	ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], color_red, color_green, color_blue);
}
inline uintptr_t GetGameBase()
{
	return *(uintptr_t*)(__readgsqword(0x60) + 0x10);
}
// Better Speedhack
namespace Speed {

	template<class SpeedT>
	class MainSpeed {
		SpeedT time_offset;
		SpeedT time_last_update;

		double speed_;

	public:
		MainSpeed(SpeedT currentRealTime, double initialSpeed) {
			time_offset = currentRealTime;
			time_last_update = currentRealTime;
			speed_ = initialSpeed;
		}

		SpeedT getSpeed(SpeedT currentRealTime) {
			SpeedT difference = currentRealTime - time_last_update;
			return (SpeedT)(speed_ * difference) + time_offset;
		}

		void setSpeed(SpeedT currentRealTime, double speed) {
			time_offset = getSpeed(currentRealTime);
			time_last_update = currentRealTime;
			speed_ = speed;
		}


	};

	typedef DWORD(WINAPI* NtGetTickCount_)(void);
	typedef ULONGLONG(WINAPI* NtGetTickCount64_)(void);
	typedef DWORD(WINAPI* NtTimeGetTime_)(void);
	typedef BOOL(WINAPI* NtQueryPerformanceCounter_)(LARGE_INTEGER* lpPerformanceCount);

	static NtGetTickCount_ NtGetTickCount_original;
	static NtGetTickCount64_ NtGetTickCount64_original;
	static NtTimeGetTime_ NttimeGetTime_original;
	static NtQueryPerformanceCounter_ NtQueryPerformanceCounter_original;

	static MainSpeed<DWORD> g_MainSpeed(0, 0);
	static MainSpeed<ULONGLONG> g_MainSpeed64(0, 0);
	static MainSpeed<LONGLONG> g_MainSpeed_Long(0, 0);


	static DWORD WINAPI GetTickCountHook(void) {
		return g_MainSpeed.getSpeed(NtGetTickCount_original());
	}

	static ULONGLONG WINAPI GetTickCount64Hook(void) {
		return g_MainSpeed64.getSpeed(NtGetTickCount64_original());
	}

	static BOOL WINAPI QueryPerformanceCounterHook(LARGE_INTEGER* lpPerformanceCount) {
		LARGE_INTEGER PerformanceCount;
		BOOL ReturnValue = NtQueryPerformanceCounter_original(&PerformanceCount);
		lpPerformanceCount->QuadPart = g_MainSpeed_Long.getSpeed(PerformanceCount.QuadPart);
		return ReturnValue;
	}

	static VOID InitSpeedHack() {

		/*	NtGetTickCount_ NtGetTickCount = (NtGetTickCount_)SpoofCall(GetProcAddress, (HMODULE)GetGameBase(xorstr(L"Kernel32.dll")), (LPCSTR)xorstr("GetTickCount"));
			NtGetTickCount64_ NtGetTickCount64 = (NtGetTickCount64_)SpoofCall(GetProcAddress, (HMODULE)GetGameBase(xorstr(L"Kernel32.dll")), (LPCSTR)xorstr("GetTickCount64"));
			NtQueryPerformanceCounter_ NtQueryPerformanceCounter = (NtQueryPerformanceCounter_)SpoofCall(GetProcAddress, (HMODULE)GetGameBase(xorstr(L"Kernel32.dll")), (LPCSTR)xorstr("QueryPerformanceCounter"));
			LARGE_INTEGER lpPerformanceCount;

			DWORD MainSpeed_CurrentRealTime = NtGetTickCount();
			ULONGLONG MainSpeed64_CurrentRealTime = NtGetTickCount64();

			g_MainSpeed = MainSpeed<DWORD>(MainSpeed_CurrentRealTime, 1.0);
			g_MainSpeed64 = MainSpeed<ULONGLONG>(MainSpeed64_CurrentRealTime, 1.0);
			NtQueryPerformanceCounter(&lpPerformanceCount);
			g_MainSpeed_Long = MainSpeed<LONGLONG>(lpPerformanceCount.QuadPart, 1.0);


			NtTimeGetTime_ NtTimeGetTime = (NtTimeGetTime_)SpoofCall(GetProcAddress, (HMODULE)GetGameBase(xorstr(L"Winmm.dll")), (LPCSTR)xorstr("timeGetTime"));


			HookHelper::InsertHook((uintptr_t)NtGetTickCount, (uintptr_t)GetTickCountHook, (uintptr_t)&NtGetTickCount_original);
			HookHelper::InsertHook((uintptr_t)NtGetTickCount64, (uintptr_t)GetTickCount64Hook, (uintptr_t)&NtGetTickCount64_original);
			HookHelper::InsertHook((uintptr_t)NtTimeGetTime, (uintptr_t)GetTickCountHook, (uintptr_t)&NttimeGetTime_original);
			HookHelper::InsertHook((uintptr_t)NtQueryPerformanceCounter, (uintptr_t)QueryPerformanceCounterHook, (uintptr_t)&NtQueryPerformanceCounter_original);*/
	}

	static BOOL SpeedHack(double speed) {
		g_MainSpeed.setSpeed(NtGetTickCount_original(), speed);
		g_MainSpeed64.setSpeed(NtGetTickCount64_original(), speed);
		LARGE_INTEGER lpPerformanceCount;
		NtQueryPerformanceCounter_original(&lpPerformanceCount);
		g_MainSpeed_Long.setSpeed(lpPerformanceCount.QuadPart, speed);
		return TRUE;
	}
}


// Watermark and Speed

void DrawWaterMark(ImGuiWindow& windowshit, std::string str, ImVec2 loc, ImU32 colr, bool centered = false)
{
	ImVec2 size = { 0,0 };
	float minx = 0;
	float miny = 0;
	if (centered)
	{
		size = ImGui::GetFont()->CalcTextSizeA(windowshit.DrawList->_Data->FontSize, 0x7FFFF, 0, str.c_str());
		minx = size.x / 2.f;
		miny = size.y / 2.f;
	}

	windowshit.DrawList->AddText(ImVec2((loc.x - 1) - minx, (loc.y - 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
	windowshit.DrawList->AddText(ImVec2((loc.x + 1) - minx, (loc.y + 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
	windowshit.DrawList->AddText(ImVec2((loc.x + 1) - minx, (loc.y - 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
	windowshit.DrawList->AddText(ImVec2((loc.x - 1) - minx, (loc.y + 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
	windowshit.DrawList->AddText(ImVec2(loc.x - minx, loc.y - miny), colr, str.c_str());
}


namespace HookFunctions {
	bool Init(bool NoSpread, bool CalcShot, bool Speed);
	bool NoSpreadInitialized = false;
	bool CalcShotInitialized = false;
	bool SpeedInitialized = false;
}


// Dont forget to call this at the start of the cheat or it wont work!

void gaybow(ImGuiWindow& window) {
	auto RGB = ImGui::GetColorU32({ color_red, color_green, color_blue, 255 });
	//DrawWaterMark(window, "Ritz is sex", ImVec2(50, 100), RGB, false);
	//DrawWaterMark(window, "Second text", ImVec2(50, 120), FpsColor, false);

/*
* 	if (Settings::Speed) {
		if (NiggerKeyState(VK_SHIFT)) {
			if (!HookFunctions::SpeedInitialized) {
				HookFunctions::Init(false, false, true);
			}
			Speed::SpeedHack(Settings::SpeedValue);
		}
		else {
			Speed::SpeedHack(1.0);
		}
	}
*/
}






uintptr_t TargetPawn = 0;


ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;



WNDPROC oWndProc = NULL;


typedef HRESULT(*present_fn)(IDXGISwapChain*, UINT, UINT);
inline present_fn present_original{ };

typedef HRESULT(*resize_fn)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
inline resize_fn resize_original{ };

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Draw2DBoundingBox(Vector3 StartBoxLoc, float flWidth, float Height, ImColor color)
{
	StartBoxLoc.x = StartBoxLoc.x - (flWidth / 2);
	ImDrawList* Renderer = ImGui::GetOverlayDrawList();
	Renderer->AddLine(ImVec2(StartBoxLoc.x, StartBoxLoc.y), ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y), color, 1); //bottom
	Renderer->AddLine(ImVec2(StartBoxLoc.x, StartBoxLoc.y), ImVec2(StartBoxLoc.x, StartBoxLoc.y + Height), color, 1); //left
	Renderer->AddLine(ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y), ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y + Height), color, 1); //right
	Renderer->AddLine(ImVec2(StartBoxLoc.x, StartBoxLoc.y + Height), ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y + Height), color, 1); //up
}

void DrawCorneredBox(int X, int Y, int W, int H, ImColor color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);
	ImDrawList* Renderer = ImGui::GetOverlayDrawList();
	Renderer->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, thickness);

	Renderer->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, thickness);

	Renderer->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), color, thickness);

	Renderer->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), color, thickness);

	Renderer->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), color, thickness);

	Renderer->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), color, thickness);

	Renderer->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), color, thickness);

	Renderer->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), color, thickness);

}

bool IsAiming()
{
	return NiggerKeyState(VK_RBUTTON);
}

auto GetSyscallIndex(std::string ModuleName, std::string SyscallFunctionName, void* Function) -> bool
{
	auto ModuleBaseAddress = LI_FN(GetModuleHandleA)(ModuleName.c_str());
	if (!ModuleBaseAddress)
		ModuleBaseAddress = LI_FN(LoadLibraryA)(ModuleName.c_str());
	if (!ModuleBaseAddress)
		return false;

	auto GetFunctionAddress = LI_FN(GetProcAddress)(ModuleBaseAddress, SyscallFunctionName.c_str());
	if (!GetFunctionAddress)
		return false;

	auto SyscallIndex = *(DWORD*)((PBYTE)GetFunctionAddress + 4);

	*(DWORD*)((PBYTE)Function + 4) = SyscallIndex;

	return true;
}

extern "C"
{
	NTSTATUS _NtUserSendInput(UINT a1, LPINPUT Input, int Size);
};

VOID mouse_event_(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{
	static bool doneonce;
	if (!doneonce)
	{
		if (!GetSyscallIndex(xorstr("win32u.dll"), xorstr("NtUserSendInput"), _NtUserSendInput))
			return;
		doneonce = true;
	}

	INPUT Input[3] = { 0 };
	Input[0].type = INPUT_MOUSE;
	Input[0].mi.dx = dx;
	Input[0].mi.dy = dy;
	Input[0].mi.mouseData = dwData;
	Input[0].mi.dwFlags = dwFlags;
	Input[0].mi.time = 0;
	Input[0].mi.dwExtraInfo = dwExtraInfo;

	_NtUserSendInput((UINT)1, (LPINPUT)&Input, (INT)sizeof(INPUT));
}


Vector3 head2, neck, pelvis, chest, leftShoulder, rightShoulder, leftElbow, rightElbow, leftHand, rightHand, leftLeg, rightLeg, leftThigh, rightThigh, leftFoot, rightFoot, leftFeet, rightFeet, leftFeetFinger, rightFeetFinger;

bool GetAllBones(uintptr_t CurrentActor) {
	Vector3 chesti, chestatright;

	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &head2);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 66, &neck);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 2, &pelvis);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 37, &chesti);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 8, &chestatright);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 38, &leftShoulder);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 9, &rightShoulder);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 39, &leftElbow);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 10, &rightElbow);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 62, &leftHand);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 33, &rightHand);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 78, &leftLeg);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 71, &rightLeg);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 84, &leftThigh);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 77, &rightThigh);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 81, &leftFoot);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 73, &rightFoot);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 82, &leftFeet);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 86, &rightFeet);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 83, &leftFeetFinger);
	SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 76, &rightFeetFinger);

	SDK::Classes::AController::WorldToScreen(head2, &head2);
	SDK::Classes::AController::WorldToScreen(neck, &neck);
	SDK::Classes::AController::WorldToScreen(pelvis, &pelvis);
	SDK::Classes::AController::WorldToScreen(chesti, &chesti);
	SDK::Classes::AController::WorldToScreen(chestatright, &chestatright);
	SDK::Classes::AController::WorldToScreen(leftShoulder, &leftShoulder);
	SDK::Classes::AController::WorldToScreen(rightShoulder, &rightShoulder);
	SDK::Classes::AController::WorldToScreen(leftElbow, &leftElbow);
	SDK::Classes::AController::WorldToScreen(rightElbow, &rightElbow);
	SDK::Classes::AController::WorldToScreen(leftHand, &leftHand);
	SDK::Classes::AController::WorldToScreen(rightHand, &rightHand);
	SDK::Classes::AController::WorldToScreen(leftLeg, &leftLeg);
	SDK::Classes::AController::WorldToScreen(rightLeg, &rightLeg);
	SDK::Classes::AController::WorldToScreen(leftThigh, &leftThigh);
	SDK::Classes::AController::WorldToScreen(rightThigh, &rightThigh);
	SDK::Classes::AController::WorldToScreen(leftFoot, &leftFoot);
	SDK::Classes::AController::WorldToScreen(rightFoot, &rightFoot);
	SDK::Classes::AController::WorldToScreen(leftFeet, &leftFeet);
	SDK::Classes::AController::WorldToScreen(rightFeet, &rightFeet);
	SDK::Classes::AController::WorldToScreen(leftFeetFinger, &leftFeetFinger);
	SDK::Classes::AController::WorldToScreen(rightFeetFinger, &rightFeetFinger);

	chest.x = chesti.x + ((chestatright.x - chesti.x) / 2);
	chest.y = chesti.y;

	return true;
}

// Simple Fov Fix lmao

bool InFov(uintptr_t CurrentPawn, int FovValue) {
	Vector3 HeadPos; SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentPawn, 98, &HeadPos); SDK::Classes::AController::WorldToScreen(HeadPos, &HeadPos);
	auto dx = HeadPos.x - (Renderer_Defines::Width / 2);
	auto dy = HeadPos.y - (Renderer_Defines::Height / 2);
	auto dist = sqrtf(dx * dx + dy * dy);

	if (dist < FovValue) {
		return true;
	}
	else {
		return false;
	}
}
inline float custom_sqrtf(float _X)
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_X)));
}

inline float custom_sinf(float _X)
{
	return _mm_cvtss_f32(_mm_sin_ps(_mm_set_ss(_X)));
}

inline float custom_cosf(float _X)
{
	return _mm_cvtss_f32(_mm_cos_ps(_mm_set_ss(_X)));
}

inline float custom_acosf(float _X)
{
	return _mm_cvtss_f32(_mm_acos_ps(_mm_set_ss(_X)));
}

inline float custom_tanf(float _X)
{
	return _mm_cvtss_f32(_mm_tan_ps(_mm_set_ss(_X)));
}

inline float custom_atan2f(float _X, float _Y)
{
	return _mm_cvtss_f32(_mm_atan2_ps(_mm_set_ss(_X), _mm_set_ss(_Y)));
}

inline int custom_compare(const char* X, const char* Y)
{
	while (*X && *Y) {
		if (*X != *Y) {
			return 0;
		}
		X++;
		Y++;
	}

	return (*Y == '\0');
}

inline int custom_wcompare(const wchar_t* X, const wchar_t* Y)
{
	while (*X && *Y) {
		if (*X != *Y) {
			return 0;
		}
		X++;
		Y++;
	}

	return (*Y == L'\0');
}

inline const wchar_t* custom_wcsstr(const wchar_t* X, const wchar_t* Y)
{
	while (*X != L'\0') {
		if ((*X == *Y) && custom_wcompare(X, Y)) {
			return X;
		}
		X++;
	}
	return NULL;
}

inline const char* custom_strstr(const char* X, const char* Y)
{
	while (*X != '\0') {
		if ((*X == *Y) && custom_compare(X, Y)) {
			return X;
		}
		X++;
	}
	return NULL;
}

inline int custom_strlen(const char* string)
{
	int cnt = 0;
	if (string)
	{
		for (; *string != 0; ++string) ++cnt;
	}
	return cnt;
}

inline int custom_wcslen(const wchar_t* string)
{
	int cnt = 0;
	if (string)
	{
		for (; *string != 0; ++string) ++cnt;
	}
	return cnt;
}

Vector3 calcangle(Vector3& zaz, Vector3& daz) {

	Vector3 dalte = zaz - daz;
	Vector3 ongle;
	float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
	ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
	ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;
	if (dalte.x >= 0.f) ongle.y += 180.f;
	return ongle;
}
struct APlayerCameraManager_GetCameraLocation_Params
{
	Vector3                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};
Vector3 GetCameraLocation(uintptr_t PlayerCameraManager)
{
	static PVOID AAA = 0;
	if (!AAA)
		AAA = FN::FindObject("GetCameraLocation");

	APlayerCameraManager_GetCameraLocation_Params params;

	FN::ProcessEvent(PlayerCameraManager, AAA, &params);

	return params.ReturnValue;
}
class color
{
public:
	float R, G, B, A;

	color()
	{
		R = G = B = A = 0;
	}

	color(float R, float G, float B, float A)
	{
		this->R = R;
		this->G = G;
		this->B = B;
		this->A = A;
	}
};
struct FLinearColor
{
	float R;
	float G;
	float B;
	float A;
};
struct FPawnHighlight
{
	float                                              Priority_28_E2E1B5344846E187B9C11B863A7F0698;             // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	FLinearColor                                Inner_21_4CC2801147EA190DE16F59B34F36853E;                // 0x0004(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	FLinearColor                                Outer_22_5A1D7D0543D303E8B54B66A7F7BD2E2E;                // 0x0014(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FresnelBrightness_23_52B0F96447FF640F47DF2895B0602E92;    // 0x0024(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FresnelExponent_24_B427CF0C441AA37ED49833BF7579DE6D;      // 0x0028(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              UsesPulse_25_E29229F64E540F0617E4C4987AD77605;            // 0x002C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};
bool IsDead(uintptr_t actor)
{
	if (!valid_pointer((uintptr_t)actor)) return false;

	struct
	{
		bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
	} params;

	FN::ProcessEvent(uintptr_t(actor), ObjectsAddresses::IsDead, &params);

	return params.ReturnValue;
}
void ApplyPawnHighlight(uintptr_t actor, color InnerCol, color OuterCol)
{
	//if (!valid_pointer(uintptr_t(actor))) return;

	static PVOID AAA = 0;
	if (!AAA)
		AAA = FN::FindObject("ApplyPawnHighlight");

	struct APlayerPawn_Athena_C_ApplyPawnHighlight_Params
	{
		uintptr_t Source;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
		FPawnHighlight                              HitGlow;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	} params;

	FPawnHighlight HitGlow;

	HitGlow.FresnelBrightness_23_52B0F96447FF640F47DF2895B0602E92 = 0.f;
	HitGlow.FresnelExponent_24_B427CF0C441AA37ED49833BF7579DE6D = 0;
	HitGlow.Inner_21_4CC2801147EA190DE16F59B34F36853E = { (float)InnerCol.R, (float)InnerCol.G, (float)InnerCol.B, (float)InnerCol.A };//{ 1.f, 0.f, 0.f, 1.f };//{ (float)col.R, (float)col.G, (float)col.B, (float)col.A };
	HitGlow.Outer_22_5A1D7D0543D303E8B54B66A7F7BD2E2E = { (float)OuterCol.R, (float)OuterCol.G, (float)OuterCol.B, (float)OuterCol.A };//{ 0.f, 1.f, 0.f, 1.f };//{ (float)col.R, (float)col.G, (float)col.B, (float)col.A };
	HitGlow.Priority_28_E2E1B5344846E187B9C11B863A7F0698 = 0.f;
	HitGlow.UsesPulse_25_E29229F64E540F0617E4C4987AD77605 = 0.f;


	params.Source = uintptr_t(actor);
	params.HitGlow = HitGlow;

	FN::ProcessEvent(uintptr_t(actor), AAA, &params);

}
struct APlayerController_FOV_Params
{
	float                                              NewFOV;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};
void FOVChangerShit(uintptr_t _this, float NewFOV)
{


	APlayerController_FOV_Params params;
	params.NewFOV = NewFOV;

	FN::ProcessEvent(_this, ObjectsAddresses::FOV, &params);
}
Vector3 o_CamRot;
Vector3 o_CamLoc;
Vector3 OriginalLocation;
Vector3 OriginalRotation;
struct FMinimalViewInfo {
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	float AspectRatio;
};
void(*o_GetPlayerViewPoint)(uintptr_t, Vector3*, Vector3*) = nullptr;
void hk_GetPlayerViewPoint(uintptr_t player_controller, Vector3* Location, Vector3* Rotation)
{
	o_GetPlayerViewPoint(player_controller, Location, Rotation);

	OriginalLocation = *Location;
	OriginalRotation = *Rotation;

	if (valid_pointer(LocalPawn))
	{
		if (Settings::SilentAim)
		{
			if (NiggerKeyState(VK_RBUTTON))
			{

				
					uintptr_t Mesh = read<uintptr_t>((uintptr_t)LocalPawn + 0x310);
					if (GetAsyncKeyState(VK_RBUTTON))
					{

						write<Vector3>(Mesh + 0x140, Vector3(0, -rand() % (int)360, 0));
						int spin = 1;
						uintptr_t CurrentActorMesh = read<uintptr_t>(LocalPawn + 0x310);
						write<Vector3>(CurrentActorMesh + 0x140, Vector3(0, spin, 1));
						spin + 30;
						write<Vector3>(CurrentActorMesh + 0x140, Vector3(1, rand() % 361, 1));
					}
					else
					{
						write<Vector3>(Mesh + 0x140, Vector3(0, -90, 0));
					}
				Vector3 camloc = *Location;

				Vector3 VectorPos;
				VectorPos.x = udboxA.x - camloc.x;
				VectorPos.y = udboxA.y - camloc.y;
				VectorPos.z = udboxA.z - camloc.z;

				float distance = (double)(sqrtf(VectorPos.x * VectorPos.x + VectorPos.y * VectorPos.y + VectorPos.z * VectorPos.z));

				Vector3 rot;
				rot.x = -((acosf(VectorPos.z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
				rot.y = atan2f(VectorPos.y, VectorPos.x) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
				rot.z = 0;

				*Rotation = rot;
			}
		}
	}
}

float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}

int faken_rot = 0;

void SwastikaCrosshair()
{

	POINT Screen; int oodofdfo, jbjfdbdsf;
	Screen.x = GetSystemMetrics(0);
	Screen.y = GetSystemMetrics(1);
	//Middle POINT
	POINT Middle; Middle.x = (int)(Screen.x / 2); Middle.y = (int)(Screen.y / 2);
	int a = (int)(Screen.y / 2 / 30);
	float gamma = atan(a / a);
	faken_rot++;
	int Drehungswinkel = faken_rot;

	int i = 0;
	while (i < 4)
	{
		std::vector <int> p;
		p.push_back(a * sin(GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[0]		p0_A.x
		p.push_back(a * cos(GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[1]		p0_A.y
		p.push_back((a / cos(gamma)) * sin(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));	//p[2]		p0_B.x
		p.push_back((a / cos(gamma)) * cos(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));	//p[3]		p0_B.y

		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Middle.x, Middle.y), ImVec2(Middle.x + p[0], Middle.y - p[1]), ImColor(255, 0, 0, 255));
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Middle.x + p[0], Middle.y - p[1]), ImVec2(Middle.x + p[2], Middle.y - p[3]), ImColor(255, 0, 0, 255));

		i++;
	}

}
bool EntitiyLoop()
{


	ImDrawList* Renderer = ImGui::GetOverlayDrawList();


	if (Settings::crosshair)
	{
		Renderer->AddLine(ImVec2(Renderer_Defines::Width / 2 - 7, Renderer_Defines::Height / 2), ImVec2(Renderer_Defines::Width / 2 + 1, Renderer_Defines::Height / 2), ImColor(255, 0, 0, 255), 1.0);
		Renderer->AddLine(ImVec2(Renderer_Defines::Width / 2 + 8, Renderer_Defines::Height / 2), ImVec2(Renderer_Defines::Width / 2 + 1, Renderer_Defines::Height / 2), ImColor(255, 0, 0, 255), 1.0);
		Renderer->AddLine(ImVec2(Renderer_Defines::Width / 2, Renderer_Defines::Height / 2 - 7), ImVec2(Renderer_Defines::Width / 2, Renderer_Defines::Height / 2), ImColor(255, 0, 0, 255), 1.0);
		Renderer->AddLine(ImVec2(Renderer_Defines::Width / 2, Renderer_Defines::Height / 2 + 8), ImVec2(Renderer_Defines::Width / 2, Renderer_Defines::Height / 2), ImColor(255, 0, 0, 255), 1.0);
	}

	if (Settings::ShowFovCircle and !Settings::fov360)
		Renderer->AddCircle(ImVec2(Renderer_Defines::Width / 2, Renderer_Defines::Height / 2), Settings::FovCircle_Value, SettingsColor::FovCircle, 124);











	try
	{
		float FOVmax = 9999.f;

		float closestDistance = FLT_MAX;
		uintptr_t closestPawn = NULL;
		bool closestPawnVisible = false;


		uintptr_t MyTeamIndex = 0, EnemyTeamIndex = 0;
		uintptr_t GWorld = read<uintptr_t>(UWorld); if (!GWorld) return false;

		uintptr_t Gameinstance = read<uint64_t>(GWorld + StaticOffsets::OwningGameInstance); if (!Gameinstance) return false;

		uintptr_t LocalPlayers = read<uint64_t>(Gameinstance + StaticOffsets::LocalPlayers); if (!LocalPlayers) return false;

		uintptr_t LocalPlayer = read<uint64_t>(LocalPlayers); if (!LocalPlayer) return false;

		PlayerController = read<uint64_t>(LocalPlayer + StaticOffsets::PlayerController); if (!PlayerController) return false;

		static bool once = 0;


		if (!once)
		{
			auto GetPlayerViewPoint_VFTable = *(uintptr_t*)(uintptr_t(PlayerController));
			auto GetPlayerViewPoint_addr = *(uintptr_t*)(GetPlayerViewPoint_VFTable + 0x7B0);

			MH_Initialize();
			MH_CreateHook((PVOID)GetPlayerViewPoint_addr, hk_GetPlayerViewPoint, reinterpret_cast<PVOID*>(&o_GetPlayerViewPoint));
			MH_EnableHook((PVOID)GetPlayerViewPoint_addr);
			once = 1;
		}

		uintptr_t PlayerCameraManager = read<uint64_t>(PlayerController + StaticOffsets::PlayerCameraManager); if (!PlayerCameraManager) return false;

		LocalPawn = read<uint64_t>(PlayerController + StaticOffsets::AcknowledgedPawn);

		uintptr_t Ulevel = read<uintptr_t>(GWorld + StaticOffsets::PersistentLevel); if (!Ulevel) return false;

		uintptr_t AActors = read<uintptr_t>(Ulevel + StaticOffsets::AActors); if (!AActors) return false;

		uintptr_t ActorCount = read<int>(Ulevel + StaticOffsets::ActorCount); if (!ActorCount) return false;


		uintptr_t LocalRootComponent;
		Vector3 LocalRelativeLocation;

		if (valid_pointer(LocalPawn)) {
			LocalRootComponent = read<uintptr_t>(LocalPawn + 0x190);
			LocalRelativeLocation = read<Vector3>(LocalRootComponent + 0x128);
		}
		if (Settings::boatfly)
		{
			if (LocalPawn)
			{

				//AFortAthenaVehicle    FrontMassRatio    0x958    float
				//AFortAthenaVehicle    RearMassRatio    0x95c    float
				uint64_t VEHICLE_STATS = read<uint64_t>(LocalPawn + 0x2348); //AFortPlayerPawn    CurrentVehicle    0x21b8    AActor *
				if (GetAsyncKeyState(VK_SHIFT))write<char>(VEHICLE_STATS + 0x6AA, 1);//AFortAthenaVehicle    bUseGravity : 1    	0x67a    char
				uintptr_t LocalVehicle = read<uintptr_t>(LocalPawn + 0x2348);
				if (LocalVehicle)
				{
					write<float>(LocalVehicle + 0x9A0, -0.100);
					write<float>(LocalVehicle + 0x9A4, -0.100);
				}
			}
		}
		Vector3 HeadPos, Headbox, bottom, bulletpos;

		for (int i = 0; i < ActorCount; i++) {

			auto CurrentActor = read<uintptr_t>(AActors + i * sizeof(uintptr_t));

			auto name = SDK::Classes::UObjectA::GetObjectName(CurrentActor);

			bool IsVisible = false;
			if (valid_pointer(LocalPawn))
			{
					if (Settings::vehicle && strstr(name, xorstr("Valet_BasicTruck_Vehicle_C"))) {

					uintptr_t LlamaRootComponent = read<uintptr_t>(CurrentActor + 0x102A);
					Vector3 LlamaRoot = read<Vector3>(LlamaRootComponent + 0x11C);
					Vector3 ItemPosition1 = read<Vector3>(LlamaRootComponent + 0x128);
					Vector3 headpos1;
					SDK::Classes::AController::WorldToScreen(Vector3(headpos1.x, headpos1.y, headpos1.z), &headpos1);
				
					//ItemRootW2S

					ImColor col;
					col = SettingsColor::ChestESP;

					std::string Text = (char*)("[ Vehicle ]");

					ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());

					std::string null = "";
					std::string finalstring = null + xorstr(" [Vehicle") + std::to_string((int)distance) + xorstr("m]");



					Renderer->AddText(ImVec2(headpos1.x - TextSize.x / 2, headpos1.y + 55 - TextSize.y / 2), col, Text.c_str());
					}
				}
		


			if (valid_pointer(LocalPawn))
			{
				if (strstr(name, xorstr("PlayerPawn"))) {
					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &HeadPos);
					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &bottom);

					SDK::Classes::AController::WorldToScreen(Vector3(HeadPos.x, HeadPos.y, HeadPos.z + 20), &Headbox);
					SDK::Classes::AController::WorldToScreen(bottom, &bottom);

					if (Headbox.x == 0 && Headbox.y == 0) continue;
					if (bottom.x == 0 && bottom.y == 0) continue;
					Vector3 udhead;
					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &udbox);

					SDK::Classes::AController::WorldToScreen(udbox, &udhead);

					//if (NiggerKeyState(VK_RBUTTON))
					//{
					//	write<Vector3>(LocalPawn + 0x310 + 0x140, Vector3(0, -rand() % (int)360, 0));
					//}


					uintptr_t MyState = read<uintptr_t>(LocalPawn + StaticOffsets::PlayerState);
					if (!MyState) continue;

					MyTeamIndex = read<uintptr_t>(MyState + StaticOffsets::TeamIndex);
					if (!MyTeamIndex) continue;

					uintptr_t EnemyState = read<uintptr_t>(CurrentActor + StaticOffsets::PlayerState);
					if (!EnemyState) continue;

					EnemyTeamIndex = read<uintptr_t>(EnemyState + StaticOffsets::TeamIndex);
					if (!EnemyTeamIndex) continue;


					if (CurrentActor == LocalPawn) continue;


					Vector3 NAAAA;

					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &NAAAA);
					SDK::Classes::AController::WorldToScreen(NAAAA, &NAAAA);
					auto dx = NAAAA.x - (Renderer_Defines::Width / 2);
					auto dy = NAAAA.y - (Renderer_Defines::Height / 2);
					auto dist = sqrtf(dx * dx + dy * dy);
					if (dist < Settings::FovCircle_Value && dist < closestDistance) {
						closestDistance = dist;
						closestPawn = CurrentActor;
					}

					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(closestPawn, 68, &udboxA);


					Vector3 viewPoint;

					if (Settings::Aim)
					{
						if (NiggerKeyState(VK_RBUTTON))
						{
							if (InFov(CurrentActor, Settings::FovCircle_Value)) {

								auto camerlocation = GetCameraLocation(PlayerCameraManager);
								//auto originalrot = GetControlRotation(PlayerController);
								auto NewRotation = calcangle(camerlocation, udbox);
								SDK::Classes::AController::SetControlRotation(NewRotation, false);
								//SDK::Classes::AController::SetControlRotation(originalrot, false);

							}
						}
					}
				}
				}




			/*auto camerlocation = GetCameraLocation(PlayerCameraManager)
				auto NewRotation = calcangle(camerlocation, udbox)
				SDK::Classes::AController::SetControlRotation(NewRotation, false);*/

			//if (strstr(name, xorstr("MeatballVehicle_L")) || strstr(name, xorstr("Valet_BasicCar_Vehicle_IO_C")) || strstr(name, xorstr("Valet_BasicCar_Vehicle_IO_C")) || strstr(name, xorstr("Valet_SportsCar_Vehicle_C"))) {

			//	uintptr_t ItemRootComponent = read<uintptr_t>(CurrentActor + 0x190);
			//	Vector3 ItemPosition1 = read<Vector3>(ItemRootComponent + 0x128);
			//	float ItemDist = LocalRelativeLocation.Distance(ItemPosition1) / 100.f;
			//	if (ItemDist < Settings::MaxESPDistance) {
			//		if (Settings::VehiclesESP) {
			//			Vector3 VehiclePosition1;

			//			SDK::Classes::AController::WorldToScreen(ItemPosition1, &VehiclePosition1);


			//			std::string null = "";
			//			std::string finalstring = null + xorstr(" [") + std::to_string((int)distance) + xorstr("m]");


			//			ImVec2 DistanceTextSize = ImGui::CalcTextSize(finalstring.c_str());

			//			ImColor col;

			//			if (IsVisible) {
			//				col = SettingsColor::Distance;
			//			}
			//			else {
			//				col = SettingsColor::Distance_notvisible;
			//			}

			//			//Draw::BackgroundFilledRBG(bottom.x - 30, bottom.y, 50, 20, ImColor(235, 89, 88, 255));
			//			Renderer->AddText(ImVec2(bottom.x - DistanceTextSize.x / 2, bottom.y + DistanceTextSize.y / 2), col, finalstring.c_str());
			//		}
			//	}
			//}
			if (Settings::botai && strstr(name, xorstr("PlayerPawn_Athena_Phoebe_C"))) {

				Vector3 headpos1;
				SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &headpos1);
				SDK::Classes::AController::WorldToScreen(Vector3(headpos1.x, headpos1.y, headpos1.z), &headpos1);

				ImColor col;
				col = SettingsColor::bot;

				std::string Text = (char*)("[ BOT/AI ]");

				ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());

				std::string null = "";
				std::string finalstring = null + xorstr(" [BOT/AI") + std::to_string((int)distance) + xorstr("m]");



				Renderer->AddText(ImVec2(headpos1.x - TextSize.x / 2, headpos1.y + 55 - TextSize.y / 2), col, Text.c_str());

			}
			if (Settings::animal && strstr(name, xorstr("NPC_Pawn_Irwin_Prey_Burt_C")) || strstr(name, xorstr("NPC_Pawn_Irwin_Prey_Nug_C")))
			{

				Vector3 headpos1;
				SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &headpos1);
				SDK::Classes::AController::WorldToScreen(Vector3(headpos1.x, headpos1.y, headpos1.z), &headpos1);

				ImColor col;
				col = SettingsColor::animal;

				std::string Text = (char*)("[ Animal ]");

				ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());

				std::string null = "";
				std::string finalstring = null + xorstr(" [Animal") + std::to_string((int)distance) + xorstr("m]");



				Renderer->AddText(ImVec2(headpos1.x - TextSize.x / 2, headpos1.y + 55 - TextSize.y / 2), col, Text.c_str());

			}

			if (Settings::iobot && strstr(name, xorstr("BP_IOPlayerPawn_Base_C"))) {

				Vector3 headpos1;
				SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &headpos1);
				SDK::Classes::AController::WorldToScreen(Vector3(headpos1.x, headpos1.y, headpos1.z), &headpos1);

				ImColor col;
				col = SettingsColor::io;

				std::string Text = (char*)("[ IO Guard ]");

				ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());

				std::string null = "";
				std::string finalstring = null + xorstr(" [IO Guard") + std::to_string((int)distance) + xorstr("m]");



				Renderer->AddText(ImVec2(headpos1.x - TextSize.x / 2, headpos1.y + 55 - TextSize.y / 2), col, Text.c_str());

			}
			if (Settings::cartp && strstr(name, xorstr("AthenaPlayerMarker_WithCustomization"))) {

				uintptr_t ItemRootComponent = read<uintptr_t>(CurrentActor + 0x190);
				Vector3 ItemPosition1 = read<Vector3>(ItemRootComponent + 0x1280);


				if (Settings::cartp) {
					Vector3 ClosestPing = { ItemPosition1.x, ItemPosition1.y, ItemPosition1.z };
				}
			}

			if (Settings::trader && strstr(name, xorstr("BP_PlayerPawn_Tandem_C"))) {

				Vector3 headpos1;
				SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &headpos1);
				SDK::Classes::AController::WorldToScreen(Vector3(headpos1.x, headpos1.y, headpos1.z), &headpos1);

				ImColor col;
				col = SettingsColor::trader;

				std::string Text = (char*)("[ Trader NPC ]");

				ImVec2 TextSize = ImGui::CalcTextSize(Text.c_str());

				std::string null = "";
				std::string finalstring = null + xorstr(" [Trader NPC") + std::to_string((int)distance) + xorstr("m]");



				Renderer->AddText(ImVec2(headpos1.x - TextSize.x / 2, headpos1.y + 55 - TextSize.y / 2), col, Text.c_str());

			}

		


			
			if (strstr(name, xorstr("BP_PlayerPawn")) || strstr(name, xorstr("PlayerPawn")))
			{

				if (SDK::Utils::CheckInScreen(CurrentActor, Renderer_Defines::Width, Renderer_Defines::Height)) {

					Vector3 HeadPos, Headbox, bottom;

					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &bulletpos);

					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &HeadPos);
					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &bottom);

					SDK::Classes::AController::WorldToScreen(Vector3(HeadPos.x, HeadPos.y, HeadPos.z + 20), &Headbox);
					SDK::Classes::AController::WorldToScreen(bottom, &bottom);


					if (Settings::BoxTypeSelected == 0 or Settings::BoxTypeSelected == 1 or Settings::Skeleton) {
						GetAllBones(CurrentActor);
					}

					//int MostRightBone, MostLeftBone;
					int array[20] = { head2.x, neck.x, pelvis.x, chest.x, leftShoulder.x, rightShoulder.x, leftElbow.x, rightElbow.x, leftHand.x, rightHand.x, leftLeg.x, rightLeg.x, leftThigh.x, rightThigh.x, leftFoot.x, rightFoot.x, leftFeet.x, rightFeet.x, leftFeetFinger.x, rightFeetFinger.x };
					int MostRightBone = array[0];
					int MostLeftBone = array[0];

					for (int mostrighti = 0; mostrighti < 20; mostrighti++)
					{
						if (array[mostrighti] > MostRightBone)
							MostRightBone = array[mostrighti];
					}

					for (int mostlefti = 0; mostlefti < 20; mostlefti++)
					{
						if (array[mostlefti] < MostLeftBone)
							MostLeftBone = array[mostlefti];
					}



					float ActorHeight = (Headbox.y - bottom.y);
					if (ActorHeight < 0) ActorHeight = ActorHeight * (-1.f);

					int ActorWidth = MostRightBone - MostLeftBone;



					if (Settings::Skeleton)
					{

						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Skeleton;
						}
						else {
							col = SettingsColor::Skeleton_notvisible;
						}


						Renderer->AddLine(ImVec2(head2.x, head2.y), ImVec2(neck.x, neck.y), col, 1.f);
						Renderer->AddLine(ImVec2(neck.x, neck.y), ImVec2(chest.x, chest.y), col, 1.f);
						Renderer->AddLine(ImVec2(chest.x, chest.y), ImVec2(pelvis.x, pelvis.y), col, 1.f);
						Renderer->AddLine(ImVec2(chest.x, chest.y), ImVec2(leftShoulder.x, leftShoulder.y), col, 1.f);
						Renderer->AddLine(ImVec2(chest.x, chest.y), ImVec2(rightShoulder.x, rightShoulder.y), col, 1.f);
						Renderer->AddLine(ImVec2(leftShoulder.x, leftShoulder.y), ImVec2(leftElbow.x, leftElbow.y), col, 1.f);
						Renderer->AddLine(ImVec2(rightShoulder.x, rightShoulder.y), ImVec2(rightElbow.x, rightElbow.y), col, 1.f);
						Renderer->AddLine(ImVec2(leftElbow.x, leftElbow.y), ImVec2(leftHand.x, leftHand.y), col, 1.f);
						Renderer->AddLine(ImVec2(rightElbow.x, rightElbow.y), ImVec2(rightHand.x, rightHand.y), col, 1.f);
						Renderer->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(leftLeg.x, leftLeg.y), col, 1.f);
						Renderer->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(rightLeg.x, rightLeg.y), col, 1.f);
						Renderer->AddLine(ImVec2(leftLeg.x, leftLeg.y), ImVec2(leftThigh.x, leftThigh.y), col, 1.f);
						Renderer->AddLine(ImVec2(rightLeg.x, rightLeg.y), ImVec2(rightThigh.x, rightThigh.y), col, 1.f);
						Renderer->AddLine(ImVec2(leftThigh.x, leftThigh.y), ImVec2(leftFoot.x, leftFoot.y), col, 1.f);
						Renderer->AddLine(ImVec2(rightThigh.x, rightThigh.y), ImVec2(rightFoot.x, rightFoot.y), col, 1.f);
						Renderer->AddLine(ImVec2(leftFoot.x, leftFoot.y), ImVec2(leftFeet.x, leftFeet.y), col, 1.f);
						Renderer->AddLine(ImVec2(rightFoot.x, rightFoot.y), ImVec2(rightFeet.x, rightFeet.y), col, 1.f);
						Renderer->AddLine(ImVec2(leftFeet.x, leftFeet.y), ImVec2(leftFeetFinger.x, leftFeetFinger.y), col, 1.f);
						Renderer->AddLine(ImVec2(rightFeet.x, rightFeet.y), ImVec2(rightFeetFinger.x, rightFeetFinger.y), col, 1.f);






					}

					if (Settings::DistanceESP && SDK::Utils::CheckInScreen(CurrentActor, Renderer_Defines::Width, Renderer_Defines::Height)) {
						Vector3 HeadNotW2SForDistance;
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 98, &HeadNotW2SForDistance);
						float distance = LocalRelativeLocation.Distance(HeadNotW2SForDistance) / 100.f;

						std::string null = "";
						std::string finalstring = null + xorstr(" ") + std::to_string((int)distance) + xorstr("m");


						ImVec2 DistanceTextSize = ImGui::CalcTextSize(finalstring.c_str());

						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Distance;
						}
						else {
							col = SettingsColor::Distance_notvisible;
						}
						//Draw::BackgroundFilledRBG(bottom.x - 30, bottom.y, 50, 20, ImColor(235, 89, 88, 255));
						Renderer->AddText(ImVec2(bottom.x - DistanceTextSize.x / 2, bottom.y + DistanceTextSize.y / 2), col, finalstring.c_str());

					}

					if (Settings::playername)
					{
						auto playerState = read<uintptr_t>((uintptr_t)CurrentActor + 0x2a8);

						if (playerState)
						{
							auto name = SDK::Classes::AController::GetPlayerName(playerState);
							if (name.c_str())
							{
								ImColor col;
								if (IsVisible) {
									col = SettingsColor::Distance;
								}
								else {
									col = SettingsColor::Distance_notvisible;
								}

								char* str = new char[4046];
								wcstombs(str, name.c_str(), 13);

								ImVec2 DistanceTextSize = ImGui::CalcTextSize(str);
								Renderer->AddText(ImVec2(head2.x - DistanceTextSize.x / 7, head2.y + DistanceTextSize.y / 7), col, str);
							}
						}
					}

					if (Settings::GetPlayerWeapon)
					{
						auto playerState = read<uintptr_t>((uintptr_t)CurrentActor + 0x2a8 + 0x3F0);

						if (playerState)
						{
							auto name = SDK::Classes::AController::GetPlayerWeapon(playerState);
							if (name.c_str())
							{
								ImColor col;
								if (IsVisible) {
									col = SettingsColor::Distance;
								}
								else {
									col = SettingsColor::Distance_notvisible;
								}

								char* str = new char[4046];
								wcstombs(str, name.c_str(), 13);

								ImVec2 DistanceTextSize = ImGui::CalcTextSize(str);
								Renderer->AddText(ImVec2(head2.x - DistanceTextSize.x / 7, head2.y + DistanceTextSize.y / 7), col, str);
							}
						}
					}
					if (Settings::SnapLines) {
						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Snaplines;
						}
						else {
							col = SettingsColor::Snaplines_notvisible;
						}
						Vector3 LocalPelvis;
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(LocalPawn, 0, &LocalPelvis);
						SDK::Classes::AController::WorldToScreen(LocalPelvis, &LocalPelvis);

						Renderer->AddLine(ImVec2(LocalPelvis.x, LocalPelvis.y), ImVec2(pelvis.x, pelvis.y), col, 1.f);
					}
					if (Settings::Box and Settings::BoxTypeSelected == 2) {

						Vector3 BottomNoW2S;
						Vector3 HeadNoW2S;

						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 68, &HeadNoW2S);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 0, &BottomNoW2S);


						Vector3 bottom1;
						Vector3 bottom2;
						Vector3 bottom3;
						Vector3 bottom4;

						SDK::Classes::AController::WorldToScreen(Vector3(BottomNoW2S.x + 30, BottomNoW2S.y - 30, BottomNoW2S.z), &bottom1);
						SDK::Classes::AController::WorldToScreen(Vector3(BottomNoW2S.x - 30, BottomNoW2S.y - 30, BottomNoW2S.z), &bottom2);
						SDK::Classes::AController::WorldToScreen(Vector3(BottomNoW2S.x - 30, BottomNoW2S.y + 30, BottomNoW2S.z), &bottom3);
						SDK::Classes::AController::WorldToScreen(Vector3(BottomNoW2S.x + 30, BottomNoW2S.y + 30, BottomNoW2S.z), &bottom4);



						Vector3 top1;
						Vector3 top2;
						Vector3 top3;
						Vector3 top4;

						SDK::Classes::AController::WorldToScreen(Vector3(HeadNoW2S.x + 30, HeadNoW2S.y - 30, HeadNoW2S.z), &top1);
						SDK::Classes::AController::WorldToScreen(Vector3(HeadNoW2S.x - 30, HeadNoW2S.y - 30, HeadNoW2S.z), &top2);
						SDK::Classes::AController::WorldToScreen(Vector3(HeadNoW2S.x - 30, HeadNoW2S.y + 30, HeadNoW2S.z), &top3);
						SDK::Classes::AController::WorldToScreen(Vector3(HeadNoW2S.x + 30, HeadNoW2S.y + 30, HeadNoW2S.z), &top4);


						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Box;
						}
						else {
							col = SettingsColor::Box_notvisible;
						}

						Renderer->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), col, 1.f);
						Renderer->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), col, 1.f);
						Renderer->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), col, 1.f);
						Renderer->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), col, 1.f);


						Renderer->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), col, 1.f);
						Renderer->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), col, 1.f);
						Renderer->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), col, 1.f);
						Renderer->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), col, 1.f);


						Renderer->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), col, 1.f);
						Renderer->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), col, 1.f);
						Renderer->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), col, 1.f);
						Renderer->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), col, 1.f);




					}


		
					if (Settings::AimWhileJumping) { 
						write<bool>(LocalPawn + 0x4B35, true); //bADSWhileNotOnGround
					}

					uintptr_t CurrentWeapon = read<uintptr_t>(LocalPawn + 0x868); //CurrentWeapon Offset
					if (Settings::RapidFire) {
						float a = 0;
						float b = 0;
						if (CurrentWeapon) {
							a = read<float>(CurrentWeapon + 0xAB0); //LastFireTime Offset
							b = read<float>(CurrentWeapon + 0xAB4); //LastFireTimeVerified Offset
							write<float>(CurrentWeapon + 0xAB0, a + b - Settings::RapidFireValue); //LastFireTime Offset
						}
					}
				
			


					if (Settings::PlayerFly)
					{
						if (LocalPawn)
						{
							write<float>(LocalPawn + 0x2088, 10.0f); //AFortPlayerPawn	ZiplineJumpStrength	0x1c40	FCurveTableRowHandle
							write<bool>(LocalPawn + 0x2088 + 0x18, true);
						}
					}
			
					if (Settings::radar)
					{

						ImGuiStyle* style = &ImGui::GetStyle();
						style->WindowRounding = 0.2f;

						ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13529413f, 0.14705884f, 0.15490198f, 0.82f));
						ImGuiWindowFlags TargetFlags;

						TargetFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

						if (Settings::radar) {
							ImGui::SetNextWindowPos(ImVec2{ /*220, 400*/15, 830 }, ImGuiCond_Once);
						}
						if (ImGui::Begin(xorstr("radar"), 0, ImVec2(200, 200), -1.f, TargetFlags))
						{
							ImDrawList* Draw = ImGui::GetOverlayDrawList();
							ImVec2 DrawPos = ImGui::GetCursorScreenPos();
							ImVec2 DrawSize = ImGui::GetContentRegionAvail();

							ImVec2 midRadar = ImVec2(DrawPos.x + (DrawSize.x / 2), DrawPos.y + (DrawSize.y / 2));

							ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x - DrawSize.x / 2.f, midRadar.y), ImVec2(midRadar.x + DrawSize.x / 2.f, midRadar.y), IM_COL32(0, 0, 0, 50));
							ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x, midRadar.y - DrawSize.y / 2.f), ImVec2(midRadar.x, midRadar.y + DrawSize.y / 2.f), IM_COL32(0, 0, 0, 50));

							if (PlayerController || PlayerController &&  PlayerCameraManager && LocalPawn && CamRot.y) {
								renderRadar();
							}
						}
						ImGui::PopStyleColor();
						ImGui::End();
					}

					if (Settings::FOVChanger)
					{
						uintptr_t PlayerCameraManager = read<uintptr_t>(0x30 + 0x328);
						write<float>(PlayerCameraManager + 0x29C + 0x4, 120, Settings::FOV); // + 0x4


					}
					if (Settings::fov360) {
						if (Settings::VisibleCheck and IsVisible) {

							auto NewRotation = SDK::Utils::CalculateNewRotation(CurrentActor, LocalRelativeLocation, Settings::AimPrediction);
							SDK::Classes::AController::SetControlRotation(NewRotation, false);
							if (IsVisible and Settings::trigger) {
								mouse_event_(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								mouse_event_(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
					}

		/*			if (Settings::playervisible)
					{

						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Box;
						}
						else {
							col = SettingsColor::Box_notvisible;
						}

						if (PlayerController || PlayerController && PlayerCameraManager && LocalPawn && CamRot.y) {
						renderRadar();
						}
					}
		*/
					if (Settings::boat && GetAsyncKeyState(VK_SHIFT))
					{

						//AFortAthenaVehicle    FrontMassRatio    0x958    float
						//AFortAthenaVehicle    RearMassRatio    0x95c    float

						uintptr_t LocalVehicle = read<uintptr_t>(LocalPawn + 0x2348);
						if (LocalVehicle)
						{
						/*	write<float>(LocalVehicle + 0x9A0, -0.100);
							write<float>(LocalVehicle + 0x9A4, -0.100);*/

							write<float>(LocalVehicle + 0xCB4, 3); //CachedSpeed
							write<float>(LocalVehicle + 0x918, 3); //TopSpeedCurrentMultiplier
							write<float>(LocalVehicle + 0x91C, 3); //PushForceCurrentMultiplier
							write<float>(LocalVehicle + 0x7AC, 100); //WaterEffectsVehicleMaxSpeedKmh
						}

					}		

				
			

					if (GetAsyncKeyState(VK_F4)) {
						std::cout << "\n[info] CurrentVehicle Coordinates";

						uintptr_t MyVehicle = read<uintptr_t>(LocalPawn + 0x2348);
						Vector3 MyVehiclePosition = read<Vector3>(MyVehicle + 0x128);

						std::cout << "\nVehicle Pointer: " << (uintptr_t)MyVehicle;
						std::cout << "\nVehicle Coords X: " << MyVehiclePosition.x;
						std::cout << "\nVehicle Coords Y: " << MyVehiclePosition.y;
						std::cout << "\nVehicle Coords Z: " << MyVehiclePosition.z;
					}



					if (Settings::AimWhileJumping) {
						write<bool>(LocalPawn + 0x4B35, true); //bADSWhileNotOnGround
					}


					if (Settings::nominigun) {
						{
							float TimeHeatWasLastAdded = read<float>(LocalPawn + 0x1474);
							if (TimeHeatWasLastAdded != 0.f) {
								write<float>(LocalPawn + 0x1474, 0.f);
							}
							float TimeOverheatedBegan = read<float>(LocalPawn + 0x1478);

							if (TimeOverheatedBegan != 0.f) {
								write<float>(LocalPawn + 0x1478, 0.f);
							}

							float OverheatValue = read<float>(LocalPawn + 0x146C);
							if (OverheatValue != 0.f) {
								write<float>(LocalPawn + 0x146C, 0.f);
							}

							float WeaponOverheatedAnimation = read<float>(LocalPawn + 0x1460);
							if (WeaponOverheatedAnimation != 0.f) {
								write<float>(LocalPawn + 0x1460, 0.f);
							}
						}
					}
					if (Settings::AirStuck) {
						float CustomTimeDilation = read<float>(LocalPawn + 0x64);
						if (NiggerKeyState(VK_CAPITAL)) {
							if (CustomTimeDilation != 0.1f) {
								write<float>(LocalPawn + 0x64, 0.1f);
							}
						}
						else {
							if (CustomTimeDilation != 1.f) {
								write<float>(LocalPawn + 0x64, 1.f);
							}
						}
					}
					if (Settings::InstantRevive) {

						//AFortPlayerStateAthena	InteractingRebootVan	0x1680	ABuildingGameplayActorSpawnMachine*
						//ABuildingGameplayActorSpawnMachine	ResurrectionStartDelay	0x990	FScalableFloat

						float ResurrectionStartDelay = read<float>(LocalPawn + 0x1768 + 0xA28 );
						if (ResurrectionStartDelay != 0.001f) {
							write<float>(LocalPawn + 0xA28 + 0x990, 0.001f);
						}
					}
					if (Settings::Box and Settings::BoxTypeSelected == 0) {


						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Box;
						}
						else {
							col = SettingsColor::Box_notvisible;
						}

						Draw2DBoundingBox(Headbox, ActorWidth, ActorHeight, col);
					}
					if (Settings::Box and Settings::BoxTypeSelected == 1) {
						ImColor col;
						if (IsVisible) {
							col = SettingsColor::Box;
						}
						else {
							col = SettingsColor::Box_notvisible;
						}

						DrawCorneredBox(Headbox.x - (ActorWidth / 2), Headbox.y, ActorWidth, ActorHeight, col, 1.5);
					}
				}
			}
		}

		if (!LocalPawn) return false;


		for (auto Itemlevel_i = 0UL; Itemlevel_i < read<DWORD>(GWorld + (StaticOffsets::Levels + sizeof(PVOID))); ++Itemlevel_i) {
			uintptr_t ItemLevels = read<uintptr_t>(GWorld + StaticOffsets::Levels);
			if (!ItemLevels) return false;

			uintptr_t ItemLevel = read<uintptr_t>(ItemLevels + (Itemlevel_i * sizeof(uintptr_t)));
			if (!ItemLevel) return false;

			for (int i = 0; i < read<DWORD>(ItemLevel + (StaticOffsets::AActors + sizeof(PVOID))); ++i) {
				uintptr_t ItemsPawns = read<uintptr_t>(ItemLevel + StaticOffsets::AActors);
				if (!ItemsPawns) return false;

				uintptr_t CurrentItemPawn = read<uintptr_t>(ItemsPawns + (i * sizeof(uintptr_t)));

				auto CurrentItemPawnName = SDK::Classes::UObjectA::GetObjectName(CurrentItemPawn);

				bool IsVisible = false;


				if (strstr(CurrentItemPawnName, xorstr("CBGA_ShieldsSmall_C"))) {
					{
						if (Settings::bdistance)
						{
							char DisplayName[256];
							float Distance = (CurrentItemPawn) / 100;
							sprintf_s(DisplayName, TEXT("Shield mushroom (%.fm)"), Distance);

						}
					}
				}
		
		
			/*	if (strstr(CurrentItemPawnName, xorstr("Tiered_Chest")) || strstr(CurrentItemPawnName, xorstr("Tiered_Ammo"))) {


					CHAR text[0xFFFF] = { 0 };

					Vector3 ChestPosition;
					float distance = LocalRelativeLocation.Distance(ChestPosition) / 100.f;


					Vector3 ItemPosition = read<Vector3>(0x190 + 0x128);
					float ItemDist = LocalRelativeLocation.Distance(ItemPosition) / 100.f;


					SDK::Classes::AController::WorldToScreen(ItemPosition, &ChestPosition);

					Vector3 AmmoPosition;
					SDK::Classes::AController::WorldToScreen(ItemPosition, &AmmoPosition);


					std::string null = "";
					std::string finalstring = null + xorstr("Ammo [") + std::to_string((int)distance) + xorstr("m]");
					ImVec2 DistanceTextSize = ImGui::CalcTextSize(finalstring.c_str());

					ImColor col;
					if (IsVisible) {
						col = SettingsColor::Distance;
					}
					else {
						col = SettingsColor::Distance_notvisible;
					}
					Renderer->AddText(ImVec2(ChestPosition.x / 2, ChestPosition.y / 2), col, finalstring.c_str());
					Renderer->AddText(ImVec2(AmmoPosition.x / 2, AmmoPosition.y  / 2), col, finalstring.c_str());


				}
			*/
			




				if (Settings::InstantRevive) {
					if (LocalPawn && PlayerController)
					{
						write<float>(LocalPawn + 0x4280, 0.001); // AFortPlayerPawnAthena->ReviveFromDBNOTime
					}
				}

				if (Settings::fakedownON) {
					if (LocalPawn && PlayerController)
					{
						write<float>(LocalPawn + 0x7C2, 0.01f); //bAllowBuildingActorTeleport::bIsDBNO 0x57E
						Settings::fakedownON = false;
					}
				}
		

				if (Settings::fakedownOff) {
					if (LocalPawn && PlayerController)
					{
						write<float>(LocalPawn + 0x7C2, 1.00f); //bAllowBuildingActorTeleport::bIsDBNO 0x57E
						Settings::fakedownOff = false;
					}
				}

				if (Settings::fs) {
					
					if (GetAsyncKeyState(VK_F2)) {
					std::cout << "\n[info] Input test (aimbot)";
					std::cout << "\nPlayerController: 0x" << PlayerController;

					write<float>(PlayerController + 0x528, 69);
					write<float>(PlayerController + 0x52C, 69);

					std::cout << "\n[fn_input] wrote new input: 69";

					std::cout << "\nFortPointer::LocalPlayerController::InputYawScale: 0x" << read<float>(PlayerController + 0x528);
					std::cout << "\nFortPointer::LocalPlayerController::InputPitchScale: 0x" << read<float>(PlayerController + 0x52C);

					}
				}
	

				if (valid_pointer(LocalPawn))
				{
					if (strstr(CurrentItemPawnName, xorstr("B_Prj_Bullet_DMR")) || strstr(CurrentItemPawnName, xorstr("B_Prj_Bullet_Sniper")) || strstr(CurrentItemPawnName, xorstr("B_Prj_Bullet_Sniper_Heavy_C")) || strstr(CurrentItemPawnName, xorstr("B_Prj_Bullet"))) {
						auto CurrentItemPos = read<Vector3>(CurrentItemPawn + 0x190 + 0x128);

						SDK::Classes::AController::WorldToScreen(CurrentItemPos, &CurrentItemPos);

						/*		static char memes[128];
								static wchar_t wmemes[128];
								sprintf(memes, ("[ PROJECTILE %d m ]"), distance);*/


						SDK::Classes::AController::FHitResult xxxx;
						SDK::Classes::AController::K2_SetActorLocation(CurrentItemPawn, bulletpos, false, true, &xxxx);
					}
				}

			}
			}

			if (NiggerKeyState(VK_RBUTTON) and closestPawn) {

				//Silent
				if (Settings::SilentAim) {
					TargetPawn = closestPawn;
				}

				//Bullettp
				if (Settings::Bullettp) {
					TargetPawn = closestPawn;
				}
			}
			else {
				TargetPawn = 0;
			}
	}
	catch (...) {}
}



struct Canvas_K2_DrawLine_Params
{
	ImVec2                                   ScreenPositionA_69;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	ImVec2                                   ScreenPositionB_69;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Thickness_69;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	color                                RenderColor_69;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

struct UCanvas_K2_DrawText_Params
{


	class UFont* RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FString                                     RenderText;                                               // (Parm, ZeroConstructor)
	struct FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

void K2_DrawLine(uintptr_t* Canvas, ImVec2 ScreenPositionA_69, ImVec2 ScreenPositionB_69, float Thickness_69, color RenderColor_69)
{
	static PVOID fn = NULL;
	if (!fn)
		fn = FN::FindObject("K2_DrawLine");

	Canvas_K2_DrawLine_Params params;
	params.ScreenPositionA_69 = ScreenPositionA_69;
	params.ScreenPositionB_69 = ScreenPositionB_69;
	params.Thickness_69 = Thickness_69;
	params.RenderColor_69 = RenderColor_69;

	FN::ProcessEvent((uintptr_t)Canvas, fn, &params);
}

void K2_DrawText(UObject* Canvas, class UFont* RenderFont, const class FString& RenderText, const struct FVector2D& ScreenPosition, const struct FVector2D& Scale, const struct FLinearColor& RenderColor, float Kerning, const struct FLinearColor& ShadowColor, const struct FVector2D& ShadowOffset, bool bCentreX, bool bCentreY, bool bOutl, const struct FLinearColor& OutlineColor)
{

	
	static PVOID fn = NULL;
	if (!fn)
		fn = FN::FindObject("K2_DrawText");



	UCanvas_K2_DrawText_Params params;
	params.RenderFont = RenderFont;
	params.RenderText = RenderText;
	params.RenderColor = RenderColor;
	params.Kerning = Kerning;
	params.ShadowColor = ShadowColor;
	params.bCentreX = bCentreX;
	params.bCentreY = bCentreY;
	params.bOutlined = bOutl;
	params.OutlineColor = OutlineColor;


	FN::ProcessEvent((uintptr_t)Canvas, fn, &params);
}


void ColorAndStyle() {

	
	ImGui::StyleColorsClassic();
	auto& Style = ImGui::GetStyle();
	ImGuiStyle* style = &ImGui::GetStyle();
	Style.WindowRounding = 9.000f;
	Style.WindowBorderSize = 2.000;
	style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
	style->Colors[ImGuiCol_TitleBg] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_SliderGrab] = ImColor(111, 3, 252);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(111, 3, 252);
	style->Colors[ImGuiCol_Button] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_WindowBg] = ImColor(27, 27, 27, 255);
	style->Colors[ImGuiCol_ChildWindowBg] = ImColor(24, 24, 24, 255);
	style->Colors[ImGuiCol_PopupBg] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_Border] = ImColor(136, 38, 156, 255);
	style->Colors[ImGuiCol_BorderShadow] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_MenuBarBg] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_CheckMark] = ImColor(136, 38, 156, 255);
	style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_Column] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_ColumnHovered] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_ColumnActive] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_PlotLines] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_PlotHistogram] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_TextSelectedBg] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_Separator] = ImColor(31, 31, 31, 255);



}

void Active() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(55, 55, 55);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(55, 55, 55);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 0, 0);
}
void Hovered() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(55, 55, 55);
}

void Active1() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(0, 55, 0);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 55, 0);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(55, 0, 0);
}
void Hovered1() {
	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->Colors[ImGuiCol_Button] = ImColor(55, 0, 0);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(55, 0, 0);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 55, 0);
}


ImGuiWindow& CreateScene() {
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin(xorstr("##mainscenee"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	return *ImGui::GetCurrentWindow();
}

VOID MenuAndDestroy(ImGuiWindow& window) {




	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);


	if (ShowMenu) {
		ColorAndStyle();
		ImGui::SetNextWindowSize({  530, 500  });
		ImGuiStyle* style = &ImGui::GetStyle();
		static int maintabs = 0;
		static int esptabs = 0;
		if (ImGui::Begin(xorstr("ProxyFn Internal by naze#1250 and LeProxy#1336"), &ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {

			ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetIO().MousePos, ImVec2(ImGui::GetIO().MousePos.x + 7.4f, ImGui::GetIO().MousePos.y + 7.4f), ImColor(3, 3, 3, 255));

	            ImGui::SetCursorPos({ 8.f,31.f });
				if (ImGui::Button("Aimbot", { 164.f,29.f }))
				{
					maintabs = 0;
				}
				ImGui::SetCursorPos({ 181.f,31.f });
				if (ImGui::Button("Visuals", { 164.f,29.f }))
				{
					maintabs = 1;
				}
				ImGui::SetCursorPos({ 353.f,31.f });
				if (ImGui::Button("Mods", { 164.f,29.f }))
				{
					maintabs = 2;
				}
				ImGui::SetCursorPos({ 524.f,31.f });
				if (ImGui::Button("Misc", { 164.f,29.f }))
				{
					maintabs = 3;
				}



			ImGui::Separator(8);


			if (maintabs == 0) {

				ImGui::Text(TEXT("-> EasyAntiCheat ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 0.9f), TEXT("Semi Undetected"));
				ImGui::Text(TEXT("-> BattlEye = GAY")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.92f, 0.92f, 0.3f, 0.9f), TEXT("MEGA VERY DETECTED"));
				ImGui::Text(xorstr("If you bought it you got scammed"));
				ImGui::Text(xorstr("if you press f4 you see in the exe vehicle Coordinates"));

				ImGui::Text(xorstr("Aimbot"));
				ImGui::Checkbox(xorstr("Memory Aim"), &Settings::Aim);
				ImGui::Checkbox(xorstr("Sticky Silent (360)"), &Settings::SilentAim);
				ImGui::Checkbox(xorstr("Pediction"), &Settings::AimPrediction);



				ImGui::Combo(xorstr("Aimbone"), &Menu_AimBoneInt, AimBone_TypeItems, sizeof(AimBone_TypeItems) / sizeof(*AimBone_TypeItems));

				if (Menu_AimBoneInt == 0) Settings::aimbone = 66;
				if (Menu_AimBoneInt == 1) Settings::aimbone = 65;
				if (Menu_AimBoneInt == 2) Settings::aimbone = 2;
				if (Menu_AimBoneInt == 3) Settings::aimbone = 0;

				ImGui::PushItemWidth(190);
				ImGui::SliderInt(xorstr("Aimbot Smooth"), &Settings::smooth, 1, 20);


				ImGui::SliderInt(xorstr("Fov Circle Value"), &Settings::FovCircle_Value, 30, 800);
				ImGui::ColorEdit4(xorstr("Fov Circle"), SettingsColor::FovCircle_float, ImGuiColorEditFlags_NoInputs);







			}

			else if (maintabs == 1) {


				

				if (esptabs == 0) {
					ImGui::Checkbox(xorstr("Box ESP"), &Settings::Box);
					if (Settings::Box) {
						ImGui::Combo(xorstr("Box"), &Settings::BoxTypeSelected, ESP_Box_TypeItems, sizeof(ESP_Box_TypeItems) / sizeof(*ESP_Box_TypeItems));
					}
					ImGui::Checkbox(xorstr("Distance"), &Settings::DistanceESP);
					ImGui::Checkbox(xorstr("Snaplines"), &Settings::SnapLines);
					ImGui::Checkbox(xorstr("Skeleton"), &Settings::Skeleton);
					ImGui::Checkbox(xorstr("Player Visible Check (MAYBE CRASH)"), &Settings::playervisible);
					ImGui::Checkbox(xorstr("Bot/Ai Check"), &Settings::botai);
					ImGui::Checkbox(xorstr("IO Bot Check"), &Settings::iobot);
					ImGui::Checkbox(xorstr("Trader NPC"), &Settings::trader);
					ImGui::Checkbox(xorstr("Aniaml"), &Settings::animal);
					ImGui::Checkbox(xorstr("Player Name"), &Settings::playername);
					ImGui::Checkbox(xorstr("Player Weapon"), &Settings::GetPlayerWeapon);

					
					ImGui::SliderInt(xorstr("Visuals Distance"), &Settings::MaxESPDistance, 10, 500);

					ImGui::Checkbox(xorstr("Show Fov Circle"), &Settings::ShowFovCircle);
					ImGui::Checkbox(xorstr("Crosshair"), &Settings::crosshair);
					ImGui::Checkbox(xorstr("Nazi Crosshiar"), &Settings::sussy);


				}




			}
			else if (maintabs == 2) {
				ImGui::Text(xorstr("All Exploits Working (UNSAFE!!!)"));
				ImGui::Checkbox(xorstr("RapidFire"), &Settings::RapidFire);
				ImGui::Checkbox(xorstr("Aim While Jumping"), &Settings::AimWhileJumping);
				ImGui::Checkbox(xorstr("Player fly"), &Settings::PlayerFly); 
				ImGui::Checkbox(xorstr("Radar"), &Settings::radar);
				ImGui::Checkbox(xorstr("Spinbot"), &Settings::spinbot);
				ImGui::Checkbox(xorstr("Boat Boost (SHIFT)"), &Settings::boat);
				ImGui::Checkbox(xorstr("No Minigun Cooldown"), &Settings::nominigun);
				ImGui::Checkbox(xorstr("Boat fly"), &Settings::boatfly);
				ImGui::Checkbox(xorstr("Car Teleport to ping"), &Settings::cartp);
				ImGui::Checkbox(xorstr("Instant Rebot (E)"), &Settings::InstantRevive);
				ImGui::Checkbox(xorstr("Airstuck (SHIFT)"), &Settings::AirStuck);
				ImGui::Checkbox(xorstr("Instant Revive"), &Settings::InstantRevive);
				ImGui::Checkbox(xorstr("Bullet Teleport"), &Settings::Bullettp);
				if (Settings::RapidFire) {
					ImGui::SliderFloat(xorstr("RapidFire value"), &Settings::RapidFireValue, 0.1, 1.0);
				}
			}
			else if (maintabs == 3) {



			}
			ImGui::End();
		}
	}
	if (Settings::sussy) {

	SwastikaCrosshair();
	}

	ImGui::Render();
}




HRESULT present_hooked(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
	static float width = 0;
	static float height = 0;
	static HWND hWnd = 0;
	if (!device)
	{

		//MessageBoxA(NULL, "IM INTO THE PRESENT HOOOOKED!!", "", MB_OK);

		swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
		device->GetImmediateContext(&immediateContext);
		//MessageBoxA(NULL, "Before RenderTargetDefine and release", "", MB_OK);
		ID3D11Texture2D* renderTarget = nullptr;
		swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
		device->CreateRenderTargetView(renderTarget, nullptr, &renderTargetView);
		renderTarget->Release();
		//MessageBoxA(NULL, "Before backBuffer", "", MB_OK);
		ID3D11Texture2D* backBuffer = 0;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&backBuffer);
		D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
		backBuffer->GetDesc(&backBufferDesc);
		//MessageBoxA(NULL, "Before FindWindow", "", MB_OK);
		HWND hWnd = LI_FN(FindWindowA)(xorstr("UnrealWindow"), xorstr("Fortnite  "));
		//if (!width) {
			//oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
			//oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&WndProc)); // Hook
		//}

		width = (float)backBufferDesc.Width;
		height = (float)backBufferDesc.Height;
		backBuffer->Release();

		ImGui::GetIO().Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\Tahoma.ttf"), 13.0f);

		ImGui_ImplDX11_Init(hWnd, device, immediateContext);
		ImGui_ImplDX11_CreateDeviceObjects();

	}
	immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
	//MessageBoxA(NULL, "Before CreateScene", "", MB_OK);
	auto& window = CreateScene();

	if (ShowMenu) {
		ImGuiIO& io = ImGui::GetIO();

		POINT p;
		SpoofCall(GetCursorPos, &p);
		io.MousePos.x = p.x;
		io.MousePos.y = p.y;


		//MessageBoxA(NULL, "Before NiggerKeyState", "", MB_OK);
		if (NiggerKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].y = io.MousePos.y;
		}
		else {
			io.MouseDown[0] = false;
		}
	}

	// Call this one here!
	gaybow(window);
	EntitiyLoop();
	//MessageBoxA(NULL, "Before second NiggerKeyState", "", MB_OK);
	if (NiggerKeyState(VK_INSERT) & 1)
	{
		ShowMenu = !ShowMenu;
	}

	//MessageBoxA(NULL, "Before MenuAndDestroy", "", MB_OK);
	MenuAndDestroy(window);
	//MessageBoxA(NULL, "Before TheReturn", "", MB_OK);
	return SpoofCall(present_original, swapChain, syncInterval, flags);
}



HRESULT resize_hooked(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return SpoofCall(resize_original, swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}





PVOID SpreadCaller = nullptr;
BOOL(*Spread)(PVOID a1, float* a2, float* a3);
BOOL SpreadHook(PVOID a1, float* a2, float* a3)
{
	if (Settings::NoSpread && _ReturnAddress() == SpreadCaller && IsAiming()) {
		return 0;
	}

	return SpoofCall(Spread, a1, a2, a3);
}









bool HookFunctions::Init(bool NoSpread, bool CalcShot, bool Speed) {
	if (!NoSpreadInitialized) {
		if (NoSpread) {
		}
	}
	//if (!CalcShotInitialized) {
	//	if (CalcShot) {
	//		auto CalcShotAddr = MemoryHelper::PatternScan(xorstr("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 33 FF 89 7C 24 30 48 39 3D ? ? ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 1D ? ? ? ? 48 85 C0 0F 84 ? ? ? ? FF D0 4C 8B F8"));
	//		HookHelper::InsertHook(CalcShotAddr, (uintptr_t)CalculateShotHook, (uintptr_t)&CalculateShot);
	//		CalcShotInitialized = true;
	//	}
	//}
	if (!SpeedInitialized) {
		if (Speed) {
			Speed::InitSpeedHack();
			SpeedInitialized = true;
		}
	}
	return true;
}


//if (!CalcShotInitialized) {
//	if (CalcShot) {
//		auto CalcShotAddr = MemoryHelper::PatternScan(xorstr("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8D A1 ? ? ? ?"));
//		HookHelper::InsertHook(CalcShotAddr, (uintptr_t)CalculateShotHook, (uintptr_t)&CalculateShot);
//		CalcShotInitialized = true;
//	}
//}
//if (!SpeedInitialized) {
//	if (Speed) {
//		Speed::InitSpeedHack();
//		SpeedInitialized = true;
//	}
//}
//return true;
//



//#include <MinHook.h>
//#pragma comment(lib, "minhook.lib")
bool InitializeHack()
{
	if (!HookHelper::DiscordModule) {
		MessageBoxA(NULL, "Enable discord overlay, try restarting discord as admin!", "Monkey Error 1337", MB_OK);
		exit(0);
	}
	#pragma warning(disable : 4996)
	AllocConsole();
	static_cast<VOID>(freopen(("CONIN$"), ("r"), stdin));
	static_cast<VOID>(freopen(("CONOUT$"), ("w"), stdout));
	static_cast<VOID>(freopen(("CONOUT$"), ("w"), stderr));
						Beep(523, 500);

	MessageBoxA(0, "g_pSpoofGadget", "Succesfull", 0);
	MessageBoxA(0, "Hunde Freestyle", "Wichtig Und Richtig", 0);
	MessageBoxA(0, "Dortmund", "Berliner", 0);

	Renderer_Defines::Width = LI_FN(GetSystemMetrics)(SM_CXSCREEN);
	Renderer_Defines::Height = LI_FN(GetSystemMetrics)(SM_CYSCREEN);
	UWorld = MemoryHelper::PatternScan("48 89 05 ? ? ? ? 48 8B 4B 78");
	UWorld = RVA(UWorld, 7);

	FreeFn = MemoryHelper::PatternScan(xorstr("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0"));
	ProjectWorldToScreen = MemoryHelper::PatternScan(xorstr("E8 ? ? ? ? 84 C0 74 4D 4C 8D 45 20"));
	ProjectWorldToScreen = RVA(ProjectWorldToScreen, 5);

	//LineOfS = MemoryHelper::PatternScan(xorstr("48 8B C4 48 89 58 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 20 45 8A E9"));

	GetNameByIndex = MemoryHelper::PatternScan(xorstr("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B 01 48 8B F2"));
	BoneMatrix = MemoryHelper::PatternScan(xorstr("E8 ? ? ? ? 0F 10 40 68"));
	BoneMatrix = RVA(BoneMatrix, 5);

	GGObject = MemoryHelper::PatternScan(xorstr("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1"));
	GGObject = RVA(GGObject, 7);

	FN::objects = (GObjects*)GGObject;

	uintptr_t* KismetStringLibrary = 0;
	uintptr_t* Canvas = 0;

	auto Dortmund = FN::FindObject("KismetStringLibrary");
	KismetStringLibrary = (uintptr_t*)Dortmund;
	std::cout << "KismetStringLibrary:" << Dortmund << std::endl;

	auto UWorld = MemoryHelper::PatternScan("48 89 05 ? ? ? ? 48 8B 4B 78");
	std::cout << "Uworld:" << UWorld << std::endl;

	
	auto DortmundA = FN::FindObject("Canvas");
	Canvas = (uintptr_t*)DortmundA;
	std::cout << "Canvas:" << DortmundA << std::endl;
	std::cout << "g_pSpoofGadget" << std::endl;

	//auto UObjectPtr = MemoryHelper::PatternScan(xorstr("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1")); //Gobject
	//FN::objects = decltype(FN::objects)(RVA(UObjectPtr, 7));

	//ObjectsAddresses::FOV = SpoofCall(FN::FindObject, (const char*)xorstr("FOV"));
	//ObjectsAddresses::AddYawInput = SpoofCall(FN::FindObject, (const char*)xorstr("AddYawInput"));
	//ObjectsAddresses::AddPitchInput = SpoofCall(FN::FindObject, (const char*)xorstr("AddPitchInput"));
	//ObjectsAddresses::GetCameraLocation = SpoofCall(FN::FindObject, (const char*)xorstr("GetCameraLocation"));
	//ObjectsAddresses::IsDead = SpoofCall(FN::FindObject, (const char*)xorstr("IsDead"));

	NiggerKeyState = (LPFN_MBA)LI_FN(GetProcAddress)(LI_FN(GetModuleHandleA)(xorstr("win32u.dll")), xorstr("NtUserGetAsyncKeyState"));

	//auto OwningGameInstance = *(uintptr_t*)(UWorld + 0x1a8);
	//if (!OwningGameInstance) return FALSE;
	//auto LocalPlayers = *(uintptr_t*)(OwningGameInstance + 0x38);
	//if (!LocalPlayers) return FALSE;
	//auto LocalPlayer = *(uintptr_t*)(LocalPlayers);
	//if (!LocalPlayer) return FALSE;
	//auto PlayerController = *(uintptr_t*)(LocalPlayers + 0x30);
	//if (!PlayerController) return FALSE;

	//auto GetPlayerViewPoint_VFTable = *(uintptr_t*)(uintptr_t(PlayerController));
	//auto GetPlayerViewPoint_addr = *(uintptr_t*)(GetPlayerViewPoint_VFTable + 0x7A0); //GetPlayerViewpoint

	//MH_Initialize();

	//MH_CreateHook((PVOID)GetPlayerViewPoint_addr, hk_GetPlayerViewPoint, reinterpret_cast<PVOID*>(&o_GetPlayerViewPoint));
	//MH_EnableHook((PVOID)GetPlayerViewPoint_addr);
	auto level = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC sd;
	{
		ZeroMemory(&sd, sizeof sd);
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = LI_FN(FindWindowA)(xorstr("UnrealWindow"), xorstr("Fortnite  "));
		sd.SampleDesc.Count = 1;
		sd.Windowed = TRUE;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	IDXGISwapChain* swap_chain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;

	LI_FN(D3D11CreateDeviceAndSwapChain)(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &level, 1, D3D11_SDK_VERSION, &sd, &swap_chain, &device, nullptr, &context);

	auto* swap_chainvtable = reinterpret_cast<uintptr_t*>(swap_chain);
	swap_chainvtable = reinterpret_cast<uintptr_t*>(swap_chainvtable[0]);

	DWORD old_protect;
	present_original = reinterpret_cast<present_fn>(reinterpret_cast<DWORD_PTR*>(swap_chainvtable[8]));
	LI_FN(VirtualProtect)(swap_chainvtable, 0x2B8, PAGE_EXECUTE_READWRITE, &old_protect);
	swap_chainvtable[8] = reinterpret_cast<DWORD_PTR>(present_hooked);
	LI_FN(VirtualProtect)(swap_chainvtable, 0x2B8, old_protect, &old_protect);

	DWORD old_protect_resize;
	resize_original = reinterpret_cast<resize_fn>(reinterpret_cast<DWORD_PTR*>(swap_chainvtable[13]));
	LI_FN(VirtualProtect)(swap_chainvtable, 0x2B8, PAGE_EXECUTE_READWRITE, &old_protect_resize);
	swap_chainvtable[13] = reinterpret_cast<DWORD_PTR>(resize_hooked);
	LI_FN(VirtualProtect)(swap_chainvtable, 0x2B8, old_protect_resize, &old_protect_resize);
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//if (InitMain() == false) { return 0; }
		InitializeHack();
	}
	return TRUE;
}
