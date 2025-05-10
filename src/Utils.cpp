#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "Eigen/Core"
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{

    bool ImportMesh(PolygonalMesh& mesh)
    {

        if(!ImportCell0Ds(mesh))
            return false;

        if(!ImportCell1Ds(mesh))
            return false;
        
        if(!ImportCell2Ds(mesh))
            return false;

        return true;
    }

    bool ImportCell0Ds(PolygonalMesh& mesh){

        ifstream ifs("./Cell0Ds.csv");

        if(ifs.fail())
           return false;

        list<string> listLines;
        
        string line;
        while(getline(ifs, line))
            listLines.push_back(line);
        
        ifs.close(); 
        
        
        listlLines.pop_front();

        
        mesh.NumCell0Ds = listLines.size();

        if(mesh.NumCell0Ds == 0){
            cerr << "There is no cell 0D" << endl;
            return false;
        }

       
        mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
        mesh.Cell0DsCoordinates = Eigen::Matrix3Xd::Zero(3, mesh.NumCell0Ds);
    
        for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if(it == mesh.MarkerCell0Ds.end())
            {
                mesh.MarkerCell0Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell0Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }

    }

        return true;
    }

    bool ImportCell1Ds(PolygonalMesh& mesh){
        
        ifstream ifs("./Cell1Ds.csv");

        if(ifs.fail())
           
            return false;
        
        list<string> listLines;
        
        string line;
        while(getline(ifs, line))
            listLines.push_back(line);
        
        ifs.close();
        // remove header
        listLines.pop_front();

        mesh.NumCell1Ds = listLines.size();

        if(mesh.NumCell1Ds == 0){
            cerr << "There is no cell 1D" << endl;
            return false;
        }

        mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
        mesh.Cell1DsExtrema = Eigen::Matrix2Xi::Zero(2, mesh.NumCell1Ds);
       

         for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        converter >>  id >> marker >>  mesh.Cell1DsExtrema(0, id) >>  mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell1Ds.find(marker);
            if(it == mesh.MarkerCell1Ds.end())
            {
                mesh.MarkerCell1Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell1Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }
    }

        return true;
    }

    bool ImportCell2Ds(PolygonalMesh& mesh){
        
        ifstream ifs;
        ifs.open("./Cell2Ds.csv");

        if(ifs.fail())
            return false;
        
        
        list<string> listLines;

        string line;
        while(getline(ifs, line))
            listLines.push_back(line);
        
        ifs.close();
        //remove header
        listLines.pop_front();

        mesh.NumCell2Ds = listLines.size();

        if(mesh.NumCell2Ds == 0){
            cerr << "There is no cell 2D" << endl;
            return false;
        }

        mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsMarkers = Eigen::VectorXi::Zero(mesh.NumCell2Ds);

        
        unsigned int id;
        unsigned int NumVertices;
        unsigned int NumEdges;
        char c;
        for(const string& line : listLines){

            istringstream inputLine(line);

            inputLine >> id >> c
                      >> mesh.Cell2DsMarkers(id) >> c
                      >> NumVertices;
            
            mesh.Cell2DsVertices[id].resize(NumVertices);

            for(int i= 0; i< NumVertices; i++){
                inputLine >> c >> mesh.Cell2DsVertices[id][i];
            }

            inputLine >> c >> NumEdges;
            mesh.Cell2DsEdges[id].resize(NumEdges);

            for(int j = 0; j < NumEdges; j++){
                inputLine >> c >> mesh.Cell2DsEdges[id][j];
            }
            
        }

        }eturn true;
    }


    // Test imported properties
    bool Cell0DsMarkersTest(PolygonalMesh& mesh){
        vector<int> markersCell0Dscsv = {1, 2, 3, 4, 0, 8, 5, 6, 7, 0, 0, 0, 0, 0, 0, 8, 5, 6, 0, 0, 7, 
            8, 6, 7, 5, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        
        for(unsigned int id = 0; id < markersCell0Dscsv.size(); id++){
            if(markersCell0Dscsv[id] != mesh.Cell0DsMarkers[id]){
                cerr << "errore nell'importazione" << endl;
               
                return false;
            }
        }

        return true;
    }

    bool Cell1DsMarkersTest(PolygonalMesh& mesh){
        vector<int> markersCell1Dscsv ={0, 0, 0, 0, 0, 0, 6, 0, 5, 0, 0, 8, 0, 0, 7, 0, 0, 7, 0, 5, 0, 
            0, 5, 6, 7, 8, 6, 0, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(unsigned int id = 0; id < markersCell1Dscsv.size(); id++){
            if(markersCell1Dscsv[id] != mesh.Cell1DsMarkers[id]){
                cerr << "Errore nell'importazione." << endl;
                
                return false;
            }
        }
        
        return true;
    }

    bool Cell2DsMarkersTest(PolygonalMesh& mesh){
        vector<int> markersCell2Dscsv ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(unsigned int id = 0; id < markersCell2Dscsv.size(); id++){
            if(markersCell2Dscsv[id] != mesh.Cell2DsMarkers[id]){
                cerr << "Errore nell'importazione." << endl;
                
                return false;
            }
        }
        
        return true;
    }

    bool EdgesLengthsTest(PolygonalMesh& mesh, const double& tol){
        for(unsigned int id = 0; id < mesh.NumCell1Ds; id++){
            int id1 = mesh.Cell1DsExtrema(0, id);
            int id2 = mesh.Cell1DsExtrema(1, id);
            double x1 = mesh.Cell0DsCoordinates(0, id1);
             double x2 = mesh.Cell0DsCoordinates(0, id2);
              double x = x2 - x1;
             double y1 = mesh.Cell0DsCoordinates(1, id1);
            double y2 = mesh.Cell0DsCoordinates(1, id2);
            double y= y2 - y1;
            double length = sqrt(x* x + y*y);
            if(length <= tol){
                cerr << "Edge di lunghezza nulla." << endl;
                
                return false;
            }
        }
        return true;
    }

