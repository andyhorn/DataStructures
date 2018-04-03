#include <iostream>
#include <windows.h>
#include <fileapi.h>
#include <winuser.h>
#include <handleapi.h>
#include "GenTree.h"
#include <fstream>

using std::ofstream;

static const wchar_t* READ_DIR = L"C:\\Users\\andyj\\Documents";
static const char* WRITE_DIR = "C:\\Users\\andyj\\Documents\\DirectoryTree.txt";

bool ListDirectoryContents(const wchar_t *sDir, GenTree &tree);

void PrintNode(GenNode *);

int main()
{
	std::cout << "Reading directory..." << endl;
	GenTree tree;
	ListDirectoryContents(READ_DIR, tree);
	std::cout << "Writing to file..." << endl;
	tree.DepthFirst(PrintNode);
	std::cout << "Done!" << endl;
	std::cin.get();
	return 0;
}

bool ListDirectoryContents(const wchar_t *sDir, GenTree &tree)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	wchar_t sPath[2048];
	tree.AddNode(new GenNode(sDir, nullptr, true));
	//Specify a file mask. *.* = We want everything! 
	wsprintf(sPath, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
		return false;
	}

	do
	{
		//Find first file will always return "."
		//    and ".." as the first two directories. 
		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{
			//Build up our file path using the passed in 
			//  [sDir] and the file/foldername we just found: 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

			/* Need a way to create a node based on end of pathname, whether it be a dir or a file. */
			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				// create pointer to current working directory
				// change working directory to new directory, add children
				GenNode *temp = nullptr;
				// wprintf(L"Directory: %s\n", sPath);
				temp = tree.GetWorkingDir();
				tree.AddNode(new GenNode(sPath, temp, true));
				ListDirectoryContents(sPath, tree); 
				// once finished, return to parent directory saved in temp pointer
				tree.SetWorkingDir(temp);
			}
			else {
				// add file as node as child to working directory
				/*wprintf(L"File: %s\n", sPath);*/
				tree.AddNode(new GenNode(sPath, tree.GetWorkingDir(), false));
			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file. 

	FindClose(hFind); //Always, Always, clean things up! 

	return true;
}

void PrintNode(GenNode * const node)
{
	ofstream file;
	file.open(WRITE_DIR, std::ios::out | std::ios::app);
	file << node->GetPath() << endl;
	file.close();
}
