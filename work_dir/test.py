import keras
from keras.layers import Input, Dense
import numpy as np


x = np.linspace(0, 1, 10001)
xx = zip(x[0:-1], x[1:])

yy = []

for i in xx:
	yy.append(np.sin(i[0]) + i[1] * np.random.normal(0.0, 1.0))

x = np.array(xx)
y = np.array(yy)

y = np.reshape(y, (len(y), 1))


input1 = Input(shape = (2,))
input2 = Input(shape = (1,))
input3 = keras.layers.concatenate([input1, input2])
s1 = Dense(1, activation = "sigmoid")(input3)
s2 = Dense(1, activation = "sigmoid")(input3)
t3 = Dense(1, activation = "tanh")(input3)
s4 = keras.layers.multiply([s2, t3])
s5 = Dense(1, activation = "sigmoid")(input3)
input_C = Input(shape = (1,))
tmp1 = keras.layers.multiply([input_C, s1])
tmp2 = keras.layers.add([tmp1, s4])
t33 = Dense(1, activation = "tanh")(tmp2)
tmp3 = keras.layers.multiply([t33, s5])

model = keras.models.Model(inputs = [input1, input2, input_C], outputs = [tmp3, tmp2])


model.compile(optimizer = "adam", loss = "binary_crossentropy")

q0 = [ np.array([x[0].tolist()]), np.array([0]), np.array([0]) ]
q1 = [ y[0], np.array([0]) ]
