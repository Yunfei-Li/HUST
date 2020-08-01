# coding: utf-8
# Copyright (c) 2020 - <yongkangli.ee@outlook.com>
"""
@author: Yongkang.Li
@software: Pycharm
Created at 4:52 PM on May 19 2020
Description: Implement Text Classification based on Naive-Bayes
"""


import jieba
import re
import matplotlib.pyplot as plt
import math


def stopwordslist(filePath):
    """
    :param filePath: the file path of the stopwords list
    :return: the list of stopwords
    """
    stopwords = [line.strip() for line in open(filePath, 'r', encoding='utf-8').readlines()]
    return stopwords


def wordslist(filePath):
    """
    :param filePath: the file path of the text
    :return: the words list
    """
    words = []
    email = open(filePath, encoding='gb2312', errors='ignore').read()
    email = email[email.index("\n\n")::]             # to remove the header of the email
    pattern = re.compile("[^\u4e00-\u9fa5]")         # the range of encoded Chinese characters is \u4e00 to \u9fa5
    email = "".join(pattern.split(email)).strip()    # to remove all the non-Chinese characters
    words.extend(list(jieba.cut(email, cut_all=False, HMM=bool)))
    return words


def getindexes(filePath):
    """
    :param filePath: the file path of the index file
    :return: labels, indexes
    """
    strs = [line.strip() for line in open(filePath, 'r', encoding='utf-8').readlines()]
    labels = []
    indexes = []
    for i in range(len(strs)):
        if "ham" in strs[i]:
            labels.append(0)
            indexes.append("trec06c"+strs[i][6:])
        else:
            labels.append(1)
            indexes.append("trec06c"+strs[i][7:])
    return labels, indexes

def removestopwords(words, stopwords):
    """
    :param words: a words list
    :param stopwords: stopped words
    :return: stopwords removed words list
    """
    for word in words:
        if word in stopwords:
            words.remove(word)

def count2prob(counts, spam_counts, ham_counts):
    """
    :param words: word list
    :return: conditional probability of each word, spam and ham respectively
    """
    ham_probs = {}
    spam_probs = {}
    for word in counts.keys():
        ham_probs[word] = ham_counts[word] / counts[word]
        spam_probs[word] = spam_counts[word] / counts[word]
    return spam_probs, ham_probs

def training(indexes, training_size, stopwords, labels):
    """
    :param indexes: the file path indexes of each email
    :param training_size: the number of emails to be used for training process
    :param stopwords: stopped words
    :param labels: whether it is a spam or ham
    :return: spam_probs, ham_probs
    """
    wordslists = []  # the list of wordslist of all training emails
    words = []  # store all words in one list
    for i in range(training_size):
        tmp = wordslist(indexes[i])
        removestopwords(tmp, stopwords)
        wordslists.append(tmp)
        words += tmp
    counts = {}  # key: word, value: frequency
    for word in words:
        counts[word] = counts.get(word, 0) + 1
    d = counts.keys()
    z = [0 for _ in range(len(d))]
    spam_counts = dict(zip(d, z))  # initialization, key: word in spam, value: frequency in spam
    ham_counts = dict(zip(d,z))  # initialization, key: word in ham, value: frequency in ham
    for i in range(training_size):
        if labels[i]:
            for word in wordslists[i]:
                spam_counts[word] += 1
        else:
            for word in wordslists[i]:
                ham_counts[word] += 1
    spam_probs, ham_probs = count2prob(counts, spam_counts, ham_counts)  # convert frequency to conditional probability
    return spam_counts, ham_counts, spam_probs, ham_probs

def NBpredict(spamprobs, hamprobs, spamprob, hamprob, stopwords, index, mode):
    """
    :param spamprobs: words in spams with probability
    :param hamprobs: words in hams with probability
    :param spamprob: the true probability of spam
    :param hamprob: the true probability of ham
    :param stopwords: stopped words
    :param index: the file path index of the email to be tested
    :param mode: Discrete or Multinomial
    :return: the prediction
    """
    words = wordslist(index)
    removestopwords(words, stopwords)
    counts = {}
    ham = math.log(hamprob)
    spam = math.log(spamprob)
    for word in words:
        counts[word] = counts.get(word, 0) + 1
    for word in counts.keys():
        if mode == 'Multinomial':  # to choose the Multinomial Feature
            times = counts[word]
        else:                      # to choose the Discrete Feature
            times = 1
        ham += times * math.log(hamprobs.get(word, 0.5)+0.001)
        spam += times * math.log(spamprobs.get(word, 0.5)+0.001)
    if ham > spam:
        return 0
    else:
        return 1

if __name__ == '__main__':
    stopwords = stopwordslist("stopwords_chinese.txt")
    labels, indexes = getindexes("trec06c/full/newindex")
    spamprob = sum(labels)/len(labels)
    hamprob = 1-(sum(labels)/len(labels))
    training_size = 35000
    spamcounts, hamcounts, spamprobs, hamprobs = training(indexes, training_size, stopwords, labels)


    spam_p_order = sorted(spamprobs.items(), key=lambda x: x[1], reverse=True)
    ham_p_order = sorted(hamprobs.items(), key=lambda x: x[1], reverse=True)
    spam_f_order = sorted(spamcounts.items(), key=lambda x: x[1], reverse=True)
    ham_f_order = sorted(hamcounts.items(), key=lambda x: x[1], reverse=True)
    print([key for (key, value) in spam_p_order[:50]])
    print([key for (key, value) in ham_p_order[:50]])
    print([key for (key, value) in spam_f_order[:50]])
    print([key for (key, value) in ham_f_order[:50]])

    predictions = []
    truth = []
    for i in range(15000):
        predictions.append(NBpredict(spamprobs, hamprobs, spamprob, hamprob, stopwords, indexes[training_size+i], 'Discrete'))
        truth.append(labels[training_size+i])

    # to evaluate the result
    TP = 0
    TN = 0
    FP = 0
    FN = 0
    for i in range(len(predictions)):
        if predictions[i]:
            if truth[i]:
                TP += 1
            else:
                FP += 1
        else:
            if truth[i]:
                FN += 1
            else:
                TN += 1
    precision = TP / (TP + FP)
    recall = TP / (TP + FN)
    F1 = 2 * precision * recall / (precision + recall)
    accuracy = (TP + TN) / (TP + TN + FP + FN)
    plt.imshow([[TP, FP], [FN, TN]], cmap='binary')
    plt.show()
    print('accuracy=', accuracy)
    print('precision=', precision)
    print('recall=', recall)
    print('F1=', F1)
