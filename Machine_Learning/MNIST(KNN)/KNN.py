# -*- coding: utf-8 -*-
"""
Created on Sat Apr 18 15:11:51 2020

@author: Jovy
"""


import numpy as np
import struct
import matplotlib.pyplot as plt

def idx1_ubyte_parser(idx1_ubyte_filename):
    '''
    
    Parameters
    ----------
    idx1_ubyte_filename : string
        the filename of the idx1_ubyte file
    
    Returns 
    -------
    labels
    
    '''
    #read the idx1_ubyte_file in binary format
    data_b = open(idx1_ubyte_filename, 'rb').read()
    
    #principal information about the labels
    offset = 0
    format_header = '>ii'
    magic_number, num_labels = struct.unpack_from(format_header, data_b, offset)
    
    #read the labels
    offset += struct.calcsize(format_header)
    format_label = '>B'
    labels = np.empty(num_labels)
    for i in range(num_labels):
        labels[i] = struct.unpack_from(format_label, data_b, offset)[0]
        offset += struct.calcsize(format_label)
        
    labels = labels.reshape(num_labels)
    
    return labels



def idx3_ubyte_parser(idx3_ubyte_filename):
    '''
    
    Parameters
    ----------
    idx1_ubyte_filename : string
        the filename of the idx3_ubyte file

    Returns
    -------
    datasets
    
    '''
    #read the idx3_ubyte file in binary format
    data_b = open(idx3_ubyte_filename, 'rb').read()
    
    #principal information about the dataset
    offset = 0
    format_header = '>iiii'
    magic_number, num_images, num_rows, num_columns = struct.unpack_from(format_header, data_b, offset)
    
    #read the images
    image_size = num_rows * num_columns
    offset += struct.calcsize(format_header)
    format_image = '>' + str(image_size) + 'B'
    images = np.empty((num_images, num_rows, num_columns))
    for i in range(num_images):
        images[i] = np.array(struct.unpack_from(format_image, data_b, offset)).reshape(num_rows, num_columns)
        offset += struct.calcsize((format_image))
    
    #plot figure
    #plt.imshow(images[i], 'gray')
    #plt.pause(1)
    #plt.show()
    
    return images



def KNN (K, training_images, training_labels, test_image):
    '''
    
    Parameters
    ----------
    K : int
        the key parameter of KNN
    training_images : np.array
        training sets
    training_labels : np.array
        labels of training sets
    test_image : np.array
        the image to be tested

    Returns
    -------
    Prediction

    '''
    
    #calculate distances
    (training_range, y, z) = np.shape(training_images)
    distances = []
    for i in range(training_range):
        difference = (test_image - training_images[i]) **2
        distance = np.sum(np.reshape(difference,(difference.size,)))
        distances.append(distance)
        
    #sort the distances and get the corresponding labels
    index = np.argsort(distances)
    count = np.zeros((10))
    #plt.figure()
    for i in range(K):
        label = int(training_labels[index[i]])
        count[label] = count[label] + 1
        #plot figure
        #plt.subplot(1,K,i+1)
        #plt.imshow(training_images[index[i]], 'gray')
        #plt.xticks([])
        #plt.yticks([])
    #plt.show()
        
    #find the most class in its K Nearest Neighbours
    classes = np.argsort(count)

    return classes[9]
    
def test_accuracy(K, training_images, training_labels, testing_images, testing_labels):
    '''
    labels = training_labels[index]
    
    #find the K Nearest Neighbours and count the frequency
    valid = labels[ : K]
    
    Parameters
    ----------
    K : int
        the key parameter of KNN
    training_images : np.array
        training sets
    training_labels : np.array
        labels of training sets
    testing_images : np.array
        testing sets
    testing_labels : np.array
        labels of testing sets
        
    Returns
    -------
    Accuracy
    
    '''
    
    right = 0
    (testing_range, y, z) = np.shape(testing_images)
    for test_position in range(testing_range):
        test_image = testing_images[test_position]
        prediction = KNN(K, training_images, training_labels, test_image)
        if int(testing_labels[test_position]) == int(prediction):
            right += 1
    
    accuracy = right / testing_range
    
    return accuracy
    
    
    
if __name__ == '__main__' :
    train_data_filename = 'C:/Users/Jovy/Desktop/MyFile/Desk/Engineer/CS/python_project/MNIST-KNN/train-images.idx3-ubyte'
    train_label_filename = 'C:/Users/Jovy/Desktop/MyFile/Desk/Engineer/CS/python_project/MNIST-KNN/train-labels.idx1-ubyte'
    #test_data_filename = 'C:/Users/Jovy/Desktop/MyFile/Desk/Engineer/CS/python_project/MNIST-KNN/t10k-images.idx3-ubyte'
    #test_label_filename = 'C:/Users/Jovy/Desktop/MyFile/Desk/Engineer/CS/python_project/MNIST-KNN/t10k-labels.idx1-ubyte'
    
    test_label_filename = 'C:/Users/Jovy/Desktop/MyFile/Desk/Engineer/CS/python_project/MNIST-KNN/train-labels.idx1-ubyte'
    test_data_filename = 'C:/Users/Jovy/Desktop/MyFile/Desk/Engineer/CS/python_project/MNIST-KNN/train-images.idx3-ubyte'
    
    train_images = idx3_ubyte_parser(train_data_filename)
    test_images = idx3_ubyte_parser(test_data_filename)
    train_labels = idx1_ubyte_parser(train_label_filename)
    test_labels = idx1_ubyte_parser(test_label_filename)
    
    mode = int(input('1.test single images\n2.test the accuracy\n3.draw misclassification rate\nchoose a mode:'))
    
    if mode == 1:
        while True:
            train_start = int(input('Enter the Start image of the traing datasets (0-59999) :'))
            train_end = int(input('Enter the End image of the training datasets (0-60000) :'))
            test_position = int(input('Enter the Test image of the testing datasets (0- 9999) :'))
            
            #get the designated testing image and label & slice the training set
            test_image = test_images[test_position]
            training_images = train_images[train_start : train_end]
            training_labels = train_labels[train_start : train_end]
            
            #plot the figure
            #plt.figure()
            #plt.imshow(test_images[test_position], 'gray')
            #plt.pause(0.001)
            #plt.show()
            
            K = int(input('Parameter K = '))
            
            prediction = KNN(K, training_images, training_labels, test_image)
            
            print('The  true  label  of  the  tested  image  : ',int(test_labels[test_position]))
            print('The prediction of KNN with K equal to ', K, ' : ', prediction)
            
            stop = input('To Exit? y/n :')
            if stop == 'y':
                break
    
    elif mode == 2:
        train_start = int(input('Enter the Start image of the traing datasets (0-59999) :'))
        train_end = int(input('Enter the End image of the training datasets (0-60000) :'))
        test_start = int(input('Enter the Start image of the testing process (0- 9999) :'))
        test_end = int(input('Endter the End image of the testing process (0-10000) :'))
        K = int(input('Parameter K = '))
        
        training_images = train_images[train_start : train_end]
        training_labels = train_labels[train_start : train_end]
        testing_images = train_images[test_start : test_end]
        testing_labels = train_labels[test_start : test_end]
        
        accuracy = test_accuracy(K, training_images, training_labels, testing_images, testing_labels)
        
        print('accuracy = ', accuracy)
        
    elif mode == 3:
        train_start = int(input('Enter the Start image of the traing datasets (0-59999) :'))
        train_end = int(input('Enter the End image of the training datasets (0-60000) :'))
        test_start = int(input('Enter the Start image of the testing process (0- 9999) :'))
        test_end = int(input('Endter the End image of the testing process (0-10000) :'))
        K_start = int(input('Enter the Smallest K of the testing process :'))
        K_end = int(input('Enter the Biggest  K of the testing process :'))
        K_step = int(input('Enter the step of  K of the testing process :'))
        
        training_images = train_images[train_start : train_end]
        training_labels = train_labels[train_start : train_end]
        testing_images = train_images[test_start : test_end]
        testing_labels = train_labels[test_start : test_end]
        
        accuracy = []
        mis_rate = []
        
        for K in range(K_start, K_end, K_step):
            acc = test_accuracy(K, training_images, training_labels, testing_images, testing_labels)
            accuracy.append(acc)
            mis_rate.append(1-acc)
            print('K = ', K, 'accuracy = ', acc)
        
        T = np.array(range(K_start, K_end, K_step))
        power = np.array(mis_rate)
        plt.plot(T, power)
        plt.scatter(T, power)
        plt.xlabel('K')
        plt.ylabel('misclassification rate')
        plt.show()

    else:
        print('Invalid Input!')