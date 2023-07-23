#include <iostream>
#include <vector>

#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/RboxPoints.h>
#include <libqhullcpp/QhullFacet.h>
#include <libqhullcpp/QhullSet.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <libqhullcpp/QhullVertex.h>
#include <libqhullcpp/QhullPoint.h>


int main()
{
    std::vector<coordT> points;

    // Generate 2D point cloud
    for (int i = 0; i < 100; i++) {
        coordT x = ((coordT) rand() / (RAND_MAX));
        coordT y = ((coordT) rand() / (RAND_MAX));
        points.push_back(x);
        points.push_back(y);
    }

    // Compute qhull
    orgQhull::RboxPoints rp;
    rp.setDimension(2);
    rp.append(points);

    // Generate convex hull and print boundary points
    orgQhull::Qhull qhull;
    qhull.runQhull(rp, "Qt");

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
                // double* coords = p.coordinates();
                // vec3 aPoint = vec3(coords[0], coords[1], coords[2]);
                for (int i = 0; i < p.dimension(); ++i) 
                {
                    std::cout << p.coordinates()[i] << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}