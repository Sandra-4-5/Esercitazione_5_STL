#pragma once 
#include "Eigen/Eigen"

using namespace Eigen;
using namespace std;


namespace PolygonalLibrary{

    struct PolygonalMesh{

        unsigned int NumCell0Ds;
        vector<unsigned int> Cell0DsId;
        MatrixXd Cell0DsCoordinates;//Cell0DsCoordinates;
        map<unsigned int, list<unsigned int>> MarkersCell0Ds;

        unsigned int NumCell1Ds;
        vector<unsigned int> Cell1DsId;
        MatrixXi Cell1DsExtrema; //  Cell1DsExtrema;
        map<unsigned int, list<unsigned int>> MarkersCell1Ds;

        unsigned int NumCell2Ds;
        vector<unsigned int> Cell2DsId;
        vector<vector<int>> Cell2DsVertices;
        vector<vector<int>> Cell2DsEdges;
        VectorXi MarkersCell2Ds;


    };

}
