#include <check.h>

#include "../s21_matrix.h"

START_TEST(test_create_matrix_1) {
  matrix_t A;
  int res = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_2) {
  matrix_t A;
  int res = s21_create_matrix(5, 10, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_3) {
  matrix_t A;
  int res = s21_create_matrix(0, 5, &A);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_4) {
  matrix_t A;
  int res = s21_create_matrix(7, -5, &A);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_remove_matrix) {
  matrix_t A;
  int rows = 5, cols = 5;

  int res = s21_create_matrix(rows, cols, &A);
  if (res == OK) {
    s21_remove_matrix(&A);
    ck_assert_ptr_eq(A.matrix, NULL);
    ck_assert_int_eq(A.rows, 0);
    ck_assert_int_eq(A.columns, 0);
  }
}

START_TEST(test_eq_matrix_1) {
  matrix_t A, B;
  int rows = 10, cols = 5;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);

  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_2) {
  matrix_t A, B;
  int rows = 6, cols = 6;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = rows + cols - i - j;
      B.matrix[i][j] = rows + cols - i - j;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_3) {
  matrix_t A, B;
  int rows = 9, cols = 3;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j + 1;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, EQ_FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_4) {
  matrix_t A, B;
  int rows1 = 9, cols1 = 3;
  int rows2 = 3, cols2 = 9;
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);

  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, EQ_FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_1) {
  matrix_t A, B, C, D;
  int rows = 3, cols = 5;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &C);

  double count = 0.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
      count = count + 1.0;
    }
  }
  int res_sum = s21_sum_matrix(&A, &B, &D);
  int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res_sum, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t A, B, C;
  A.matrix = NULL;
  s21_create_matrix(2, 6, &B);

  int res = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_3) {
  matrix_t A, B, C;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 3, &B);

  int res = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_1) {
  matrix_t A, B, C, D;
  int rows = 4, cols = 6;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &C);

  double count = 0.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
      count++;
    }
  }
  int res_sum = s21_sub_matrix(&A, &B, &D);
  int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res_sum, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t A, B, C;
  s21_create_matrix(4, 8, &A);
  B.matrix = NULL;

  int res = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_3) {
  matrix_t A, B, C;
  s21_create_matrix(6, 5, &A);
  s21_create_matrix(6, 6, &B);

  int res = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_1) {
  matrix_t A, B, C;
  int rows = 5, cols = 5;
  double number = 3.2;

  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  int res_mult_num = s21_mult_number(&A, number, &C);
  int res_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res_mult_num, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t A, B, C;
  int rows = 4, cols = 9;
  double number = 5.0;

  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);

  int res_mult_num = s21_mult_number(&A, number, &C);
  int res_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res_mult_num, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_number_3) {
  matrix_t A, B;
  A.matrix = NULL;
  double number = 5.2;

  int res = s21_mult_number(&A, number, &B);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_matrix_1) {
  matrix_t A, B, C, D;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(2, 3, &C);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j + 1.0;
    }
  }

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = i * j + 1.0;
    }
  }

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int k = 0; k < A.columns; k++) {
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  int res_mult = s21_mult_matrix(&A, &B, &D);
  int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res_mult, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A, B, C, D;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &D);

  int res_mult = s21_mult_matrix(&A, &B, &C);
  int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res_mult, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_mult_matrix_3) {
  matrix_t A, B, C;
  s21_create_matrix(3, 5, &A);
  s21_create_matrix(6, 3, &B);

  int res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_4) {
  matrix_t A, B, C;
  s21_create_matrix(4, 6, &A);
  B.matrix = NULL;

  int res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 6, &A);
  s21_create_matrix(6, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j + 1.0;
      B.matrix[j][i] = i + j + 1.0;
    }
  }

  int res_trans = s21_transpose(&A, &C);
  int res_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res_trans, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}

START_TEST(test_transpose_2) {
  matrix_t A, B, C;
  s21_create_matrix(7, 7, &A);
  s21_create_matrix(7, 7, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j + 1.0;
      B.matrix[j][i] = i + j + 1.0;
    }
  }

  int res_trans = s21_transpose(&A, &C);
  int res_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res_trans, OK);
  ck_assert_int_eq(res_eq, EQ_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}

START_TEST(test_transpose_3) {
  matrix_t A, B;
  A.matrix = NULL;

  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, ERROR_OR_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], 0);
  ck_assert_int_eq(B.matrix[0][1], 10);
  ck_assert_int_eq(B.matrix[0][2], -20);
  ck_assert_int_eq(B.matrix[1][0], 4);
  ck_assert_int_eq(B.matrix[1][1], -14);
  ck_assert_int_eq(B.matrix[1][2], 8);
  ck_assert_int_eq(B.matrix[2][0], -8);
  ck_assert_int_eq(B.matrix[2][1], -2);
  ck_assert_int_eq(B.matrix[2][2], 4);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;

  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], -12);
  ck_assert_int_eq(B.matrix[0][1], 20);
  ck_assert_int_eq(B.matrix[0][2], -2);
  ck_assert_int_eq(B.matrix[1][0], 0);
  ck_assert_int_eq(B.matrix[1][1], 0);
  ck_assert_int_eq(B.matrix[1][2], 0);
  ck_assert_int_eq(B.matrix[2][0], 12);
  ck_assert_int_eq(B.matrix[2][1], -20);
  ck_assert_int_eq(B.matrix[2][2], 2);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t A, B;
  s21_create_matrix(4, 3, &A);

  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_1) {
  matrix_t A;
  double det = 0.0;

  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j + 1.0;
    }
  }

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(det, 0);
  s21_remove_matrix(&A);
}

START_TEST(test_determinant_2) {
  matrix_t A;
  double det = 0.0;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = -2;
  A.matrix[0][3] = 6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -10;
  A.matrix[1][2] = 5;
  A.matrix[1][3] = -3;
  A.matrix[2][0] = 4;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = -1;
  A.matrix[2][3] = 2;
  A.matrix[3][0] = 7;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = -4;
  A.matrix[3][3] = 1;

  int res = s21_determinant(&A, &det);
  ck_assert_double_eq(det, 858);
  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A;
  double det = 0.0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(det, 5);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4) {
  matrix_t A;
  double det = 0.0;
  s21_create_matrix(3, 5, &A);

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}

START_TEST(test_inverse_matrix_1) {
  matrix_t A, B;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(B.matrix[0][0], 1);
  ck_assert_int_eq(B.matrix[0][1], -1);
  ck_assert_int_eq(B.matrix[0][2], 1);
  ck_assert_int_eq(B.matrix[1][0], -38);
  ck_assert_int_eq(B.matrix[1][1], 41);
  ck_assert_int_eq(B.matrix[1][2], -34);
  ck_assert_int_eq(B.matrix[2][0], 27);
  ck_assert_int_eq(B.matrix[2][1], -29);
  ck_assert_int_eq(B.matrix[2][2], 24);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A, B;

  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j + 1.0;
    }
  }

  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_inverse_matrix_3) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);

  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_matrix");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_create_matrix_1);
  tcase_add_test(tc_core, test_create_matrix_2);
  tcase_add_test(tc_core, test_create_matrix_3);
  tcase_add_test(tc_core, test_create_matrix_4);

  tcase_add_test(tc_core, test_remove_matrix);

  tcase_add_test(tc_core, test_eq_matrix_1);
  tcase_add_test(tc_core, test_eq_matrix_2);
  tcase_add_test(tc_core, test_eq_matrix_3);
  tcase_add_test(tc_core, test_eq_matrix_4);

  tcase_add_test(tc_core, test_sum_matrix_1);
  tcase_add_test(tc_core, test_sum_matrix_2);
  tcase_add_test(tc_core, test_sum_matrix_3);

  tcase_add_test(tc_core, test_sub_matrix_1);
  tcase_add_test(tc_core, test_sub_matrix_2);
  tcase_add_test(tc_core, test_sub_matrix_3);

  tcase_add_test(tc_core, test_mult_number_1);
  tcase_add_test(tc_core, test_mult_number_2);
  tcase_add_test(tc_core, test_mult_number_3);

  tcase_add_test(tc_core, test_mult_matrix_1);
  tcase_add_test(tc_core, test_mult_matrix_2);
  tcase_add_test(tc_core, test_mult_matrix_3);
  tcase_add_test(tc_core, test_mult_matrix_4);

  tcase_add_test(tc_core, test_transpose_1);
  tcase_add_test(tc_core, test_transpose_2);
  tcase_add_test(tc_core, test_transpose_3);

  tcase_add_test(tc_core, test_calc_complements_1);
  tcase_add_test(tc_core, test_calc_complements_2);
  tcase_add_test(tc_core, test_calc_complements_3);

  tcase_add_test(tc_core, test_determinant_1);
  tcase_add_test(tc_core, test_determinant_2);
  tcase_add_test(tc_core, test_determinant_3);
  tcase_add_test(tc_core, test_determinant_4);

  tcase_add_test(tc_core, test_inverse_matrix_1);
  tcase_add_test(tc_core, test_inverse_matrix_2);
  tcase_add_test(tc_core, test_inverse_matrix_3);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_decimal_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}