#include <iostream>
#include "file.h"
#include "player.h"

int main()
{
    FileStorage fileStorage = listFilesInDirectory(".\\music");
    fileStorage.createPlaylist();

    std::cout << "Loading playlist" << std::endl;

    if (fileStorage.playlist.empty())
    {
        std::cout << "No audio files found in the directory." << std::endl;
        return -1;
    }

    for (const auto& [index, filePath] : fileStorage.playlist)
    {
        std::cout << index << ": " << filePath << std::endl;
    }

    std::cout << "Select file: ";
    int selectedIndex;
    std::cin >> selectedIndex;

    playFile(fileStorage.playlist[selectedIndex]);

    return 0;
}