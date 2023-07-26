#include <iostream>
#include <fstream>
#include <vector>

#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/RboxPoints.h>
#include <libqhullcpp/QhullFacet.h>
#include <libqhullcpp/QhullSet.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <libqhullcpp/QhullVertex.h>
#include <libqhullcpp/QhullPoint.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


int main()
{
    std::ifstream fin("E:\\code\\dgp\\concaveman-cpp\\data\\points-1k.json");
    json data = json::parse(fin);
    fin.close();

    std::vector<coordT> points;

    // Generate 2D point cloud
    //for (int i = 0; i < 100; i++) {
    //    coordT x = ((coordT) rand() / (RAND_MAX));
    //    coordT y = ((coordT) rand() / (RAND_MAX));
    //    points.push_back(x);
    //    points.push_back(y);
    //}
    for (auto it : data)
    {
        points.push_back(it[0]);
        points.push_back(it[1]);
        // std::cout << "value: " << it << '\n';
    }

    // Compute qhull
    orgQhull::RboxPoints rp;
    rp.setDimension(2);
    rp.append(points);

    // Generate convex hull and print boundary points
    orgQhull::Qhull qhull;
    qhull.runQhull(rp, "Qt");

    orgQhull::QhullVertexList vs = qhull.vertexList();
    orgQhull::QhullVertexListIterator it(vs);
    std::cout.precision(10);
    while (it.hasNext()) 
    {
        orgQhull::QhullPoint p = it.next().point();
        int pid = p.id();
        std::cout << "p" << pid << endl;
        
        for (int i = 0; i < p.dimension(); ++i)
        {
            std::cout << p.coordinates()[i] << " ";
        }
        std::cout << points[pid * 2] << " ";
        std::cout << points[pid * 2 + 1] << " ";
        std::cout << std::endl;
    }

 /*
    orgQhull::QhullFacetList facets = qhull.facetList();
    for (orgQhull::QhullFacetList::iterator it = facets.begin(); it != facets.end(); ++it)
    {
        if ((*it).isGood())
        {
            orgQhull::QhullFacet f = *it;
            orgQhull::QhullVertexSet vSet = f.vertices();
            for (orgQhull::QhullVertexSet::iterator vIt = vSet.begin(); vIt != vSet.end(); ++vIt)
            {
                orgQhull::QhullVertex v = *vIt;
                orgQhull::QhullPoint p = v.point();
                countT pid = p.id();
                std::cout << pid << std::endl;
                 //double* coords = p.coordinates();
                 //vec3 aPoint = vec3(coords[0], coords[1], coords[2]);
                std::cout.precision(10);
                for (int i = 0; i < p.dimension(); ++i) 
                {
                    std::cout << p.coordinates()[i] << " ";
                }
                std::cout << "id" << std::endl;
                std::cout << points[pid * 2] << " ";
                std::cout  << points[pid * 2 + 1] << " ";
                std::cout << std::endl;
            }
        }
    }
 */

    return 0;
}