import tensorflow as tf
from tensorflow import keras
from keras.applications import ResNet50
from keras.layers import Input, Flatten, Dense
from keras.models import Model
from keras.optimizers import Adam
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.datasets import fetch_lfw_people
import numpy as np

#lfw 데이터셋 로드 및 분할
lfw_people = fetch_lfw_people(min_faces_per_person=20, resize=0.7)
mask = np.zeros(lfw_people.target.shape, dtype=np.bool_)
lfw_people_unique = np.unique(lfw_people.target)
for target in lfw_people_unique:
    mask[np.where(lfw_people.target == target)[0][:20]] = 1
x_people = lfw_people.data[mask]
y_people = lfw_people.target[mask]

x_people = x_people.reshape(-1, 87, 65)
x_people = x_people[..., np.newaxis]  # lfw 데이터셋의 RGB 채널 축을 추가
x_people = np.tile(x_people, (1, 1, 1, 3))  # RGB 채널을 3으로 변환
# ResNet50 모델 사용
base_model = ResNet50(weights='imagenet', include_top=False, input_tensor=Input(shape=(87, 65, 3)))

# 분류를 위한 추가적인 레이어
x = Flatten()(base_model.output)
x = Dense(128, activation='relu')(x)
predictions = Dense(len(np.unique(y_people)), activation='softmax')(x)
model = Model(inputs=base_model.input, outputs=predictions)


X_train, X_test, y_train, y_test = train_test_split(x_people, y_people, test_size=0.2, random_state=0)

# 모델 훈련 및 평가 모델
model.compile(optimizer=Adam(learning_rate=1e-4), loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# 모델 훈련
model.fit(X_train, y_train, batch_size=32, epochs=200, validation_data=(X_test, y_test))

# Evaluate the model
y_pred = model.predict(X_test)
y_pred = np.argmax(y_pred, axis=1)
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy: {:.2f}%".format(accuracy * 100))
