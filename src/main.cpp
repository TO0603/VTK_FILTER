#include <string>
#include <iostream>

#include <FilterVTK.h>
#include <CreatePFI.h>

int main(int argc, char* argv[])
{
    //コマンドライン引数に何か入力されているかを判別
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " InputFilename e.g. hoge.vtk" << std::endl;
        return EXIT_FAILURE;
    }

    //コマンドライン引数からファイル名を取得
    std::string inputFilename = argv[1];
    int path_i = inputFilename.find_last_of("/") + 1;
    int ext_i = inputFilename.find_last_of(".");
    std::string fileName = inputFilename.substr(path_i,ext_i-path_i);

    FilterVTK *filterVTK = new FilterVTK();
    filterVTK->readVTKFile(inputFilename);

    CreatePFI *createPFI = new CreatePFI(fileName,*filterVTK);
//    createPFI->setCoordArray();

    return EXIT_SUCCESS;
}
