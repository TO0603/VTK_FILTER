#ifndef CREATEPFI_H
#define CREATEPFI_H
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeExporter>
#include <kvs/KVSMLUnstructuredVolumeObject>
#include "FilterVTK.h"


class CreatePFI
{

private:
    const size_t m_number_of_nodes;
    const size_t m_number_of_cells;
    const size_t m_number_of_veclen;
    kvs::ValueArray<kvs::Real32> m_coord_array;
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;
    float m_volume_min_max_coord[6];
public:
//    CreatePFI(FilterVTK filterVTK,long long number_of_nodes,long long number_of_cells, int number_of_veclens, int number_of_points);
    CreatePFI(FilterVTK filterVTK);
    void setCoordArray();
    void setValueArray(double tmp);
    void setConnectionArray(double tmp);

private:
    kvs::UnstructuredVolumeObject* create_unstructured_volume_object(int cellType,
                                                                     const size_t nnodes,
                                                                     const size_t ncells,
                                                                     const size_t veclen,
                                                                     kvs::ValueArray<kvs::Real32> CoordArray,
                                                                     kvs::ValueArray<kvs::Real32> ValueArray,
                                                                     kvs::ValueArray<kvs::UInt32> ConnectionArray);
};

#endif // CREATEPFI_H
