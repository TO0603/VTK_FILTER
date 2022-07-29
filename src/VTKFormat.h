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
#include <vtkCellDataToPointData.h>
#include <kvs/ValueArray>

class VTKFormat
{

private:
    vtkGenericDataObjectReader* m_reader;//

public:
    VTKFormat();
    void read( std::string input_vtk_file );
    vtkGenericDataObjectReader* getReader() { return m_reader; }
};

#endif // FILTERVTK_H
