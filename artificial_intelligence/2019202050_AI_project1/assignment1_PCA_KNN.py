# library import
from sklearn.decomposition import PCA
from sklearn.datasets import fetch_lfw_people
import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import mglearn
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
import numpy as np


people = fetch_lfw_people(min_faces_per_person=20, resize=0.7) # 최소 인당 사진 수, 사진 비율
image_shape = people.images[0].shape # image 크기(87x65)
print('people.images의 형태 \n{}'.format(people.images.shape)) # people객체의 image 형태: (3023, 87, 65)
print('class 갯수 \n{}'.format(len(people.target_names))) # people객체의 class 갯수, 62

# 각 target이 나타난 횟수 계산
counts = np.bincount(people.target)

print('<사진 분포 확인>')

for i, (count, name) in enumerate(zip(counts, people.target_names)):
    print('{0:25} {1:3}'.format(name, count), end= '\t')
    if (i + 1) % 4 == 0:
        print()
print()

### 데이터셋의 편중을 막기 위해 20개의 이미지만 선택
mask = np.zeros(people.target.shape, dtype=np.bool_) # 2370개의 boolean타입 False 생성

people_unique = np.unique(people.target) # 중복된 값 제외

for target in people_unique:
    mask[np.where(people.target == target)[0][:20]] = 1 
x_people = people.data[mask] # 훈련 데이터
y_people = people.target[mask] # 정답 데이터

print('20개만 뽑은 데이터의 형태 \n{}'.format(x_people.shape))
# scaler = MinMaxScaler()
# x_people_scaled = scaler.fit_transform(x_people)#전처리
# x_train, x_test, y_train, y_test = train_test_split(x_people_scaled, y_people, stratify=y_people, random_state=0) # 그룹화할 데이터, 랜덤상태, 전처리

x_train, x_test, y_train, y_test = train_test_split(x_people, y_people, stratify=y_people, random_state=0) # 그룹화할 데이터, 랜덤상태

x_train = x_train.reshape(-1,87,65) #30개로 분할한 데이터의 사진 출력을 위해 reshape
fig, axes = plt.subplots(5, 1, # figure객체와 5x2의 plot객체를 각각 할당
                         subplot_kw={'xticks': (), 'yticks': ()},figsize=(10, 10)) # subplot의 축 설정

for target, image, ax in zip(y_train, x_train, axes.reshape(-1)):
    ax.imshow(image) # imshow로 그림 출력
    ax.set_title(people.target_names[target]) # 각 subplot의 제목

x_train = x_train.reshape(-1,5655) #knn에 데이터를 넣기위해 차원을 2로 줄임

knn = KNeighborsClassifier(n_neighbors=1) # 이웃의 수

knn.fit(x_train, y_train) # 모델 학습

print('knn.score(x_test, y_test) \n PCA 적용하지 않은 knn 점수: {:.3f}'.format(knn.score(x_test, y_test)))

mglearn.plots.plot_pca_whitening() # PCA scatter plot 예시

n_components = None
pca = PCA(n_components=n_components)
# PCA 모델을 데이터에 fitting
pca.fit(x_train)
# 누적 기여율 계산
explained_variance_ratio = pca.explained_variance_ratio_
cumulative_explained_variance = explained_variance_ratio.cumsum()

# 원하는 누적 기여율(예: 0.90)을 만족하는 주성분 개수 찾기
desired_cumulative_variance = 0.90
n_components = np.argmax(cumulative_explained_variance >= desired_cumulative_variance) + 1

print(f"선택한 주성분 개수: {n_components}")
print(f"누적 기여율: {cumulative_explained_variance[n_components - 1]:.2f}")


# PCA 모델 생성 및 적용
pca = PCA(n_components=n_components, whiten=True, random_state=0) # 주성분 갯수, whitening option, 랜덤상태
pca.fit(x_train) # PCA 학습

x_train_pca = pca.transform(x_train) # PCA를 데이터에 적용
x_test_pca = pca.transform(x_test)

print('pca 적용 전 shape:{}'.format(x_train.shape))
print(x_train)
print('pca 적용 후 shape:{}'.format(x_train_pca.shape))
print(x_train_pca)
# PCA를 적용한 데이터 형태
print('x_train_pca.shape \ntrain형태:{}'.format(x_train_pca.shape)) 
print('x_test_pca.shape \ntest형태:{}'.format(x_test_pca.shape))


knn = KNeighborsClassifier(n_neighbors=1) # 이웃의 수

knn.fit(x_train_pca, y_train) # 모델 학습

print('PCA적용한 knn 점수: \n{:.3f}'.format(knn.score(x_test_pca, y_test)))


print('pca.components_.shape \n{}'.format(pca.components_.shape))

fig1, axes1 = plt.subplots(10, 10, # subplot 3x5를 axes에 할당

                         subplot_kw={'xticks': (), 'yticks': ()},figsize=(10, 10)) # subplot 축 설정

for i, (comp, ax) in enumerate(zip(pca.components_, axes1.reshape(-1))): # pca.components_와 axes.ravel()을 하나씩 순서대로 할당한 후 인덱스 부여
    ax.imshow(comp.reshape(image_shape)) # image_shape= (87, 65)
    ax.set_title('pricipal component {}'.format(i+1)) # image title

# 원래 데이터로부터 PCA를 적용한 데이터를 역변환하여 복구
x_train_pca_reconstructed = pca.inverse_transform(x_train_pca)

# 복구된 이미지 형태 확인
print('x_train_pca_reconstructed.shape \n복구된 이미지 형태:{}'.format(x_train_pca_reconstructed.shape))

# 복구된 이미지를 시각화
fig2, axes2 = plt.subplots(5, 1, figsize=(10, 10))
for i, ax in enumerate(axes2.reshape(-1)):
    ax.imshow(x_train_pca_reconstructed[i].reshape(image_shape))
    ax.set_title(f'Reconstructed Image {i+1}')
    ax.axis('off')
plt.show()