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

class FilterVTK
{

private:
    int m_number_of_field_data_in_file;
    int m_number_of_scalars_in_file;
    vtkPointData* m_point_data;
    vtkCellData* m_cell_data;
    int m_number_of_point_data_arrays;
    int m_number_of_point_data_components;
    int m_number_of_point_data_tuples;
    int m_number_of_cell_data_arrays;
    int m_number_of_cell_data_components;
    int m_number_of_cell_data_tuples;
    long long m_number_of_nodes;
    long long m_number_of_elements;
    int m_number_of_kinds;
    int m_number_of_points;


public:
    FilterVTK();
    void readVTKFile(std::string input_vtk_file);
    long long getNumberOfNodes()    { return m_number_of_nodes; }
    long long getNumberOfElements() { return m_number_of_elements; }
    int getNumberOfKinds()    { return m_number_of_kinds; }
    int getNumberOfPoints()   { return m_number_of_points; }

private:
    void check_vtk_data_set_type(vtkGenericDataObjectReader* reader);
    void read_vtk_file_parameter(vtkGenericDataObjectReader* reader);
};

#endif // FILTERVTK_H
