#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name); // print name of chunk

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset); // disassemble each chunk for each chunk
    }
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1]; //byte constant index is the position of the code
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]); //print value of constant at that index
    printf("'\n");
    return offset + 2; //returns beginning of next instruction, as this instruction is 2 bytes
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}