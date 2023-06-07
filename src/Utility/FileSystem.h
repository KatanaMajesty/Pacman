#pragma once

#include <string>
#include <filesystem>

class FileSystem
{
private:
	FileSystem();

public:
	FileSystem(const FileSystem&) = delete;
	FileSystem& operator=(const FileSystem&) = delete;

	static FileSystem& Get();

	const std::filesystem::path& GetExecutablePath() const { return m_executablePath; }
	const std::filesystem::path& GetAssetsPath() const { return m_assetsPath; }

private:
	std::filesystem::path m_executablePath;
	std::filesystem::path m_assetsPath;
};