#include <string>
#include <vtkGenericDataObjectReader.h>
#include <vtkDataReader.h>
#include <vtkDataSet.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkCell.h>
#include <vtkDataArray.h>
#include <vtkIdList.h>

#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeExporter>
#include <kvs/ExternalFaces>
#include <kvs/KVSMLUnstructuredVolumeObject>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void WritePFIFile()
{
    //    FILE *pfi = NULL;
    //    int itmp;
    //    float ftmp[6];
    //    pfi = fopen("./out/tetrahedra.pfi", "wb");
    //    //頂点数
    //    itmp = nnodes;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //要素数
    //    itmp = ncells;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //要素タイプ
    //    itmp = 4;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //ファイルタイプ
    //    itmp = 0;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //ファイル数
    //    itmp = 0;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //成分数(ベクトル?)
    //    itmp = 1;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //開始ステップ
    //    itmp = 0;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //終了ステップ
    //    itmp = 0;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //サブボリューム数
    //    itmp = 1;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //座標の最大最小値
    //    ftmp[0] = -2.0;
    //    ftmp[1] = -2.0;
    //    ftmp[2] = 0.0;
    //    ftmp[3] = 2.0;
    //    ftmp[4] = 2.0;
    //    ftmp[5] = 2.0;
    //    fwrite(&ftmp, 4, 6, pfi);
    //    //サブボリュームの頂点数
    //    itmp = nnodes;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //サブボリュームの要素数
    //    itmp = ncells;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //サブボリュームの座標の最大最小値
    //    fwrite(&ftmp, 4, 6, pfi);
    //    //ステップ1の成分最小値
    //    itmp = 1;
    //    fwrite(&itmp, 4, 1, pfi);
    //    //ステップ1の成分最大値
    //    itmp = 5;
    //    fwrite(&itmp, 4, 1, pfi);
    //    fclose(pfi);
}

void WriteKVSML()
{

}
//VTKの要素タイプをKVSの非構造格子型要素タイプに変換する。
/*
 * VTK_EMPTY_CELL           = 0
 * VTK_VERTEX               = 1
 * VTK_POLY_VERTEX          = 2
 * VTK_LINE                 = 3
 * VTK_POINT_LINE           = 4
 * VTK_TRIANGLE             = 5
 * VTK_TRIANGLE_STRIPE      = 6
 * VTK_POLYGON              = 7
 * VTK_PIXEL                = 8
 * VTK_QUAD                 = 9
 * VTK_TETRA                = 10
 * VTK_VOXEL                = 11
 * VTK_HEXAHEDRON           = 12
 * VTK_WEDGE                = 13
 * VTK_PYRAMID              = 14
 * VTK_QUADRATIC_TETRA      = 24
 * VTK_QUADRATIC_HEXAHEDRON = 25
*/

//enum VTKCellType
//{
//    Hexahedra = 12,
//    Pyramid = 14
//}
kvs::UnstructuredVolumeObject::CellType GetKVSUnstructuredCellType(int vtk_cellType)
{
    if(vtk_cellType == 0)
        return kvs::UnstructuredVolumeObject::UnknownCellType;
    if(vtk_cellType == 10)
        return kvs::UnstructuredVolumeObject::Tetrahedra;
    if(vtk_cellType == 12)
        return kvs::UnstructuredVolumeObject::Hexahedra;
    if(vtk_cellType == 24)
        return kvs::UnstructuredVolumeObject::QuadraticTetrahedra;
    if(vtk_cellType == 25)
        return kvs::UnstructuredVolumeObject::QuadraticHexahedra;
    if(vtk_cellType == 14)
        return kvs::UnstructuredVolumeObject::Pyramid;
    if(vtk_cellType == 1)
        return kvs::UnstructuredVolumeObject::Point;//?
    if(vtk_cellType == 13) //?
        return kvs::UnstructuredVolumeObject::Prism;
}

//pfiファイルで使用する非構造格子型要素タイプを取得する関数
int GetPFIUnstructuredCellType(kvs::UnstructuredVolumeObject::CellType kvs_cellType){
    if(kvs_cellType == kvs::UnstructuredVolumeObject::UnknownCellType)
        return 0;//EXIT
    if(kvs_cellType == kvs::UnstructuredVolumeObject::Tetrahedra)
        return 4;
    if(kvs_cellType == kvs::UnstructuredVolumeObject::Hexahedra)
        return 7;
    if(kvs_cellType == kvs::UnstructuredVolumeObject::QuadraticTetrahedra)
        return 0;//?
    if(kvs_cellType == kvs::UnstructuredVolumeObject::QuadraticHexahedra)
        return 0;//?
    if(kvs_cellType == kvs::UnstructuredVolumeObject::Pyramid)
        return 5;
    if(kvs_cellType == kvs::UnstructuredVolumeObject::Point)
        return 0;//?
    if(kvs_cellType == kvs::UnstructuredVolumeObject::Prism)
        return 6;
}

//ボリュームデータを作る関数
kvs::UnstructuredVolumeObject* CreateUnstructuredVolumeObject(int cellType,
                                                              const size_t nnodes,
                                                              const size_t ncells,
                                                              const size_t veclen,
                                                              kvs::ValueArray<kvs::Real32> coords,
                                                              kvs::ValueArray<kvs::Real32> values,
                                                              kvs::ValueArray<kvs::UInt32> connections)
{
    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeObject();
    object->setCellType( GetKVSUnstructuredCellType(cellType)); //convertVTKCellTypetoKVSCellTYpe(celltype)
    object->setVeclen( veclen );
    object->setNumberOfNodes( nnodes );
    object->setNumberOfCells( ncells );
    object->setCoords( coords );
    object->setConnections( connections );
    object->setValues( values );
    object->updateMinMaxCoords();
    object->updateMinMaxValues();
    object->updateNormalizeParameters();
#ifdef DEBUG
    std::cout << __FILE__ << ":" << __func__ << ":" << __LINE__    << std::endl;
    std::cout << cellType << std::endl;
    std::cout << *object << std::endl;
    //    std::cout << object->coords() << std::endl;
    std::cout << connections << std::endl;
#endif
    return object;
}



int main(int argc, char* argv[])
{
    //コマンドライン引数で.vtkファイルを指定しているかどうかを判別
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " InputFilename e.g. hoge.vtk" << endl;
        return EXIT_FAILURE;
    }

    //コマンドライン引数からファイル名を取得
    std::string inputFilename = argv[1];
    int path_i = inputFilename.find_last_of("/") + 1;
    int ext_i = inputFilename.find_last_of(".");
    std::string fileName = inputFilename.substr(path_i,ext_i-path_i);

    //vtkのデータを取得
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    //標準的なデータ型を取得する(あくまで例)
    if (reader->IsFilePolyData())
    {
        std::cout << "output is polydata," << std::endl;
        auto output = reader->GetPolyDataOutput();
        std::cout << "   output has " << output->GetNumberOfPoints() << " points." << std::endl;
    }

    if (reader->IsFileUnstructuredGrid())
    {
        //vtkデータから値を取得
        std::cout << "output is unstructured grid," << std::endl;
        auto output                = reader->GetUnstructuredGridOutput();
        int n_file_fields          = reader->GetNumberOfFieldDataInFile();
        int n_file_scalars         = reader->GetNumberOfScalarsInFile();
        vtkPointData* point_data   = output->GetPointData();
        vtkCellData* cell_data     = output->GetCellData();
        int n_pointData_arrays     = point_data->GetNumberOfArrays();
        int n_pointData_components = point_data->GetNumberOfComponents();
        int n_pointData_tuples     = point_data->GetNumberOfTuples();
        int n_cellData_arrays      = cell_data->GetNumberOfArrays();
        int n_cellData_components  = cell_data->GetNumberOfComponents();
        int n_cellData_tuples      = cell_data->GetNumberOfTuples();
        long long m_nnodes         = output->GetNumberOfPoints();
        long long m_nelements      = output->GetNumberOfCells();
        int m_nkinds               = n_pointData_components + n_cellData_components;

#ifdef DEBUG
        std::cout << "m_nnodes = " << m_nnodes << std::endl;
        std::cout << "m_nelements = " << m_nelements << std::endl;
        std::cout << "n_file_fields = " << n_file_fields << std::endl;
        std::cout << "n_file_scalars = " << n_file_scalars << std::endl;
        std::cout << "n_pointData_arrays = "<< n_pointData_arrays << std::endl;
        std::cout << "n_pointData_components = "<< n_pointData_components << std::endl;
        std::cout << "n_pointData_tuples = "<< n_pointData_tuples << std::endl;
        std::cout << "n_cellData_arrays = "<< n_cellData_arrays << std::endl;
        std::cout << "n_cellData_components = "<< n_cellData_components << std::endl;
        std::cout << "n_cellData_tuples = "<< n_cellData_tuples << std::endl;
        std::cout << "veclen = " << m_nkinds << std::endl;
#endif

        //取得した値をKVSのボリュームデータ作成に必要なものに代入
        const size_t nnodes        = m_nnodes;
        const size_t ncells        = m_nelements;
        const size_t veclen        = m_nkinds;
        kvs::ValueArray<kvs::Real32> CoordArray(nnodes * 3);
        kvs::ValueArray<kvs::Real32> ValueArray(nnodes * veclen);
        //        kvs::ValueArray<kvs::UInt32> ConnectionArray(ncells * 8);
        kvs::ValueArray<kvs::UInt32> ConnectionArray(ncells * output->GetCell(0)->GetNumberOfPoints());
        //PFIファイルの作成に必要な変数
        float volume_minmax_coord[6];

#ifdef DEBUG
        //        std::cout << "nnodes         = " << nnodes << std::endl;
        //        std::cout << "ncells         = " << ncells << std::endl;
        //        std::cout << "veclen         = " << veclen << std::endl;
        //        std::cout << "CoordArray     : " << std::endl;
#endif

        //座標の代入
        for(int i = 0; i < m_nnodes; i++){
            double* point = output->GetPoint(i);
            CoordArray[i * 3] = point[0];
            CoordArray[i * 3 + 1] = point[1];
            CoordArray[i * 3 + 2] = point[2];
#ifdef DEBUG
            //            std::cout << CoordArray[i * 3] << "," << CoordArray[i * 3 + 1] << "," << CoordArray[i * 3 + 2] << std::endl;
#endif
        }

#ifdef DEBUG
        //        std::cout << "ValueArray     : " << std::endl;
#endif

        //ポイント物理値の代入
        vtkDataArray* pointData_array = NULL;
        double* pointComponents = NULL;
        for(int i = 0; i < n_pointData_arrays; i++ ){
            pointData_array = point_data->GetArray(i);
            for(int j = 0; j < n_pointData_tuples; j++){
                pointComponents = pointData_array->GetTuple(j);
                ValueArray[j] = pointComponents[0];
#ifdef DEBUG
                //                std::cout << ValueArray[j] << std::endl;
#endif
            }
        }

        //接続情報の代入
        int new_id;
        int cellType;
        vtkNew<vtkIdList> included_points;
        int connection_index = 0;
        for(int i = 0; i < m_nelements; i++){
            vtkCell* element = output->GetCell(i);
            cellType = element->GetCellType();
#ifdef DEBUG
            //            std::cout << "CellType        = " << cellType << std::endl;
#endif
            int n_points = element->GetNumberOfPoints();
#ifdef DEBUG
            std::cout << "n_points        = " << n_points << std::endl;
            std::cout << "ConnectionArray : " << std::endl;
#endif
            for(int j = 0; j < n_points; j++){
                int id1= element->GetPointId(j);
                new_id = 1 + included_points->InsertNextId(id1);
                ConnectionArray[ connection_index ] = id1;
                std::cout << "ConnectionArray[" << connection_index << "]"<< ConnectionArray[j] << std::endl;
                connection_index++;
#ifdef DEBUG
                //std::cout << "ConnectionArray[" << j + i*n_points << "]"<< ConnectionArray[j] << std::endl;
                //std::cout << "ConnectionArray[" << connection_index << "]"<< ConnectionArray[j] << std::endl;
#endif
            }
        }




        kvs::UnstructuredVolumeObject* volume = CreateUnstructuredVolumeObject(cellType,
                                                                               nnodes,
                                                                               ncells,
                                                                               veclen,
                                                                               CoordArray,
                                                                               ValueArray,
                                                                               ConnectionArray);

        volume_minmax_coord[0] = volume->minObjectCoord().x();
        volume_minmax_coord[1] = volume->minObjectCoord().y();
        volume_minmax_coord[2] = volume->minObjectCoord().z();
        volume_minmax_coord[3] = volume->maxObjectCoord().x();
        volume_minmax_coord[4] = volume->maxObjectCoord().y();
        volume_minmax_coord[5] = volume->maxObjectCoord().z();

#ifdef DEBUG
        for(int i = 0; i < 6; i++){
            std::cout << volume_minmax_coord[i] << std::endl;
        }
#endif

        kvs::KVSMLUnstructuredVolumeObject* kvsml =
                new kvs::UnstructuredVolumeExporter<kvs::KVSMLUnstructuredVolumeObject>( volume );
        kvsml->setWritingDataType( kvs::KVSMLUnstructuredVolumeObject::ExternalBinary );
        kvsml->write("./out/" + fileName + "_00000_0000001_0000001.kvsml");
        delete kvsml;



        FILE *pfi = NULL;
        int itmp;
        float ftmp[6];
        std::string pfiFileName = "./out/" + fileName + ".pfi";
        //            pfi = fopen("./out/tetrahedra.pfi", "wb");
        pfi = fopen(pfiFileName.c_str(), "wb");
        //頂点数
        itmp = nnodes;
        fwrite(&itmp, 4, 1, pfi);
        //要素数
        itmp = ncells;
        fwrite(&itmp, 4, 1, pfi);
        //要素タイプ
        itmp = GetPFIUnstructuredCellType(volume->cellType());
        fwrite(&itmp, 4, 1, pfi);
        //ファイルタイプ
        itmp = 0;
        fwrite(&itmp, 4, 1, pfi);
        //ファイル数
        itmp = 0;
        fwrite(&itmp, 4, 1, pfi);
        //成分数(ベクトル?)
        itmp = veclen;
        fwrite(&itmp, 4, 1, pfi);
        //開始ステップ
        itmp = 0;
        fwrite(&itmp, 4, 1, pfi);
        //終了ステップ
        itmp = 0;
        fwrite(&itmp, 4, 1, pfi);
        //サブボリューム数
        itmp = 1;
        fwrite(&itmp, 4, 1, pfi);
        //座標の最大最小値
        ftmp[0] = volume_minmax_coord[0];
        ftmp[1] = volume_minmax_coord[1];
        ftmp[2] = volume_minmax_coord[2];
        ftmp[3] = volume_minmax_coord[3];
        ftmp[4] = volume_minmax_coord[4];
        ftmp[5] = volume_minmax_coord[5];
        fwrite(&ftmp, 4, 6, pfi);
        //サブボリュームの頂点数
        itmp = nnodes;
        fwrite(&itmp, 4, 1, pfi);
        //サブボリュームの要素数
        itmp = ncells;
        fwrite(&itmp, 4, 1, pfi);
        //サブボリュームの座標の最大最小値
        fwrite(&ftmp, 4, 6, pfi);
        //ステップ1の成分最小値
        itmp = 1;
        fwrite(&itmp, 4, 1, pfi);
        //ステップ1の成分最大値
        itmp = 5;
        fwrite(&itmp, 4, 1, pfi);
        fclose(pfi);
        delete volume;



    }

    return EXIT_SUCCESS;
}
