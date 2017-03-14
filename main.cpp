#include <iostream>
#include "Eigen/Eigen"
using namespace std;
using namespace Eigen;


/*
 *  For classification :
 *  1) create_model.
 *  2) sommeModel.
 *
 * For regression :
 *  1) Create_model.
 *  2) regression.
 *  3) sommeRegression.
 *
 *
 * */






// creer le model :
double* create_model(int sizeModel){
    double * array = new double[sizeModel+1];
    // generer aléatoire.
    srand (time(NULL));
    for(int i = 0;i<sizeModel+1;i++){
        if(i==0){
            array[0] = 1;
        }else{
            double val = rand() % -2 + 1;
            if(val == 0){
                array[i] = 0;

            }else if(val > 0){
                array[i] = 1;
            }else{
                array[i] = -1;
            }
        }

    }

    return array;
}

void deleteModel(double* model){
    delete[] model;
}

double sommeRegression(double * array,int size,double* model, int sizeModel,int biais){
    double res = 0;
    for(int i = 0;i<sizeModel+1;i++){
        if(i==0){
            res += biais*model[0];
        }else{
            res+=model[i]*array[i-1];
        }
    }
    return res;
}

double somme(double * array,int size,double* model, int sizeModel,int biais){
    double res = 0;
    for(int i = 0;i<sizeModel+1;i++){
        if(i==0){
            res += biais*model[0];
        }else{
            res+=model[i]*array[i-1];
        }
    }
    if(res >= 0){
        return 1;
    }
    return -1;
}
void reajustModel(double* model,int sizeModel,double* inputArray,int biais,int sortieattendue){
    double alhpa = 0.1;
    cout << "In reajuste model function "<<endl;
    for(int i = 0;i<sizeModel+1;i++){
        if(i==0){
            model[i] = model[i] + alhpa*biais*sortieattendue;
            cout << model[i]<<endl;
        }else{
            model[i] = model[i]+alhpa*sortieattendue*inputArray[i-1];
            cout << model[i]<<endl;
        }

    }

}


void regression(double* w, double *input,int sizeInput, int sizeElementInput, double* output){
  int biais = 1;
  MatrixXd x(sizeInput/sizeElementInput,sizeElementInput+1);
  MatrixXd y(sizeInput/sizeElementInput, 1);
  int j = 0;
    for(int i = 0;i<(sizeInput / sizeElementInput);i++){

        for(int j = 0;j<sizeElementInput+1;j++){

            if(j==0){
                x(i,j) = biais;
            } else{
                x(i,j) = input[i*sizeElementInput+j-1];
            }
        }
        y(i, 0)=output[i];
    }

    cout << x << endl;

    cout << y << endl;

    auto W = (((x.transpose()*x).inverse()*x.transpose())*y);

    for (int i = 0; i < sizeElementInput + 1; i++)
    {
        w[i] = W(i,0);
    }
}

void sommeModel(double * model, int sizeModel, double *input , int sizeInput, int sizeElementInput, double* output){
    int biais = 1;
    int res = 0;
    int division = sizeInput / sizeElementInput;
    int j = 0;
    for(int i = 0;i<division;i++){
         cout << "in loop N° "<<i<<endl;
        cout << "" << endl;
        double* inputsArray = new double[sizeElementInput];
        for(int j = 0 ; j< sizeElementInput; j++){
            inputsArray[j] = input[i*sizeElementInput+j];
        }
        double resultat = somme(inputsArray,sizeInput,model,sizeModel,biais);
        if(resultat!=(int)output[i]){
            reajustModel(model,sizeModel,inputsArray,biais,output[i]);
        }else{
            cout << "NO MODIFY" <<endl;
        }
        delete[] inputsArray;
    }
}




int main() {

    double * model = create_model(2);
    double *input = new double[6]
            {
                    -1,1,
                    0,0,
                    1,0
            };


    double* output = new double[3];
    output[0]= -1;
    output[1]= 1;
    output[2]= 1;
    for (int i = 0; i < 1000; i++)
        sommeModel(model,2,input,6,2,output);

    cout<< "RESULLLLLLT " << model[0] << " " << model[1] << " " << model[2] << endl;



    delete[] model;
    delete[] input;

    double *input2 = new double[6]
            {
                    12,3,
                    9,1,
                    1,-9
            };
    double* outputs = new double[3];
    outputs[0]= -1;
    outputs[1]= 8;
    outputs[2]= 3;


    double * model2 = create_model(2);
    regression(model2, input2,6,2,outputs);


    cout << "regression " << sommeRegression(input2+4, 2, model2, 2, 1) <<endl;

    delete[] model2;
    delete[] outputs;
    delete[] input2;
    return 0;
}