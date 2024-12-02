import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

class Director:
    def __init__(self, model, optimizer, learning_rate, train_loader, test_loader):
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu") # for gpu
        self.model = model.to(self.device) 
        self.criterion = nn.CrossEntropyLoss() #loss function
        self.optimizer = self.set_optimizer(optimizer, learning_rate) # optimizer
        self.train_loader = train_loader
        self.test_loader = test_loader
        self.train_accuracies = [] #train accuracy list
        self.test_accuracies = [] #test accuracy list

    def set_optimizer(self, optimizer, learning_rate):
        if optimizer == "SGD": #gradient descent
            return optim.SGD(self.model.parameters(), lr=learning_rate, momentum=0.9)
        elif optimizer == "Adam": #adam optimizer
            return optim.Adam(self.model.parameters(), lr=learning_rate)
        else:
            raise ValueError("Invalid optimizer")

    def train(self):
        self.model.train() #train mode
        correct = 0
        total = 0
        for i,data in enumerate(self.train_loader):
            images, labels = data
            images, labels = images.to(self.device), labels.to(self.device) # for gpu
            self.optimizer.zero_grad() #initialize gradient
            outputs = self.model(images)
            loss = self.criterion(outputs, labels) #calculate loss
            loss.backward()
            self.optimizer.step()
            with torch.no_grad(): #evaluate for train
                _, predicted = torch.max(outputs.data, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item() #if matched, put in correct
        train_accuracy = 100 * correct / total
        print(f'Train Accuracy: {train_accuracy} %')
        self.train_accuracies.append(train_accuracy) #put in list each epoch
            

    def test(self):
        self.model.eval() #test mode
        correct = 0
        total = 0
        with torch.no_grad(): #evaluate for test
            for data in self.test_loader:
                images, labels = data
                images, labels = images.to(self.device), labels.to(self.device) #for gpu
                outputs = self.model(images)
                _, predicted = torch.max(outputs.data, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item()#if matched, put in correct
        test_accuracy = 100 * correct / total
        print(f'Test Accuracy: {test_accuracy} %')
        self.test_accuracies.append(test_accuracy)#put in list each epoch
    
    def plot(self):
        epochs = range(1, len(self.train_accuracies) + 1)
        plt.plot(epochs, self.train_accuracies, label='Train Accuracy')
        plt.plot(epochs, self.test_accuracies, label='Test Accuracy')
        plt.xlabel('Epochs')
        plt.ylabel('Accuracy (%)')
        plt.title('2019202050_KHL') #kang hyun lee
        plt.legend()
        plt.show()
        

    def run(self, epochs):
        for epoch in range(epochs):
            print(f'Epoch {epoch + 1}/{epochs}')
            self.train()
            self.test()