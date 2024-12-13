# -*- coding: utf-8 -*-

import numpy as np
      
def feature_normalization(data): # 10 points
    # parameter 
    feature_num = data.shape[1]
    data_point = data.shape[0]
    
    # you should get this parameter correctly
    normal_feature = np.zeros([data_point, feature_num])
    mu = np.zeros([feature_num])
    std = np.zeros([feature_num])
    
    # Calculate average and standard deviation value based on feature
    mu = np.mean(data,axis = 0)
    std = np.std(data,axis = 0)

    #normalization
    normal_feature = (data - mu)/std

    return normal_feature
        
def split_data(data, label, split_factor):
    return  data[:split_factor], data[split_factor:], label[:split_factor], label[split_factor:] # split data based on split_factor

def get_normal_parameter(data, label, label_num): # 20 points
    # parameter
    feature_num = data.shape[1]
    
    # you should get this parameter correctly    
    mu = np.zeros([label_num,feature_num])
    sigma = np.zeros([label_num,feature_num])

    for i in range(label_num):
        data_i = data[np.where(label == i)] # Extracting features per label in train data
        mu[i] = np.mean(data_i,axis=0) # Calculating feature averages per label
        sigma[i] = np.std(data_i,axis=0)# Calculating feature standard deviations per label
    
    return mu, sigma

def get_prior_probability(label, label_num): # 10 points
    # parameter
    data_point = label.shape[0] # total train data
    
    # you should get this parameter correctly
    prior = np.zeros([label_num])
    for i in range(label_num):
        prior[i] = np.size(np.where(label == i)) # Calculating number of images per label in train data
    
    return prior/data_point # Convert to percentage

def Gaussian_PDF(x, mu, sigma): # 10 points
    # calculate a probability (PDF) using given parameters
    # you should get this parameter correctly
    pdf = 0
    
    # Calculate pdf based on Gaussian function
    sigma_squared = sigma ** 2
    coefficient = 1 / np.sqrt(2 * np.pi * sigma_squared)
    exponent = -((x - mu) ** 2) / (2 * sigma_squared)
    pdf = coefficient * np.exp(exponent)

    return pdf

def Gaussian_Log_PDF(x, mu, sigma): # 10 points
    # calculate a probability (PDF) using given parameters
    # you should get this parameter correctly
    log_pdf = 0
    
    # Implementation of log of Gaussian function
    sigma_squared = sigma ** 2
    log_term = 1 / np.sqrt(2 * np.pi * sigma_squared)
    exponent_term = -((x - mu) ** 2) / (2 * sigma_squared)
    log_pdf = np.log(log_term) + exponent_term
    
    return log_pdf

def Gaussian_NB(mu, sigma, prior, data): # 40 points
    # parameter
    data_point = data.shape[0]
    label_num = mu.shape[0]
    
    # you should get this parameter correctly   
    likelihood = np.zeros([data_point, label_num])
    posterior = np.zeros([data_point, label_num])
    ## evidence can be ommitted because it is a constant
    
    for i in range(data_point):
        for j in range(label_num):
            likelihood[i][j] = np.sum(Gaussian_Log_PDF(data[i],mu[j],sigma[j])) # Add the log of likelihoods per feature to get the likelihood per label
            posterior[i][j] = likelihood[i][j] + np.log(prior[j]) # Add the log of prior per label
            
    return posterior

def classifier(posterior):
    data_point = posterior.shape[0]
    prediction = np.zeros([data_point])
    
    prediction = np.argmax(posterior, axis=1) # Predict the class with the highest probability
    
    return prediction
        
def accuracy(pred, gnd):
    data_point = len(gnd)
    
    hit_num = np.sum(pred == gnd) # Calculating number of correct

    return (hit_num / data_point) * 100, hit_num

    ## total 100 point you can get 