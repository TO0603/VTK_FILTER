#include <string>
#include <iostream>

#include <VTKFormat.h>
#include <CreatePFI.h>
#include <SetVolumeObject.h>
int main(int argc, char* argv[])
{
    //コマンドライン引数に何か入力されているかを判別
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " InputFilepath e.g. hoge.vtk" << std::endl;
        return EXIT_FAILURE;
    }

    //コマンドライン引数からファイル名を取得
    std::string inputFilepath = argv[1];
    int path_i = inputFilepath.find_last_of( "/" ) + 1;
    int ext_i = inputFilepath.find_last_of( "." );
    std::string baseName = inputFilepath.substr( path_i, ext_i-path_i );

    VTKFormat *vtk = new VTKFormat();
    vtk->read( inputFilepath );
    vtk->generate();

    CreatePFI *createPFI = new CreatePFI( baseName, *vtk );
    std::string kvsml_filename = createPFI->KVSMLFileName();

    kvs::UnstructuredVolumeObject* volume = new SetVolumeObject( *vtk );
    createPFI->write( volume );

    kvs::KVSMLUnstructuredVolumeObject* kvsml =
            new kvs::UnstructuredVolumeExporter<kvs::KVSMLUnstructuredVolumeObject>( volume );
    kvsml->setWritingDataType( kvs::KVSMLUnstructuredVolumeObject::ExternalBinary );
    kvsml->write( kvsml_filename );

    delete vtk;
    delete createPFI;
    delete volume;
    delete kvsml;
    std::cout << "[EXIT]" << std::endl;
    return EXIT_SUCCESS;
}
