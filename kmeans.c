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

int main(int k, int iter, int arg c, char **argv)
{ 
    int i;
    int num_of_elements=0;
    int j;
    int max_line_len;
    int d=1;
    char ch;
    char *line;
    double[] number;
    FILE *points = fopen(argv[1], "r");
    while ((ch = fgetc(points)) != '\n')
    {
        if(ch==','){
            d+=1;
        }
        
        
    }
    /*if not empty*/
    num_of_elements += 1;
    max_line_len = 100*d;

    /*count number of points in the file*/
    *line = (char *)malloc(max_line_len+1, sizeof(char));
    while(fgets (char *line, int max_line_len, FILE *points)){
        num_of_elements += 1;
    }

    rewind(points);
    /*memory allocation for all the points in the file*/
    double[] elements_1d = (double *)calloc(num_of_elements*d, sizeof(double));
    double[][] elements = calloc(d,sizeof(double *));
    for(i=0; i<num_of_elements; i++){
        elements[i] = elements_1d+i*d;
    } 
    /*memory allocation for k centroids*/
    double[] centroids_1d = (double *)calloc(k*d, sizeof(double));
    double[][] centroids = calloc(d,sizeof(double *));
    for(i=0; i<k; i++){
        centroids[i] = centroids_1d+i*d;
    }
    /*put all the points in one array, and the first k of them in the centroids array*/
    i=0;
    while(fgets (char *line, int max_line_len, FILE *points)){
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
    int[] clusters_1d = (int *)calloc(k*num_of_elements, sizeof(int));
    int[][] clusters = calloc(num_of_elements,sizeof(int *));
    for(j=0; j<k; j++){
        clusters[j] = clusters_1d+j*num_of_elements;
    } 
    
    i=0;
    for(i; i<iter; i++){

    }
    

    return 0;
}