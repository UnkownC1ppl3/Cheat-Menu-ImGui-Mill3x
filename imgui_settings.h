#include "imgui.h"

namespace c
{
	inline ImVec4 accent = ImColor(118, 187, 117);
	inline ImVec4 separator = ImColor(22, 23, 26);

	namespace bg
	{
		inline ImVec4 background = ImColor(15, 15, 15);
		inline ImVec2 size = ImVec2(650, 570);
		inline float rounding = 8.f;
	}

	namespace child
	{
		inline ImVec4 background = ImColor(17, 17, 18);
		inline ImVec4 cap = ImColor(20, 21, 23);
		inline float rounding = 8.f;
	}

	namespace page
	{
		inline ImVec4 background_active = ImColor(31, 33, 38);
		inline ImVec4 background = ImColor(22, 23, 25);

		inline ImVec4 text_hov = ImColor(69, 74, 95);
		inline ImVec4 text = ImColor(68, 71, 85);

		inline float rounding = 4.f;
	}

	namespace elements
	{
		inline ImVec4 background_hovered = ImColor(31, 33, 38);
		inline ImVec4 background = ImColor(22, 23, 25);
		inline float rounding = 2.f;
	}

	namespace checkbox
	{
		inline ImVec4 mark = ImColor(0, 0, 0, 255);
	}

	namespace text
	{
		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hov = ImColor(69, 74, 95);
		inline ImVec4 text = ImColor(68, 71, 85);
	}
}