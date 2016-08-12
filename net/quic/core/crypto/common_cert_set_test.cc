// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/quic/core/crypto/common_cert_set.h"

#include <stdint.h>

#include "testing/gtest/include/gtest/gtest.h"

using base::StringPiece;

namespace net {
namespace test {

static const unsigned char kGIACertificate1[] = {
    0x30, 0x82, 0x03, 0xf0, 0x30, 0x82, 0x02, 0xd8, 0xa0, 0x03, 0x02, 0x01,
    0x02, 0x02, 0x03, 0x02, 0x3a, 0x76, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86,
    0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x42, 0x31,
    0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53,
    0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0d, 0x47,
    0x65, 0x6f, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x49, 0x6e, 0x63, 0x2e,
    0x31, 0x1b, 0x30, 0x19, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x12, 0x47,
    0x65, 0x6f, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x47, 0x6c, 0x6f, 0x62,
    0x61, 0x6c, 0x20, 0x43, 0x41, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x33, 0x30,
    0x34, 0x30, 0x35, 0x31, 0x35, 0x31, 0x35, 0x35, 0x35, 0x5a, 0x17, 0x0d,
    0x31, 0x36, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39,
    0x5a, 0x30, 0x49, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
    0x13, 0x02, 0x55, 0x53, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04,
    0x0a, 0x13, 0x0a, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x20, 0x49, 0x6e,
    0x63, 0x31, 0x25, 0x30, 0x23, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x1c,
    0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x20, 0x49, 0x6e, 0x74, 0x65, 0x72,
    0x6e, 0x65, 0x74, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74,
    0x79, 0x20, 0x47, 0x32, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09,
    0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03,
    0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
    0x00, 0x9c, 0x2a, 0x04, 0x77, 0x5c, 0xd8, 0x50, 0x91, 0x3a, 0x06, 0xa3,
    0x82, 0xe0, 0xd8, 0x50, 0x48, 0xbc, 0x89, 0x3f, 0xf1, 0x19, 0x70, 0x1a,
    0x88, 0x46, 0x7e, 0xe0, 0x8f, 0xc5, 0xf1, 0x89, 0xce, 0x21, 0xee, 0x5a,
    0xfe, 0x61, 0x0d, 0xb7, 0x32, 0x44, 0x89, 0xa0, 0x74, 0x0b, 0x53, 0x4f,
    0x55, 0xa4, 0xce, 0x82, 0x62, 0x95, 0xee, 0xeb, 0x59, 0x5f, 0xc6, 0xe1,
    0x05, 0x80, 0x12, 0xc4, 0x5e, 0x94, 0x3f, 0xbc, 0x5b, 0x48, 0x38, 0xf4,
    0x53, 0xf7, 0x24, 0xe6, 0xfb, 0x91, 0xe9, 0x15, 0xc4, 0xcf, 0xf4, 0x53,
    0x0d, 0xf4, 0x4a, 0xfc, 0x9f, 0x54, 0xde, 0x7d, 0xbe, 0xa0, 0x6b, 0x6f,
    0x87, 0xc0, 0xd0, 0x50, 0x1f, 0x28, 0x30, 0x03, 0x40, 0xda, 0x08, 0x73,
    0x51, 0x6c, 0x7f, 0xff, 0x3a, 0x3c, 0xa7, 0x37, 0x06, 0x8e, 0xbd, 0x4b,
    0x11, 0x04, 0xeb, 0x7d, 0x24, 0xde, 0xe6, 0xf9, 0xfc, 0x31, 0x71, 0xfb,
    0x94, 0xd5, 0x60, 0xf3, 0x2e, 0x4a, 0xaf, 0x42, 0xd2, 0xcb, 0xea, 0xc4,
    0x6a, 0x1a, 0xb2, 0xcc, 0x53, 0xdd, 0x15, 0x4b, 0x8b, 0x1f, 0xc8, 0x19,
    0x61, 0x1f, 0xcd, 0x9d, 0xa8, 0x3e, 0x63, 0x2b, 0x84, 0x35, 0x69, 0x65,
    0x84, 0xc8, 0x19, 0xc5, 0x46, 0x22, 0xf8, 0x53, 0x95, 0xbe, 0xe3, 0x80,
    0x4a, 0x10, 0xc6, 0x2a, 0xec, 0xba, 0x97, 0x20, 0x11, 0xc7, 0x39, 0x99,
    0x10, 0x04, 0xa0, 0xf0, 0x61, 0x7a, 0x95, 0x25, 0x8c, 0x4e, 0x52, 0x75,
    0xe2, 0xb6, 0xed, 0x08, 0xca, 0x14, 0xfc, 0xce, 0x22, 0x6a, 0xb3, 0x4e,
    0xcf, 0x46, 0x03, 0x97, 0x97, 0x03, 0x7e, 0xc0, 0xb1, 0xde, 0x7b, 0xaf,
    0x45, 0x33, 0xcf, 0xba, 0x3e, 0x71, 0xb7, 0xde, 0xf4, 0x25, 0x25, 0xc2,
    0x0d, 0x35, 0x89, 0x9d, 0x9d, 0xfb, 0x0e, 0x11, 0x79, 0x89, 0x1e, 0x37,
    0xc5, 0xaf, 0x8e, 0x72, 0x69, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x81,
    0xe7, 0x30, 0x81, 0xe4, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04,
    0x18, 0x30, 0x16, 0x80, 0x14, 0xc0, 0x7a, 0x98, 0x68, 0x8d, 0x89, 0xfb,
    0xab, 0x05, 0x64, 0x0c, 0x11, 0x7d, 0xaa, 0x7d, 0x65, 0xb8, 0xca, 0xcc,
    0x4e, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14,
    0x4a, 0xdd, 0x06, 0x16, 0x1b, 0xbc, 0xf6, 0x68, 0xb5, 0x76, 0xf5, 0x81,
    0xb6, 0xbb, 0x62, 0x1a, 0xba, 0x5a, 0x81, 0x2f, 0x30, 0x12, 0x06, 0x03,
    0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x08, 0x30, 0x06, 0x01, 0x01,
    0xff, 0x02, 0x01, 0x00, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x1d, 0x0f, 0x01,
    0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x01, 0x06, 0x30, 0x35, 0x06, 0x03,
    0x55, 0x1d, 0x1f, 0x04, 0x2e, 0x30, 0x2c, 0x30, 0x2a, 0xa0, 0x28, 0xa0,
    0x26, 0x86, 0x24, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x67, 0x2e,
    0x73, 0x79, 0x6d, 0x63, 0x62, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x63, 0x72,
    0x6c, 0x73, 0x2f, 0x67, 0x74, 0x67, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x2e,
    0x63, 0x72, 0x6c, 0x30, 0x2e, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05,
    0x07, 0x01, 0x01, 0x04, 0x22, 0x30, 0x20, 0x30, 0x1e, 0x06, 0x08, 0x2b,
    0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x01, 0x86, 0x12, 0x68, 0x74, 0x74,
    0x70, 0x3a, 0x2f, 0x2f, 0x67, 0x2e, 0x73, 0x79, 0x6d, 0x63, 0x64, 0x2e,
    0x63, 0x6f, 0x6d, 0x30, 0x17, 0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x10,
    0x30, 0x0e, 0x30, 0x0c, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 0x01, 0xd6,
    0x79, 0x02, 0x05, 0x01, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
    0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00,
    0x27, 0x8c, 0xcf, 0xe9, 0xc7, 0x3b, 0xbe, 0xc0, 0x6f, 0xe8, 0x96, 0x84,
    0xfb, 0x9c, 0x5c, 0x5d, 0x90, 0xe4, 0x77, 0xdb, 0x8b, 0x32, 0x60, 0x9b,
    0x65, 0xd8, 0x85, 0x26, 0xb5, 0xba, 0x9f, 0x1e, 0xde, 0x64, 0x4e, 0x1f,
    0xc6, 0xc8, 0x20, 0x5b, 0x09, 0x9f, 0xab, 0xa9, 0xe0, 0x09, 0x34, 0x45,
    0xa2, 0x65, 0x25, 0x37, 0x3d, 0x7f, 0x5a, 0x6f, 0x20, 0xcc, 0xf9, 0xfa,
    0xf1, 0x1d, 0x8f, 0x10, 0x0c, 0x02, 0x3a, 0xc4, 0xc9, 0x01, 0x76, 0x96,
    0xbe, 0x9b, 0xf9, 0x15, 0xd8, 0x39, 0xd1, 0xc5, 0x03, 0x47, 0x76, 0xb8,
    0x8a, 0x8c, 0x31, 0xd6, 0x60, 0xd5, 0xe4, 0x8f, 0xdb, 0xfa, 0x3c, 0xc6,
    0xd5, 0x98, 0x28, 0xf8, 0x1c, 0x8f, 0x17, 0x91, 0x34, 0xcb, 0xcb, 0x52,
    0x7a, 0xd1, 0xfb, 0x3a, 0x20, 0xe4, 0xe1, 0x86, 0xb1, 0xd8, 0x18, 0x0f,
    0xbe, 0xd6, 0x87, 0x64, 0x8d, 0xc5, 0x0a, 0x25, 0x42, 0x51, 0xef, 0xb2,
    0x38, 0xb8, 0xe0, 0x1d, 0xd0, 0xe1, 0xfc, 0xe6, 0xf4, 0xaf, 0x46, 0xba,
    0xef, 0xc0, 0xbf, 0xc5, 0xb4, 0x05, 0xf5, 0x94, 0x75, 0x0c, 0xfe, 0xa2,
    0xbe, 0x02, 0xba, 0xea, 0x86, 0x5b, 0xf9, 0x35, 0xb3, 0x66, 0xf5, 0xc5,
    0x8d, 0x85, 0xa1, 0x1a, 0x23, 0x77, 0x1a, 0x19, 0x17, 0x54, 0x13, 0x60,
    0x9f, 0x0b, 0xe1, 0xb4, 0x9c, 0x28, 0x2a, 0xf9, 0xae, 0x02, 0x34, 0x6d,
    0x25, 0x93, 0x9c, 0x82, 0xa8, 0x17, 0x7b, 0xf1, 0x85, 0xb0, 0xd3, 0x0f,
    0x58, 0xe1, 0xfb, 0xb1, 0xfe, 0x9c, 0xa1, 0xa3, 0xe8, 0xfd, 0xc9, 0x3f,
    0xf4, 0xd7, 0x71, 0xdc, 0xbd, 0x8c, 0xa4, 0x19, 0xe0, 0x21, 0x23, 0x23,
    0x55, 0x13, 0x8f, 0xa4, 0x16, 0x02, 0x09, 0x7e, 0xb9, 0xaf, 0xee, 0xdb,
    0x53, 0x64, 0xbd, 0x71, 0x2f, 0xb9, 0x39, 0xce, 0x30, 0xb7, 0xb4, 0xbc,
    0x54, 0xe0, 0x47, 0x07,
};
static const unsigned char kGIACertificate2[] = {
    0x30, 0x82, 0x03, 0xf0, 0x30, 0x82, 0x02, 0xd8, 0xa0, 0x03, 0x02, 0x01,
    0x02, 0x02, 0x03, 0x02, 0x3a, 0x83, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86,
    0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x42, 0x31,
    0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53,
    0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0d, 0x47,
    0x65, 0x6f, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x49, 0x6e, 0x63, 0x2e,
    0x31, 0x1b, 0x30, 0x19, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x12, 0x47,
    0x65, 0x6f, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x47, 0x6c, 0x6f, 0x62,
    0x61, 0x6c, 0x20, 0x43, 0x41, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x33, 0x30,
    0x34, 0x30, 0x35, 0x31, 0x35, 0x31, 0x35, 0x35, 0x36, 0x5a, 0x17, 0x0d,
    0x31, 0x36, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39,
    0x5a, 0x30, 0x49, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
    0x13, 0x02, 0x55, 0x53, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04,
    0x0a, 0x13, 0x0a, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x20, 0x49, 0x6e,
    0x63, 0x31, 0x25, 0x30, 0x23, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x1c,
    0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x20, 0x49, 0x6e, 0x74, 0x65, 0x72,
    0x6e, 0x65, 0x74, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74,
    0x79, 0x20, 0x47, 0x32, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09,
    0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03,
    0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
    0x00, 0x9c, 0x2a, 0x04, 0x77, 0x5c, 0xd8, 0x50, 0x91, 0x3a, 0x06, 0xa3,
    0x82, 0xe0, 0xd8, 0x50, 0x48, 0xbc, 0x89, 0x3f, 0xf1, 0x19, 0x70, 0x1a,
    0x88, 0x46, 0x7e, 0xe0, 0x8f, 0xc5, 0xf1, 0x89, 0xce, 0x21, 0xee, 0x5a,
    0xfe, 0x61, 0x0d, 0xb7, 0x32, 0x44, 0x89, 0xa0, 0x74, 0x0b, 0x53, 0x4f,
    0x55, 0xa4, 0xce, 0x82, 0x62, 0x95, 0xee, 0xeb, 0x59, 0x5f, 0xc6, 0xe1,
    0x05, 0x80, 0x12, 0xc4, 0x5e, 0x94, 0x3f, 0xbc, 0x5b, 0x48, 0x38, 0xf4,
    0x53, 0xf7, 0x24, 0xe6, 0xfb, 0x91, 0xe9, 0x15, 0xc4, 0xcf, 0xf4, 0x53,
    0x0d, 0xf4, 0x4a, 0xfc, 0x9f, 0x54, 0xde, 0x7d, 0xbe, 0xa0, 0x6b, 0x6f,
    0x87, 0xc0, 0xd0, 0x50, 0x1f, 0x28, 0x30, 0x03, 0x40, 0xda, 0x08, 0x73,
    0x51, 0x6c, 0x7f, 0xff, 0x3a, 0x3c, 0xa7, 0x37, 0x06, 0x8e, 0xbd, 0x4b,
    0x11, 0x04, 0xeb, 0x7d, 0x24, 0xde, 0xe6, 0xf9, 0xfc, 0x31, 0x71, 0xfb,
    0x94, 0xd5, 0x60, 0xf3, 0x2e, 0x4a, 0xaf, 0x42, 0xd2, 0xcb, 0xea, 0xc4,
    0x6a, 0x1a, 0xb2, 0xcc, 0x53, 0xdd, 0x15, 0x4b, 0x8b, 0x1f, 0xc8, 0x19,
    0x61, 0x1f, 0xcd, 0x9d, 0xa8, 0x3e, 0x63, 0x2b, 0x84, 0x35, 0x69, 0x65,
    0x84, 0xc8, 0x19, 0xc5, 0x46, 0x22, 0xf8, 0x53, 0x95, 0xbe, 0xe3, 0x80,
    0x4a, 0x10, 0xc6, 0x2a, 0xec, 0xba, 0x97, 0x20, 0x11, 0xc7, 0x39, 0x99,
    0x10, 0x04, 0xa0, 0xf0, 0x61, 0x7a, 0x95, 0x25, 0x8c, 0x4e, 0x52, 0x75,
    0xe2, 0xb6, 0xed, 0x08, 0xca, 0x14, 0xfc, 0xce, 0x22, 0x6a, 0xb3, 0x4e,
    0xcf, 0x46, 0x03, 0x97, 0x97, 0x03, 0x7e, 0xc0, 0xb1, 0xde, 0x7b, 0xaf,
    0x45, 0x33, 0xcf, 0xba, 0x3e, 0x71, 0xb7, 0xde, 0xf4, 0x25, 0x25, 0xc2,
    0x0d, 0x35, 0x89, 0x9d, 0x9d, 0xfb, 0x0e, 0x11, 0x79, 0x89, 0x1e, 0x37,
    0xc5, 0xaf, 0x8e, 0x72, 0x69, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x81,
    0xe7, 0x30, 0x81, 0xe4, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04,
    0x18, 0x30, 0x16, 0x80, 0x14, 0xc0, 0x7a, 0x98, 0x68, 0x8d, 0x89, 0xfb,
    0xab, 0x05, 0x64, 0x0c, 0x11, 0x7d, 0xaa, 0x7d, 0x65, 0xb8, 0xca, 0xcc,
    0x4e, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14,
    0x4a, 0xdd, 0x06, 0x16, 0x1b, 0xbc, 0xf6, 0x68, 0xb5, 0x76, 0xf5, 0x81,
    0xb6, 0xbb, 0x62, 0x1a, 0xba, 0x5a, 0x81, 0x2f, 0x30, 0x0e, 0x06, 0x03,
    0x55, 0x1d, 0x0f, 0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x01, 0x06,
    0x30, 0x2e, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01,
    0x04, 0x22, 0x30, 0x20, 0x30, 0x1e, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05,
    0x05, 0x07, 0x30, 0x01, 0x86, 0x12, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f,
    0x2f, 0x67, 0x2e, 0x73, 0x79, 0x6d, 0x63, 0x64, 0x2e, 0x63, 0x6f, 0x6d,
    0x30, 0x12, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x08,
    0x30, 0x06, 0x01, 0x01, 0xff, 0x02, 0x01, 0x00, 0x30, 0x35, 0x06, 0x03,
    0x55, 0x1d, 0x1f, 0x04, 0x2e, 0x30, 0x2c, 0x30, 0x2a, 0xa0, 0x28, 0xa0,
    0x26, 0x86, 0x24, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x67, 0x2e,
    0x73, 0x79, 0x6d, 0x63, 0x62, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x63, 0x72,
    0x6c, 0x73, 0x2f, 0x67, 0x74, 0x67, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x2e,
    0x63, 0x72, 0x6c, 0x30, 0x17, 0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x10,
    0x30, 0x0e, 0x30, 0x0c, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 0x01, 0xd6,
    0x79, 0x02, 0x05, 0x01, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
    0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00,
    0xaa, 0xfa, 0xa9, 0x20, 0xcd, 0x6a, 0x67, 0x83, 0xed, 0x5e, 0xd4, 0x7e,
    0xde, 0x1d, 0xc4, 0x7f, 0xe0, 0x25, 0x06, 0x00, 0xc5, 0x24, 0xfb, 0xa9,
    0xc8, 0x2d, 0x6d, 0x7e, 0xde, 0x9d, 0x82, 0x65, 0x2c, 0x81, 0x63, 0x34,
    0x66, 0x3e, 0xe9, 0x52, 0xc2, 0x08, 0xb4, 0xcb, 0x2f, 0xf7, 0x5f, 0x99,
    0x3a, 0x6a, 0x9c, 0x50, 0x7a, 0x85, 0x05, 0x8c, 0x7d, 0xd1, 0x2a, 0x48,
    0x84, 0xd3, 0x09, 0x6c, 0x7c, 0xc2, 0xcd, 0x35, 0x9f, 0xf3, 0x82, 0xee,
    0x52, 0xde, 0x68, 0x5f, 0xe4, 0x00, 0x8a, 0x17, 0x20, 0x96, 0xf7, 0x29,
    0x8d, 0x9a, 0x4d, 0xcb, 0xa8, 0xde, 0x86, 0xc8, 0x0d, 0x6f, 0x56, 0x87,
    0x03, 0x7d, 0x03, 0x3f, 0xdc, 0xfa, 0x79, 0x7d, 0x21, 0x19, 0xf9, 0xc8,
    0x3a, 0x2f, 0x51, 0x76, 0x8c, 0xc7, 0x41, 0x92, 0x71, 0x8f, 0x25, 0xce,
    0x37, 0xf8, 0x4a, 0x4c, 0x00, 0x23, 0xef, 0xc4, 0x35, 0x10, 0xae, 0xe0,
    0x23, 0x80, 0x73, 0x7c, 0x4d, 0x34, 0x2e, 0xc8, 0x6e, 0x90, 0xd6, 0x10,
    0x1e, 0x99, 0x84, 0x73, 0x1a, 0x70, 0xf2, 0xed, 0x55, 0x0e, 0xee, 0x17,
    0x06, 0xea, 0x67, 0xee, 0x32, 0xeb, 0x2c, 0xdd, 0x67, 0x07, 0x3f, 0xf6,
    0x8b, 0xc2, 0x70, 0xde, 0x5b, 0x00, 0xe6, 0xbb, 0x1b, 0xd3, 0x36, 0x1a,
    0x22, 0x6c, 0x6c, 0xb0, 0x35, 0x42, 0x6c, 0x90, 0x09, 0x3d, 0x93, 0xe9,
    0x64, 0x09, 0x22, 0x0e, 0x85, 0x06, 0x9f, 0xc2, 0x73, 0x21, 0xd3, 0xe6,
    0x5f, 0x80, 0xe4, 0x8d, 0x85, 0x22, 0x3a, 0x73, 0x03, 0xb1, 0x60, 0x8e,
    0xae, 0x68, 0xe2, 0xf4, 0x3e, 0x97, 0xe7, 0x60, 0x12, 0x09, 0x68, 0x36,
    0xde, 0x3a, 0xd6, 0xe2, 0x43, 0x95, 0x5b, 0x37, 0x81, 0x92, 0x81, 0x1f,
    0xbb, 0x8d, 0xd7, 0xad, 0x52, 0x64, 0x16, 0x57, 0x96, 0xd9, 0x5e, 0x34,
    0x7e, 0xc8, 0x35, 0xd8,
};

TEST(CommonCertSets, FindGIA_1) {
  StringPiece gia(reinterpret_cast<const char*>(kGIACertificate1),
                  sizeof(kGIACertificate1));

  const CommonCertSets* sets(CommonCertSets::GetInstanceQUIC());
  // Common Cert Set 1's hash.
  const uint64_t in_hash = UINT64_C(0xff715ce4e7e9267b);
  uint64_t hash;
  uint32_t index;
  ASSERT_TRUE(sets->MatchCert(
      gia,
      StringPiece(reinterpret_cast<const char*>(&in_hash), sizeof(in_hash)),
      &hash, &index));
  EXPECT_EQ(in_hash, hash);

  StringPiece gia_copy = sets->GetCert(hash, index);
  EXPECT_FALSE(gia_copy.empty());
  ASSERT_EQ(gia.size(), gia_copy.size());
  EXPECT_EQ(0, memcmp(gia.data(), gia_copy.data(), gia.size()));
}

TEST(CommonCertSets, FindGIA_2) {
  StringPiece gia(reinterpret_cast<const char*>(kGIACertificate2),
                  sizeof(kGIACertificate2));

  const CommonCertSets* sets(CommonCertSets::GetInstanceQUIC());
  // Common Cert Set 2's hash.
  const uint64_t in_hash = UINT64_C(0xe81a92926081e801);
  uint64_t hash;
  uint32_t index;
  ASSERT_TRUE(sets->MatchCert(
      gia,
      StringPiece(reinterpret_cast<const char*>(&in_hash), sizeof(in_hash)),
      &hash, &index));
  EXPECT_EQ(in_hash, hash);

  StringPiece gia_copy = sets->GetCert(hash, index);
  EXPECT_FALSE(gia_copy.empty());
  ASSERT_EQ(gia.size(), gia_copy.size());
  EXPECT_EQ(0, memcmp(gia.data(), gia_copy.data(), gia.size()));
}

TEST(CommonCertSets, NonMatch) {
  const CommonCertSets* sets(CommonCertSets::GetInstanceQUIC());
  StringPiece not_a_cert("hello");
  const uint64_t in_hash = UINT64_C(0xc9fef74053f99f39);
  uint64_t hash;
  uint32_t index;
  EXPECT_FALSE(sets->MatchCert(
      not_a_cert,
      StringPiece(reinterpret_cast<const char*>(&in_hash), sizeof(in_hash)),
      &hash, &index));
}

}  // namespace test
}  // namespace net
