import os
import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, f1_score, precision_score, recall_score, classification_report, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.decomposition import TruncatedSVD
from sklearn.preprocessing import MinMaxScaler
from imblearn.over_sampling import SMOTE
from sklearn.pipeline import Pipeline
from sklearn.compose import ColumnTransformer
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import OneHotEncoder

# Load the data
file_path = "data/train.csv"
data = pd.read_csv(file_path)

# Separate features and target
train_data = data.drop(columns=["target"])
train_label = data["target"]

# Remove columns with missing values and columns with only one unique value
train_data = train_data.dropna(axis=1)
train_data = train_data.loc[:, train_data.nunique() > 1]

# Identify categorical and numerical columns
categorical_cols = train_data.select_dtypes(include=['object']).columns
numerical_cols = train_data.select_dtypes(include=['int64', 'float64']).columns

# Preprocessing pipeline
preprocessor = ColumnTransformer(
    transformers=[
        ('num', MinMaxScaler(), numerical_cols),
        ('cat', Pipeline(steps=[('imputer', SimpleImputer(strategy='constant', fill_value='missing')),
                                ('onehot', OneHotEncoder(handle_unknown='ignore', sparse_output=True))]), categorical_cols)
    ])

# Apply preprocessing
train_data_preprocessed = preprocessor.fit_transform(train_data)

# Apply TruncatedSVD to keep 99% variance
svd = TruncatedSVD(n_components=200, random_state=110)
df_train_svd = svd.fit_transform(train_data_preprocessed)

# Balance the dataset using SMOTE
smote = SMOTE(random_state=110)
df_train_resampled, train_y_resampled = smote.fit_resample(df_train_svd, train_label)

# Initialize and train the model
model = RandomForestClassifier(n_estimators=200, random_state=110, class_weight='balanced')
model.fit(df_train_resampled, train_y_resampled)

file_path = "./data/test.csv"
test_data = pd.read_csv(file_path)

# Preprocess the test data similarly to the training data
test_data_preprocessed = preprocessor.transform(test_data.drop(columns=['target','Set ID']))

# Apply TruncatedSVD (or PCA if needed) to the test data
test_data_svd = svd.transform(test_data_preprocessed)

# Predict the target for the test data
test_predictions = model.predict(test_data_svd)
test_predictions

# Update the submission dataframe with the predictions
submission_data = pd.read_csv("./submission.csv")
submission_data['target'] = test_predictions

# Save the updated submission file
submission_data.to_csv("./submission.csv", index=False)