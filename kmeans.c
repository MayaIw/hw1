# include <stdio.h>
# include <stdlib.h>
# include <math.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

double distance(double *p, double *q, int d)
{
    int i;
    double distance = 0;
    double sum_of_squares = 0;
    for(i=0; i<d; i++)
    {
        sum_of_squares += pow(p[i]-q[i],2);
    }
    distance = sqrt(sum_of_squares);
    return distance;
}

int clusterAssign(double *x, double **centroids, int k, int d)
{
    double min_distance = distance(x, centroids[0],d);
    int cluster = 0;
    int i;
    double dist;
    for(i=1; i<k; i++)
    {
        dist = distance(x, centroids[i],d);
        if(dist <= min_distance)
        {
            min_distance = dist;
            cluster = i;
        }
    }
    return cluster;
}

void printClusters(double **clusters, int d,  int k){
    int i=0;
    int j=0;
    for(i=0; i<k; i++){
        for(j=0; j<d; j++){
            printf("%.4f", clusters[i][j]);
            if(j<d-1){
                printf("%c", ',');
            }
        }
        printf("\n");
    }

}

void centroidUpdate(double **clusters, int *size_of_clusters, int k, int d)
{
    int i = 0;
    int j = 0;
    for(i=0; i < k; i++)
    {   
        for(j=0; j<d ; j++)
        {
            if(size_of_clusters[i]==0){
                printf("An Error Has Occurred\n");
                exit(1);
            }
            clusters[i][j] /= size_of_clusters[i];
        }
    }
    return;
}

void delete_cord( struct cord *head ){
    if ( head != NULL )
        {
            delete_cord( head->next );
            free( head );
        }
    }

void delete_vector(struct vector *head){
    if(head!=NULL){
        delete_vector(head->next);
        delete_cord(head->cords);
        free(head);
    }
}

int main(int argc, char **argv)
{ 
    int k;
    int iter; 
    int num_of_elements=0;
    int d=0;
    int is_end_of_line = 0;
    double *elements_1d;
    double **elements;
    double *centroids_1d;
    double **centroids;
    double *clusters_1d;
    double **clusters;
    int *size_of_clusters;
    int assigned_centroid;
    
    struct vector *head_vec, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int i, j, l;
    double n;
    char c;
    struct vector *loop_vector;
    struct cord *loop_cord;

    int end = 0;

    if (argc == 2) 
    {
        k = atoi(argv[1]);
        iter = 200;
    }
    else if(argc ==3)
    {
        k = atoi(argv[1]);
        iter = atoi(argv[2]);
        if(iter<1 || iter>1000 || iter!= atof(argv[2])){
            printf("Invalid maximum iteration!\n");
            exit(1);
        }
    }
    else
    {
        printf("An Error Has Occurred\n");
        exit(1);
    }

    head_cord = malloc(sizeof(struct cord)); 
    if(head_cord==NULL){
        printf("An Error Has Occurred\n");
        exit(1);
    }
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    if(head_vec==NULL){
        printf("An Error Has Occurred\n");
        free(head_cord);
        exit(1);
    }
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2)
    {
        if(!is_end_of_line){
            d+=1;
        }
        if (c == '\n')
        {   is_end_of_line =1;
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = calloc(1,sizeof(struct vector));
            if(curr_vec->next==NULL){
                printf("An Error Has Occurred\n");
                delete_vector(head_vec);
                exit(1);
            }
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = calloc(1,sizeof(struct cord));
            if(head_cord==NULL){
                printf("An Error Has Occurred\n");
                delete_vector(head_vec);
                exit(1);
            }
            curr_cord = head_cord;
            curr_cord->next = NULL;
            num_of_elements++;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }
    
    free(curr_cord);

    if(k<1 || k>num_of_elements || k!= atof(argv[1])){
        printf("Invalid number of clusters!\n");
        delete_vector(head_vec);
        exit(1);
    }


    /*memory allocation for all the points in the file*/
    elements_1d = calloc(num_of_elements*d, sizeof(double));
    if(elements_1d == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        exit(1);
    }
    elements = calloc(num_of_elements,sizeof(double *));
    if(elements == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        free(elements_1d);
        exit(1);
    }
    for(i=0; i<num_of_elements; i++)
    {
        elements[i] = elements_1d+i*d;
    } 

    /*memory allocation for k centroids*/
    centroids_1d = calloc(k*d, sizeof(double));
    if(centroids_1d == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        free(elements_1d);
        free(elements);
        exit(1);
    }
    centroids = calloc(k,sizeof(double *));
    if(centroids == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        free(elements_1d);
        free(elements);
        free(centroids_1d);
        exit(1);
    }
    for(i=0; i<k; i++)
    {
        centroids[i] = centroids_1d+i*d;
    }

    /*put the first k points in the centroids array*/
    i=0;
    j=0;
    
    loop_vector = head_vec;
    for(i=0; i<k; i++){
        loop_cord = loop_vector->cords;
        for(j=0; j<d; j++){
            centroids[i][j]= loop_cord->value;
            loop_cord=loop_cord->next;
        }
        loop_vector=loop_vector->next;
    }
    
    /*memory allocation for sum matrix "representing" clusters*/
    clusters_1d = calloc(k*d, sizeof(double));
    if(clusters_1d == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        free(elements_1d);
        free(elements);
        free(centroids_1d);
        free(centroids);
        exit(1);
    }
    clusters = calloc(k,sizeof(double *));
    if(clusters == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        free(elements_1d);
        free(elements);
        free(centroids_1d);
        free(centroids);
        free(clusters_1d);
        exit(1);
    }
    for(j=0; j<k; j++)
    {
        clusters[j] = clusters_1d+j*d;
    } 

    /*memory allocation for array of sizes of clusters*/
    size_of_clusters = calloc(k, sizeof(int));
    if(size_of_clusters == NULL){
        printf("An Error Has Occurred\n");
        delete_vector(head_vec);
        free(elements_1d);
        free(elements);
        free(centroids_1d);
        free(centroids);
        free(clusters_1d);
        free(clusters);
        exit(1);
    }
    
    /*assignment of elements into 2d matrix*/
    i=0;
    j=0;
    loop_vector = head_vec;
    for(i=0; i<num_of_elements; i++){
        loop_cord = loop_vector->cords;
        for(j=0; j<d; j++){
            elements[i][j]= loop_cord->value;
            loop_cord=loop_cord->next;
        }
        loop_vector=loop_vector->next;
    }
    delete_vector(head_vec);
    
    i=0;
    j=0;
    l=0;
    for(i=0; i<iter; i++)
    { 
       for(j=0; j<num_of_elements; j++){ 
        assigned_centroid= clusterAssign(elements[j], centroids,k,d);
        for(l=0; l<d; l++){
            clusters[assigned_centroid][l] += elements[j][l];
        }
        size_of_clusters[assigned_centroid]+=1;
       }
       centroidUpdate(clusters, size_of_clusters, k, d);
       j=0;
       end=1;
       for(j=0; j<k; j++){
        if(distance(centroids[j],clusters[j],d)>= 0.001){
            end = 0;
            break;
        }
       
       }
       if(end){
        break;
       }
       j=0;
       l=0;
       for(j=0;j<k;j++){
        for(l=0;l<d;l++){
            centroids[j][l] = clusters[j][l];
            clusters[j][l]=0;
        }
        size_of_clusters[j]=0;
       }
    }

    
    printClusters(centroids, d, k);

    free(elements);
    free(centroids);
    free(centroids_1d);
    free(elements_1d);
    free(clusters);
    free(size_of_clusters);
    free(clusters_1d);

    
    return 0;
}