#pragma once
#include <numbers>
#include <cmath>

#define M_PI 3.14159265358979323846264338327950288419716939937510
static ULONG ww = GetSystemMetrics(SM_CXSCREEN);
static ULONG wh = GetSystemMetrics(SM_CYSCREEN);
namespace UE4Structs
{
	typedef struct _ValEntity {
		uintptr_t Actor;
	}ValEntity;

	std::vector<ValEntity> ValList;

	struct view_matrix_t {
		float* operator[ ](int index) {
			return matrix[index];
		}

		float matrix[4][4];
	};

	struct Vector3
	{
		// constructor
		constexpr Vector3(
			const float x = 0.f,
			const float y = 0.f,
			const float z = 0.f) noexcept :
			x(x), y(y), z(z) { }

		// operator overloads
		constexpr const Vector3& operator-(const Vector3& other) const noexcept
		{
			return Vector3{ x - other.x, y - other.y, z - other.z };
		}

		constexpr const Vector3& operator+(const Vector3& other) const noexcept
		{
			return Vector3{ x + other.x, y + other.y, z + other.z };
		}

		constexpr const Vector3& operator/(const float factor) const noexcept
		{
			return Vector3{ x / factor, y / factor, z / factor };
		}

		constexpr const Vector3& operator*(const float factor) const noexcept
		{
			return Vector3{ x * factor, y * factor, z * factor };
		}

		constexpr const bool operator>(const Vector3& other) const noexcept {
			return x > other.x && y > other.y && z > other.z;
		}

		constexpr const bool operator>=(const Vector3& other) const noexcept {
			return x >= other.x && y >= other.y && z >= other.z;
		}

		constexpr const bool operator<(const Vector3& other) const noexcept {
			return x < other.x && y < other.y && z < other.z;
		}

		constexpr const bool operator<=(const Vector3& other) const noexcept {
			return x <= other.x && y <= other.y && z <= other.z;
		}

		// utils
		constexpr const Vector3& ToAngle() const noexcept
		{
			return Vector3{
				std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
				std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
				0.0f };
		}

		float length() const {
			return std::sqrt(x * x + y * y + z * z);
		}

		float length2d() const {
			return std::sqrt(x * x + y * y);
		}

		constexpr const bool IsZero() const noexcept
		{
			return x == 0.f && y == 0.f && z == 0.f;
		}

		Vector3 world_to_screen(view_matrix_t matrix) const {
			float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
			float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];

			float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

			float inv_w = 1.f / w;
			_x *= inv_w;
			_y *= inv_w;

			// Check the values at this point
			//std::cout << "_x: " << _x << ", _y: " << _y << ", w: " << w << std::endl;
			float screen_x = ww * 0.5f;
			float screen_y = wh * 0.5f;

			screen_x += 0.5f * _x * ww + 0.5f;
			screen_y -= 0.5f * _y * wh + 0.5f;

			// Check the final screen coordinates
			//std::cout << "screen_x: " << screen_x << ", screen_y: " << screen_y << std::endl;

			return { screen_x, screen_y, w };
		}

		// struct data
		float x, y, z;
	};

}

namespace ColorStructs
{

	typedef struct
	{
		DWORD R;
		DWORD G;
		DWORD B;
		DWORD A;
	}RGBA;

	class Color
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
		RGBA greens = { 25,255,25,140 };
		RGBA envy = { 0,255,255,255 };
		RGBA black = { 0,0,0,255 };
		RGBA neger = { 215, 240, 180, 255 };
		RGBA negernot = { 222, 180, 200, 255 };
		RGBA gray = { 128,128,128,255 };
		RGBA white = { 255,255,255,255 };
		RGBA blues = { 30,144,255,255 };
		RGBA lightblue = { 135,206,250,255 };
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

		RGBA filled = { 0, 0, 0, 150 };

		RGBA Plum = { 221,160,221,160 };

	};
	Color Col;
}

