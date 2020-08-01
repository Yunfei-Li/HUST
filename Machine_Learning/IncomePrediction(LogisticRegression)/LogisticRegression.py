# coding: utf-8
# Copyright (c) 2020 - <yongkangli.ee@outlook.com>
"""
@author: Yongkang.Li
@software: Pycharm
Created at 2:35 PM on Jun 10 2020
Discription: income predicition(Logistic Regression)
"""

import math
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import StandardScaler


class LinearLogicRegression:
    def __init__(self, epoches=1000, alpha=0.01002, beta1=0.9, beta2=0.9, mode="SGD", penalty=None, lbd=0.00001, silent=True, graph=True):
        """
        :param epoches: the number of rounds
        :param alpha: learning rate
        :param beta1: moment parameter(Moment, Nesterov, Adam, Nadam)
        :param beta2: delta parameter(AdaDelta, Adam, Nadam)
        :param mode: "Vanilla", "Moment", "Nesterov", "AdaGrad", "AdaDelta", "Adam", "Nadam", "StepDiminish", "ContinuousExpDiminish", "DotSumDiminish", "SqrtDiminish"
        :param penalty: "l1", "l2"
        :param lbd: lambda, the parameter for regularization
        :param silent: whether to print the updating process
        :param graph: whether to draw the loss function
        """
        self.epoches = epoches
        self.alpha = alpha
        self.beta1 = beta1
        self.beta2 = beta2
        self.mode = mode
        self.penalty = penalty
        self.lbd = lbd
        self.silent = silent
        self.graph = graph
        self.weights = None
        
    def sigmoid(self, x):
        return 1.0 / (1 + np.exp(-x))

    def data2matrix(self, X):

        return np.array([[1.0, *d] for d in X])

    def fit(self, X, X_test, y, y_test):
        # to add an column to plus b
        mat_train = self.data2matrix(X)
        mat_test = self.data2matrix(X_test)

        # initialization
        self.weights = np.random.uniform(-0.1, 0.1, (1, len(mat_train[0])))
        V = np.zeros((1, len(mat_train[0])))
        squareWeights = 0
        moment = np.zeros(self.weights.shape)
        if self.graph:
            iterations = []
            loss_training = []
            loss_testing = []

        # start iterations
        for epoch in range(self.epoches):
            # Adaptive Learning Rate && update the weights
            if self.mode == "Vanilla":
                gradient = self.computeGradient(mat_train, y)
                self.weights -= self.alpha * gradient
            elif self.mode == "Momentum":
                gradient = self.computeGradient(mat_train, y)
                moment = self.beta1 * moment + (1 - self.beta1) * gradient
                self.weights -= self.alpha * moment
            elif self.mode == "Nesterov":
                weights = self.weights
                self.weights -= self.alpha * moment
                gradient = self.computeGradient(mat_train, y)
                moment = self.beta1 * moment + (1 - self.beta1) * gradient
                self.weights = weights - self.alpha * moment
            elif self.mode == "AdaGrad":
                gradient = self.computeGradient(mat_train, y)
                V += np.square(gradient)
                self.weights -= (self.alpha / np.sqrt(V)) * gradient
            elif self.mode == "AdaDelta":
                gradient = self.computeGradient(mat_train, y)
                V = self.beta2 * V + (1 - self.beta2) * np.square(gradient)
                self.weights -= (self.alpha / np.sqrt(V)) * gradient
            elif self.mode == "Adam":
                gradient = self.computeGradient(mat_train, y)
                moment = self.beta1 * moment + (1 - self.beta1) * gradient
                V = self.beta2 * V + (1 - self.beta2) * np.square(gradient)
                self.weights -= (self.alpha / np.sqrt(V)) * moment
            elif self.mode == "Nadam":
                weights = self.weights
                self.weights -= (self.alpha / np.sqrt(V + 1)) * moment
                gradient = self.computeGradient(mat_train, y)
                moment = self.beta1 * moment + (1 - self.beta1) * gradient
                V = self.beta2 * V + (1 - self.beta2) * np.square(gradient)
                self.weights = weights - (self.alpha / np.sqrt(V)) * moment
            elif self.mode == "SqrtDiminish":
                gradient = self.computeGradient(mat_train, y)
                self.weights -= (self.alpha / math.sqrt(epoch + 1)) * gradient
            elif self.mode == "StepDiminish":
                if epoch % 100 == 0:
                    self.alpha *= 0.8
                gradient = self.computeGradient(mat_train, y)
                self.weights -= (self.alpha / math.sqrt(epoch + 1)) * gradient
            elif self.mode == "ContinuousExpDiminish":
                self.alpha *= 0.99
                gradient = self.computeGradient(mat_train, y)
                self.weights -= (self.alpha / math.sqrt(epoch + 1)) * gradient
            elif self.mode == "DotSumDiminish":
                gradient = self.computeGradient(mat_train, y)
                squareWeights += np.dot(gradient, gradient.T)
                self.weights -= (self.alpha / math.sqrt(squareWeights)) * gradient
            else:
                print("Error: No such mode!")

            # document the data
            if self.graph:
                iterations.append(epoch)
                loss_training.append(self.computeEntropyLoss(mat_train, y))
                loss_testing.append(self.computeEntropyLoss(mat_test, y_test))

            # output the process
            if not self.silent:
                print('Round {}:\n'.format(epoch), self.weights)

        # plot the loss graph
        if self.graph:
            plt.plot(iterations, loss_training, label='training loss')
            plt.plot(iterations, loss_testing, label='test loss')
            plt.xlabel('epoches')
            plt.ylabel('loss')
            plt.legend()
            plt.show()

    def computeGradient(self, x, y):
        """
        :param x: data
        :param y: labels
        :return: gradient
        """
        # compute gradient
        z = self.sigmoid(np.dot(x, self.weights.T))
        gradient = -np.sum(np.dot(x.T, (y - z)), axis=1)

        #  add different kind of regularization
        if self.penalty == "l2":
            gradient += self.lbd * self.weights[0, :]
        elif self.penalty == "l1":
            gradient += self.lbd * np.array(list(map(lambda x: 1 if x > 0 else -1, self.weights[0, :])))

        return gradient

    def computeEntropyLoss(self, mat, y):
        """
        :param mat: transformed data
        :param y: labels
        :return: Cross Entropy
        """
        calculation = self.sigmoid(np.dot(mat, self.weights.T))
        one_minus_calculation = np.where(calculation==1, 1, 1 - calculation)
        calculation = np.where(calculation==0, 1, calculation)
        one_minus_calculation = np.log(one_minus_calculation)
        calculation = np.log(calculation)
        loss = np.mean(np.where(y, - calculation, - one_minus_calculation))
        return loss

    def score(self, X_test, y_test):
        """
        :param X_test: test data
        :param y_test: test labels
        :return: accuracy
        """
        X_test = self.data2matrix(X_test)
        calculation = np.dot(X_test, self.weights.T)
        prediction = np.where(calculation < 0.5, 0, 1)
        correct = np.equal(prediction, y_test)
        accuracy = np.mean(correct)
        return accuracy

    def FindBestAlpha(self, X, X_test, y, y_test, start, end, step):
        """
        :param X: training data
        :param X_test: test data
        :param y: training labels
        :param y_test: test labels
        :param start: the start point of alpha
        :param end: the end point of alpha
        :param step: the change of alpha of each round
        :return: the best alpha with the highest accuracy
        """
        alphas = []
        mis = []
        self.alpha = start
        while self.alpha <= end:
            self.fit(X, X_test, y, y_test)
            alphas.append(self.alpha)
            mis.append(1 - self.score(X_test, y_test))
            self.alpha += step
        # output the best lambda
        print(mis.index(min(mis)), 1 - min(mis))
        # plot the data
        plt.plot(alphas, mis)
        plt.xlabel('learning rate')
        plt.ylabel('misclassification rate')
        plt.show()


    def FindBestLambda(self, X, X_test, y, y_test, start, end, step):
        """
        :param X: training data
        :param X_test: test data
        :param y: training labels
        :param y_test: test labels
        :param start: the start point of lambda
        :param end: the end point of lambda
        :param step: the change of lambda of each round
        :return: the best parameter lambda with the highest accuracy
        """
        lbds = []
        mis = []
        self.lbd = start
        while self.lbd <= end:
            self.fit(X, X_test, y, y_test)
            lbds.append(self.lbd)
            mis.append(1 - self.score(test_data, test_labels))
            self.lbd += step
        
        # output the best lambda
        print(mis.index(min(mis)), 1 - min(mis))
        
        # plot the data
        plt.plot(lbds, mis)
        plt.xlabel('lambda')
        plt.ylabel('misclassification rate')
        plt.show()


if __name__ == '__main__':
    # parameters
    filename = r'C:/Users/Jovy/OneDrive/Desktop/MyFile/Desk/Engineer/CS/python_project/income-KNN/income.csv'
    training_size = 3000
    total_size = 4000

    # read the .csv file
    with open(filename, encoding='utf-8') as f:
        all_data = np.loadtxt(f, delimiter=',')

    # preprocessing: x'=(tan x)^(2 / pi) -> MinMaxScaler -> StandardScaler
    data = all_data[:, 1:58]
    data = np.array(data)
    data = np.arctan(data) ** (2 / np.pi)
    mms = MinMaxScaler()
    data = mms.fit_transform(data)
    stdsc = StandardScaler()
    data = stdsc.fit_transform(data)

    # divide the data: 3000 for training and 1000 for testing
    training_data = data[:training_size, :]
    training_labels = all_data[:training_size, 58:59]
    test_data = data[training_size:total_size, :]
    test_labels = all_data[training_size:total_size, 58:59]

    # set hyper-parameters and start training
    clf = LinearLogicRegression(epoches=1000, alpha=.0036, penalty="l2", mode="Vanilla", lbd=3, silent=True, graph=True)
    clf.fit(training_data, test_data, training_labels, test_labels)

    # test the result
    print(clf.score(test_data, test_labels))
