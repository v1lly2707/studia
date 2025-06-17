import numpy as np

def initialize_centroids_forgy(data, k):
    # TODO implement random initialization
    return data[np.random.choice(data.shape[0], k, replace=False)] #losowe wybranie punktów z danych jako centroidy

def initialize_centroids_kmeans_pp(data, k):
    # TODO implement kmeans++ initizalization
    centroids = np.zeros((k, data.shape[1]))
    centroids[0] = data[np.random.choice(data.shape[0],1, replace=False)] #pierwszy centroid wybieramy losowo
    for i in range(1, k): #dla kolejnych obliczamt minimalna odleglosc do centroidow - ten z najwieksza odlegloscia bedzie nowym centroidem
        distances = np.zeros(data.shape[0])
        for j in range(data.shape[0]):
            distances[j] = np.min(np.sqrt(np.sum((data[j]-centroids[:i])**2)))
            centroids[i] = data[distances.argmax()]
    return centroids

def assign_to_cluster(data, centroid): #przydzielamy do centroidow
    # TODO find the closest cluster for each data point
    assignments =  np.zeros(data.shape[0], dtype=int) #obliczamy odleglosci metoda euklidesowa
    # TODO implement the assignment step
    for i in range(data.shape[0]):
        distances = np.zeros(centroid.shape[0])
        for j in range(centroid.shape[0]):
            distances[j] = np.sqrt(np.sum((data[i]-centroid[j])**2))
        assignments[i] = distances.argmin()
    return assignments


def update_centroids(data, assignments): #dla kazdego klastra obliczana jest srednia wszystkich punktow przypisanych do tego klastr
    # TODO find new centroids based on the assignments
    centroids = np.zeros((len(np.unique(assignments)), data.shape[1]))
    for i in range(len(np.unique(assignments))):
        centroids[i] = np.mean(data[assignments == i], axis=0)
    return centroids



def mean_intra_distance(data, assignments, centroids): #obliczenie sredniej odległości punktów od ich centroidow
    return np.sqrt(np.sum((data - centroids[assignments, :])**2))

def k_means(data, num_centroids, kmeansplusplus= False):
    # centroids initizalization
    if kmeansplusplus:
        centroids = initialize_centroids_kmeans_pp(data, num_centroids)
    else: 
        centroids = initialize_centroids_forgy(data, num_centroids)

    
    assignments  = assign_to_cluster(data, centroids)
    for i in range(100): # max number of iteration = 100
        print(f"Intra distance after {i} iterations: {mean_intra_distance(data, assignments, centroids)}")
        centroids = update_centroids(data, assignments)
        new_assignments = assign_to_cluster(data, centroids)
        if np.all(new_assignments == assignments): # stop if nothing changed
            break
        else:
            assignments = new_assignments

    return new_assignments, centroids, mean_intra_distance(data, new_assignments, centroids)         

