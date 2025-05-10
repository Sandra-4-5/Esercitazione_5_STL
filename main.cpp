#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"
#include <string>
#include <cmath>

using namespace std;
using namespace PolygonalLibrary;
using namespace Eigen;

int main()
{
    PolygonalMesh mesh;


    if(!ImportMesh(mesh)){
        cerr << "file not found " << endl;
        return 1;
    }

    Gedim::UCDUtilities utilities;
    {      
        
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.MarkerCell0Ds)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();


    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates,
                           cell0Ds_properties);
    }         
    
    {     
         vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.MarkerCell1Ds)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema,
                             {},
                             
                             mesh.Cell1DsMarkers);

    }                   
    


   

    // Test Cell0Ds
    if(!Cell0DsMarkersTest(mesh)){
        return 1;
    }
    cout << endl;
    cout << "import Cell1DsMarkers well done" << endl;
    


    //Test Cell1Ds
    if(!Cell1DsMarkersTest(mesh)){
        return 1;
    }
    cout << "import Cell1DsMarkers well done" << endl;
    cout << endl;

    //Test Cell2Ds
   
    if(!Cell2DsMarkersTest(mesh)){
        return 1;
    }
    cout << "imports Cell1DsMarkers well done " << endl;
    
    double tol = 1e-6;
    // Test Edges length
    if(!EdgesLengthsTest(mesh, tol)){
        return 1;
    }
    cout << "edges have non zero length" << endl;
    cout << endl;

   

    return 0; 
}