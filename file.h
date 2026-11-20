#include <iostream>
#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

enum class FileType
{
    MP3,
    WAV,
    FLAC,
    UNKNOWN
};

struct FileStorage
{
    std::vector<fs::path> mp3Files;
    std::vector<fs::path> wavFiles;
    std::vector<fs::path> flacFiles;
    std::map<int, fs::path> playlist;

    void createPlaylist()
    {
        int index = 0;
        for (const auto& file : mp3Files)
        {
            playlist[index++] = file;
        }

        for (const auto& file : wavFiles)
        {
            playlist[index++] = file;
        }

        for (const auto& file : flacFiles)
        {
            playlist[index++] = file;
        }
    }
};

FileType getFileType(const fs::path filePath)
{
    const auto extension = filePath.extension();

    if (extension == ".mp3")
        return FileType::MP3;
    else if (extension == ".wav")
        return FileType::WAV;
    else if (extension == ".flac")
        return FileType::FLAC;
    else
        return FileType::UNKNOWN;
}

FileStorage listFilesInDirectory(const std::string& directoryPath)
{
    FileStorage fileStorage;
    try
    {
        for (const auto& entry : fs::directory_iterator(directoryPath))
        {
            const fs::path filePath = entry.path();
            const bool file = entry.is_regular_file();

            if (file)
            {
                const FileType fileType = getFileType(filePath);
                switch (fileType)
                {
                    case FileType::MP3:
                        fileStorage.mp3Files.push_back(filePath);
                        break;
                    case FileType::WAV:
                        fileStorage.wavFiles.push_back(filePath);
                        break;
                    case FileType::FLAC:
                        fileStorage.flacFiles.push_back(filePath);
                    default:
                        break;
                }
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    return fileStorage;
}