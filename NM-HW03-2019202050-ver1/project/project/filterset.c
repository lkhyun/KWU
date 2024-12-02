#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ORIGINAL_WIDTH 256
#define ORIGINAL_HEIGHT 256
#define NEW_WIDTH 512
#define NEW_HEIGHT 512

const char* imageFiles[] = { "./dataset/lr/Barbara_256x256_yuv400_8bit.raw", "./dataset/lr/Couple_256x256_yuv400_8bit.raw", "./dataset/lr/Lena_256x256_yuv400_8bit.raw" };
const char* compareFiles[] = { "./dataset/gt/Barbara_512x512_yuv400_8bit.raw", "./dataset/gt/Couple_512x512_yuv400_8bit.raw", "./dataset/gt/Lena_512x512_yuv400_8bit.raw" };
const char* outputFiles[] = { "./dataset/result/Barbara_512x512_yuv400_8bit.raw", "./dataset/result/Couple_512x512_yuv400_8bit.raw", "./dataset/result/Lena_512x512_yuv400_8bit.raw" };

unsigned char image[ORIGINAL_HEIGHT][ORIGINAL_WIDTH]; //�ε��� 256x256 image
unsigned char Original_Image[NEW_HEIGHT][NEW_WIDTH]; //���� 512x512 image (PSNR �񱳸� ���� �ε�)
unsigned char Interpolation_Image[NEW_HEIGHT+12][NEW_WIDTH+12];//interpolation�� image
unsigned char PSNR_test[NEW_HEIGHT][NEW_WIDTH];//interpolation�� image���� PSNR �񱳸� ���� 512x512��ŭ �̾Ƴ� ����
unsigned char paddedimage[ORIGINAL_HEIGHT+6][ORIGINAL_WIDTH+6];//padding ó���� image
unsigned char image_group[ORIGINAL_HEIGHT][ORIGINAL_WIDTH];//padding ó���� image�� �� �ȼ��� �׷��� ����
int group_count[25];//�׷�� �� �ȼ� ��

char Mask_V[7][7] = { {1,2,2,0,-2,-2,-1},
					  {1,2,3,0,-3,-2,-1},
					  {1,3,4,0,-4,-3,-1},
					  {1,4,5,0,-5,-4,-1},
					  {1,3,4,0,-4,-3,-1},
					  {1,2,3,0,-3,-2,-1},
					  {1,2,2,0,-2,-2,-1}
};
char Mask_H[7][7] = { {-1,-1,-1,-1,-1,-1,-1},
					  {-2,-2,-3,-4,-3,-2,-2},
					  {-2,-3,-4,-5,-4,-3,-2},
					  {0,0,0,0,0,0,0},
					  {2,3,4,5,4,3,2},
					  {2,2,3,4,3,2,2},
					  {1,1,1,1,1,1,1}
};
char Mask_D135[7][7] = { {0,3,2,1,1,1,1},
	                     {-3,0,4,3,2,1,1},
	                     {-2,-4,0,5,4,2,1},
	                     {-1,-3,-5,0,5,3,1},
	                     {-1,-2,-4,-5,0,4,2},
	                     {-1,-1,-2,-3,-4,0,3},
                         {-1,-1,-1,-1,-2,-3,0} 
};
char Mask_D45[7][7] = { {-1,-1,-1,-1,-2,-3,0},
                        {-1,-1,-2,-3,-4,0,3},
                        {-1,-2,-4,-5,0,4,2},
                        {-1,-3,-5,0,5,3,1},
                        {-2,-4,0,5,4,2,1},
                        {-3,0,4,3,2,1,1},
                        {0,3,2,1,1,1,1},
};

void inverseMatrix(double A[49][49], double result[49][49]);
void padImage();
unsigned char clip(double value);
int classifyRange(int value, int minvalue, int maxvalue);
void PSNR(int imageindex);

int main()
{
    for (int z = 0; z < sizeof(imageFiles) / sizeof(imageFiles[0]); z++)
    {
        int maxvalue = 0;
        int minvalue = 0;
        double optimalfilter[3][25][49]; //H: 0,V: 1,D: 2
        memset(optimalfilter, 0, sizeof(optimalfilter));
        FILE* interpolation_file = fopen(imageFiles[z], "rb");
        FILE* original_file = fopen(compareFiles[z], "rb");
        if (interpolation_file == NULL || original_file == NULL)
        {
            perror("���� ���� ����");
            return 1;
        }

        // 2D �̹��� �迭 �ʱ�ȭ
        memset(image, 0, sizeof(image));
        memset(Original_Image, 0, sizeof(Original_Image));
        memset(group_count, 0, sizeof(group_count));

        // ���� ������ �迭�� �б�
        for (int y = 0; y < ORIGINAL_HEIGHT; y++)
        {
            for (int x = 0; x < ORIGINAL_WIDTH; x++)
            {
                if (fread(&image[y][x], 1, 1, interpolation_file) != 1)
                {
                    perror("�̹��� ������ �б� ����");
                    fclose(interpolation_file);
                    return 1;
                }
            }
        }
        for (int y = 0; y < NEW_HEIGHT; y++)
        {
            for (int x = 0; x < NEW_WIDTH; x++)
            {
                if (fread(&Original_Image[y][x], 1, 1, original_file) != 1)
                {
                    perror("�̹��� ������ �б� ����");
                    fclose(original_file);
                    return 1;
                }
            }
        }
        fclose(interpolation_file);
        fclose(original_file);
        
        //padding
        padImage();

        int decisionMinMax[ORIGINAL_HEIGHT][ORIGINAL_WIDTH];
        memset(decisionMinMax, 0, sizeof(decisionMinMax));
        //�ִ�, �ּ� Ȱ���� ����
        for (int i = 0; i < ORIGINAL_HEIGHT; i++)
        {
            for (int j = 0; j < ORIGINAL_WIDTH; j++)
            {
                for (int k = 0; k < 7; k++)
                {
                    for (int p = 0; p < 7; p++)
                    {
                        decisionMinMax[i][j] += paddedimage[i + k][j + p] * (Mask_V[k][p] + Mask_H[k][p] + Mask_D135[k][p] + Mask_D45[k][p]);
                    }
                }
            }
        }
        for (int i = 0; i < ORIGINAL_HEIGHT; i++) 
        {
            for (int j = 0; j < ORIGINAL_WIDTH; j++) 
            {
                if (decisionMinMax[i][j] > maxvalue) 
                {
                    maxvalue = decisionMinMax[i][j];
                }
                if (decisionMinMax[i][j] < minvalue) 
                {
                    minvalue = decisionMinMax[i][j];
                }
            }
        }
        //�׷� ����
        for (int i = 0; i < ORIGINAL_HEIGHT; i++)
        {
            for (int j = 0; j < ORIGINAL_WIDTH; j++)
            {
                int vertical = 0;
                int horizontal = 0;
                int diagonal135 = 0;
                int diagonal45 = 0;
                int activity = 0;
                int direction = 0;// horizontal:1, diagonal45:2, vertical:3, diagonal135:4
                int direction_Max = 0;
                for (int k = 0; k < 7; k++)
                {
                    for (int p = 0; p < 7; p++)
                    {
                        vertical += paddedimage[i + k][j + p] * Mask_V[k][p];
                        horizontal += paddedimage[i + k][j + p] * Mask_H[k][p];
                        diagonal135 += paddedimage[i + k][j + p] * Mask_D135[k][p];
                        diagonal45 += paddedimage[i + k][j + p] * Mask_D45[k][p];
                    }
                }

                activity = classifyRange(vertical + horizontal + diagonal135 + diagonal45, minvalue, maxvalue);
                direction_Max = horizontal;
                direction = 1;
                if (diagonal45 > direction_Max)
                {
                    direction_Max = diagonal45;
                    direction = 2;
                }
                if (vertical > direction_Max)
                {
                    direction_Max = vertical;
                    direction = 3;
                }
                if (diagonal135 > direction_Max)
                {
                    direction_Max = diagonal135;
                    direction = 4;
                }
                if (horizontal == vertical) { direction = 0; }
                if (diagonal135 == diagonal45) { direction = 0; }
                image_group[i][j] = (activity * 5) + direction; //�̹��� �׷������� �ٲٱ�
                group_count[image_group[i][j]]++;
            }
        }

        //padding�� �̹��� ��ĭ�� ���ݵξ� ��ġ��
        for (int i = 0; i < ORIGINAL_HEIGHT + 6; i++)
        {
            for (int j = 0; j < ORIGINAL_WIDTH + 6; j++)
            {
                Interpolation_Image[i * 2][j * 2] = paddedimage[i][j];
            }
        }
        
        //find optimal filter
        for (int g = 0; g < 25; g++)
        {
            if (group_count[g] == 0)
            {
                continue;
            }
            int index = 0;//X �������� �ε���
            double** collection = (double**)calloc(group_count[g],sizeof(double*));//�׷��� ���� �ȼ��� ������ ��
            for (int i = 0; i < group_count[g]; i++)
            {
                collection[i] = (double*)calloc(49,sizeof(double));
            }
            unsigned char* Y_H = (unsigned char*)calloc(group_count[g],sizeof(unsigned char));//H �����ȼ���
            unsigned char* Y_V = (unsigned char*)calloc(group_count[g], sizeof(unsigned char));//V �����ȼ���
            unsigned char* Y_D = (unsigned char*)calloc(group_count[g], sizeof(unsigned char));//D �����ȼ���
            double autocorrelation[49][49];
            double inverseMat[49][49];
            double crosscorrelation[49];

            memset(autocorrelation, 0, sizeof(autocorrelation));
            memset(inverseMat, 0, sizeof(inverseMat));
            memset(crosscorrelation, 0, sizeof(crosscorrelation));
            for (int i = 0; i < ORIGINAL_HEIGHT; i++)
            {
                for (int j = 0; j < ORIGINAL_WIDTH; j++)
                {
                    if (image_group[i][j] == g)
                    {
                        Y_H[index] = Original_Image[i * 2][(j * 2) + 1];
                        Y_V[index] = Original_Image[(i * 2) + 1][j * 2];
                        Y_D[index] = Original_Image[(i * 2) + 1][(j * 2) + 1];
                        for (int k = 0; k < 7; k++)
                        {
                            for (int p = 0; p < 7; p++)
                            {
                                collection[index][(7 * k) + p] = (int)paddedimage[i + k][j + p];
                            }
                        }
                        index++;
                    }
                }
            }
            for (int i = 0; i < 49; i++)
            {
                for (int j = 0; j < 49; j++)
                {
                    for (int k = 0; k < group_count[g]; k++)
                    {
                        autocorrelation[i][j] += collection[k][i] * collection[k][j];
                    }
                }
            }
            inverseMatrix(autocorrelation, inverseMat);
			for (int i = 0; i < 49; i++) //horizontal
			{
				for (int k = 0; k < group_count[g]; k++)
				{
					crosscorrelation[i] += collection[k][i] * Y_H[k];
				}
			}
            for (int i = 0; i < 49; i++)
            {
                for (int j = 0; j < 49; j++)
                {
                    optimalfilter[0][g][i] += inverseMat[i][j] * crosscorrelation[j];
                }
            }
            memset(crosscorrelation, 0, sizeof(crosscorrelation));
            for (int i = 0; i < 49; i++) //vertical
            {
                for (int k = 0; k < group_count[g]; k++)
                {
                    crosscorrelation[i] += collection[k][i] * Y_V[k];
                }
            }
            for (int i = 0; i < 49; i++)
            {
                for (int j = 0; j < 49; j++)
                {
                    optimalfilter[1][g][i] += inverseMat[i][j] * crosscorrelation[j];
                }
            }
            memset(crosscorrelation, 0, sizeof(crosscorrelation));
            for (int i = 0; i < 49; i++) //Diagonal
            {
                for (int k = 0; k < group_count[g]; k++)
                {
                    crosscorrelation[i] += collection[k][i] * Y_D[k];
                }
            }
            for (int i = 0; i < 49; i++)
            {
                for (int j = 0; j < 49; j++)
                {
                    optimalfilter[2][g][i] += inverseMat[i][j] * crosscorrelation[j];
                }
            }
            for (int i = 0; i < group_count[g]; i++)
            {
                free(collection[i]);
            }
            free(collection);
            free(Y_H);
            free(Y_V);
            free(Y_D);
        }
        //interpolation
        for (int i = 0; i < ORIGINAL_HEIGHT; i++)
        {
            for (int j = 0; j < ORIGINAL_WIDTH; j++)
            {
                double H = 0.0;
                double V = 0.0;
                double D = 0.0;
                for (int k = 0; k < 7; k++)
                {
                    for (int p = 0; p < 7; p++)
                    {
                        H += paddedimage[i + k][j + p] * optimalfilter[0][image_group[i][j]][(7 * k) + p];
                        V += paddedimage[i + k][j + p] * optimalfilter[1][image_group[i][j]][(7 * k) + p];
                        D += paddedimage[i + k][j + p] * optimalfilter[2][image_group[i][j]][(7 * k) + p];
                    }
                }
                if (clip(H) == 255 || clip(H) == 0)
                {
                    Interpolation_Image[(i + 3) * 2][((j + 3) * 2) + 1] = (Interpolation_Image[(i + 3) * 2][((j + 3) * 2)] + Interpolation_Image[(i + 3) * 2][((j + 3) * 2) + 2]) / 2;
                }
                else
                {
                    Interpolation_Image[(i + 3) * 2][((j + 3) * 2) + 1] = clip(H);
                }
                if (clip(V) == 255 || clip(V) == 0)
                {
                    Interpolation_Image[((i + 3) * 2) + 1][(j + 3) * 2] = (Interpolation_Image[(i + 3) * 2][(j + 3) * 2] + Interpolation_Image[((i + 3) * 2) + 2][(j + 3) * 2]) / 2;
                }
                else
                {
                    Interpolation_Image[((i + 3) * 2) + 1][(j + 3) * 2] = clip(V);
                }
                if (clip(D) == 255 || clip(D) == 0)
                {
                    Interpolation_Image[((i + 3) * 2) + 1][((j + 3) * 2) + 1] = (Interpolation_Image[(i + 3) * 2][((j + 3) * 2)] + Interpolation_Image[((i + 3) * 2) + 2][((j + 3) * 2) + 2]) / 2;
                }
                else
                {
                    Interpolation_Image[((i + 3) * 2) + 1][((j + 3) * 2) + 1] = clip(D);
                }
            }
        }
        FILE* output_file = fopen(outputFiles[z], "wb");
        
        for (int y = 0; y < 512; y++)
        {
            for (int x = 0; x < 512; x++)
            {
                fwrite(&Interpolation_Image[y+6][x+6], 1, 1, output_file);
                PSNR_test[y][x] = Interpolation_Image[y + 6][x + 6];
            }
        }
        fclose(output_file);
        PSNR(z);
    }
    return 0;
}

void padImage()
{
    for (int i = 0; i < ORIGINAL_HEIGHT + 6; i++)
    {
        for (int j = 0; j < ORIGINAL_WIDTH + 6; j++)
        {
            // �е� ������ ó��
            if (i < 3 || i >= ORIGINAL_HEIGHT + 3 || j < 3 || j >= ORIGINAL_WIDTH + 3)
            {
                // ���� ����� �ȼ��� ã�Ƽ� ä���
                int originalX = (j - 3 < 0) ? 0 : (j - 3 >= ORIGINAL_WIDTH) ? ORIGINAL_WIDTH - 1 : j - 3;
                int originalY = (i - 3 < 0) ? 0 : (i - 3 >= ORIGINAL_HEIGHT) ? ORIGINAL_HEIGHT - 1 : i - 3;
                /*paddedimage[i][j] = image[originalY][originalX];*/
                paddedimage[i][j] = 0;
            }
            // ���� �̹��� ������ ó��
            else
            {
                paddedimage[i][j] = image[i - 3][j - 3];
            }
        }
    }
}

int classifyRange(int value, int minvalue, int maxvalue)
{
    int range = maxvalue - minvalue;

    if (range == 0) {
        return 0;
    }
    //���� 5��
    int interval = range / 5;

    // �߾� ���� ���̱�
    int centralInterval = interval / 3;

    int mappedValue = value - minvalue;

    // ���� �����ϸ�
    mappedValue = (mappedValue < 0) ? 0 : (mappedValue > range) ? range : mappedValue;

    int rangeIndex;

    // ������ �߾ӿ� �ִ��� üũ
    if (mappedValue >= interval * 2 && mappedValue <= interval * 3) {
        rangeIndex = 2 + (mappedValue - interval * 2) / centralInterval;
    }
    else {
        rangeIndex = mappedValue / interval;
    }

    return rangeIndex;
}

void inverseMatrix(double A[49][49], double result[49][49]) 
{
    // ���� ��� �����
    for (int i = 0; i < 49; i++) 
    {
        for (int j = 0; j < 49; j++) 
        {
            result[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // ���콺 �ҰŹ�
    for (int i = 0; i < 49; i++) 
    {
        // �밢 ���� 1
        double pivot = A[i][i];
        for (int j = 0; j < 49; j++) 
        {
            A[i][j] /= pivot;
            result[i][j] /= pivot;
        }

        //�ٸ� �࿡�� ���� �� ����
        for (int k = 0; k < 49; k++) 
        {
            if (k != i) 
            {
                double factor = A[k][i];
                for (int j = 0; j < 49; j++) 
                {
                    A[k][j] -= factor * A[i][j];
                    result[k][j] -= factor * result[i][j];
                }
            }
        }
    }
}

unsigned char clip(double value)
{
    if (value < 0)
    {
        return 0;
    }
    else if (value > 255)
    {
        return 255;
    }
    else
    {
        return (unsigned char)value;
    }
}
void PSNR(int imageindex)
{
    double error = 0;
    double MSE = 0.0;
    double psnr = 0.0;
    for (int i = 0; i < NEW_HEIGHT; i++)
    {
        for (int j = 0; j < NEW_WIDTH; j++)
        {
            error += pow(PSNR_test[i][j] - Original_Image[i][j], 2);
        }
    }
    MSE = error / (NEW_HEIGHT * NEW_WIDTH);
    psnr = (20 * log10(255)) - (10 * log10(MSE));
    if (imageindex == 0) { printf("(Barbara): %lfdB\n", psnr); }
    else if (imageindex == 1) { printf("(Couple): %lfdB\n", psnr); }
    else { printf("(Lena): %lfdB\n", psnr); }

}