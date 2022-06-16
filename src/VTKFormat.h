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

class VTKFormat
{

private:
//    vtkNew<vtkGenericDataObjectReader>* m_reader;
    vtkGenericDataObjectReader* m_reader;
    vtkDataSet* m_output;
    int m_nfield_data_in_file;
    int m_nscalars_in_file;
    vtkPointData* m_point_data;
    vtkCellData* m_cell_data;
    int m_npoint_data_arrays;//m_npoint_data_arrays
    int m_npoint_data_components;
    int m_npoint_data_tuples;
    int m_ncell_data_arrays;
    int m_ncell_data_components;
    int m_ncell_data_tuples;
    long long m_nnodes;
    long long m_nelements;
    int m_nkinds;
    int m_npoints;
    int m_cell_type;
    kvs::ValueArray<kvs::Real32> m_coord_array;//m_coords
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;


public:
    VTKFormat();
    void read(std::string input_vtk_file);
    void generate();
    long long getNumberOfNodes() { return m_nnodes; }
    long long getNumberOfElements() { return m_nelements; }
    int getNumberOfKinds() { return m_nkinds; }
    int getNumberOfPoints() { return m_npoints; }
    int getCellType() { return m_cell_type; }

    void setNumberOfNodes(long long nnodes) { m_nnodes = nnodes; }
    void setNumberOfElements(long long nelements) { m_nelements = nelements; }
    void setNumberOfKinds(int nkinds) { m_nkinds = nkinds; }
    void setNumberOfPoints(int npoints) {  m_npoints = npoints; }
    void setCellType(int cell_type) {  m_cell_type = cell_type; }

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
