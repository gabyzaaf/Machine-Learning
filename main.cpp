#include <iostream>

using namespace std;

// create the model
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

double somme(int * array,int size,double* model, int sizeModel,int biais){
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
void reajustModel(double* model,int sizeModel,int* inputArray,int biais,int sortieattendue){
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
    //return model;
}


void sommeModel(double * model, int sizeModel, double *input , int sizeInput, int sizeElementInput, double* output){
    int biais = 1;
    int res = 0;
    int division = sizeInput / sizeElementInput;
    int j = 0;
    for(int i = 0;i<division;i++){
         cout << "in loop N° "<<i<<endl;
        cout << "" << endl;
        int* inputsArray = new int[sizeElementInput];
        for(int j = 0 ; j< sizeElementInput; j++){
            inputsArray[j] = input[i*sizeElementInput+j];
        }
        double resultat = somme(inputsArray,sizeInput,model,sizeModel,biais);
        if(resultat!=(int)output[i]){
            reajustModel(model,sizeModel,inputsArray,biais,output[i]);
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
    /*for(int i = 0;i<8;i++){
        input[i] = (i+1)*i;
    }*/
    int* array = new int[2];
    double* output = new double[3];
    output[0]= -1;
    output[1]= 1;
    output[2]= 1;
    for (int i = 0; i < 1000; i++)
        sommeModel(model,2,input,6,2,output);

    cout<< "RESULLLLLLT " << model[0] << " " << model[1] << " " << model[2] << endl;


    delete[] model;
    delete[] input;
    delete[] array;


    return 0;
}
