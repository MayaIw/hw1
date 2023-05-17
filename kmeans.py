import math
import sys

#p1, p2 are arrays with float values, representing d dimentional points
#the function calculates the euclidean distance between p1 and p2
def distance(p1, p2, d):
    #if(len(p1)!=len(p2)):
    #    print("An Error Has Occurred")
    #    exit()
    sum_of_squares = 0
    for i in range(d):
        sum_of_squares += (p1[i]-p2[i])**2
    distance = math.sqrt(sum_of_squares)
    return distance

#x is a point in R^d, centroids is an array with k points in R^d
def clusterAssign(x, centriods, k, d):
   #num_of_clusters = len(centriods)
   min_distance = distance(x, centriods[0], d)
   cluster = 0
   for i in range(1, k):
       dist = distance(x, centriods[i], d)
       if dist <= min_distance:
           min_distance = dist
           cluster = i
   return cluster 

#clusters is a 2D array of sum of the points in each cluster
#size of clusters is an array of the size of each cluster
#k is the number of clusters
#d is the number of coordinates of each point
def centriodUpdate(clusters, size_of_clusters, k, d):
    for i in range(k):
        for j in range(d):
            if size_of_clusters[i]==0:
                print("An Error Has Occurred")
                exit()
            clusters[i][j] /= size_of_clusters[i]
    return

def printClusters(clusters, d, k):
    for i in range(k):
        for j in range(d):
            print('%.4f' % clusters[i][j], end='')
            if j<d-1:
                print(",", end='')
        print('')
    return

def is_float(n):
    try:
        float(n)
        return True
    except:
        return False

#"main"
def main():
    k=0
    iter=0
    file=None
    file_name=""
    elements = []
    centroids = []
    num_of_elements=0
    d=0
    line_count =0
    end=0

    if len(sys.argv) != 4:
        k = int(sys.argv[1])
        iter = 200
        file_name = sys.argv[2] 
    else:
        k = int(sys.argv[1])
        iter = int(sys.argv[2])
        file_name = str(sys.argv[3])

    file = open(file_name, "r")
    for line in file:
        point = [float(n) for n in line.split(',') if is_float(n)] 
        elements.append(point)
        line_count+=1
        if line_count<=k:
            centroids.append(point)
    
    #print(elements)
    #print("hello")
    #print(centroids)

    num_of_elements=len(elements)
    d=len(elements[0])
    #print("d=", d)
    #print("k=", k)
    #print("num of elements=", num_of_elements)

    clusters = [[0.0 for i in range(d)] for j in range(k)] 
    size_of_clusters = [0.0 for i in range(k)]
    #print("clusters", clusters)
    #print("size of clusters", size_of_clusters)

    assigned_centriod=0
    for i in range(iter):
        print("iteration", i)
        for j in range(num_of_elements):
            assigned_centriod=clusterAssign(elements[j],centroids, k, d)
            print("assigned_centriod", assigned_centriod)
            for l in range(d):
                clusters[assigned_centriod][l] += elements[j][l]
            size_of_clusters[assigned_centriod]+=1
            #print("size of clusters")    
            #print(size_of_clusters)
        centriodUpdate(clusters, size_of_clusters, k, d)
        #print("clusters")
        #print(clusters)
        j=0
        end=1
        for j in range(k):
            if distance(centroids[j], clusters[j], d)>=0.001:
                end=0
                break
        if end:
            break  
        j=0
        l=0
        for j in range(k):
            for l in range(d):
                centroids[j][l] = clusters[j][l]
                clusters[j][l] = 0
            size_of_clusters[j] = 0

    printClusters(centroids, d, k)

if __name__ == "__main__":
    main()