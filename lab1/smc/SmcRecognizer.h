#ifndef SMC_RECOGNIZER_H
#define SMC_RECOGNIZER_H

#include "SmcRecognizer_sm.h"

typedef struct SmcRecognizer {
    int is_correct;
    struct SmcRecognizerContext _fsm;
} SmcRecognizer;

void SmcRecognizer_Init(SmcRecognizer* smc_recognizer); 
void check_str(SmcRecognizer* smc_recognizer, char* str);  
void SmcRecognizer_Correct(SmcRecognizer* smc_recognizer);
void SmcRecognizer_Incorrect(SmcRecognizer* smc_recognizer);

#endif
