#include <stdio.h>
#include <memory.h>
#include "FirePiCam.h"
#include "version.h"

/**
 * main
 */
int main(int argc, const char **argv)
{
  char filename[100];

  fprintf(stderr, "%s version %d.%d\n", basename(argv[0]), firepicam_VERSION_MAJOR, firepicam_VERSION_MINOR);
  int status = firepicam_create(argc, argv);
  int frame;

  for (frame = 0; status == 0 && frame<=20; frame++) {
    JPG_Buffer buffer;
    buffer.pData = NULL;
    buffer.length = 0;
    
    status = firepicam_acquireImage(&buffer);

    int fileIndex = frame; // % 10;
    if (buffer.length > 0) {
      firepicam_print_elapsed();
      fprintf(stderr, "%x %dB => acquired\n", buffer.pData, buffer.length);
      sprintf(filename, "camcv%0d.jpg", fileIndex);
      FILE * fJPG = fopen(filename, "w");
      fwrite(buffer.pData, 1, buffer.length, fJPG);
      fflush(fJPG);
      fclose(fJPG);
      firepicam_print_elapsed();
      fprintf(stderr, "%x %dB => %s\n", buffer.pData, buffer.length, filename);
    } else {
      firepicam_print_elapsed();
      fprintf(stderr, "%x %dB IGNORED\n", buffer.pData, buffer.length);
    }
  } // end for (frame)

  firepicam_destroy(status);
}
