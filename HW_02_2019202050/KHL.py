# -*- coding: utf-8 -*-

import copy
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn import datasets
from sklearn.cluster import KMeans
import warnings
warnings.filterwarnings("ignore") # ignore seaborn code expression warning 
# Libraries added without justification are a minus factor.
    


# Seed setting
seed_num = 2022
#np.random.seed(seed_num)
iteration = 100     # Number of times to repeat steps E and M.


class EM:
    # expectation-maximization algorithm, EM algorithm
    # The EM class is a class that implements an EM algorithm using GMM and kmeans.
    
    # Within the fit function, the remaining functions should be used.
    # Other functions can be added, but all tasks must be implemented with Python built-in functions and Numpy functions.
    # You should annotate each function with a description of the function and parameters(Leave a comment).
    
    def __init__(self, n_clusters, iteration):
        # """
        # Parameters
        # ----------
        # n_clusters (int): Num of clusters (num of GMM)
        # iteration (int): Num of iteration 
        #     Termination conditions if the model does not converge
        # mean (ndarray): Num of clusters x Num of features
        #     The mean vector that each cluster has.
        # sigma (ndarray): Num of clusters x Num of features x Num of features     
        #     The covariance matrix that each cluster has.
        # pi (ndarray): Num of labels (num of clusters)
        #     z(x), Prior probability that each cluster has.
        # return None.
        # -------
        # None.

        # """
        self.n_clusters = n_clusters   
        self.iteration = iteration  
        self.mean = np.zeros((3,4)) 
        self.sigma = np.zeros((3,4,4)) 
        self.pi = np.zeros((3))  
        
    def initialization(self, data): 
        # 1.initialization, 10 points
        # Initial values for mean, sigma, and pi should be assigned.
        # It have a significant impact on performance.  

        # your comment here
        # parameter initialization function (mean, sigma, pi)
        # parameter -> data(150 x 4): iris data
        # return none.

        # your code here

        # Select 3 unique row indices from 0 to 149 without replacement
        selected_indices = np.random.choice(150, 3, replace=False)

        # Use these indices to select rows from the dataset
        self.mean = data[selected_indices, :]

        # Use the overall covariance of the data as the initial value
        self.sigma[0] = np.cov(data, rowvar=False)
        self.sigma[1] = np.cov(data, rowvar=False)
        self.sigma[2] = np.cov(data, rowvar=False)
        # Set to have the same ratio as the initial value
        self.pi[0] = 1/3
        self.pi[1] = 1/3
        self.pi[2] = 1/3
        return
            
    def multivariate_gaussian_distribution(self, x, mean, sigma):
        # """ 2.multivariate_gaussian_distribution, 10 points
        # Use the linear algebraic functions of Numpy. π of this function is not self.pi
        
        # your comment here
        # multivariate gaussian distribution formula function
        # parameter -> x(1 x 4): one data
        #           -> mean(1 x 4): The mean value per cluster is delivered
        #           -> sigma(4 x 4): The sigma value per cluster is delivered
        # return result value.

        # Implementing multivariate gaussian distribution formula
        Gaussian_distribution = (1. / (np.sqrt((2 * np.pi)**4 * np.linalg.det(sigma))) * np.exp(-np.dot((x - mean), np.dot(np.linalg.inv(sigma), (x - mean).T)) / 2))
        return Gaussian_distribution
    
    def expectation(self, data):
        # """ 3.expectation step, 20 points
        # The multivariate_gaussian_distribution(MVN) function must be used.
        
        # your comment here
        # expectation function(E-step of EM algorithm)
        # parameter -> data(150 x 4): iris data
        # return posterior(150 x 3)
        # your code here
        posterior = np.zeros((150,3)) # num of data x num of clusters

        for i in range(data.shape[0]):
            denominator = 0. # denominator initializing
            for j in range(3):
                posterior[i][j] = self.pi[j] * self.multivariate_gaussian_distribution(x=data[i],mean=self.mean[j],sigma=self.sigma[j]) #Likelihood calculated based on current parameters
                denominator += self.pi[j] * self.multivariate_gaussian_distribution(x=data[i],mean=self.mean[j],sigma=self.sigma[j]) # maginalization

            posterior[i] = posterior[i]/denominator # posterior

        return posterior

    def maximization(self, data, posterior): 
        # """ 4.maximization step, 20 points
        # Hint. np.outer
        
        # your comment here
        # maximization function(M-step of EM algorithm)
        # parameter -> data(150 x 4): iris data
        #           -> posterior(150 x 3): Posterior generated from E-step required for parameter readjustment
        # return none.
        # your code here
        denominator = np.sum(posterior, axis=0) # Sum of posteriors for all data
        
        # By differentiating A, B, and C, the parameter that maximizes the likelihood can be readjusted to the posterior value.
        for i in range(3): # Repeat as many clusters
            mean = 0.
            sigma = 0.
            for j in range(data.shape[0]): # mean value readjustment
                mean += data[j]*posterior[j][i]
            self.mean[i] = mean / denominator[i]

            for j in range(data.shape[0]): # Sigma value readjustment
                sigma += posterior[j][i] * np.outer((data[j]-self.mean[i]),(data[j]-self.mean[i]))
            self.sigma[i] = sigma / denominator[i]

            self.pi[i] = denominator[i] / data.shape[0] # pi value readjustment

        return
        
    def fit(self, data):
        # """ 5.fit clustering, 20 points
        # Functions initialization, expectation, and maximization should be used by default.
        # Termination Condition. Iteration is finished or posterior is the same as before. (Beware of shallow copy)
        # Prediction for return should be formatted. Refer to iris['target'] format.
        
        # your comment here
        # model fitting function(EM algorithm)
        # parameter -> data(150 x 4): iris data
        # return prediction(150,)
        # your code here
        self.initialization(data=data) # initializing parameter
        for i in range(self.iteration): # Repeat as many times as iteration
            posterior = self.expectation(data=data) # E-step
            self.maximization(data=data,posterior=posterior) # M-step

        prediction = np.argmax(posterior,axis=1) # Predict label using posterior
        return prediction

def plotting(data, labels):
    # """ 6.plotting, 20 points with report
    # Default = seaborn pairplot
    
    # your comment here
    # plot function based on data
    # parameter -> data(150 x 4): iris data
    #           -> labels(150,): iris labels
    # return none.
    # your code here
    sns.pairplot(pd.DataFrame(data=data, columns=iris['feature_names']).assign(labels=labels), hue='labels') # data plot
    plt.show()
    return
    
    
if __name__ == '__main__':
    # Loading and labeling data
    iris = datasets.load_iris()
    original_data = pd.DataFrame(data= np.c_[iris['data'], iris['target']], columns= iris['feature_names'] + ['labels'])
    original_data['labels'] = original_data['labels'].map({0:'setosa', 1:'versicolor', 2:'virginica'})
    
    plotting(original_data.drop(columns=['labels']), original_data['labels']) # Pass data and labels separately

    # Only data is used W/O labels because EM and Kmeans are unsupervised learning
    data = iris['data']
    
    # Unsupervised learning(clustering) using EM algorithm
    EM_model = EM(n_clusters=3, iteration=iteration)
    EM_pred = EM_model.fit(data)
    EM_pd = pd.DataFrame(data= np.c_[data, EM_pred], columns= iris['feature_names'] + ['labels'])
    EM_pd['labels'] = EM_pd['labels'].map({0:'setosa', 1:'versicolor', 2:'virginica'})
    
    plotting(EM_pd.drop(columns=['labels']), EM_pd['labels']) # Pass data and labels separately
    
    # Why are these two elements almost the same? Write down the reason in your report. Additional 10 points
    print(f'pi :            {EM_model.pi}')
    print(f'count / total : {np.bincount(EM_pred) / 150}')
    
    # Unsupervised learning(clustering) using KMeans algorithm
    KM_model = KMeans(n_clusters=3, init='random', random_state=seed_num, max_iter=iteration).fit(data)
    KM_pred = KM_model.predict(data)
    KM_pd = pd.DataFrame(data= np.c_[data, KM_pred], columns= iris['feature_names'] + ['labels'])
    KM_pd['labels'] = KM_pd['labels'].map({0:'setosa', 1:'versicolor', 2:'virginica'})
    
    plotting(KM_pd.drop(columns=['labels']), KM_pd['labels']) # Pass data and labels separately
    # No need to explain.
    for idx in range(2):
        EM_point = np.argmax(np.bincount(EM_pred[idx*50:(idx+1)*50]))
        KM_point = np.argmax(np.bincount(KM_pred[idx*50:(idx+1)*50]))
        EM_pred = np.where(EM_pred == idx, 3, EM_pred)
        EM_pred = np.where(EM_pred == EM_point, idx, EM_pred)
        EM_pred = np.where(EM_pred == 3, EM_point, EM_pred)
        KM_pred = np.where(KM_pred == idx, 3, KM_pred)
        KM_pred = np.where(KM_pred == KM_point, idx, KM_pred)
        KM_pred = np.where(KM_pred == 3, KM_point, KM_pred)
    
    EM_hit = np.sum(iris['target']==EM_pred)
    KM_hit = np.sum(iris['target']==KM_pred)
    print(f'EM Accuracy: {round(EM_hit / 150,2)}    Hit: {EM_hit} / 150')
    print(f'KM Accuracy: {round(KM_hit / 150,2)}    Hit: {KM_hit} / 150')
    