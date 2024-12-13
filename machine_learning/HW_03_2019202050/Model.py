import torch
import torch.nn as nn

"""
Implemenet ResNetBlock and ResNet.
Add hyperparameters to ResNet model.
Refer to ReseNet paper, freely modify the model, but you must implement the residuals.
"""

class ResNetBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride = 1): #default stride 1
        super(ResNetBlock, self).__init__()
        self.basicblock = nn.Sequential( # residual block
            nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(),
            nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=False),
            nn.BatchNorm2d(out_channels)
        )
        self.relu = nn.ReLU()
        self.downsample = nn.Sequential()
        if stride != 1 or in_channels != out_channels: #Downsampling to match matrix size
            self.downsample = nn.Sequential(
                nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(out_channels)
            )
            
    def forward(self, x):
        identity = self.downsample(x)
        out = self.basicblock(x)
        out += identity #skip connecting
        out = self.relu(out)
        return out


class ResNet(nn.Module):
    def __init__(self, out_class=10): #cifar-10 dataset has 10 classes
        super(ResNet, self).__init__()
        self.conv1 = nn.Sequential(nn.Conv2d(3,64,kernel_size=7,stride=2,padding=5), #convolution 7x7
                                   nn.BatchNorm2d(64),
                                   nn.ReLU())
        self.maxpool = nn.MaxPool2d(kernel_size=(2,2),stride=(2,2))
        
        self.layer1_1 = ResNetBlock(64,64)
        self.layer1_2 = ResNetBlock(64,64)
        self.layer1_3 = ResNetBlock(64,64)
        
        self.layer2_1 = ResNetBlock(64,128,stride=2) # image size 1/2
        self.layer2_2 = ResNetBlock(128,128)
        self.layer2_3 = ResNetBlock(128,128)
        self.layer2_4 = ResNetBlock(128,128)
        
        self.layer3_1 = ResNetBlock(128,256,stride=2) # image size 1/2
        self.layer3_2 = ResNetBlock(256,256)
        self.layer3_3 = ResNetBlock(256,256)
        self.layer3_4 = ResNetBlock(256,256)
        self.layer3_5 = ResNetBlock(256,256)
        self.layer3_6 = ResNetBlock(256,256)
        
        self.layer4_1 = ResNetBlock(256,512,stride=2) # image size 1/2
        self.layer4_2 = ResNetBlock(512,512)
        self.layer4_3 = ResNetBlock(512,512)
        
        self.avgpool = nn.AdaptiveAvgPool2d((1,1)) #average polling
        self.fc1 = nn.Linear(512,128)
        self.fc2 = nn.Linear(128,out_class)                     
        

    def forward(self, x): #RasNet configuration
        x = self.conv1(x)
        x = self.maxpool(x)
        
        x = self.layer1_1(x)
        x = self.layer1_2(x)
        x = self.layer1_3(x)
        
        x = self.layer2_1(x)
        x = self.layer2_2(x)
        x = self.layer2_3(x)
        x = self.layer2_4(x)
        
        x = self.layer3_1(x)
        x = self.layer3_2(x)
        x = self.layer3_3(x)
        x = self.layer3_4(x)
        x = self.layer3_5(x)
        x = self.layer3_6(x)
        
        x = self.layer4_1(x)
        x = self.layer4_2(x)
        x = self.layer4_3(x)
        
        x = self.avgpool(x)
        x = torch.flatten(x, 1) # flatten x
        x = self.fc1(x)
        x = self.fc2(x)
        return x
