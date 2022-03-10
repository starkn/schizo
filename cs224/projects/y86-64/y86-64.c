#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

const int MAX_MEM_SIZE  = (1 << 13);

int getOP(int ifun, int valB, int valA, bool *of) {
  if(ifun == ADD) {
    int valE = valB + valA;
    *of = ((valB > 0 && valA > 0 && valE < 0) || (valB < 0 && valA < 0 && valE > 0));
    return valE;
  }

  if (ifun == SUB) {
    valA *= -1;
    int valE = valB + valA;
    *of = ((valB > 0 && valA > 0 && valE < 0) || (valB < 0 && valA < 0 && valE > 0));
    return valE;
  }

  if (ifun == AND) {
    return valB & valA;
  }

  if (ifun == XOR) {
    return valB ^ valA;
  }

  //this shouldn't happen
  return 0;
}

void setSigns(int valE, bool of) {
  bool sf = 0;
  bool zf = 0;

  if (valE < 0)
    sf = 1;
  if (valE == 0)
    zf = 1;
  
  setFlags(sf, zf, of);
}

void fetchStage(int *icode, int *ifun, int *rA, int *rB, wordType *valC, wordType *valP) {
  *icode = getByteFromMemory(getPC()) >> 4;
  *ifun = getByteFromMemory(getPC()) & 0xf;

  if (*icode == NOP || *icode == HALT || *icode == RET) {
    *valP = getPC() + 1;
    return;
  }

  if (*icode == JXX || *icode == CALL) {
    *valP = getPC() + 9;
    *valC = getWordFromMemory(getPC()+1);
    return;
  }

  *rA = getByteFromMemory(getPC()+1) >> 4;
  *rB = getByteFromMemory(getPC()+1) & 0xf;

  if (*icode == POPQ || *icode == PUSHQ || *icode == OPQ || *icode == RRMOVQ) {
    *valP = getPC() + 2;
    return;
  }

  if(*icode == MRMOVQ || *icode == IRMOVQ || *icode == RMMOVQ) {
    *valC = getWordFromMemory(getPC() + 2);
    *valP = getPC() + 10;
    return;
  }

  //This shouldn't happen
  *icode = HALT;
  *valP = getPC() + 1;
  return;
}

void decodeStage(int icode, int rA, int rB, wordType *valA, wordType *valB) {
  if(icode == RMMOVQ || icode == PUSHQ || icode == OPQ || icode == RRMOVQ) {
    *valA = getRegister(rA);
  }
  if(icode == RMMOVQ || icode == MRMOVQ || icode == OPQ) {
    *valB = getRegister(rB);
  }

  if(icode == RET || icode == POPQ) {
    *valA = getRegister(RSP);
  }

  if(icode == PUSHQ || icode == POPQ || icode == CALL || icode == RET) {
    *valB = getRegister(RSP);
  }
 
}

void executeStage(int icode, int ifun, wordType valA, wordType valB, wordType valC, wordType *valE, bool *Cnd) {
  if(icode == RMMOVQ || MRMOVQ) {
    *valE = valB + valC;
  }

  if(icode == PUSHQ || icode == CALL) {
    *valE = valB - 8;
  }

  if (icode == POPQ || icode == RET) {
    *valE = valB + 8;
  }

  if (icode == JXX) {
    *Cnd = Cond(ifun);
  }

  if (icode == OPQ) {
    bool of = 0;
    *valE = getOP(ifun, valB, valA, &of);
    setSigns(*valE, of);
  }

  if(icode == RRMOVQ) {
    *valE = 0 + valA;
  }

  if (icode == IRMOVQ)
  {
    *valE = 0 + valC;
  }
}

void memoryStage(int icode, wordType valA, wordType valP, wordType valE, wordType *valM) {
  if (icode == RMMOVQ || icode == PUSHQ) {
    setWordInMemory(valE, valA);
  }

  if (icode == MRMOVQ) {
    *valM = getWordFromMemory(valE);
  }

  if (icode == POPQ || icode == RET) {
    *valM = getWordFromMemory(valA);
  }

  if (icode == CALL) {
    setWordInMemory(valE, valP);
  }
}

void writebackStage(int icode, int rA, int rB, wordType valE, wordType valM) {
  if (icode == MRMOVQ || icode == POPQ) {
    setRegister(rA, valM);
  }

  if (icode == PUSHQ || icode == POPQ || icode == CALL || icode == RET) {
    setRegister(RSP, valE);
  }

  if (icode == OPQ || icode == IRMOVQ || icode == RRMOVQ) {
    setRegister(rB, valE);
  }
}

void pcUpdateStage(int icode, wordType valC, wordType valP, bool Cnd, wordType valM) {
  setPC(valP);
  if (icode == JXX) {
    wordType value = Cnd ? valC : valP;
    setPC(value);
  }

  if (icode == CALL) {
    setPC(valC);
  }

  if (icode == RET) {
    setPC(valM);
  }

  if (icode == HALT) {
    setStatus(STAT_HLT);
  }
    
}

void stepMachine(int stepMode) {
  /* FETCH STAGE */
  int icode = 0, ifun = 0;
  int rA = 0, rB = 0;
  wordType valC = 0;
  wordType valP = 0;
 
  /* DECODE STAGE */
  wordType valA = 0;
  wordType valB = 0;

  /* EXECUTE STAGE */
  wordType valE = 0;
  bool Cnd = 0;

  /* MEMORY STAGE */
  wordType valM = 0;

  fetchStage(&icode, &ifun, &rA, &rB, &valC, &valP);
  applyStageStepMode(stepMode, "Fetch", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  decodeStage(icode, rA, rB, &valA, &valB);
  applyStageStepMode(stepMode, "Decode", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  executeStage(icode, ifun, valA, valB, valC, &valE, &Cnd);
  applyStageStepMode(stepMode, "Execute", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  memoryStage(icode, valA, valP, valE, &valM);
  applyStageStepMode(stepMode, "Memory", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  writebackStage(icode, rA, rB, valE, valM);
  applyStageStepMode(stepMode, "Writeback", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  pcUpdateStage(icode, valC, valP, Cnd, valM);
  applyStageStepMode(stepMode, "PC update", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  incrementCycleCounter();
}

/** 
 * main
 * */
int main(int argc, char **argv) {
  int stepMode = 0;
  FILE *input = parseCommandLine(argc, argv, &stepMode);

  initializeMemory(MAX_MEM_SIZE);
  initializeRegisters();
  loadMemory(input);

  applyStepMode(stepMode);
  while (getStatus() != STAT_HLT) {
    stepMachine(stepMode);
    applyStepMode(stepMode);
#ifdef DEBUG
    printMachineState();
    printf("\n");
#endif
  }
  printMachineState();
  return 0;
}