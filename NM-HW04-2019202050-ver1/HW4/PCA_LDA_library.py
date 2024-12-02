import torch
import torchvision
from torchvision import transforms, datasets
from torch.utils.data import DataLoader
import numpy as np
from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
import matplotlib.pyplot as plt

np.random.seed(42)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])

train_dataset = datasets.ImageFolder(root="HW04-dataset/Training", transform=transform)
test_dataset = datasets.ImageFolder(root="HW04-dataset/Test", transform=transform)

train_dataloader = DataLoader(train_dataset, batch_size=len(train_dataset), shuffle=False)
test_dataloader = DataLoader(test_dataset, batch_size=len(test_dataset), shuffle=False)

train_images, train_labels = next(iter(train_dataloader))
test_images, test_labels = next(iter(test_dataloader))

train_images, train_labels = train_images.to(device), train_labels.to(device)
test_images, test_labels = test_images.to(device), test_labels.to(device)

mean_values = np.mean(train_images.cpu().numpy(), axis=(2, 3), keepdims=True)
standardized_train_data = train_images.cpu().numpy() - mean_values
mean_values_test = np.mean(test_images.cpu().numpy(), axis=(2, 3), keepdims=True)
standardized_test_data = test_images.cpu().numpy() - mean_values_test

num_samples, num_channels, height, width = standardized_train_data.shape
standardized_train_data_2d = standardized_train_data.reshape(num_samples, num_channels * height * width)

num_samples_test, _, _, _ = standardized_test_data.shape
standardized_test_data_2d = standardized_test_data.reshape(num_samples_test, num_channels * height * width)

# 누적 기여율을 기반으로 PCA 축 개수 정하기
cumulative_explained_variance_ratio_threshold = 0.95
pca = PCA()
projected_train_data_pca = pca.fit_transform(standardized_train_data_2d)
cumulative_explained_variance_ratio = np.cumsum(pca.explained_variance_ratio_)
num_components = 2
# num_components = np.argmax(cumulative_explained_variance_ratio >= cumulative_explained_variance_ratio_threshold) + 1 #누적기여율에 따른 component 결정
pca = PCA(n_components=num_components)
projected_train_data_pca = pca.fit_transform(standardized_train_data_2d)
projected_test_data_pca = pca.transform(standardized_test_data_2d)
print(f"cumulative_explained_variance_ratio_threshold:{cumulative_explained_variance_ratio_threshold}")
print(f"num_components(PCA):{num_components}")

# LDA는 누적기여율이 아닌 클래스 간 분산과 클래스 내 분산의 비율을 이용
lda = LDA()
projected_train_data_lda = lda.fit_transform(standardized_train_data_2d, train_labels.cpu().numpy())
explained_variance_ratio = lda.explained_variance_ratio_
cumulative_explained_variance_ratio = np.cumsum(explained_variance_ratio)
num_components = 2
# num_components = np.argmax(cumulative_explained_variance_ratio >= cumulative_explained_variance_ratio_threshold) + 1
lda = LDA(n_components=num_components)
projected_train_data_lda = lda.fit_transform(standardized_train_data_2d,train_labels.cpu().numpy())
projected_test_data_lda = lda.transform(standardized_test_data_2d)
print(f"num_components(LDA):{num_components}")


model_pca = LogisticRegression(solver='lbfgs', max_iter=1000)
model_pca.fit(projected_train_data_pca, train_labels.cpu().numpy())

model_lda = LogisticRegression(solver='lbfgs', max_iter=1000)
model_lda.fit(projected_train_data_lda, train_labels.cpu().numpy())

test_predictions_pca = model_pca.predict(projected_test_data_pca)

test_predictions_lda = model_lda.predict(projected_test_data_lda)

accuracy_pca = accuracy_score(test_labels.cpu().numpy(), test_predictions_pca)
print(f"Accuracy (PCA): {accuracy_pca}")

# Evaluate accuracy for LDA
accuracy_lda = accuracy_score(test_labels.cpu().numpy(), test_predictions_lda)
print(f"Accuracy (LDA): {accuracy_lda}")

plt.figure(figsize=(16, 5))

plt.subplot(1, 4, 1)
plt.scatter(projected_train_data_pca[:, 0], projected_train_data_pca[:, 1], c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (PCA)')
plt.title('PCA Projection of Training Data(scikit-learn)')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.legend()

plt.subplot(1, 4, 2)
plt.scatter(projected_test_data_pca[:, 0], projected_test_data_pca[:, 1], c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (PCA)')
plt.title('PCA Projection of Test Data(scikit-learn)')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.legend()

plt.subplot(1, 4, 3)
plt.scatter(projected_train_data_lda[:, 0], projected_train_data_lda[:, 1], c=train_labels.cpu().numpy(), cmap='viridis', label='Training Data (LDA)')
plt.title('LDA Projection of Training Data (scikit-learn)')
plt.xlabel('Discriminant Component 1')
plt.ylabel('Discriminant Component 2')
plt.legend()

plt.subplot(1, 4, 4)
plt.scatter(projected_test_data_lda[:, 0], projected_test_data_lda[:, 1], c=test_labels.cpu().numpy(), cmap='viridis', label='Test Data (LDA)')
plt.title('LDA Projection of Test Data (scikit-learn)')
plt.xlabel('Discriminant Component 1')
plt.ylabel('Discriminant Component 2')
plt.legend()

plt.tight_layout()
plt.show()