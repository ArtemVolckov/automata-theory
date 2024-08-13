#include <string.h>
#include <stdio.h>
#include "SmcRecognizer.h"


void SmcRecognizer_Init(SmcRecognizer* smc_recognizer) {
    smc_recognizer->is_correct = 0;
    SmcRecognizerContext_Init(&smc_recognizer->_fsm, smc_recognizer);        
}

void check_str(SmcRecognizer* smc_recognizer, char* str) {
    size_t str_len = strlen(str);

    for (int i = 0; i < str_len; ++i) {
        SmcRecognizerContext_letter(&smc_recognizer->_fsm, str[i]);
    }
    SmcRecognizerContext_EOS(&smc_recognizer->_fsm);
}

void SmcRecognizer_Correct(SmcRecognizer* smc_recognizer) {
    smc_recognizer->is_correct = 1;
}

void SmcRecognizer_Incorrect(SmcRecognizer* smc_recognizer) {
    smc_recognizer->is_correct = 0;
}
