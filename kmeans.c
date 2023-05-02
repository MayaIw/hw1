# include <stdio.h>
# include <stdlib.h>
# include <math.h>

double distance(double[] p, double[] q)
{
    int d = sizeof(p);
    int i = 0;
    double distance = 0;
    double sum_of_squares = 0;
    if(d!=sizeof(q))
    {
        printf("An Error Has Occurred");
        exit(0);
    }
    for(i; i<d; i++)
    {
        sum_of_squares += pow(p[i]-q[i],2);
    }
    distance = sqrt(sum_of_squares);
    return distance;
}

int clusterAssign(double[] x, double[][] centroids)
{
    int num_of_clusters = sizeof(centroids);
    double min_distance = distance(x, centroids[0]);
    int cluster = 0;
    int i = 1;
    for(i; i<num_of_clusters; i++)
    {
        double distance = distance(x, centroids[i]);
        if(distance <= min_distance)
        {
            min_distance = distance;
            cluster = i;
        }
    }
    return cluster;
}

double[] centroidUpdate(double[][] cluster_members)
{
    int cluster_size = sizeof(cluster_members);
    int d = sizeof(cluster_members[0]); /*cluster_members[0] is the current centroid*/
    double[] centroid = (double *)calloc(d, sizeof(double));
    assert(centroid != NULL);
    int i = 0;
    int j = 0;
    for(j; j<d ; j++)
    {
        for(i; i < cluster_size; i++)
        {
            centroid[j] += cluster_members[i][j];
        }
        centroid[j] /= cluster_size;
    }
    return centroid;
}

int main(void)
{

    

    return 0;
}