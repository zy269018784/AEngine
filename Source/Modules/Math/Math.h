#pragma once

inline int Clamp(int A, int Min, int Max)
{
	if (A < Min)
		return Min;
	if (A > Max)
		return Max;
	return A;
}

inline int Mod(int a, int m) 
{
	int r = a % m;
	return r < 0 ? r + m : r;
}