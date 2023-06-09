# -*- coding: utf-8 -*-
"""dl_a3_fashion.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1I-3Mrai276OtzLQKA-gt5qa0i9NLfrLC
"""

import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt

# Load the data
# (x_train, y_train), (x_test, y_test) = keras.datasets.fashion_mnist.load_data()

train_df = pd.read_csv('fashion-mnist_train.csv')
test_df = pd.read_csv('fashion-mnist_test.csv')

x_train = train_df.iloc[:,1:].to_numpy()
x_train = x_train.reshape([-1,28,28,1])
x_train = x_train / 255

y_train = train_df.iloc[:,0].to_numpy()

x_test = test_df.iloc[:,1:].to_numpy()
x_test = x_test.reshape([-1,28,28,1])
x_test = x_test / 255

y_test = test_df.iloc[:,0].to_numpy()

class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat','Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# Display some images
plt.figure(figsize=(10,10))
for i in range(25):
    plt.subplot(5, 5, i+1)
    plt.xticks([])
    plt.yticks([])
    plt.imshow(x_train[i], cmap='gray')
    plt.xlabel(class_names[y_train[i]])
plt.show()

# Convert the training and testing data into tensors
x_train = tf.convert_to_tensor(x_train,)
y_train = tf.convert_to_tensor(y_train)
y_test

# Convert the labels to one-hot encoded vectors
num_classes = 10
y_train = keras.utils.to_categorical(y_train)
y_test = keras.utils.to_categorical(y_test)

"""The model consists of a single convolutional layer with 16 filters, followed by a max pooling layer, a flatten layer, and two fully connected layers."""

# Build the model
model = keras.Sequential([
    layers.Conv2D(filters=16, kernel_size=(3, 3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2, 2)),
    layers.Flatten(),
    layers.Dense(units=64, activation='relu'),
    layers.Dense(units=num_classes, activation='softmax')
])

model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

# Train the model
history = model.fit(x_train, y_train, epochs=1, batch_size=32, validation_split=0.1)

# Evaluate the model
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=0)
print(test_acc, test_loss)

from sklearn.metrics import confusion_matrix

y_pred = model.predict(x_test)
cm = confusion_matrix(y_pred.argmax(axis=1), y_test.argmax(axis=1))

# Display confusion matrix as image
plt.imshow(cm)

# Add axis labels and tick marks
plt.xticks(range(10))
plt.yticks(range(10))
plt.xlabel("Predicted label")
plt.ylabel("True label")

# Add color bar
plt.colorbar()

# Show plot
plt.show()

from sklearn.metrics import classification_report

cr = classification_report(y_test.argmax(axis=1), y_pred.argmax(axis=1), target_names=class_names)
print(cr)