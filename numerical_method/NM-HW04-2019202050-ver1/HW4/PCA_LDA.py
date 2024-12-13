import torch
import torchvision
from torchvision import transforms, datasets
from torch.utils.data import DataLoader
import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics.pairwise import cosine_distances, euclidean_distances
from mpl_toolkits.mplot3d import Axes3D

np.random.seed(42)

# 사진 크기 조정 및 tensor로 변환
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])

# 데이터셋 가져오기
train_dataset = datasets.ImageFolder(root="HW04-dataset/Training", transform=transform)
test_dataset = datasets.ImageFolder(root="HW04-dataset/Test", transform=transform)

# dataloader를 이용해 instance화
train_dataloader = DataLoader(train_dataset, batch_size=len(train_dataset), shuffle=False)
test_dataloader = DataLoader(test_dataset, batch_size=len(test_dataset), shuffle=False)

# 이미지와 라벨 분리
train_images, train_labels = next(iter(train_dataloader))
test_images, test_labels = next(iter(test_dataloader))

# 훈련데이터와 정답데이터 분리
train_images, train_labels = train_images, train_labels
test_images, test_labels = test_images, test_labels

#데이터셋 shape 출력
print("<train data>")
print(train_images.shape)
print(" ")
print("<test data>")
print(test_images.shape)
print(" ")

#PCA 표준화(평균 구하고 데이터셋에서 빼기)
mean_values = np.mean(train_images.cpu().numpy(), axis=(2, 3), keepdims=True)
standardized_train_data = train_images.cpu().numpy() - mean_values
#LDA 표준화(평균 구하고 데이터셋에서 빼기)
mean_values_lda = np.mean(train_images.cpu().numpy(), axis=(2, 3), keepdims=True)
standardized_train_data_lda = train_images.cpu().numpy() - mean_values_lda

# shape가 (샘플 수 x RGB x height x width) 이므로 샘플 수 x image_1d 꼴로 변형
num_samples, num_channels, height, width = standardized_train_data.shape
standardized_train_data_2d = standardized_train_data.reshape(num_samples, num_channels * height * width)
print("<standardized_train_data>")
print(standardized_train_data_2d.shape)
print(" ")

num_samples_lda, num_channels_lda, height_lda, width_lda = standardized_train_data_lda.shape
standardized_train_data_2d_lda = standardized_train_data_lda.reshape(num_samples_lda, num_channels_lda * height_lda * width_lda)
print("<standardized_train_data_lda>")
print(standardized_train_data_2d_lda.shape)
print(" ")

#클래스의 산포 행렬을 저장하기 위한 행렬 선언(초기에는 모두 0)
class_scatter_matrix_lda = np.zeros((num_channels_lda * height_lda * width_lda, num_channels_lda * height_lda * width_lda))
#클래스들의 평균 저장할 리스트
class_means_lda = []

#클래스 개수만큼 반복
for i in range(len(np.unique(train_labels.cpu().numpy()))):
    #클래스에 해당하는 샘플 추출
    class_samples_lda = standardized_train_data_2d_lda[train_labels.cpu().numpy() == i]
    #클래스내 샘플들의 평균 구하기
    class_mean_lda = np.mean(class_samples_lda, axis=0)
    #리스트에 클래스 평균 추가
    class_means_lda.append(class_mean_lda)
    #산포 행렬 업데이트
    class_scatter_matrix_lda += np.dot((class_samples_lda - class_mean_lda).T, (class_samples_lda - class_mean_lda))

#모든 클래스의 평균 계산
total_mean_lda = np.mean(standardized_train_data_2d_lda, axis=0)
#클래스간 산포 저장할 행렬
classes_scatter_matrix_lda = np.zeros((num_channels_lda * height_lda * width_lda, num_channels_lda * height_lda * width_lda))
#클래스간 산포 행렬 구하기
for i in range(len(np.unique(train_labels.cpu().numpy()))):
    class_samples_lda = standardized_train_data_2d_lda[train_labels.cpu().numpy() == i]
    classes_scatter_matrix_lda += np.dot((class_means_lda[i] - total_mean_lda).reshape(-1, 1), (class_means_lda[i] - total_mean_lda).reshape(1, -1))

#PCA의 공분산 행렬 구하기
covariance_matrix_train = np.cov(standardized_train_data_2d, rowvar=False)
#고유벡터 고유값 구하기
eigenvalues_train, eigenvectors_train = np.linalg.eigh(covariance_matrix_train)

#LDA연산시 특이행렬을 방지하기 위한 축 추가
reg_param = 1e-3
class_scatter_matrix_lda += reg_param * np.eye(class_scatter_matrix_lda.shape[0])
classes_scatter_matrix_lda += reg_param * np.eye(classes_scatter_matrix_lda.shape[0])
eigenvalues_lda, eigenvectors_lda = np.linalg.eigh(np.linalg.inv(class_scatter_matrix_lda).dot(classes_scatter_matrix_lda))

#고유벡터들을 고유값 크기 순으로 정렬
sorted_indices_train = np.argsort(eigenvalues_train)[::-1]
eigenvalues_train = eigenvalues_train[sorted_indices_train]
eigenvectors_train = eigenvectors_train[:, sorted_indices_train]

sorted_indices_lda = np.argsort(eigenvalues_lda)[::-1]
eigenvalues_lda = eigenvalues_lda[sorted_indices_lda]
eigenvectors_lda = eigenvectors_lda[:, sorted_indices_lda]

#사용할 축 개수 설정
k_train = 28
selected_eigenvectors_train = eigenvectors_train[:, :k_train]

k_train_lda = k_train
selected_eigenvectors_lda = eigenvectors_lda[:, :k_train_lda]
print(f"사용할 축 개수: {k_train}")

#고유벡터에 데이터 투영
projected_train_data = np.dot(standardized_train_data_2d, selected_eigenvectors_train)

projected_train_data_lda = standardized_train_data_2d_lda.dot(selected_eigenvectors_lda)

#테스트 데이터 표준화
mean_values_test = np.mean(test_images.cpu().numpy(), axis=(2, 3), keepdims=True)
standardized_test_data = test_images.cpu().numpy() - mean_values_test

mean_values_test_lda = np.mean(test_images.cpu().numpy(), axis=(2, 3), keepdims=True)
standardized_test_data_lda = test_images.cpu().numpy() - mean_values_test_lda


#고유벡터에 투영하기 전 행렬 변형
num_samples_test, _, _, _ = standardized_test_data.shape
standardized_test_data_2d = standardized_test_data.reshape(num_samples_test, num_channels * height * width)

num_samples_test_lda, _, _, _ = standardized_test_data_lda.shape
standardized_test_data_2d_lda = standardized_test_data_lda.reshape(num_samples_test_lda, num_channels_lda * height_lda * width_lda)

#훈련데이터를 이용해 구한 고유벡터에 투영
projected_test_data = np.dot(standardized_test_data_2d, selected_eigenvectors_train)

projected_test_data_lda = standardized_test_data_2d_lda.dot(selected_eigenvectors_lda)

#분류 성능 평가를 위해 로지스틱회귀 모델 학습
model = LogisticRegression(solver='lbfgs', max_iter=1000)
model.fit(projected_train_data, train_labels.cpu().numpy())

model_lda = LogisticRegression(solver='lbfgs', max_iter=1000)
model_lda.fit(projected_train_data_lda, train_labels.cpu().numpy())

#유클리드 거리로 분류하는 모델 학습
num_neighbor = 2
print(f"knn_neighbor: {num_neighbor}")
knn_euclidean = KNeighborsClassifier(n_neighbors=num_neighbor, metric='euclidean')
knn_euclidean.fit(projected_train_data, train_labels.cpu().numpy())

knn_euclidean_lda = KNeighborsClassifier(n_neighbors=num_neighbor, metric='euclidean')
knn_euclidean_lda.fit(projected_train_data_lda, train_labels.cpu().numpy())

# 코사인 거리로 분류하는 모델 학습
knn_cosine = KNeighborsClassifier(n_neighbors=num_neighbor, metric='cosine')
knn_cosine.fit(projected_train_data, train_labels.cpu().numpy())

knn_cosine_lda = KNeighborsClassifier(n_neighbors=num_neighbor, metric='cosine')
knn_cosine_lda.fit(projected_train_data_lda, train_labels.cpu().numpy())

# PCA와 LDA SVM 모델 생성
SVM_kernel = 'linear'
print(f"SVM_kernel: {SVM_kernel}")
print(" ")
svm_model_pca = SVC(kernel=SVM_kernel)
svm_model_pca.fit(projected_train_data, train_labels.cpu().numpy())

svm_model_lda = SVC(kernel=SVM_kernel)
svm_model_lda.fit(projected_train_data_lda, train_labels.cpu().numpy())

#테스트 데이터를 이용한 예측
test_predictions = model.predict(projected_test_data)
test_predictions_lda = model_lda.predict(projected_test_data_lda)
knn_predictions_euclidean = knn_euclidean.predict(projected_test_data)
knn_predictions_euclidean_lda = knn_euclidean.predict(projected_test_data_lda)
knn_predictions_cosine = knn_cosine.predict(projected_test_data)
knn_predictions_cosine_lda = knn_cosine.predict(projected_test_data_lda)
test_predictions_svm_pca = svm_model_pca.predict(projected_test_data)
test_predictions_svm_lda = svm_model_lda.predict(projected_test_data_lda)

#정확도 출력
accuracy = accuracy_score(test_labels.cpu().numpy(), test_predictions)
print(f"Logistic_Regression_Accuracy(PCA): {accuracy}")
print(" ")

accuracy_lda = accuracy_score(test_labels.cpu().numpy(), test_predictions_lda)
print(f"Logistic_Regression_Accuracy(LDA): {accuracy_lda}")
print(" ")

accuracy_knn_euclidean = accuracy_score(test_labels.cpu().numpy(), knn_predictions_euclidean)
print(f"k-NN_Euclidean_Accuracy(PCA): {accuracy_knn_euclidean}")
print(" ")

accuracy_knn_euclidean_lda = accuracy_score(test_labels.cpu().numpy(), knn_predictions_euclidean_lda)
print(f"k-NN_Euclidean_Accuracy(LDA): {accuracy_knn_euclidean_lda}")
print(" ")

accuracy_knn_cosine = accuracy_score(test_labels.cpu().numpy(), knn_predictions_cosine)
print(f"k-NN_Cosine_Accuracy(PCA): {accuracy_knn_cosine}")
print(" ")

accuracy_knn_cosine_lda = accuracy_score(test_labels.cpu().numpy(), knn_predictions_cosine_lda)
print(f"k-NN_Cosine_Accuracy(LDA): {accuracy_knn_cosine_lda}")
print(" ")

accuracy_svm_pca = accuracy_score(test_labels.cpu().numpy(), test_predictions_svm_pca)
print(f"SVM_Accuracy (PCA): {accuracy_svm_pca}")
print(" ")

accuracy_svm_lda = accuracy_score(test_labels.cpu().numpy(), test_predictions_svm_lda)
print(f"SVM_Accuracy (LDA): {accuracy_svm_lda}")
print(" ")

# #1D
# plt.figure(figsize=(12, 10))

# plt.subplot(2, 2, 1)
# plt.scatter(projected_train_data[:, 0], np.zeros_like(projected_train_data[:, 0]), c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (PCA)')
# plt.title('PCA Projection of Training Data')
# plt.xlabel('Principal Component 1')
# plt.legend()

# plt.subplot(2, 2, 2)
# plt.scatter(projected_test_data[:, 0], np.zeros_like(projected_test_data[:, 0]), c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (PCA)')
# plt.title('PCA Projection of Test Data')
# plt.xlabel('Principal Component 1')
# plt.legend()

# plt.subplot(2, 2, 3)
# plt.scatter(projected_train_data_lda[:, 0], np.zeros_like(projected_train_data_lda[:, 0]), c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (LDA)')
# plt.title('LDA Projection of Training Data')
# plt.xlabel('Discriminant Component 1')
# plt.legend()

# # LDA 테스트데이터
# plt.subplot(2, 2, 4)
# plt.scatter(projected_test_data_lda[:, 0], np.zeros_like(projected_test_data_lda[:, 0]), c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (LDA)')
# plt.title('LDA Projection of Test Data')
# plt.xlabel('Discriminant Component 1')
# plt.legend()

# # Show the plots
# plt.tight_layout()
# plt.show()

#2D
plt.figure(figsize=(12, 10))

# PCA 훈련데이터
plt.subplot(2, 2, 1)
plt.scatter(projected_train_data[:, 0], projected_train_data[:, 1], c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (PCA)')
plt.title('PCA Projection of Training Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.legend()

# PCA 테스트데이터
plt.subplot(2, 2, 2)
plt.scatter(projected_test_data[:, 0], projected_test_data[:, 1], c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (PCA)')
plt.title('PCA Projection of Test Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.legend()

# LDA 훈련데이터
plt.subplot(2, 2, 3)
plt.scatter(projected_train_data_lda[:, 0], projected_train_data_lda[:, 1], c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (LDA)')
plt.title('LDA Projection of Training Data')
plt.xlabel('Discriminant Component 1')
plt.ylabel('Discriminant Component 2')
plt.legend()

# LDA 테스트데이터
plt.subplot(2, 2, 4)
plt.scatter(projected_test_data_lda[:, 0], projected_test_data_lda[:, 1], c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (LDA)')
plt.title('LDA Projection of Test Data')
plt.xlabel('Discriminant Component 1')
plt.ylabel('Discriminant Component 2')
plt.legend()

# plot 띄우기
plt.tight_layout()
plt.show()

# #3D
# fig = plt.figure(figsize=(12, 10))

# # PCA 훈련데이터
# ax1 = fig.add_subplot(2, 2, 1, projection='3d')
# ax1.scatter(projected_train_data[:, 0], projected_train_data[:, 1], projected_train_data[:, 2], c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (PCA)')
# ax1.set_title('PCA Projection of Training Data')
# ax1.set_xlabel('Principal Component 1')
# ax1.set_ylabel('Principal Component 2')
# ax1.set_zlabel('Principal Component 3')
# ax1.legend()

# # PCA 테스트데이터
# ax2 = fig.add_subplot(2, 2, 2, projection='3d')
# ax2.scatter(projected_test_data[:, 0], projected_test_data[:, 1], projected_test_data[:, 2], c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (PCA)')
# ax2.set_title('PCA Projection of Test Data')
# ax2.set_xlabel('Principal Component 1')
# ax2.set_ylabel('Principal Component 2')
# ax2.set_zlabel('Principal Component 3')
# ax2.legend()

# # LDA 훈련데이터
# ax3 = fig.add_subplot(2, 2, 3, projection='3d')
# ax3.scatter(projected_train_data_lda[:, 0], projected_train_data_lda[:, 1], projected_train_data_lda[:, 2], c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (LDA)')
# ax3.set_title('LDA Projection of Training Data')
# ax3.set_xlabel('Discriminant Component 1')
# ax3.set_ylabel('Discriminant Component 2')
# ax3.set_zlabel('Discriminant Component 3')
# ax3.legend()

# # LDA 테스트데이터
# ax4 = fig.add_subplot(2, 2, 4, projection='3d')
# ax4.scatter(projected_test_data_lda[:, 0], projected_test_data_lda[:, 1], projected_test_data_lda[:, 2], c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (LDA)')
# ax4.set_title('LDA Projection of Test Data')
# ax4.set_xlabel('Discriminant Component 1')
# ax4.set_ylabel('Discriminant Component 2')
# ax4.set_zlabel('Discriminant Component 3')
# ax4.legend()

# # plot 띄우기
# plt.tight_layout()
# plt.show()