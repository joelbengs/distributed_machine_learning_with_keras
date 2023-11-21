#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

#include "net.h" // network weights
#include "testdata.h" // test data

#define N_INPUTS 1024
#define N_OUTPUTS 2
// in your projects you may need to tweak this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 19*1024

Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;

void setup() {
    Serial.begin(9600);
    tf.begin(seizure_model);
}


void loop() {


    // check if model loaded fine
    //if (!tf.isOk()) {
    //    Serial.print("ERROR: ");
    //    Serial.println(tf.getErrorMessage());
    //    //while (true) delay(1000);
    //}
    
    float x_test[1024] = {0};
    float y_pred[2] = {0};
    int j = 0;


    Serial.print("Id \t Category \t Time \n");

    for (j=0; j < 40; j=j+1)
    {

      for(int i = 0; i < N_INPUTS; i++)
        {x_test[i] = x_test_cut[j][i];  }
    

      uint32_t start = micros();
  
      tf.predict(x_test, y_pred);
  
      uint32_t timeit = micros() - start;
  

      //Serial.print("Predicted proba are: ");  
      //for (int i = 0; i < 2; i++) {
      //    Serial.print(y_pred[i]);
      //    Serial.print(i == 1 ? '\n' : ',');
      //}
  

      Serial.print(j+1);
      Serial.print("\t");
      Serial.print(tf.probaToClass(y_pred));
      Serial.print("\t");
      Serial.print(timeit/1240000.0);
      Serial.print("\n");

  
      delay(1000);
    }
}
