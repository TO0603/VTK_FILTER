#ifndef FILTERVTK_H
#define FILTERVTK_H
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

#include <kvs/ValueArray>

class FilterVTK
{

private:
    vtkDataSet* m_output;
    int m_number_of_field_data_in_file;
    int m_number_of_scalars_in_file;
    vtkPointData* m_point_data;
    vtkCellData* m_cell_data;
    int m_number_of_point_data_arrays;//m_npoint_data_arrays
    int m_number_of_point_data_components;
    int m_number_of_point_data_tuples;
    int m_number_of_cell_data_arrays;
    int m_number_of_cell_data_components;
    int m_number_of_cell_data_tuples;
    long long m_number_of_nodes;
    long long m_number_of_elements;
    int m_number_of_kinds;
    int m_number_of_points;
    int m_cell_type;
    kvs::ValueArray<kvs::Real32> m_coord_array;//m_coords
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;


public:
    FilterVTK();
    void readVTKFile(std::string input_vtk_file);
    long long getNumberOfNodes()    { return m_number_of_nodes; }
    long long getNumberOfElements() { return m_number_of_elements; }
    int getNumberOfKinds()    { return m_number_of_kinds; }
    int getNumberOfPoints()   { return m_number_of_points; }
    int getCellType() { return m_cell_type; }
    kvs::ValueArray<kvs::Real32> getCoordArray() { return m_coord_array; }
    kvs::ValueArray<kvs::Real32> getValuewArray() { return m_value_array; }
    kvs::ValueArray<kvs::UInt32> getConnectionArray() { return m_connection_array; }
    void setCoordArray(); //名前変?そもそもpublicであってるんだろうか。
    void setValueArray();
    void setConnectionArray();

private:
    void check_vtk_data_set_type(vtkGenericDataObjectReader* reader);
    void read_vtk_file_parameter(vtkGenericDataObjectReader* reader);
};

#endif // FILTERVTK_H
