# include <stdio.h>
# include <stdlib.h>
# include <math.h>

double distance(double *p, double *q)
{
    int d = sizeof(p)/sizeof(p[0]);
    int i;
    double distance = 0;
    double sum_of_squares = 0;
    if(d!=(sizeof(q)/sizeof(q[0])))
    {
        printf("An Error Has Occurred");
        exit(0);
    }
    for(i=0; i<d; i++)
    {
        sum_of_squares += pow(p[i]-q[i],2);
    }
    distance = sqrt(sum_of_squares);
    return distance;
}

int clusterAssign(double *x, double **centroids)
{
    int num_of_clusters = sizeof(centroids)/sizeof(centroids[0]);
    double min_distance = distance(x, centroids[0]);
    int cluster = 0;
    int i;
    for(i=1; i<num_of_clusters; i++)
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

void centroidUpdate(int *cluster, double *centroid, int d, double **elements, int num_of_elements)
{
    int i = 0;
    int j = 0;
    int cluster_size = 0;
    for(j=0; j<d ; j++)
    {
        centroid[j] = 0;
        for(i=0; i < num_of_elements; i++)
        {
            if(cluster[i] == 1)
            {
                cluster_size++;
                centroid[j] += elements[i][j];
            } 
        }
        centroid[j] /= cluster_size;
    }
}

void increaseArray(double *array, int curr_size)
{
    array = realloc(array, 2*curr_size*sizeof(double));
    assert(array != null);
}

int main(int argc, char **argv)
{ 
    int k;
    int iter; 
    int i;
    int num_of_elements=0;
    int j;
    int max_line_len;
    int d=0;
    char ch;
    int is_end_of_line = 0;
    double coordinate;
    double *number;
    double *elements_1d;
    double **elements;
    double *centroids_1d;
    double **centroids;
    int *clusters_1d;
    int **clusters;

    if (argc != 3) 
    {
        iter = 200;
    }
    else
    {
        k = atoi(argv[1]);
        iter = atoi(argv[2]);
    }

    while (scanf("%lf%c", &coordinate, &ch)==2)
    {
        if(!is_end_of_line)
        {
            d+=1;
            /*elements_1d = calloc(d, sizeof(double));
            assert(elements_1d != NULL);
            elements = calloc(d,sizeof(double *));
            assert(elements != NULL);    
            elements[0] = elements_1d;*/
        }
        
        if(ch=='\n')
        {
            num_of_elements += 1;
            is_end_of_line = 1;
        }
        
        
    }
    /*if not empty
    num_of_elements += 1;
    max_line_len = 100*d;*/

    /*count number of points in the file
    *line = (char *)malloc(max_line_len+1 sizeof(char));
    while(fgets (char *line, int max_line_len, FILE *points))
    {
        num_of_elements += 1;
    }*/

    rewind(points);
    /*memory allocation for all the points in the file*/
    elements_1d = calloc(num_of_elements*d, sizeof(double));
    assert(elements_1d != NULL);
    elements = calloc(d,sizeof(double *));
    assert(elements != NULL);
    for(i=0; i<num_of_elements; i++)
    {
        elements[i] = elements_1d+i*d;
    } 

    /*memory allocation for k centroids*/
    centroids_1d = calloc(k*d, sizeof(double));
    assert(centroids_1d != NULL);
    centroids = calloc(d,sizeof(double *));
    assert(centroids != NULL);
    for(i=0; i<k; i++)
    {
        centroids[i] = centroids_1d+i*d;
    }

    /*put all the points in one array, and the first k of them in the centroids array*/
    i=0;
    while(fgets (char *line, int max_line_len, FILE *points))
    {
        line[strcspn(line, "\n")] = 0;
        number = (double *)strtok(line, ',');
        elements[i] = number;
        if(i<k){
            centroids[i] = number;
        }
        i++; 
    } 

    fclose(points);
    
    /*memory allocation for binary array representing the clusters*/
    clusters_1d = calloc(k*num_of_elements, sizeof(int));
    assert(clusters_1d != NULL);
    clusters = calloc(num_of_elements,sizeof(int *));
    assert(clusters != NULL);
    for(j=0; j<k; j++)
    {
        clusters[j] = clusters_1d+j*num_of_elements;
    } 
    
    i=0;
    /*for(i; i<iter; i++)
    {

    }*/
    

    return 0;
}