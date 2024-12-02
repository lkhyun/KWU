#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ORIGINAL_WIDTH 128
#define ORIGINAL_HEIGHT 128
#define NEW_WIDTH 512
#define NEW_HEIGHT 512

const char* imageFiles[] = { "./HW02-dataset/dataset/lr/Barbara_128x128_yuv400_8bit.raw", "./HW02-dataset/dataset/lr/Couple_128x128_yuv400_8bit.raw", "./HW02-dataset/dataset/lr/Lena_128x128_yuv400_8bit.raw" };
const char* compareFiles[] = { "./HW02-dataset/dataset/gt/Barbara_512x512_yuv400_8bit.raw", "./HW02-dataset/dataset/gt/Couple_512x512_yuv400_8bit.raw", "./HW02-dataset/dataset/gt/Lena_512x512_yuv400_8bit.raw" };
unsigned char image[ORIGINAL_HEIGHT][ORIGINAL_WIDTH];
unsigned char Original_Image[NEW_HEIGHT][NEW_WIDTH];
unsigned char sixtab_paddedimage[ORIGINAL_HEIGHT + 5][ORIGINAL_WIDTH + 5];
unsigned char bicubic_paddedimage[ORIGINAL_HEIGHT + 3][ORIGINAL_WIDTH + 3];
unsigned char PSNR_test[NEW_HEIGHT][NEW_WIDTH];

int clip(int value);
void sixtab_padImage();
void bicubic_padImage();
void PSNR(int imageindex);
void gauss_elimination(double A[4][5], int n);
void Nearest_Neighbor(int imageindex);
void Bilinear(int imageindex);
void Bicubic(int imageindex);
void Six_tab(int imageindex);
int main() {
    
    for (int i = 0; i < sizeof(imageFiles) / sizeof(imageFiles[0]); i++) 
    {
        FILE* interpolation_file = fopen(imageFiles[i], "rb");
        FILE* original_file = fopen(compareFiles[i], "rb");
        if (interpolation_file == NULL || original_file == NULL) 
        {
            perror("파일 열기 오류");
            return 1;
        }

        // 2D 이미지 배열 초기화
        memset(image, 0, sizeof(image));
        memset(Original_Image, 0, sizeof(Original_Image));

        // 파일 내용을 배열에 읽기
        for (int y = 0; y < ORIGINAL_HEIGHT; y++) 
        {
            for (int x = 0; x < ORIGINAL_WIDTH; x++) 
            {
                if (fread(&image[y][x], 1, 1, interpolation_file) != 1) 
                {
                    perror("이미지 데이터 읽기 오류");
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
                    perror("이미지 데이터 읽기 오류");
                    fclose(original_file);
                    return 1;
                }
            }
        }

        fclose(interpolation_file);
        fclose(original_file);
        Nearest_Neighbor(i);
        printf("Nearest_Neighbor interpolation");
        PSNR(i);
        Bilinear(i);
        printf("Bilinear interpolation PSNR");
        PSNR(i);
        bicubic_padImage();
        Bicubic(i);
        printf("Bicubic interpolation PSNR");
        PSNR(i);
        sixtab_padImage();
        Six_tab(i);
        printf("Six_tab interpolation PSNR");
        PSNR(i);
        printf("\n");
    }
    return 0;
}

void gauss_elimination(double A[4][5], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n + 1; k++) 
            {
                A[j][k] -= ratio * A[i][k];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) 
    {
        A[i][n] /= A[i][i];
        A[i][i] = 1.0;
        for (int j = i - 1; j >= 0; j--) 
        {
            A[j][n] -= A[j][i] * A[i][n];
            A[j][i] = 0.0;
        }
    }
}
void PSNR(int imageindex)
{
    int error = 0;
    double MSE = 0.0;
    double psnr = 0.0;
    for (int i = 0; i < NEW_HEIGHT; i++)
    {
        for (int j = 0; j < NEW_WIDTH; j++)
        {
            error += pow(PSNR_test[i][j] - Original_Image[i][j],2);
        }
    }
    MSE = (double)(error / (NEW_HEIGHT * NEW_WIDTH));
    psnr = (20 * log10(255)) - (10 * log10(MSE));
    if (imageindex == 0) { printf("(Barbara): %lfdB\n", psnr); }
    else if (imageindex == 1) { printf("(Couple): %lfdB\n", psnr); }
    else { printf("(Lena): %lfdB\n", psnr); }

}
void sixtab_padImage() 
{
    for (int i = 0; i < ORIGINAL_HEIGHT + 5; i++) 
    {
        for (int j = 0; j < ORIGINAL_WIDTH + 5; j++) 
        {
            // 패딩 영역을 처리
            if (i < 2 || i >= ORIGINAL_HEIGHT + 2 || j < 2 || j >= ORIGINAL_WIDTH + 2) 
            {
                // 가장 가까운 픽셀을 찾아서 채우기
                int originalX = (j - 2 < 0) ? 0 : (j - 2 >= ORIGINAL_WIDTH) ? ORIGINAL_WIDTH - 1 : j - 2;
                int originalY = (i - 2 < 0) ? 0 : (i - 2 >= ORIGINAL_HEIGHT) ? ORIGINAL_HEIGHT - 1 : i - 2;
                sixtab_paddedimage[i][j] = image[originalY][originalX];
            }
            // 원본 이미지 영역을 처리
            else 
            {
                sixtab_paddedimage[i][j] = image[i - 2][j - 2];
            }
        }
    }
}
void bicubic_padImage()
{
    for (int i = 0; i < ORIGINAL_HEIGHT + 3; i++)
    {
        for (int j = 0; j < ORIGINAL_WIDTH + 3; j++)
        {
            // 패딩 영역을 처리
            if (i < 1 || i >= ORIGINAL_HEIGHT + 1 || j < 1 || j >= ORIGINAL_WIDTH + 1)
            {
                // 가장 가까운 픽셀을 찾아서 채우기
                int originalX = (j - 1 < 0) ? 0 : (j - 1 >= ORIGINAL_WIDTH) ? ORIGINAL_WIDTH - 1 : j - 1;
                int originalY = (i - 1 < 0) ? 0 : (i - 1 >= ORIGINAL_HEIGHT) ? ORIGINAL_HEIGHT - 1 : i - 1;
                bicubic_paddedimage[i][j] = image[originalY][originalX];
            }
            // 원본 이미지 영역을 처리
            else
            {
                bicubic_paddedimage[i][j] = image[i - 1][j - 1];
            }
        }
    }
}
int clip(int value) 
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
        return value;
    }
}
void Nearest_Neighbor(int imageindex)
{
    const char* outputFiles[] = { "./HW02-dataset/dataset/result/Barbara_512x512_yuv400_8bit_Nearest.raw", "./HW02-dataset/dataset/result/Couple_512x512_yuv400_8bit_Nearest.raw", "./HW02-dataset/dataset/result/Lena_512x512_yuv400_8bit_Nearest.raw" };
    unsigned char interpolation_image[NEW_HEIGHT][NEW_WIDTH];
    memset(interpolation_image, 0, sizeof(interpolation_image));
    for (int i = 0; i < NEW_HEIGHT; i++)
    {
        for (int j = 0; j < NEW_WIDTH; j++)
        {
            interpolation_image[i][j] = image[i / 4][j / 4];
        }
    }
    FILE* output_file = fopen(outputFiles[imageindex], "wb");
    for (int y = 0; y < 512; y++)
    {
        for (int x = 0; x < 512; x++)
        {
            fwrite(&interpolation_image[y][x], 1, 1, output_file);
            PSNR_test[y][x] = interpolation_image[y][x];
        }
    }
    fclose(output_file);
}
void Bilinear(int imageindex) 
{
    const char* outputFiles[] = { "./HW02-dataset/dataset/result/Barbara_512x512_yuv400_8bit_Bilinear.raw", "./HW02-dataset/dataset/result/Couple_512x512_yuv400_8bit_Bilinear.raw", "./HW02-dataset/dataset/result/Lena_512x512_yuv400_8bit_Bilinear.raw" };
    unsigned char interpolation_image[NEW_HEIGHT+1][NEW_WIDTH+1];
    memset(interpolation_image, 0, sizeof(interpolation_image));
    /*값 복사*/
    for (int i = 0; i < ORIGINAL_HEIGHT; i++)
    {
        for (int j = 0; j < ORIGINAL_WIDTH; j++)
        {
            interpolation_image[i * 4][j * 4] = image[i][j];
        }
    }
    /*패딩 처리*/
    for (int i = 0; i < ORIGINAL_WIDTH; i++)
    {
        interpolation_image[NEW_HEIGHT][i * 4] = image[ORIGINAL_HEIGHT-1][i];
    }
    for (int i = 0; i < ORIGINAL_HEIGHT; i++)
    {
        interpolation_image[i*4][NEW_WIDTH] = image[i][ORIGINAL_WIDTH-1];
    }
    interpolation_image[NEW_HEIGHT][NEW_WIDTH] = image[ORIGINAL_HEIGHT - 1][ORIGINAL_WIDTH - 1];

    for (int i = 0; i < NEW_HEIGHT; i+=4)
    {
        for (int j = 0; j < NEW_WIDTH; j+=4)
        {
            /*4개의 픽셀들로 이루어진 변 채우기*/
            interpolation_image[i][j + 2] = (unsigned char)clip((interpolation_image[i][j] + interpolation_image[i][j + 4]+1) >> 1);
            interpolation_image[i][j + 1] = (unsigned char)clip((interpolation_image[i][j] + interpolation_image[i][j + 2]+1) >> 1);
            interpolation_image[i][j + 3] = (unsigned char)clip((interpolation_image[i][j+2] + interpolation_image[i][j + 4]+1) >> 1);
            interpolation_image[i + 2][j] = (unsigned char)clip((interpolation_image[i][j] + interpolation_image[i+4][j] + 1) >> 1);
            interpolation_image[i + 1][j] = (unsigned char)clip((interpolation_image[i][j] + interpolation_image[i + 2][j] + 1) >> 1);
            interpolation_image[i + 3][j] = (unsigned char)clip((interpolation_image[i + 2][j] + interpolation_image[i + 4][j] + 1) >> 1);
            interpolation_image[i + 4][j + 2] = (unsigned char)clip((interpolation_image[i + 4][j] + interpolation_image[i + 4][j + 4] + 1) >> 1);
            interpolation_image[i + 4][j + 1] = (unsigned char)clip((interpolation_image[i + 4][j] + interpolation_image[i + 4][j + 2] + 1) >> 1);
            interpolation_image[i + 4][j + 3] = (unsigned char)clip((interpolation_image[i + 4][j + 2] + interpolation_image[i + 4][j + 4] + 1) >> 1);
            interpolation_image[i + 2][j + 4] = (unsigned char)clip((interpolation_image[i][j + 4] + interpolation_image[i + 4][j + 4] + 1) >> 1);
            interpolation_image[i + 1][j + 4] = (unsigned char)clip((interpolation_image[i][j + 4] + interpolation_image[i + 2][j + 4] + 1) >> 1);
            interpolation_image[i + 3][j + 4] = (unsigned char)clip((interpolation_image[i + 2][j + 4] + interpolation_image[i + 4][j + 4] + 1) >> 1);
            /*내부 채우기*/
            for (int a = 0; a < 3; a++)
            {
                interpolation_image[i + a + 1][j + 2] = (unsigned char)clip((interpolation_image[i + a + 1][j] + interpolation_image[i + a + 1][j + 4] + 1) >> 1);
                interpolation_image[i + a + 1][j + 1] = (unsigned char)clip((interpolation_image[i + a + 1][j] + interpolation_image[i + a + 1][j + 2] + 1) >> 1);
                interpolation_image[i + a + 1][j + 3] = (unsigned char)clip((interpolation_image[i + a + 1][j + 2] + interpolation_image[i + a + 1][j + 4] + 1) >> 1);
            }

        }
    }
    FILE* output_file = fopen(outputFiles[imageindex], "wb");
    for (int y = 0; y < NEW_HEIGHT; y++)
    {
        for (int x = 0; x < NEW_WIDTH; x++)
        {
            fwrite(&interpolation_image[y][x], 1, 1, output_file);
            PSNR_test[y][x] = interpolation_image[y][x];
        }
    }
    fclose(output_file);
}
void Bicubic(int imageindex) 
{
    const char* outputFiles[] = { "./HW02-dataset/dataset/result/Barbara_512x512_yuv400_8bit_bicubic.raw", "./HW02-dataset/dataset/result/Couple_512x512_yuv400_8bit_bicubic.raw", "./HW02-dataset/dataset/result/Lena_512x512_yuv400_8bit_bicubic.raw" };
    int result = 0;
    double x[4] = { -6,-2,2,6 };
    double A[4][5] = { 0 };

    unsigned char interpolation_image[NEW_HEIGHT + 12][NEW_WIDTH + 12]; //새로 변환할 이미지 배열(+padding)
    memset(interpolation_image, 0, sizeof(interpolation_image));


    for (int i = 0; i < ORIGINAL_HEIGHT + 3; i++)
    {
        for (int j = 0; j < ORIGINAL_WIDTH + 3; j++)
        {
            interpolation_image[i * 4][j * 4] = bicubic_paddedimage[i][j];
        }
    }
    for (int k = 0; k < 512; k += 4)
    {
        for (int j = 0; j < 512; j += 4)
        {
            /*가로*/
            for (int i = 0; i < 16; i += 4)
            {
                /*계수 구하기 전 값 채우기*/ 
                double y[4] = { interpolation_image[i + k][j + 0],interpolation_image[i + k][j + 4],interpolation_image[i + k][j + 8],interpolation_image[i + k][j + 12] };
                for (int i = 0; i < 4; i++) 
                {
                    for (int j = 0; j < 4; j++) 
                    {
                        A[i][j] = pow(x[i], 3 - j);
                    }
                    A[i][4] = y[i];
                }
                gauss_elimination(A, 4); //가우스 소거법 적용 A[0][4] = 3차항 계수,A[1][4] = 2차항 계수,A[2][4] = 1차항 계수,A[3][4] = 상수항
                result = (int)A[3][4];
                interpolation_image[i + k][j + 6] = (unsigned char)clip(result);
                result = (int)((-1 * A[0][4]) + (1 * A[1][4]) + (-1 * A[2][4]) + A[3][4]);
                interpolation_image[i + k][j + 5] = (unsigned char)clip(result);
                result = (int)((A[0][4]) + (A[1][4]) + (A[2][4]) + A[3][4]);
                interpolation_image[i + k][j + 7] = (unsigned char)clip(result);
            }
            /*세로*/
            for (int i = 0; i < 16; i += 4)
            {
                double y[4] = { interpolation_image[k + 0][i + j],interpolation_image[k + 4][i + j],interpolation_image[k + 8][i + j],interpolation_image[k + 12][i + j] };
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        A[i][j] = pow(x[i], 3 - j);
                    }
                    A[i][4] = y[i];
                }
                gauss_elimination(A, 4);
                result = (int)(A[3][4]);
                interpolation_image[6 + k][i + j] = (unsigned char)clip(result);
                result = (int)((-1 * A[0][4]) + (1 * A[1][4]) + (-1 * A[2][4]) + A[3][4]);
                interpolation_image[5 + k][i + j] = (unsigned char)clip(result);
                result = (int)((A[0][4]) + (A[1][4]) + (A[2][4]) + A[3][4]);
                interpolation_image[7 + k][i + j] = (unsigned char)clip(result);
            }
            /*내부*/
            for (int i = 1; i < 4; i++)
            {
                double y[4] = { interpolation_image[i + k + 4][j + 0],interpolation_image[i + k + 4][j + 4],interpolation_image[i + k + 4][j + 8],interpolation_image[i + k + 4][j + 12] };
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        A[i][j] = pow(x[i], 3 - j);
                    }
                    A[i][4] = y[i];
                }
                gauss_elimination(A, 4);
                result = (int)(A[3][4]);
                interpolation_image[i + k + 4][j + 6] = (unsigned char)clip(result);
                result = (int)((-1 * A[0][4]) + (1 * A[1][4]) + (-1 * A[2][4]) + A[3][4]);
                interpolation_image[i + k + 4][j + 5] = (unsigned char)clip(result);
                result = (int)((A[0][4]) + (A[1][4]) + (A[2][4]) + A[3][4]);
                interpolation_image[i + k + 4][j + 7] = (unsigned char)clip(result);
            }
        }
    }

    FILE* output_file = fopen(outputFiles[imageindex], "wb");
    for (int y = 0; y < 512; y++)
    {
        for (int x = 0; x < 512; x++)
        {
            fwrite(&interpolation_image[y + 4][x + 4], 1, 1, output_file);
            PSNR_test[y][x] = interpolation_image[y + 4][x + 4];
        }
    }
    fclose(output_file);
}
void Six_tab(int imageindex)
{
    const char* outputFiles[] = { "./HW02-dataset/dataset/result/Barbara_512x512_yuv400_8bit_sixtab.raw", "./HW02-dataset/dataset/result/Couple_512x512_yuv400_8bit_sixtab.raw", "./HW02-dataset/dataset/result/Lena_512x512_yuv400_8bit_sixtab.raw" };
    int result_width[6] = { 0 };
    int result = 0;

    unsigned char interpolation_image[NEW_HEIGHT + 20][NEW_WIDTH + 20]; //새로 변환할 이미지 배열(+padding)
    memset(interpolation_image, 0, sizeof(interpolation_image));


    for (int i = 0; i < ORIGINAL_HEIGHT + 5; i++)
    {
        for (int j = 0; j < ORIGINAL_WIDTH + 5; j++)
        {
            interpolation_image[i * 4][j * 4] = sixtab_paddedimage[i][j];
        }
    }

    for (int k = 0; k < 512; k+=4)
    {
        for (int j = 0; j < 512; j+=4)
        {
            /*가로*/
            for (int i = 0; i < 24; i += 4)
            {
                result = (interpolation_image[i+k][j+0] - (5 * interpolation_image[i+k][j+4]) + (20 * interpolation_image[i+k][j+8]) + (20 * interpolation_image[i+k][j+12]) - (5 * interpolation_image[i+k][j+16]) + (interpolation_image[i+k][j+20]));
                interpolation_image[i+k][j+10] = (unsigned char)clip((result + 16) >> 5);
            }
            /*세로*/
            for (int i = 0; i < 24; i += 4)
            {
                result = (interpolation_image[k+0][i+j] - (5 * interpolation_image[k+4][i+j]) + (20 * interpolation_image[k+8][i+j]) + (20 * interpolation_image[k+12][i+j]) - (5 * interpolation_image[k+16][i+j]) + (interpolation_image[k+20][i+j]));
                result_width[i / 4] = result;
                interpolation_image[10+k][i+j] = (unsigned char)clip((result + 16) >> 5);
            }
            /*중앙값*/
            result = (result_width[0] - (5 * result_width[1]) + (20 * result_width[2]) + (20 * result_width[3]) - (5 * result_width[4]) + (result_width[5]));
            interpolation_image[k+10][j+10] = (unsigned char)clip((result + 512) >> 10);
            /*내부*/
            for (int a = 0; a < 4; a += 2)
            {
                for (int b = 0; b < 4; b += 2)
                {
                    interpolation_image[k + a + 8][j + b + 9] = (unsigned char)clip((interpolation_image[k + a + 8][j + b + 8] + interpolation_image[k + a + 8][j + b + 10]+1)>>1);
                    interpolation_image[k + a + 9][j + b + 8] = (unsigned char)clip((interpolation_image[k + a + 8][j + b + 8] + interpolation_image[k + a + 10][j + b + 8]+1)>>1);
                    interpolation_image[k + a + 9][j + b + 9] = (unsigned char)clip((interpolation_image[k + a + 8][j + b + 8] + interpolation_image[k + a + 10][j + b + 10]+1)>>1);
                }
            }
        }
    }

    FILE* output_file = fopen(outputFiles[imageindex], "wb");
    for (int y = 0; y < 512; y++) 
    {
        for (int x = 0; x < 512; x++) 
        {
            fwrite(&interpolation_image[y+8][x+8], 1, 1, output_file);
            PSNR_test[y][x] = interpolation_image[y + 8][x + 8];
        }
    }
    fclose(output_file);
}