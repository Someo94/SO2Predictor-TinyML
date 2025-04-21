/**
 * TinyML SO2 Prediction on ESP32
 * ----------------------------------------
 * This script loads a TensorFlow Lite model to predict SO2 removal efficiency
 * based on 4 input features. 
 * It uses EloquentTinyML and TFLite Micro libraries on an ESP32 MCU.
 * 
 * Model Architecture, change as needed:
 * - Input: 4 features
 * - Output: 1 regression value
 * - Activation: Leaky ReLU. At present, the EloquentTinyML does NOT support LEAKY_RELU automatically. It is manually added
 *
 * User Instructions:
 * - Open Serial Monitor (115200 baud)
 * - Input 4 float values separated by commas (e.g., 1.0,2.0,3.0,4.0)
 * - The model will predict the SO2 removal efficiency.
 */

#include "so2_model.h"     // TensorFlow Lite model in C array format
#include <tflm_esp32.h>    // EloquentTinyML runtime for ESP32
#include <eloquent_tinyml.h>  // TinyML simplified wrapper

// Define model parameters
#define NUMBER_OF_INPUTS 4
#define NUMBER_OF_OUTPUTS 1
#define ARENA_SIZE 20000
#define NO_OF_OPS 2  // Required ops: FullyConnected + LeakyRelu

// Instantiate TinyML model
Eloquent::TF::Sequential<NO_OF_OPS, ARENA_SIZE> tf;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("__TENSORFLOW LITE MODEL__");

    // Define input/output sizes
    tf.setNumInputs(NUMBER_OF_INPUTS);
    tf.setNumOutputs(NUMBER_OF_OUTPUTS);


    // Manually register required TensorFlow operations
    tf.resolver.AddFullyConnected();
    tf.resolver.AddLeakyRelu();

    // Load model
    while (!tf.begin(so2_model).isOk()) {
        Serial.println(tf.exception.toString());
    }

    Serial.println("Send input data: value1,value2,value3,value4");
}

void loop() {
    // Check for incoming serial data
    if (Serial.available() > 0) {
        // Read input line
        String data = Serial.readStringUntil('\n');
        
        // Parse comma-separated floats
        int commaIndex1 = data.indexOf(',');
        int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
        int commaIndex3 = data.indexOf(',', commaIndex2 + 1);

        // Check if input value format is correct
        if (commaIndex1 == -1 || commaIndex2 == -1 || commaIndex3 == -1) {
          Serial.println("Error: Invalid input format! Please send 4 comma-separated numbers.");
          return;  
        }
        
        String input1String = data.substring(0, commaIndex1);
        String input2String = data.substring(commaIndex1 + 1, commaIndex2);
        String input3String = data.substring(commaIndex2 + 1, commaIndex3);
        String input4String = data.substring(commaIndex3 + 1);

        // Convert string inputs to float
        float input1 = input1String.toFloat();
        float input2 = input2String.toFloat();
        float input3 = input3String.toFloat();
        float input4 = input4String.toFloat();
        float input_data[4] = {input1, input2, input3, input4};

        // Run inference and time it
        unsigned long startTime = micros();

        if (!tf.predict(input_data).isOk()) {
            Serial.println(tf.exception.toString());
            return;
        }

        unsigned long endTime = micros();

        // Print prediction results
        Serial.print("Predicted Efficiency: ");
        Serial.println(tf.output(0), 6);

        // Uncomment if there are multiple outputs
        //Serial.print("Predicted Efficiency: ");
       // for (int i = 0; i < NUMBER_OF_OUTPUTS; ++i) {
       //     Serial.print("Output ");
       //     Serial.print(i);
       //     Serial.print(": ");
       //     Serial.println(tf.output(i));
       // }

        Serial.print("Inference Time: ");
        Serial.print(endTime - startTime);
        Serial.println(" microseconds");
    }

    delay(1000);  
}
