/**
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * This file is part of srsLTE.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "srslte/common/liblte_security.h"
#include "srslte/common/test_common.h"
#include "srslte/srslte.h"

/*
 * Prototypes
 */

int32 arrcmp(uint8_t const* const a, uint8_t const* const b, uint32 len)
{
  uint32 i = 0;

  for (i = 0; i < len; i++) {
    if (a[i] != b[i]) {
      return a[i] - b[i];
    }
  }
  return 0;
}

/*
 * Tests
 *
 * Document Reference: 33.401 V13.1.0 Annex C.1
 */

int test_set_1()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xd3, 0xc5, 0xd5, 0x92, 0x32, 0x7f, 0xb1, 0x1c, 0x40, 0x35, 0xc6, 0x68, 0x0a, 0xf8, 0xc6, 0xd1};
  uint32_t count     = 0x398a59b4;
  uint8_t  bearer    = 0x15;
  uint8_t  direction = 1;
  uint32_t len_bits = 253, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {0x98, 0x1b, 0xa6, 0x82, 0x4c, 0x1b, 0xfb, 0x1a, 0xb4, 0x85, 0x47, 0x20, 0x29, 0xb7, 0x1d, 0x80,
                   0x8c, 0xe3, 0x3e, 0x2c, 0xc3, 0xc0, 0xb5, 0xfc, 0x1f, 0x3d, 0xe8, 0xa6, 0xdc, 0x66, 0xb1, 0xf0};
  uint8_t  ct[]  = {0xe9, 0xfe, 0xd8, 0xa6, 0x3d, 0x15, 0x53, 0x04, 0xd7, 0x1d, 0xf2, 0x0b, 0xf3, 0xe8, 0x22, 0x14,
                  0xb2, 0x0e, 0xd7, 0xda, 0xd2, 0xf2, 0x33, 0xdc, 0x3c, 0x22, 0xd7, 0xbd, 0xee, 0xed, 0x8e, 0x78};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_2()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0x2b, 0xd6, 0x45, 0x9f, 0x82, 0xc4, 0x40, 0xe0, 0x95, 0x2c, 0x49, 0x10, 0x48, 0x05, 0xff, 0x48};
  uint32_t count     = 0xc675a64b;
  uint8_t  bearer    = 0x0c;
  uint8_t  direction = 1;
  uint32_t len_bits = 798, len_bytes = (len_bits + 7) / 8;
  uint8_t msg[] = {0x7e, 0xc6, 0x12, 0x72, 0x74, 0x3b, 0xf1, 0x61, 0x47, 0x26, 0x44, 0x6a, 0x6c, 0x38, 0xce, 0xd1, 0x66,
                   0xf6, 0xca, 0x76, 0xeb, 0x54, 0x30, 0x04, 0x42, 0x86, 0x34, 0x6c, 0xef, 0x13, 0x0f, 0x92, 0x92, 0x2b,
                   0x03, 0x45, 0x0d, 0x3a, 0x99, 0x75, 0xe5, 0xbd, 0x2e, 0xa0, 0xeb, 0x55, 0xad, 0x8e, 0x1b, 0x19, 0x9e,
                   0x3e, 0xc4, 0x31, 0x60, 0x20, 0xe9, 0xa1, 0xb2, 0x85, 0xe7, 0x62, 0x79, 0x53, 0x59, 0xb7, 0xbd, 0xfd,
                   0x39, 0xbe, 0xf4, 0xb2, 0x48, 0x45, 0x83, 0xd5, 0xaf, 0xe0, 0x82, 0xae, 0xe6, 0x38, 0xbf, 0x5f, 0xd5,
                   0xa6, 0x06, 0x19, 0x39, 0x01, 0xa0, 0x8f, 0x4a, 0xb4, 0x1a, 0xab, 0x9b, 0x13, 0x48, 0x80};
  uint8_t ct[]  = {0x59, 0x61, 0x60, 0x53, 0x53, 0xc6, 0x4b, 0xdc, 0xa1, 0x5b, 0x19, 0x5e, 0x28, 0x85, 0x53, 0xa9, 0x10,
                  0x63, 0x25, 0x06, 0xd6, 0x20, 0x0a, 0xa7, 0x90, 0xc4, 0xc8, 0x06, 0xc9, 0x99, 0x04, 0xcf, 0x24, 0x45,
                  0xcc, 0x50, 0xbb, 0x1c, 0xf1, 0x68, 0xa4, 0x96, 0x73, 0x73, 0x4e, 0x08, 0x1b, 0x57, 0xe3, 0x24, 0xce,
                  0x52, 0x59, 0xc0, 0xe7, 0x8d, 0x4c, 0xd9, 0x7b, 0x87, 0x09, 0x76, 0x50, 0x3c, 0x09, 0x43, 0xf2, 0xcb,
                  0x5a, 0xe8, 0xf0, 0x52, 0xc7, 0xb7, 0xd3, 0x92, 0x23, 0x95, 0x87, 0xb8, 0x95, 0x60, 0x86, 0xbc, 0xab,
                  0x18, 0x83, 0x60, 0x42, 0xe2, 0xe6, 0xce, 0x42, 0x43, 0x2a, 0x17, 0x10, 0x5c, 0x53, 0xd0};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_3()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0x0a, 0x8b, 0x6b, 0xd8, 0xd9, 0xb0, 0x8b, 0x08, 0xd6, 0x4e, 0x32, 0xd1, 0x81, 0x77, 0x77, 0xfb};
  uint32_t count     = 0x544d49cd;
  uint8_t  bearer    = 0x04;
  uint8_t  direction = 0;
  uint32_t len_bits = 310, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {0xfd, 0x40, 0xa4, 0x1d, 0x37, 0x0a, 0x1f, 0x65, 0x74, 0x50, 0x95, 0x68, 0x7d, 0x47,
                   0xba, 0x1d, 0x36, 0xd2, 0x34, 0x9e, 0x23, 0xf6, 0x44, 0x39, 0x2c, 0x8e, 0xa9, 0xc4,
                   0x9d, 0x40, 0xc1, 0x32, 0x71, 0xaf, 0xf2, 0x64, 0xd0, 0xf2, 0x48, 0x00};
  uint8_t  ct[]  = {0x75, 0x75, 0x0d, 0x37, 0xb4, 0xbb, 0xa2, 0xa4, 0xde, 0xdb, 0x34, 0x23, 0x5b, 0xd6,
                  0x8c, 0x66, 0x45, 0xac, 0xda, 0xac, 0xa4, 0x81, 0x38, 0xa3, 0xb0, 0xc4, 0x71, 0xe2,
                  0xa7, 0x04, 0x1a, 0x57, 0x64, 0x23, 0xd2, 0x92, 0x72, 0x87, 0xf0, 0x00};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_4()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xaa, 0x1f, 0x95, 0xae, 0xa5, 0x33, 0xbc, 0xb3, 0x2e, 0xb6, 0x3b, 0xf5, 0x2d, 0x8f, 0x83, 0x1a};
  uint32_t count     = 0x72d8c671;
  uint8_t  bearer    = 0x10;
  uint8_t  direction = 1;
  uint32_t len_bits = 1022, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {0xfb, 0x1b, 0x96, 0xc5, 0xc8, 0xba, 0xdf, 0xb2, 0xe8, 0xe8, 0xed, 0xfd, 0xe7, 0x8e, 0x57, 0xf2,
                   0xad, 0x81, 0xe7, 0x41, 0x03, 0xfc, 0x43, 0x0a, 0x53, 0x4d, 0xcc, 0x37, 0xaf, 0xce, 0xc7, 0x0e,
                   0x15, 0x17, 0xbb, 0x06, 0xf2, 0x72, 0x19, 0xda, 0xe4, 0x90, 0x22, 0xdd, 0xc4, 0x7a, 0x06, 0x8d,
                   0xe4, 0xc9, 0x49, 0x6a, 0x95, 0x1a, 0x6b, 0x09, 0xed, 0xbd, 0xc8, 0x64, 0xc7, 0xad, 0xbd, 0x74,
                   0x0a, 0xc5, 0x0c, 0x02, 0x2f, 0x30, 0x82, 0xba, 0xfd, 0x22, 0xd7, 0x81, 0x97, 0xc5, 0xd5, 0x08,
                   0xb9, 0x77, 0xbc, 0xa1, 0x3f, 0x32, 0xe6, 0x52, 0xe7, 0x4b, 0xa7, 0x28, 0x57, 0x60, 0x77, 0xce,
                   0x62, 0x8c, 0x53, 0x5e, 0x87, 0xdc, 0x60, 0x77, 0xba, 0x07, 0xd2, 0x90, 0x68, 0x59, 0x0c, 0x8c,
                   0xb5, 0xf1, 0x08, 0x8e, 0x08, 0x2c, 0xfa, 0x0e, 0xc9, 0x61, 0x30, 0x2d, 0x69, 0xcf, 0x3d, 0x44};
  uint8_t  ct[]  = {0xdf, 0xb4, 0x40, 0xac, 0xb3, 0x77, 0x35, 0x49, 0xef, 0xc0, 0x46, 0x28, 0xae, 0xb8, 0xd8, 0x15,
                  0x62, 0x75, 0x23, 0x0b, 0xdc, 0x69, 0x0d, 0x94, 0xb0, 0x0d, 0x8d, 0x95, 0xf2, 0x8c, 0x4b, 0x56,
                  0x30, 0x7f, 0x60, 0xf4, 0xca, 0x55, 0xeb, 0xa6, 0x61, 0xeb, 0xba, 0x72, 0xac, 0x80, 0x8f, 0xa8,
                  0xc4, 0x9e, 0x26, 0x78, 0x8e, 0xd0, 0x4a, 0x5d, 0x60, 0x6c, 0xb4, 0x18, 0xde, 0x74, 0x87, 0x8b,
                  0x9a, 0x22, 0xf8, 0xef, 0x29, 0x59, 0x0b, 0xc4, 0xeb, 0x57, 0xc9, 0xfa, 0xf7, 0xc4, 0x15, 0x24,
                  0xa8, 0x85, 0xb8, 0x97, 0x9c, 0x42, 0x3f, 0x2f, 0x8f, 0x8e, 0x05, 0x92, 0xa9, 0x87, 0x92, 0x01,
                  0xbe, 0x7f, 0xf9, 0x77, 0x7a, 0x16, 0x2a, 0xb8, 0x10, 0xfe, 0xb3, 0x24, 0xba, 0x74, 0xc4, 0xc1,
                  0x56, 0xe0, 0x4d, 0x39, 0x09, 0x72, 0x09, 0x65, 0x3a, 0xc3, 0x3e, 0x5a, 0x5f, 0x2d, 0x88, 0x64};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_5()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0x96, 0x18, 0xae, 0x46, 0x89, 0x1f, 0x86, 0x57, 0x8e, 0xeb, 0xe9, 0x0e, 0xf7, 0xa1, 0x20, 0x2e};
  uint32_t count     = 0xc675a64b;
  uint8_t  bearer    = 0x0c;
  uint8_t  direction = 1;
  uint32_t len_bits = 1245, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {0x8d, 0xaa, 0x17, 0xb1, 0xae, 0x05, 0x05, 0x29, 0xc6, 0x82, 0x7f, 0x28, 0xc0, 0xef, 0x6a, 0x12,
                   0x42, 0xe9, 0x3f, 0x8b, 0x31, 0x4f, 0xb1, 0x8a, 0x77, 0xf7, 0x90, 0xae, 0x04, 0x9f, 0xed, 0xd6,
                   0x12, 0x26, 0x7f, 0xec, 0xae, 0xfc, 0x45, 0x01, 0x74, 0xd7, 0x6d, 0x9f, 0x9a, 0xa7, 0x75, 0x5a,
                   0x30, 0xcd, 0x90, 0xa9, 0xa5, 0x87, 0x4b, 0xf4, 0x8e, 0xaf, 0x70, 0xee, 0xa3, 0xa6, 0x2a, 0x25,
                   0x0a, 0x8b, 0x6b, 0xd8, 0xd9, 0xb0, 0x8b, 0x08, 0xd6, 0x4e, 0x32, 0xd1, 0x81, 0x77, 0x77, 0xfb,
                   0x54, 0x4d, 0x49, 0xcd, 0x49, 0x72, 0x0e, 0x21, 0x9d, 0xbf, 0x8b, 0xbe, 0xd3, 0x39, 0x04, 0xe1,
                   0xfd, 0x40, 0xa4, 0x1d, 0x37, 0x0a, 0x1f, 0x65, 0x74, 0x50, 0x95, 0x68, 0x7d, 0x47, 0xba, 0x1d,
                   0x36, 0xd2, 0x34, 0x9e, 0x23, 0xf6, 0x44, 0x39, 0x2c, 0x8e, 0xa9, 0xc4, 0x9d, 0x40, 0xc1, 0x32,
                   0x71, 0xaf, 0xf2, 0x64, 0xd0, 0xf2, 0x48, 0x41, 0xd6, 0x46, 0x5f, 0x09, 0x96, 0xff, 0x84, 0xe6,
                   0x5f, 0xc5, 0x17, 0xc5, 0x3e, 0xfc, 0x33, 0x63, 0xc3, 0x84, 0x92, 0xa8};
  uint8_t  ct[]  = {0x91, 0x9c, 0x8c, 0x33, 0xd6, 0x67, 0x89, 0x70, 0x3d, 0x05, 0xa0, 0xd7, 0xce, 0x82, 0xa2, 0xae,
                  0xac, 0x4e, 0xe7, 0x6c, 0x0f, 0x4d, 0xa0, 0x50, 0x33, 0x5e, 0x8a, 0x84, 0xe7, 0x89, 0x7b, 0xa5,
                  0xdf, 0x2f, 0x36, 0xbd, 0x51, 0x3e, 0x3d, 0x0c, 0x85, 0x78, 0xc7, 0xa0, 0xfc, 0xf0, 0x43, 0xe0,
                  0x3a, 0xa3, 0xa3, 0x9f, 0xba, 0xad, 0x7d, 0x15, 0xbe, 0x07, 0x4f, 0xaa, 0x5d, 0x90, 0x29, 0xf7,
                  0x1f, 0xb4, 0x57, 0xb6, 0x47, 0x83, 0x47, 0x14, 0xb0, 0xe1, 0x8f, 0x11, 0x7f, 0xca, 0x10, 0x67,
                  0x79, 0x45, 0x09, 0x6c, 0x8c, 0x5f, 0x32, 0x6b, 0xa8, 0xd6, 0x09, 0x5e, 0xb2, 0x9c, 0x3e, 0x36,
                  0xcf, 0x24, 0x5d, 0x16, 0x22, 0xaa, 0xfe, 0x92, 0x1f, 0x75, 0x66, 0xc4, 0xf5, 0xd6, 0x44, 0xf2,
                  0xf1, 0xfc, 0x0e, 0xc6, 0x84, 0xdd, 0xb2, 0x13, 0x49, 0x74, 0x76, 0x22, 0xe2, 0x09, 0x29, 0x5d,
                  0x27, 0xff, 0x3f, 0x95, 0x62, 0x33, 0x71, 0xd4, 0x9b, 0x14, 0x7c, 0x0a, 0xf4, 0x86, 0x17, 0x1f,
                  0x22, 0xcd, 0x04, 0xb1, 0xcb, 0xeb, 0x26, 0x58, 0x22, 0x3e, 0x69, 0x38};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_6()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0x54, 0xf4, 0xe2, 0xe0, 0x4c, 0x83, 0x78, 0x6e, 0xec, 0x8f, 0xb5, 0xab, 0xe8, 0xe3, 0x65, 0x66};
  uint32_t count     = 0xaca4f50f;
  uint8_t  bearer    = 0x0b;
  uint8_t  direction = 0;
  uint32_t len_bits = 3861, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {
      0x40, 0x98, 0x1b, 0xa6, 0x82, 0x4c, 0x1b, 0xfb, 0x42, 0x86, 0xb2, 0x99, 0x78, 0x3d, 0xaf, 0x44, 0x2c, 0x09, 0x9f,
      0x7a, 0xb0, 0xf5, 0x8d, 0x5c, 0x8e, 0x46, 0xb1, 0x04, 0xf0, 0x8f, 0x01, 0xb4, 0x1a, 0xb4, 0x85, 0x47, 0x20, 0x29,
      0xb7, 0x1d, 0x36, 0xbd, 0x1a, 0x3d, 0x90, 0xdc, 0x3a, 0x41, 0xb4, 0x6d, 0x51, 0x67, 0x2a, 0xc4, 0xc9, 0x66, 0x3a,
      0x2b, 0xe0, 0x63, 0xda, 0x4b, 0xc8, 0xd2, 0x80, 0x8c, 0xe3, 0x3e, 0x2c, 0xcc, 0xbf, 0xc6, 0x34, 0xe1, 0xb2, 0x59,
      0x06, 0x08, 0x76, 0xa0, 0xfb, 0xb5, 0xa4, 0x37, 0xeb, 0xcc, 0x8d, 0x31, 0xc1, 0x9e, 0x44, 0x54, 0x31, 0x87, 0x45,
      0xe3, 0xfa, 0x16, 0xbb, 0x11, 0xad, 0xae, 0x24, 0x88, 0x79, 0xfe, 0x52, 0xdb, 0x25, 0x43, 0xe5, 0x3c, 0xf4, 0x45,
      0xd3, 0xd8, 0x28, 0xce, 0x0b, 0xf5, 0xc5, 0x60, 0x59, 0x3d, 0x97, 0x27, 0x8a, 0x59, 0x76, 0x2d, 0xd0, 0xc2, 0xc9,
      0xcd, 0x68, 0xd4, 0x49, 0x6a, 0x79, 0x25, 0x08, 0x61, 0x40, 0x14, 0xb1, 0x3b, 0x6a, 0xa5, 0x11, 0x28, 0xc1, 0x8c,
      0xd6, 0xa9, 0x0b, 0x87, 0x97, 0x8c, 0x2f, 0xf1, 0xca, 0xbe, 0x7d, 0x9f, 0x89, 0x8a, 0x41, 0x1b, 0xfd, 0xb8, 0x4f,
      0x68, 0xf6, 0x72, 0x7b, 0x14, 0x99, 0xcd, 0xd3, 0x0d, 0xf0, 0x44, 0x3a, 0xb4, 0xa6, 0x66, 0x53, 0x33, 0x0b, 0xcb,
      0xa1, 0x10, 0x5e, 0x4c, 0xec, 0x03, 0x4c, 0x73, 0xe6, 0x05, 0xb4, 0x31, 0x0e, 0xaa, 0xad, 0xcf, 0xd5, 0xb0, 0xca,
      0x27, 0xff, 0xd8, 0x9d, 0x14, 0x4d, 0xf4, 0x79, 0x27, 0x59, 0x42, 0x7c, 0x9c, 0xc1, 0xf8, 0xcd, 0x8c, 0x87, 0x20,
      0x23, 0x64, 0xb8, 0xa6, 0x87, 0x95, 0x4c, 0xb0, 0x5a, 0x8d, 0x4e, 0x2d, 0x99, 0xe7, 0x3d, 0xb1, 0x60, 0xde, 0xb1,
      0x80, 0xad, 0x08, 0x41, 0xe9, 0x67, 0x41, 0xa5, 0xd5, 0x9f, 0xe4, 0x18, 0x9f, 0x15, 0x42, 0x00, 0x26, 0xfe, 0x4c,
      0xd1, 0x21, 0x04, 0x93, 0x2f, 0xb3, 0x8f, 0x73, 0x53, 0x40, 0x43, 0x8a, 0xaf, 0x7e, 0xca, 0x6f, 0xd5, 0xcf, 0xd3,
      0xa1, 0x95, 0xce, 0x5a, 0xbe, 0x65, 0x27, 0x2a, 0xf6, 0x07, 0xad, 0xa1, 0xbe, 0x65, 0xa6, 0xb4, 0xc9, 0xc0, 0x69,
      0x32, 0x34, 0x09, 0x2c, 0x4d, 0x01, 0x8f, 0x17, 0x56, 0xc6, 0xdb, 0x9d, 0xc8, 0xa6, 0xd8, 0x0b, 0x88, 0x81, 0x38,
      0x61, 0x6b, 0x68, 0x12, 0x62, 0xf9, 0x54, 0xd0, 0xe7, 0x71, 0x17, 0x48, 0x78, 0x0d, 0x92, 0x29, 0x1d, 0x86, 0x29,
      0x99, 0x72, 0xdb, 0x74, 0x1c, 0xfa, 0x4f, 0x37, 0xb8, 0xb5, 0x6c, 0xdb, 0x18, 0xa7, 0xca, 0x82, 0x18, 0xe8, 0x6e,
      0x4b, 0x4b, 0x71, 0x6a, 0x4d, 0x04, 0x37, 0x1f, 0xbe, 0xc2, 0x62, 0xfc, 0x5a, 0xd0, 0xb3, 0x81, 0x9b, 0x18, 0x7b,
      0x97, 0xe5, 0x5b, 0x1a, 0x4d, 0x7c, 0x19, 0xee, 0x24, 0xc8, 0xb4, 0xd7, 0x72, 0x3c, 0xfe, 0xdf, 0x04, 0x5b, 0x8a,
      0xca, 0xe4, 0x86, 0x95, 0x17, 0xd8, 0x0e, 0x50, 0x61, 0x5d, 0x90, 0x35, 0xd5, 0xd9, 0xc5, 0xa4, 0x0a, 0xf6, 0x02,
      0x28, 0x0b, 0x54, 0x25, 0x97, 0xb0, 0xcb, 0x18, 0x61, 0x9e, 0xeb, 0x35, 0x92, 0x57, 0x59, 0xd1, 0x95, 0xe1, 0x00,
      0xe8, 0xe4, 0xaa, 0x0c, 0x38, 0xa3, 0xc2, 0xab, 0xe0, 0xf3, 0xd8, 0xff, 0x04, 0xf3, 0xc3, 0x3c, 0x29, 0x50, 0x69,
      0xc2, 0x36, 0x94, 0xb5, 0xbb, 0xea, 0xcd, 0xd5, 0x42, 0xe2, 0x8e, 0x8a, 0x94, 0xed, 0xb9, 0x11, 0x9f, 0x41, 0x2d,
      0x05, 0x4b, 0xe1, 0xfa, 0x72, 0x00, 0xb0, 0x90, 0x00};
  uint8_t ct[] = {
      0x5c, 0xb7, 0x2c, 0x6e, 0xdc, 0x87, 0x8f, 0x15, 0x66, 0xe1, 0x02, 0x53, 0xaf, 0xc3, 0x64, 0xc9, 0xfa, 0x54, 0x0d,
      0x91, 0x4d, 0xb9, 0x4c, 0xbe, 0xe2, 0x75, 0xd0, 0x91, 0x7c, 0xa6, 0xaf, 0x0d, 0x77, 0xac, 0xb4, 0xef, 0x3b, 0xbe,
      0x1a, 0x72, 0x2b, 0x2e, 0xf5, 0xbd, 0x1d, 0x4b, 0x8e, 0x2a, 0xa5, 0x02, 0x4e, 0xc1, 0x38, 0x8a, 0x20, 0x1e, 0x7b,
      0xce, 0x79, 0x20, 0xae, 0xc6, 0x15, 0x89, 0x5f, 0x76, 0x3a, 0x55, 0x64, 0xdc, 0xc4, 0xc4, 0x82, 0xa2, 0xee, 0x1d,
      0x8b, 0xfe, 0xcc, 0x44, 0x98, 0xec, 0xa8, 0x3f, 0xbb, 0x75, 0xf9, 0xab, 0x53, 0x0e, 0x0d, 0xaf, 0xbe, 0xde, 0x2f,
      0xa5, 0x89, 0x5b, 0x82, 0x99, 0x1b, 0x62, 0x77, 0xc5, 0x29, 0xe0, 0xf2, 0x52, 0x9d, 0x7f, 0x79, 0x60, 0x6b, 0xe9,
      0x67, 0x06, 0x29, 0x6d, 0xed, 0xfa, 0x9d, 0x74, 0x12, 0xb6, 0x16, 0x95, 0x8c, 0xb5, 0x63, 0xc6, 0x78, 0xc0, 0x28,
      0x25, 0xc3, 0x0d, 0x0a, 0xee, 0x77, 0xc4, 0xc1, 0x46, 0xd2, 0x76, 0x54, 0x12, 0x42, 0x1a, 0x80, 0x8d, 0x13, 0xce,
      0xc8, 0x19, 0x69, 0x4c, 0x75, 0xad, 0x57, 0x2e, 0x9b, 0x97, 0x3d, 0x94, 0x8b, 0x81, 0xa9, 0x33, 0x7c, 0x3b, 0x2a,
      0x17, 0x19, 0x2e, 0x22, 0xc2, 0x06, 0x9f, 0x7e, 0xd1, 0x16, 0x2a, 0xf4, 0x4c, 0xde, 0xa8, 0x17, 0x60, 0x36, 0x65,
      0xe8, 0x07, 0xce, 0x40, 0xc8, 0xe0, 0xdd, 0x9d, 0x63, 0x94, 0xdc, 0x6e, 0x31, 0x15, 0x3f, 0xe1, 0x95, 0x5c, 0x47,
      0xaf, 0xb5, 0x1f, 0x26, 0x17, 0xee, 0x0c, 0x5e, 0x3b, 0x8e, 0xf1, 0xad, 0x75, 0x74, 0xed, 0x34, 0x3e, 0xdc, 0x27,
      0x43, 0xcc, 0x94, 0xc9, 0x90, 0xe1, 0xf1, 0xfd, 0x26, 0x42, 0x53, 0xc1, 0x78, 0xde, 0xa7, 0x39, 0xc0, 0xbe, 0xfe,
      0xeb, 0xcd, 0x9f, 0x9b, 0x76, 0xd4, 0x9c, 0x10, 0x15, 0xc9, 0xfe, 0xcf, 0x50, 0xe5, 0x3b, 0x8b, 0x52, 0x04, 0xdb,
      0xcd, 0x3e, 0xed, 0x86, 0x38, 0x55, 0xda, 0xbc, 0xdc, 0xc9, 0x4b, 0x31, 0xe3, 0x18, 0x02, 0x15, 0x68, 0x85, 0x5c,
      0x8b, 0x9e, 0x52, 0xa9, 0x81, 0x95, 0x7a, 0x11, 0x28, 0x27, 0xf9, 0x78, 0xba, 0x96, 0x0f, 0x14, 0x47, 0x91, 0x1b,
      0x31, 0x7b, 0x55, 0x11, 0xfb, 0xcc, 0x7f, 0xb1, 0x3a, 0xc1, 0x53, 0xdb, 0x74, 0x25, 0x11, 0x17, 0xe4, 0x86, 0x1e,
      0xb9, 0xe8, 0x3b, 0xff, 0xff, 0xc4, 0xeb, 0x77, 0x55, 0x57, 0x90, 0x38, 0xe5, 0x79, 0x24, 0xb1, 0xf7, 0x8b, 0x3e,
      0x1a, 0xd9, 0x0b, 0xab, 0x2a, 0x07, 0x87, 0x1b, 0x72, 0xdb, 0x5e, 0xef, 0x96, 0xc3, 0x34, 0x04, 0x49, 0x66, 0xdb,
      0x0c, 0x37, 0xca, 0xfd, 0x1a, 0x89, 0xe5, 0x64, 0x6a, 0x35, 0x80, 0xeb, 0x64, 0x65, 0xf1, 0x21, 0xdc, 0xe9, 0xcb,
      0x88, 0xd8, 0x5b, 0x96, 0xcf, 0x23, 0xcc, 0xcc, 0xd4, 0x28, 0x07, 0x67, 0xbe, 0xe8, 0xee, 0xb2, 0x3d, 0x86, 0x52,
      0x46, 0x1d, 0xb6, 0x49, 0x31, 0x03, 0x00, 0x3b, 0xaf, 0x89, 0xf5, 0xe1, 0x82, 0x61, 0xea, 0x43, 0xc8, 0x4a, 0x92,
      0xeb, 0xff, 0xff, 0xe4, 0x90, 0x9d, 0xc4, 0x6c, 0x51, 0x92, 0xf8, 0x25, 0xf7, 0x70, 0x60, 0x0b, 0x96, 0x02, 0xc5,
      0x57, 0xb5, 0xf8, 0xb4, 0x31, 0xa7, 0x9d, 0x45, 0x97, 0x7d, 0xd9, 0xc4, 0x1b, 0x86, 0x3d, 0xa9, 0xe1, 0x42, 0xe9,
      0x00, 0x20, 0xcf, 0xd0, 0x74, 0xd6, 0x92, 0x7b, 0x7a, 0xb3, 0xb6, 0x72, 0x5d, 0x1a, 0x6f, 0x3f, 0x98, 0xb9, 0xc9,
      0xda, 0xa8, 0x98, 0x2a, 0xff, 0x06, 0x78, 0x28, 0x00};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  struct timeval t[3];

  // encryption
  gettimeofday(&t[1], NULL);
  for (int i = 0; i < 100; i++) {
    err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  }
  gettimeofday(&t[2], NULL);
  get_time_interval(t);
  printf("encryption: %u bits, t=%d us, rate=%.1f Mbps/s\n",
         len_bits,
         (int)t[0].tv_usec / 100,
         (float)100 * len_bits / t[0].tv_usec);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  gettimeofday(&t[1], NULL);
  for (int i = 0; i < 100; i++) {
    err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  }
  gettimeofday(&t[2], NULL);
  get_time_interval(t);
  printf("decryption: %u bits, t=%d us, rate=%.1f Mbps/s\n",
         len_bits,
         (int)t[0].tv_usec / 100,
         (float)100 * len_bits / t[0].tv_usec);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

// set len_bitsgth to multiple of 8 respectively 128
int test_set_1_block_size()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xd3, 0xc5, 0xd5, 0x92, 0x32, 0x7f, 0xb1, 0x1c, 0x40, 0x35, 0xc6, 0x68, 0x0a, 0xf8, 0xc6, 0xd1};
  uint32_t count     = 0x398a59b4;
  uint8_t  bearer    = 0x15;
  uint8_t  direction = 1;
  uint32_t len_bits = 256, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {0x98, 0x1b, 0xa6, 0x82, 0x4c, 0x1b, 0xfb, 0x1a, 0xb4, 0x85, 0x47, 0x20, 0x29, 0xb7, 0x1d, 0x80,
                   0x8c, 0xe3, 0x3e, 0x2c, 0xc3, 0xc0, 0xb5, 0xfc, 0x1f, 0x3d, 0xe8, 0xa6, 0xdc, 0x66, 0xb1, 0xf0};
  uint8_t  ct[]  = {0xe9, 0xfe, 0xd8, 0xa6, 0x3d, 0x15, 0x53, 0x04, 0xd7, 0x1d, 0xf2, 0x0b, 0xf3, 0xe8, 0x22, 0x14,
                  0xb2, 0x0e, 0xd7, 0xda, 0xd2, 0xf2, 0x33, 0xdc, 0x3c, 0x22, 0xd7, 0xbd, 0xee, 0xed, 0x8e, 0x78};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  free(out);
  return SRSLTE_SUCCESS;
}

// inserted bit flip in msg[0]
int test_set_1_invalid()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xd3, 0xc5, 0xd5, 0x92, 0x32, 0x7f, 0xb1, 0x1c, 0x40, 0x35, 0xc6, 0x68, 0x0a, 0xf8, 0xc6, 0xd1};
  uint32_t count     = 0x398a59b4;
  uint8_t  bearer    = 0x15;
  uint8_t  direction = 1;
  uint32_t len_bits = 253, len_bytes = (len_bits + 7) / 8;
  uint8_t  msg[] = {0x99, 0x1b, 0xa6, 0x82, 0x4c, 0x1b, 0xfb, 0x1a, 0xb4, 0x85, 0x47, 0x20, 0x29, 0xb7, 0x1d, 0x80,
                   0x8c, 0xe3, 0x3e, 0x2c, 0xc3, 0xc0, 0xb5, 0xfc, 0x1f, 0x3d, 0xe8, 0xa6, 0xdc, 0x66, 0xb1, 0xf0};
  uint8_t  ct[]  = {0xe9, 0xfe, 0xd8, 0xa6, 0x3d, 0x15, 0x53, 0x04, 0xd7, 0x1d, 0xf2, 0x0b, 0xf3, 0xe8, 0x22, 0x14,
                  0xb2, 0x0e, 0xd7, 0xda, 0xd2, 0xf2, 0x33, 0xdc, 0x3c, 0x22, 0xd7, 0xbd, 0xee, 0xed, 0x8e, 0x78};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea2(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);
  TESTASSERT(err_cmp != 0);

  // decryption
  err_lte = liblte_security_decryption_eea2(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp != 0);

  free(out);
  return SRSLTE_SUCCESS;
}

/*
 * Functions
 */

int main(int argc, char* argv[])
{
  TESTASSERT(test_set_1() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_2() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_3() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_4() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_5() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_6() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_1_block_size() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_1_invalid() == SRSLTE_SUCCESS);
}
