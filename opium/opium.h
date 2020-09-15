#pragma once
#ifdef OPIUM_EXPORTS
#define OPIUM_API __declspec(dllexport)
#else
#define OPIUM_API __declspec(dllimport)
#endif

extern "C" {
	__declspec(dllexport) int __cdecl dlcMagic(int h);
}
