#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res_code = OK;
  if (rows < 1 || columns < 1) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
    } else {
      res_code = ERROR_OR_INCORRECT_MATRIX;
    }
  }
  return res_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res_code = EQ_SUCCESS;
  if (!A || !A->matrix || !B || !B->matrix || A->rows != B->rows ||
      A->columns != B->columns) {
    res_code = EQ_FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          res_code = EQ_FAILURE;
        }
      }
    }
  }
  return res_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !B || !B->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res_code = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !B || !B->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res_code = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !B || !B->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res_code = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res_code = CALCULATION_ERROR;
  } else {
    int res_code = s21_create_matrix(A->columns, A->rows, result);
    if (res_code == OK) {
      matrix_t minor_matrix;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_matrix(A->columns - 1, A->rows - 1, &minor_matrix);
          get_minor(A, &minor_matrix, i, j);

          double minor_det = 0.0;
          s21_determinant(&minor_matrix, &minor_det);
          result->matrix[i][j] = pow(-1, i + j) * minor_det;
          s21_remove_matrix(&minor_matrix);
        }
      }
    }
  }
  return res_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int res_code = OK;
  if (!A || !A->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res_code = CALCULATION_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 0.0;
    matrix_t minor;
    for (int i = 0; i < A->columns; i++) {
      double det = 0;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      get_minor(A, &minor, 0, i);
      s21_determinant(&minor, &det);
      *result += A->matrix[0][i] * pow(-1, i) * det;

      s21_remove_matrix(&minor);
    }
  }
  return res_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res_code = OK;
  if (!A || !A->matrix || !result) {
    res_code = ERROR_OR_INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res_code = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det) > EPS) {
      matrix_t tmp_matrix_1, tmp_matrix_2;
      s21_calc_complements(A, &tmp_matrix_1);
      s21_transpose(&tmp_matrix_1, &tmp_matrix_2);
      s21_mult_number(&tmp_matrix_2, 1.0 / det, result);

      s21_remove_matrix(&tmp_matrix_1);
      s21_remove_matrix(&tmp_matrix_2);

    } else {
      res_code = CALCULATION_ERROR;
    }
  }
  return res_code;
}

void get_minor(matrix_t *A, matrix_t *minor, int row, int col) {
  int m_row = 0, m_col = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    m_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;

      minor->matrix[m_row][m_col] = A->matrix[i][j];
      m_col++;
    }
    m_row++;
  }
}