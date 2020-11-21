#include <stdio.h>
#include <math.h>
#include <algorithm>
#define WIDTH 28
#define HEIGHT 28
#define NUM 13002
#define NUM1 784 //WIDTH * HEADER
#define NUM2 16 //first, second layer
#define HEADER 54
#define testcase 10

using namespace std;

double weight0[HEIGHT][WIDTH];
double weight1[NUM2][NUM1];
double weight2[NUM2][NUM2];
double weight3[10][NUM2];
double bias1[NUM2];
double bias2[NUM2];
double bias3[10];
double layer0[NUM1];
double layer1[NUM2];
double layer2[NUM2];
double layer3[10];
double yarr[10];
//feedback -> f
double layer1f[NUM2];
double layer2f[10];
double weight1f[NUM2][NUM1];
double weight2f[NUM2][NUM2];
double weight3f[10][NUM2];
double bias1f[NUM2];
double bias2f[NUM2];
double bias3f[10];
//total
double weight1ftot[NUM2][NUM1];
double weight2ftot[NUM2][NUM2];
double weight3ftot[10][NUM2];
double bias1ftot[NUM2];
double bias2ftot[NUM2];
double bias3ftot[10];
double e;
int ans;
double cost[10];
double accuracy;
double totaccuracy;

//팩토리얼 계산 함수
long long int fact(int a)
{
    if (a) return a * fact(a - 1);
    return 1;
}

//e 값 계산 함수
void euler()
{
    //20이 넘으면 overflow
    for (int i = 0; i <= 20; i++) {
        e += (1 / (double)fact(i));
    }
}

//실수를 0과 1 사이로 좁혀주는 함수 sigmoid
//sigmoid 대신 ReLU 사용 고려
double sig(double val)
{
    double ret = 1 + pow(e, -val);
    ret = 1 / ret;
    return ret;
}

//sigmoid의 도함수
double dirvsig(double val)
{
    double ret1 = 1 + pow(e, - val);
    ret1 = ret1 * ret1;
    double ret2 = pow(e, - val);
    double ret = ret2 / ret1;
    return ret;
}

void changeform(int no)
{
    if (no == 0) {
        FILE *fp10 = fopen("input0.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp10);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp10);
            double G = getc(fp10);
            double R = getc(fp10);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 1) {
        FILE *fp11 = fopen("input1.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp11);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp11);
            double G = getc(fp11);
            double R = getc(fp11);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 2) {
        FILE *fp12 = fopen("input2.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp12);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp12);
            double G = getc(fp12);
            double R = getc(fp12);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 3) {
        FILE *fp13 = fopen("input3.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp13);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp13);
            double G = getc(fp13);
            double R = getc(fp13);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 4) {
        FILE *fp14 = fopen("input4.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp14);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp14);
            double G = getc(fp14);
            double R = getc(fp14);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 5) {
        FILE *fp15 = fopen("input5.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp15);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp15);
            double G = getc(fp15);
            double R = getc(fp15);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 6) {
        FILE *fp16 = fopen("input6.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp16);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp16);
            double G = getc(fp16);
            double R = getc(fp16);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 7) {
        FILE *fp17 = fopen("input7.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp17);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp17);
            double G = getc(fp17);
            double R = getc(fp17);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 8) {
        FILE *fp18 = fopen("input8.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp18);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp18);
            double G = getc(fp18);
            double R = getc(fp18);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
    if (no == 9) {
        FILE *fp19 = fopen("input9.bmp", "rb");
        //헤더를 가져옴
    for (int i = 0; i < HEADER; i++) {
        getc(fp19);
    }
    //가중치로 변환 -> 어두울수록 가중치 높음
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double B = getc(fp19);
            double G = getc(fp19);
            double R = getc(fp19);
            weight0[i][j] = (B + G + R) / (3 * 255);
            weight0[i][j] = 1 - weight0[i][j];
        }
    }
    //위아래 뒤집기 -> 사실 필요는 없음
    for (int i = 0; i < HEIGHT / 2; i++) {
        for (int j = 0; j < WIDTH; j++) {
            swap(weight0[i][j], weight0[HEIGHT - i - 1][j]);
        }
    }
    }
}

int main()
{
    //e 값 계산
    euler();
    //파일 입력 받는 부분
    FILE *fp2 = fopen("testin.txt", "r");
    FILE *fp3 = fopen("testout.txt", "w");
    for (int i = 0; i < NUM2; i++) {
        for (int j = 0; j < NUM1; j++) {
            fscanf(fp2, "%lf", &weight1[i][j]);
        }
        fscanf(fp2, "%lf", &bias1[i]);
    }
    for (int i = 0; i < NUM2; i++) {
        for (int j = 0; j < NUM2; j++) {
            fscanf(fp2, "%lf", &weight2[i][j]);
        }
        fscanf(fp2, "%lf", &bias2[i]);
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < NUM2; j++) {
            fscanf(fp2, "%lf", &weight3[i][j]);
        }
        fscanf(fp2, "%lf", &bias3[i]);
    }
    for (int t = 0; t < testcase; t++) {
    scanf("%d", &ans);
    changeform(t);
    //weight0 -> layer0
    for (int i = 0; i < NUM1; i++) {
        layer0[i] = weight0[i / 16][i % 16];
    }
    //1단계 : layer0 -> layer1
    for (int i = 0; i < NUM2; i++) {
        double sum = 0;
        for (int j = 0; j < NUM1; j++) {
            sum += weight1[i][j] * layer0[j];
        }
        sum += bias1[i];
        layer1[i] = sig(sum);
    }
    //2단계 : layer1 -> layer2
    for (int i = 0; i < NUM2; i++) {
        double sum = 0;
        for (int j = 0; j < NUM2; j++) {
            sum += weight2[i][j] * layer1[j];
        }
        sum += bias2[i];
        layer2[i] = sig(sum);
    }
    //3단계 : layer2 -> layer3
    for (int i = 0; i < 10; i++) {
        double sum = 0;
        for (int j = 0; j < NUM2; j++) {
            sum += weight3[i][j] * layer2[j];
        }
        sum += bias3[i];
        layer3[i] = sig(sum);
    }
    //layer 1, 2, 3 생성 완료
    //y arr 생성
    for (int i = 0; i < 10; i++) {
        if (i == ans) yarr[i] = 1;
        else yarr[i] = 0;
    }
    //cost 계산
    accuracy = 0;
    for (int i = 0; i < 10; i++) {
        cost[i] = (yarr[i] - layer3[i]) * (yarr[i] - layer3[i]);
        accuracy += cost[i];
    }
    totaccuracy += accuracy;
    //layer3 편미분 -> weight3, bias3, layer2
    for (int i = 0; i < NUM2; i++) {
        layer2f[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        double tmpz = 0;
        for (int j = 0; j < NUM2; j++) {
            tmpz += weight3[i][j] * layer2[j];
        }
        tmpz += bias3[i];
        for (int j = 0; j < NUM2; j++) {
        weight3f[i][j] = -(2 * (layer3[i] - yarr[i]) * dirvsig(tmpz) * layer2[j]);
        weight3ftot[i][j] += weight3f[i][j];
        layer2f[j] += -(2 * (layer3[i] - yarr[i]) * dirvsig(tmpz) * weight3[i][j]);
        }
        bias3f[i] = -(2 * (layer3[i] - yarr[i]) * dirvsig(tmpz));
        bias3ftot[i] += bias3f[i];
    }
    //layer2 편미분 -> weight2, bias2, layer1
    for (int i = 0; i < NUM2; i++) {
        layer1f[i] = 0;
    }
    for (int i = 0; i < NUM2; i++) {
        double tmpz = 0;
        for (int j = 0; j < NUM2; j++) {
            tmpz += weight2[i][j] * layer1[j];
        }
        tmpz += bias2[i];
        for (int j = 0; j < NUM2; j++) {
        weight2f[i][j] = layer2f[i] * (dirvsig(tmpz) * layer1[j]);
        weight2ftot[i][j] += weight2f[i][j];
        layer1f[j] += layer2f[i] * (dirvsig(tmpz) * weight2[i][j]);
        }
        bias2f[i] = layer2f[i] * (dirvsig(tmpz));
        bias2ftot[i] += bias2f[i];
    }
    //layer1 편미분 -> weight1, bias1
    for (int i = 0; i < NUM2; i++) {
        double tmpz = 0;
        for (int j = 0; j < NUM1; j++) {
            tmpz += weight1[i][j] * layer0[j];
        }
        tmpz += bias1[i];
        for (int j = 0; j < NUM1; j++) {
        weight1f[i][j] = layer1f[i] * (dirvsig(tmpz) * layer0[j]);
        weight1ftot[i][j] += weight1f[i][j];
        }
        bias1f[i] = layer1f[i] * (dirvsig(tmpz));
        bias1ftot[i] += bias1f[i];
    }
    double maxi = 0;
    int maxnum;
    for (int i = 0; i < 10; i++) {
        if (layer3[i] > maxi) {
            maxi = layer3[i];
            maxnum = i;
        }
    }
    printf("layer1 : ");
    for (int i = 0; i < NUM2; i++) {
        printf("%.3lf ", layer1[i]);
    }
    printf("\n");
    printf("layer2 : ");
    for (int i = 0; i < NUM2; i++) {
        printf("%.3lf ", layer2[i]);
    }
    printf("\n");
    printf("layer3 : ");
    for (int i = 0; i < 10; i++) {
        printf("%.3lf ", layer3[i]);
    }
    printf("\n");
    printf("Answer : %d\n", maxnum);
    }
    //feedback 평균내고 weight과 bias에 실제로 적용
    //weight1, bias1
    for (int i = 0; i < NUM2; i++) {
        for (int j = 0; j < NUM1; j++) {
            weight1ftot[i][j] /= testcase;
            weight1[i][j] += weight1ftot[i][j];
        }
        bias1ftot[i] /= testcase;
        bias1[i] += bias1ftot[i];
    }
    //weight2, bias2
    for (int i = 0; i < NUM2; i++) {
        for (int j = 0; j < NUM2; j++) {
            weight2ftot[i][j] /= testcase;
            weight2[i][j] += weight2ftot[i][j];
        }
        bias2ftot[i] /= testcase;
        bias2[i] += bias2ftot[i];
    }
    //weight3, bias3
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < NUM2; j++) {
            weight3ftot[i][j] /= testcase;
            weight3[i][j] += weight3ftot[i][j];
        }
        bias3ftot[i] /= testcase;
        bias3[i] += bias3ftot[i];
    }
    //testout 파일에 변경된 값들 전부 출력
    //weight1 출력, bias1 출력
    for (int i = 0; i < NUM2; i++) {
        for (int j = 0; j < NUM1; j++) {
            fprintf(fp3, "%.3lf\n", weight1[i][j]);
        }
        fprintf(fp3, "%.3lf\n", bias1[i]);
    }
    //weight2 출력, bias2 출력
    for (int i = 0; i < NUM2; i++) {
        for (int j = 0; j < NUM2; j++) {
            fprintf(fp3, "%.3lf\n", weight2[i][j]);
        }
        fprintf(fp3, "%.3lf\n", bias2[i]);
    }
    //weight3 출력, bias3 출력
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < NUM2; j++) {
            fprintf(fp3, "%.3lf\n", weight3[i][j]);
        }
        fprintf(fp3, "%.3lf\n", bias3[i]);
    }
    //0에 가까울수록 좋음
    totaccuracy /= (double)testcase;
    printf("accuracy : %.3lf", totaccuracy);
    return 0;
}
