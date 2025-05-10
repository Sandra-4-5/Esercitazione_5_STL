#pragma once

#include <iostream>
#include <string>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary{

    
    bool ImportMesh(PolygonalMesh& mesh);


   
    bool ImportCell0Ds(PolygonalMesh& mesh);

    
    bool ImportCell1Ds(PolygonalMesh& mesh);

    
    bool ImportCell2Ds(PolygonalMesh& mesh);


    
    bool Cell0DsMarkersTest(PolygonalMesh& mesh);


    
    bool Cell1DsMarkersTest(PolygonalMesh& mesh);


   
    bool Cell2DsMarkersTest(PolygonalMesh& mesh);

    bool EdgesLengthsTest(PolygonalMesh& mesh, const double& tol);
    
    }

