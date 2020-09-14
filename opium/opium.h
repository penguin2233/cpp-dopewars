#pragma once
#ifdef OPIUM_EXPORTS
#define OPIUM_API __declspec(dllexport)
#else
#define OPIUM_API __declspec(dllimport)
#endif

bool antiPiracy();
void loadDLC();
extern "C" {
	__declspec(dllexport) void __cdecl dlcMagic(int h);
}
