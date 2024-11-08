#define NUMPIXELS 120

const int digitSegments[10][29] = {
  //0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0 },  // 0
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },  // 1
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },  // 2
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },  // 3
  { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1 },  // 4
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1 },  // 5
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },  // 6
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },  // 8
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1 }   // 9
};

const int digit = 29;
const int coron_number = 4;
const int coron_digits[digit]= {58, 59, 60 ,61};