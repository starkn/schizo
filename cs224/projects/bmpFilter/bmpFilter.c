#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

#define BAD_NUMBER_ARGS 1
#define FSEEK_ERROR 2
#define FREAD_ERROR 3
#define MALLOC_ERROR 4
#define FWRITE_ERROR 5

/**
 * Parses the command line.
 *
 * argc:      the number of items on the command line (and length of the
 *            argv array) including the executable
 * argv:      the array of arguments as strings (char* array)
 * grayscale: the integer value is set to TRUE if grayscale output indicated
 *            outherwise FALSE for threshold output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *isGrayscale) {
  if (argc > 2) {
    printf("Usage: %s [-g]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }
  
  if (argc == 2 && strcmp(argv[1], "-g") == 0) {
    *isGrayscale = TRUE;
  } else {
    *isGrayscale = FALSE;
  }

  return stdin;
}

unsigned getFileSizeInBytes(FILE* stream) {
  unsigned fileSizeInBytes = 0;
  
  rewind(stream);
  if (fseek(stream, 0L, SEEK_END) != 0) {
    exit(FSEEK_ERROR);
  }
  fileSizeInBytes = ftell(stream);

  return fileSizeInBytes;
}

void getBmpFileAsBytes(unsigned char* ptr, unsigned fileSizeInBytes, FILE* stream) {
  rewind(stream);
  if (fread(ptr, fileSizeInBytes, 1, stream) != 1) {
#ifdef DEBUG
    printf("feof() = %x\n", feof(stream));
    printf("ferror() = %x\n", ferror(stream));
#endif
    exit(FREAD_ERROR);
  }
}

unsigned char getAverageIntensity(unsigned char blue, unsigned char green, unsigned char red) {
  return (blue + green + red)/3;
}

void applyGrayscaleToPixel(unsigned char* pixel) {
  unsigned char red = *pixel;
  unsigned char green = *(pixel + 1);
  unsigned char blue = *(pixel + 2);
  unsigned char avg = getAverageIntensity(blue, green, red);
  *pixel = avg;
  *(pixel + 1) = avg;
  *(pixel + 2) = avg;
}

void applyThresholdToPixel(unsigned char* pixel) {
  unsigned char red = *pixel;
  unsigned char green = *(pixel + 1);
  unsigned char blue = *(pixel + 2);
  unsigned char avg = getAverageIntensity(blue, green, red);

  if(avg >= 128) {
    *pixel = 255;
    *(pixel+1) = 255;
    *(pixel+2) = 255;
  }
  else {
    *pixel = 0;
    *(pixel + 1) = 0;
    *(pixel + 2) = 0;
  }
  
}

void applyFilterToPixel(unsigned char* pixel, int isGrayscale) {
  if(isGrayscale) {
    applyGrayscaleToPixel(pixel);
  }
  else {
    applyThresholdToPixel(pixel);
  }
  
}

void applyFilterToRow(unsigned char* row, int width, int isGrayscale) {
  unsigned char* pixel = row;
  for(int i=0; i<width; i++) {
    applyFilterToPixel(pixel, isGrayscale);
    pixel = pixel + 3;
  }
}

void applyFilterToPixelArray(unsigned char* pixelArray, int width, int height, int isGrayscale) {
  int padding = width%4;
  unsigned char* row = pixelArray;
  for(int i=0; i<height; i++) {
    #ifdef DEBUG
      printf("Address of row %d: %p\n", i, row);
    #endif
    applyFilterToRow(row, width, isGrayscale);
    row = row + (width*3) + padding;
  }
#ifdef DEBUG
  printf("padding = %d\n", padding);
#endif  
  
}

void parseHeaderAndApplyFilter(unsigned char* bmpFileAsBytes, int isGrayscale) {
  int offsetFirstBytePixelArray = *(int *)(bmpFileAsBytes+10);
  int width = *(int *)(bmpFileAsBytes+18);
  int height = *(int *)(bmpFileAsBytes + 22);
  unsigned char* pixelArray = (bmpFileAsBytes + offsetFirstBytePixelArray);

#ifdef DEBUG
  printf("offsetFirstBytePixelArray = %u\n", offsetFirstBytePixelArray);
  printf("width = %u\n", width);
  printf("height = %u\n", height);
  printf("pixelArray = %p\n", pixelArray);
  for(int i=0; i<offsetFirstBytePixelArray+5; i++){
    printf("Address %d: %p\n", i, (bmpFileAsBytes+i));
  }
#endif

  applyFilterToPixelArray(pixelArray, width, height, isGrayscale);
}

int main(int argc, char **argv) {
  int grayscale = FALSE;
  unsigned fileSizeInBytes = 0;
  unsigned char* bmpFileAsBytes = NULL;
  FILE *stream = NULL;
  
  stream = parseCommandLine(argc, argv, &grayscale);
  fileSizeInBytes = getFileSizeInBytes(stream);

#ifdef DEBUG
  printf("fileSizeInBytes = %u\n", fileSizeInBytes);
#endif

  bmpFileAsBytes = (unsigned char *)malloc(fileSizeInBytes);
  if (bmpFileAsBytes == NULL) {
    exit(MALLOC_ERROR);
  }
  getBmpFileAsBytes(bmpFileAsBytes, fileSizeInBytes, stream);

  parseHeaderAndApplyFilter(bmpFileAsBytes, grayscale);

#ifndef DEBUG
  if (fwrite(bmpFileAsBytes, fileSizeInBytes, 1, stdout) != 1) {
    exit(FWRITE_ERROR);
  }
#endif

  free(bmpFileAsBytes);
  return 0;
}
