#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "ciphertext.h"
#include "analysissuits.h"
#include "cracker.h"

#include "util.h"

int
main()
{
  CipherText *ciphertext;
  ciphertext = CipherTextFactory::CipherTextFromStdin();
  VigenereStreamAnalysis *stats = ciphertext->stats();

  LAlphabet frequencies;
  frequencies = ciphertext->frequencies();
/*
  printf("Letter frequencies:\n");
  for (int x=0; x < ALPHABET_LEN; x++)
      printf(" %c) %ld\n", (x+'A'), frequencies[x]);
*/

//  stats->ngramcounter_.print_content();

  float friedman = VigenereStatAnalysis::friedman_test(frequencies);
//  printf("Friedman test: %f\n", friedman);
  PossibleLengths lens = VigenereStatAnalysis::kasisky_test(stats->ngramcounter_);
//  for (size_t x = 0; x < lens.size(); x++) {
//    printf(" > %zu\n", lens[x]);
//  }

  size_t selected_len = lens.back();
  std::string key = VigenereCracker::crackit(ciphertext, selected_len);
//  printf("KEY: %s\n", key.c_str());

  printf("%f;%zu;%zu;%s\n", friedman, selected_len, selected_len, key.c_str());

  delete ciphertext;

  return EXIT_SUCCESS;
}
