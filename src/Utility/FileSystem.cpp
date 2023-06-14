#include "pch.h"

#define WIN32_LEAN_AND_MEAN
#define	NOMINMAX
#include <Windows.h>

FileSystem::FileSystem()
{
	CHAR filepath[MAX_PATH];
	GetModuleFileNameA(NULL, filepath, MAX_PATH);
	m_executablePath = std::string(filepath);
	m_assetsPath = m_executablePath.parent_path().parent_path().parent_path() / "Assets";
}

FileSystem& FileSystem::Get()
{
	static FileSystem instance;
	return instance;
}
