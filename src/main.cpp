#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "ciphertext.h"
#include "analysissuits.h"

#include "util.h"

int
main()
{
  CipherText *ciphertext;
  ciphertext = CipherTextFactory::CipherTextFromStdin();
  VigenereStreamAnalysis *stats = ciphertext->stats();

  LAlphabet frequencies;
  frequencies = ciphertext->frequencies();
  printf("Letter frequencies:\n");
  for (int x=0; x < ALPHABET_LEN; x++)
      printf(" %c) %ld\n", (x+'A'), frequencies[x]);

  float friedman = VigenereStatAnalysis::friedman_test(frequencies);
  printf("Friedman test: %f\n", friedman);
  PossibleLengths lens = VigenereStatAnalysis::kasisky_test(stats->ngramcounter_);
  for (size_t x = 0; x < lens.size(); x++) {
    printf(" > %zu\n", lens[x]);
  }

  return EXIT_SUCCESS;
}
