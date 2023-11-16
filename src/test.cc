#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructors, DefaultConstructor) {
  S21Matrix matrix_1;
  S21Matrix matrix_2;
  matrix_1.SetRows(5);
  matrix_1.SetCols(5);

  ASSERT_NO_THROW(S21Matrix matrix_1);
  ASSERT_NO_THROW(S21Matrix matrix_2);

  ASSERT_TRUE(matrix_2.CheckNullptr() == 1);

  ASSERT_EQ(5, matrix_1.GetRows());
  ASSERT_EQ(5, matrix_1.GetCols());
  ASSERT_EQ(0, matrix_2.GetCols());
  ASSERT_EQ(0, matrix_2.GetCols());

  for (int i = 0; i < matrix_1.GetRows(); i++) {
    for (int j = 0; j < matrix_1.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(0.0, matrix_1(i, j));
    }
  }
}

TEST(Constructors, ParametrConstructor1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);

  ASSERT_NO_THROW(S21Matrix matrix_1);
  ASSERT_NO_THROW(S21Matrix matrix_2);

  ASSERT_EQ(matrix_1.GetRows(), matrix_2.GetRows());
  ASSERT_EQ(2, matrix_1.GetRows());
  ASSERT_EQ(2, matrix_2.GetRows());

  ASSERT_EQ(matrix_1.GetCols(), matrix_2.GetCols());
  ASSERT_EQ(2, matrix_1.GetCols());
  ASSERT_EQ(2, matrix_2.GetCols());

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(0.0, matrix_1(i, j));
      ASSERT_DOUBLE_EQ(0.0, matrix_2(i, j));
      ASSERT_DOUBLE_EQ(matrix_1(i, j), matrix_2(i, j));
    }
  }
}

// тест, который дает лики
TEST(Constructors, ParametrConstructor2) {
  EXPECT_THROW(S21Matrix matrix_1(0, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix matrix_2(-10, 2), std::invalid_argument);
}

TEST(Constructors, CopyConstructor) {
  S21Matrix matrix_1(2, 3);
  S21Matrix matrix_2(5, 5);
  matrix_1.FillMatrix(1.0);
  matrix_2.FillMatrix(2.0);

  S21Matrix matrix_3(matrix_1);
  S21Matrix matrix_4(matrix_2);

  ASSERT_NO_THROW(S21Matrix matrix_1);
  ASSERT_NO_THROW(S21Matrix matrix_2);

  ASSERT_EQ(matrix_1.GetRows(), matrix_3.GetRows());
  ASSERT_EQ(2, matrix_1.GetRows());
  ASSERT_EQ(2, matrix_3.GetRows());
  ASSERT_EQ(3, matrix_1.GetCols());
  ASSERT_EQ(3, matrix_3.GetCols());

  ASSERT_EQ(matrix_2.GetRows(), matrix_4.GetRows());
  ASSERT_EQ(5, matrix_2.GetRows());
  ASSERT_EQ(5, matrix_4.GetRows());
  ASSERT_EQ(5, matrix_2.GetCols());
  ASSERT_EQ(5, matrix_4.GetCols());

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(1.0, matrix_1(i, j));
      ASSERT_DOUBLE_EQ(1.0, matrix_3(i, j));
      ASSERT_DOUBLE_EQ(matrix_1(i, j), matrix_3(i, j));
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(2.0, matrix_2(i, j));
      ASSERT_DOUBLE_EQ(2.0, matrix_4(i, j));
      ASSERT_DOUBLE_EQ(matrix_2(i, j), matrix_4(i, j));
    }
  }
}

TEST(Constructors, MoveConstructor) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(2, 5);
  matrix_1.FillMatrix(1.0);
  matrix_2.FillMatrix(2.0);

  ASSERT_NO_THROW(S21Matrix matrix_1);
  ASSERT_NO_THROW(S21Matrix matrix_2);

  S21Matrix matrix_3(std::move(matrix_1));
  S21Matrix matrix_4(std::move(matrix_2));

  ASSERT_EQ(0, matrix_1.GetRows());
  ASSERT_EQ(0, matrix_1.GetCols());
  ASSERT_EQ(0, matrix_2.GetRows());
  ASSERT_EQ(0, matrix_2.GetCols());

  ASSERT_TRUE(matrix_1.CheckNullptr() == 1);
  ASSERT_TRUE(matrix_2.CheckNullptr() == 1);

  ASSERT_EQ(3, matrix_3.GetRows());
  ASSERT_EQ(3, matrix_3.GetCols());
  ASSERT_EQ(2, matrix_4.GetRows());
  ASSERT_EQ(5, matrix_4.GetCols());

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(1.0, matrix_3(i, j));
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(2.0, matrix_4(i, j));
    }
  }
}

TEST(Operators, Operatorplus1) {
  S21Matrix matrix_1(5, 5);
  S21Matrix matrix_2(5, 5);
  S21Matrix matrix_3(5, 5);

  matrix_1.FillMatrix(2.0);
  matrix_2.FillMatrix(3.0);
  matrix_3.FillMatrix(5.0);

  matrix_1 = matrix_1 + matrix_2;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_1(i, j));
    }
  }
}

//  тест, который дает лики
TEST(Operators, Operatorplus2) {
  S21Matrix matrix_1;
  S21Matrix matrix_2(2, 9);

  EXPECT_THROW((matrix_1 = matrix_1 + matrix_2), std::logic_error);
}

TEST(Operators, Operatorminus1) {
  S21Matrix matrix_1(5, 5);
  S21Matrix matrix_2(5, 5);
  S21Matrix matrix_3(5, 5);

  matrix_1.FillMatrix(5.0);
  matrix_2.FillMatrix(3.0);
  matrix_3.FillMatrix(2.0);

  matrix_1 = matrix_1 - matrix_2;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_1(i, j));
    }
  }
}

//  тест, который дает лики
TEST(Operators, Operatorminus2) {
  S21Matrix matrix_1;
  S21Matrix matrix_2(7, 2);

  EXPECT_THROW((matrix_1 = matrix_1 - matrix_2), std::logic_error);
}

TEST(Operators, Operatormulmatrix1) {
  S21Matrix matrix_1(4, 3);
  S21Matrix matrix_2(3, 2);
  S21Matrix matrix_3(4, 2);

  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(0, 2) = 3.0;
  matrix_1(1, 0) = 4.0;
  matrix_1(1, 1) = 5.0;
  matrix_1(1, 2) = 6.0;
  matrix_1(2, 0) = 7.0;
  matrix_1(2, 1) = 8.0;
  matrix_1(2, 2) = 9.0;
  matrix_1(3, 0) = 10.0;
  matrix_1(3, 1) = 11.0;
  matrix_1(3, 2) = 12.0;

  matrix_2(0, 0) = 13.0;
  matrix_2(0, 1) = 14.0;
  matrix_2(1, 0) = 15.0;
  matrix_2(1, 1) = 16.0;
  matrix_2(2, 0) = 17.0;
  matrix_2(2, 1) = 18.0;

  matrix_3(0, 0) = 94.0;
  matrix_3(0, 1) = 100.0;
  matrix_3(1, 0) = 229.0;
  matrix_3(1, 1) = 244.0;
  matrix_3(2, 0) = 364.0;
  matrix_3(2, 1) = 388.0;
  matrix_3(3, 0) = 499.0;
  matrix_3(3, 1) = 532.0;

  matrix_1 = matrix_1 * matrix_2;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix_1(i, j), matrix_3(i, j));
      ASSERT_TRUE(matrix_1(i, j) == matrix_3(i, j));
    }
  }
}

TEST(Operators, Operatormulmatrix2) {
  S21Matrix matrix_1(1, 8);
  S21Matrix matrix_2(2, 3);

  EXPECT_THROW(matrix_1 = matrix_1 * matrix_2, std::logic_error);
}

TEST(Operators, Brackets1) {
  S21Matrix const matrix(5, 5);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(0.0, matrix(i, j));
    }
  }
}

TEST(Operators, Brackets2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix const matrix_2(2, 2);

  EXPECT_THROW(matrix_1(0, 2), std::range_error);
  EXPECT_THROW(matrix_2(1, -2), std::range_error);
}

TEST(Operators, CopyOperator) {
  S21Matrix matrix_1(5, 5);
  S21Matrix matrix_2;

  matrix_1.FillMatrix(5.0);

  matrix_2 = matrix_1;

  ASSERT_EQ(matrix_1.GetRows(), matrix_2.GetRows());
  ASSERT_EQ(matrix_1.GetCols(), matrix_2.GetCols());

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(matrix_1(i, j), matrix_2(i, j));
    }
  }
}

TEST(Mutator, Mutator1) {
  S21Matrix matrix_1;
  S21Matrix matrix_2(3, 3);
  S21Matrix matrix_3(3, 3);

  matrix_2.FillMatrix(1.0);
  matrix_3.FillMatrix(1.0);

  matrix_1.SetCols(5);
  matrix_1.SetRows(5);
  matrix_2.SetCols(2);
  matrix_2.SetRows(2);
  matrix_3.SetCols(4);
  matrix_3.SetRows(4);

  ASSERT_EQ(5, matrix_1.GetCols());
  ASSERT_EQ(5, matrix_1.GetRows());
  ASSERT_EQ(matrix_1.GetCols(), matrix_1.GetRows());

  ASSERT_EQ(2, matrix_2.GetRows());
  ASSERT_EQ(2, matrix_2.GetCols());
  ASSERT_EQ(matrix_2.GetCols(), matrix_2.GetRows());

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_DOUBLE_EQ(0.0, matrix_1(i, j));
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(1.0, matrix_2(i, j));
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(1.0, matrix_3(i, j));
    }
  }

  for (int i = 0; i < 4; i++) {
    ASSERT_DOUBLE_EQ(0.0, matrix_3(i, 3));
    ASSERT_DOUBLE_EQ(0.0, matrix_3(3, i));
  }
}

// тест с ликами
TEST(Mutator, Mutator2) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(3, 3);

  EXPECT_THROW(matrix_1.SetCols(-1), std::logic_error);
  EXPECT_THROW(matrix_1.SetRows(0), std::logic_error);
}

TEST(Comparison, EqualMatrix) {
  S21Matrix matrix_1(2, 3);
  S21Matrix matrix_2(2, 3);
  S21Matrix matrix_3(2, 2);
  S21Matrix matrix_4(2, 2);

  matrix_1.FillMatrix(1.0);
  matrix_2.FillMatrix(3.0);
  matrix_3.FillMatrix(2.0);
  matrix_4.FillMatrix(2.0);

  ASSERT_TRUE(matrix_1.EqMatrix(matrix_2) == 0);
  ASSERT_TRUE(matrix_1.EqMatrix(matrix_3) == 0);
  ASSERT_TRUE(matrix_2.EqMatrix(matrix_3) == 0);
  ASSERT_TRUE(matrix_3.EqMatrix(matrix_4) != 0);
}

TEST(Arithmetics, SumMatrix1) {
  S21Matrix matrix_1(4, 2);
  S21Matrix matrix_2(4, 2);
  S21Matrix matrix_3(4, 2);
  S21Matrix matrix_4(4, 2);

  matrix_1.FillMatrix(1.0);
  matrix_2.FillMatrix(2.0);
  matrix_3.FillMatrix(3.0);
  matrix_4.FillMatrix(6.0);

  ASSERT_NO_THROW(matrix_1.SumMatrix(matrix_2));

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(3.0, matrix_1(i, j));
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_1(i, j));
    }
  }

  matrix_3 += matrix_1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(6.0, matrix_3(i, j));
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_4(i, j));
    }
  }

  matrix_4 = matrix_4 + matrix_1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(9.0, matrix_4(i, j));
    }
  }
}

// тест, который дает лики
TEST(Arithmetics, SumMatrix2) {
  S21Matrix matrix_1(4, 2);
  S21Matrix matrix_2(2, 2);

  matrix_1.FillMatrix(1.0);
  matrix_2.FillMatrix(2.0);

  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(Arithmetics, SubMatrix1) {
  S21Matrix matrix_1(3, 8);
  S21Matrix matrix_2(3, 8);
  S21Matrix matrix_3(3, 8);
  S21Matrix matrix_4(3, 8);

  matrix_1.FillMatrix(10.0);
  matrix_2.FillMatrix(2.0);
  matrix_3.FillMatrix(8.0);
  matrix_4.FillMatrix(6.0);

  ASSERT_NO_THROW(matrix_1.SubMatrix(matrix_2));

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      ASSERT_DOUBLE_EQ(8.0, matrix_1(i, j));
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_1(i, j));
    }
  }

  matrix_3 -= matrix_2;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      ASSERT_DOUBLE_EQ(6.0, matrix_3(i, j));
      ASSERT_DOUBLE_EQ(matrix_4(i, j), matrix_3(i, j));
    }
  }

  matrix_3 = matrix_3 - matrix_4;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      ASSERT_DOUBLE_EQ(0.0, matrix_3(i, j));
    }
  }
}

// тест, который дает лики
TEST(Arithmetics, SubMatrix2) {
  S21Matrix matrix_1(4, 2);
  S21Matrix matrix_2(2, 2);

  matrix_1.FillMatrix(10.0);
  matrix_2.FillMatrix(2.0);

  EXPECT_THROW(matrix_1.SubMatrix(matrix_2), std::logic_error);
}

TEST(Arithmetics, MulNumber) {
  S21Matrix matrix(2, 6);
  double num_1 = 2.0, num_2 = 1.5, num_3 = 2.0;

  matrix.FillMatrix(3.0);

  matrix.MulNumber(num_1);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      ASSERT_DOUBLE_EQ(6.0, matrix(i, j));
    }
  }

  matrix.MulNumber(num_2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      ASSERT_DOUBLE_EQ(9.0, matrix(i, j));
    }
  }

  matrix *= num_3;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      ASSERT_DOUBLE_EQ(18.0, matrix(i, j));
    }
  }

  matrix = matrix * num_3;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      ASSERT_DOUBLE_EQ(36.0, matrix(i, j));
    }
  }
}

TEST(Arithmetics, MulMatrix1) {
  S21Matrix matrix_1(2, 3);
  S21Matrix matrix_2(3, 2);
  S21Matrix matrix_3(2, 2);
  S21Matrix matrix_4(2, 3);
  S21Matrix matrix_5(3, 2);
  S21Matrix matrix_6(2, 2);

  matrix_1.FillMatrix(2.0);
  matrix_2.FillMatrix(3.0);
  matrix_3.FillMatrix(18.0);

  matrix_4(0, 0) = 1.0;
  matrix_4(0, 1) = 2.0;
  matrix_4(0, 2) = 3.0;
  matrix_4(1, 0) = 4.0;
  matrix_4(1, 1) = 5.0;
  matrix_4(1, 2) = 6.0;

  matrix_5(0, 0) = 7.0;
  matrix_5(0, 1) = 8.0;
  matrix_5(1, 0) = 9.0;
  matrix_5(1, 1) = 10.0;
  matrix_5(2, 0) = 11.0;
  matrix_5(2, 1) = 12.0;

  matrix_6(0, 0) = 58.0;
  matrix_6(0, 1) = 64.0;
  matrix_6(1, 0) = 139.0;
  matrix_6(1, 1) = 154.0;

  ASSERT_NO_THROW(matrix_1.MulMatrix(matrix_2));

  ASSERT_EQ(matrix_3.GetRows(), matrix_1.GetRows());
  ASSERT_EQ(matrix_3.GetCols(), matrix_1.GetCols());

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_1(i, j));
      ASSERT_DOUBLE_EQ(18.0, matrix_1(i, j));
    }
  }

  matrix_4 *= matrix_5;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix_6(i, j), matrix_4(i, j));
    }
  }
}

// тест, который дает лики
TEST(Arithmetics, MulMatrix2) {
  S21Matrix matrix_1(2, 7);
  S21Matrix matrix_2(2, 7);

  EXPECT_THROW(matrix_1.MulMatrix(matrix_2), std::logic_error);
}

TEST(Transpose, Transpose) {
  S21Matrix matrix_1(2, 4);
  S21Matrix matrix_2(4, 2);
  S21Matrix matrix_3(3, 2);
  S21Matrix matrix_4(2, 3);

  matrix_3(0, 0) = 1.0;
  matrix_3(0, 1) = 2.0;
  matrix_3(1, 0) = 3.0;
  matrix_3(1, 1) = 4.0;
  matrix_3(2, 0) = 5.0;
  matrix_3(2, 1) = 6.0;

  matrix_4(0, 0) = 1.0;
  matrix_4(0, 1) = 3.0;
  matrix_4(0, 2) = 5.0;
  matrix_4(1, 0) = 2.0;
  matrix_4(1, 1) = 4.0;
  matrix_4(1, 2) = 6.0;

  S21Matrix matrix_5 = matrix_1.Transpose();
  S21Matrix matrix_6 = matrix_3.Transpose();

  ASSERT_EQ(matrix_2.GetRows(), matrix_5.GetRows());
  ASSERT_EQ(matrix_2.GetCols(), matrix_5.GetCols());
  ASSERT_EQ(4, matrix_5.GetRows());
  ASSERT_EQ(2, matrix_5.GetCols());
  ASSERT_EQ(matrix_4.GetRows(), matrix_6.GetRows());
  ASSERT_EQ(matrix_4.GetCols(), matrix_6.GetCols());
  ASSERT_EQ(2, matrix_6.GetRows());
  ASSERT_EQ(3, matrix_6.GetCols());

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix_2(i, j), matrix_5(i, j));
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(matrix_4(i, j), matrix_6(i, j));
    }
  }
}

TEST(Determinant, Determinant1) {
  S21Matrix matrix_1(1, 1);
  S21Matrix matrix_2(2, 2);
  S21Matrix matrix_3(4, 4);
  S21Matrix matrix_4(4, 4);
  S21Matrix matrix_5(4, 4);
  double det_1 = 0.0, det_2 = 0.0, det_3 = 0.0, det_4 = 0.0, det_5 = 0.0;

  matrix_1.FillMatrix(-12.0);

  matrix_2(0, 0) = 5.0;
  matrix_2(0, 1) = 3.0;
  matrix_2(1, 0) = 2.0;
  matrix_2(1, 1) = 8.0;

  matrix_3.FillMatrix(2.0);

  matrix_4(0, 0) = 1.8;
  matrix_4(0, 1) = 7.9;
  matrix_4(0, 2) = 5.0;
  matrix_4(0, 3) = 1.9;
  matrix_4(1, 0) = 87.0;
  matrix_4(1, 1) = 7.0;
  matrix_4(1, 2) = 6.9;
  matrix_4(1, 3) = 8.1;
  matrix_4(2, 0) = 6.2;
  matrix_4(2, 1) = 13.8;
  matrix_4(2, 2) = 11.5;
  matrix_4(2, 3) = -18.0;
  matrix_4(3, 0) = -2.0;
  matrix_4(3, 1) = 23.8;
  matrix_4(3, 2) = 7.7;
  matrix_4(3, 3) = 7.5;

  det_1 = matrix_1.Determinant();
  det_2 = matrix_2.Determinant();
  det_3 = matrix_3.Determinant();
  det_4 = matrix_4.Determinant();
  det_5 = matrix_5.Determinant();

  ASSERT_DOUBLE_EQ(-12.0, det_1);
  ASSERT_DOUBLE_EQ(34.0, det_2);
  ASSERT_DOUBLE_EQ(0.0, det_3);
  ASSERT_DOUBLE_EQ(99717.2406, det_4);
  ASSERT_DOUBLE_EQ(0.0, det_5);
}

//  тест, который дает лики
TEST(Determinant, Determinant2) {
  S21Matrix matrix(1, 8);
  double det = 0.0;

  EXPECT_THROW(matrix.Determinant(), std::logic_error);
  ASSERT_DOUBLE_EQ(0.0, det);
}

TEST(Complement, CalcComplement1) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(3, 3);
  S21Matrix matrix_3(3, 3);

  S21Matrix matrix_4(4, 4);
  S21Matrix matrix_5(4, 4);
  S21Matrix matrix_6;

  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(0, 2) = 3.0;
  matrix_1(1, 0) = 0.0;
  matrix_1(1, 1) = 4.0;
  matrix_1(1, 2) = 2.0;
  matrix_1(2, 0) = 5.0;
  matrix_1(2, 1) = 2.0;
  matrix_1(2, 2) = 1.0;

  matrix_4(0, 0) = 2.0;
  matrix_4(0, 1) = 6.0;
  matrix_4(0, 2) = 5.0;
  matrix_4(0, 3) = 4.0;
  matrix_4(1, 0) = 9.0;
  matrix_4(1, 1) = 8.0;
  matrix_4(1, 2) = 6.0;
  matrix_4(1, 3) = 4.0;
  matrix_4(2, 0) = 0.0;
  matrix_4(2, 1) = 7.0;
  matrix_4(2, 2) = 0.0;
  matrix_4(2, 3) = -1.0;
  matrix_4(3, 0) = 4.0;
  matrix_4(3, 1) = -9.0;
  matrix_4(3, 2) = 7.0;
  matrix_4(3, 3) = 1.0;

  matrix_3(0, 0) = 0.0;
  matrix_3(0, 1) = 10.0;
  matrix_3(0, 2) = -20.0;
  matrix_3(1, 0) = 4.0;
  matrix_3(1, 1) = -14.0;
  matrix_3(1, 2) = 8.0;
  matrix_3(2, 0) = -8.0;
  matrix_3(2, 1) = -2.0;
  matrix_3(2, 2) = 4.0;

  matrix_5(0, 0) = 264.0;
  matrix_5(0, 1) = -39.0;
  matrix_5(0, 2) = -162.0;
  matrix_5(0, 3) = -273.0;
  matrix_5(1, 0) = -248.0;
  matrix_5(1, 1) = -6.0;
  matrix_5(1, 2) = 140.0;
  matrix_5(1, 3) = -42.0;
  matrix_5(2, 0) = 88.0;
  matrix_5(2, 1) = -147.0;
  matrix_5(2, 2) = -322.0;
  matrix_5(2, 3) = 579.0;
  matrix_5(3, 0) = 24.0;
  matrix_5(3, 1) = 33.0;
  matrix_5(3, 2) = -234.0;
  matrix_5(3, 3) = 231.0;

  matrix_2 = matrix_1.CalcComplements();
  matrix_6 = matrix_4.CalcComplements();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(matrix_3(i, j), matrix_2(i, j));
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ASSERT_DOUBLE_EQ(matrix_5(i, j), matrix_6(i, j));
    }
  }
}

//  тест, который дает лики
TEST(Complement, CalcComplement2) {
  S21Matrix matrix(2, 5);

  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(Inverse, InverseMatrix1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(3, 3);
  S21Matrix matrix_3(2, 2);
  S21Matrix matrix_4(3, 3);
  S21Matrix matrix_5(3, 3);
  S21Matrix matrix_6(1, 1);
  S21Matrix matrix_7(1, 1);

  double det_1 = -5.0, det_2 = -32.0, det_3 = 8.0;

  matrix_6.FillMatrix(8.0);

  matrix_1(0, 0) = 5.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 5.0;
  matrix_1(1, 1) = 1.0;

  matrix_2(0, 0) = 2.0;
  matrix_2(0, 1) = 4.0;
  matrix_2(0, 2) = 6.0;
  matrix_2(1, 0) = 2.0;
  matrix_2(1, 1) = 8.0;
  matrix_2(1, 2) = 6.0;
  matrix_2(2, 0) = 4.0;
  matrix_2(2, 1) = 4.0;
  matrix_2(2, 2) = 8.0;

  matrix_5(0, 0) = -1.25;
  matrix_5(0, 1) = 0.25;
  matrix_5(0, 2) = 0.75;
  matrix_5(1, 0) = -0.25;
  matrix_5(1, 1) = 0.25;
  matrix_5(1, 2) = 0.0;
  matrix_5(2, 0) = 0.75;
  matrix_5(2, 1) = -0.25;
  matrix_5(2, 2) = -0.25;

  matrix_3 = matrix_1.InverseMatrix();
  matrix_4 = matrix_2.InverseMatrix();
  matrix_7 = matrix_6.InverseMatrix();

  ASSERT_TRUE(matrix_5 == matrix_4);

  ASSERT_DOUBLE_EQ(det_1, matrix_1.Determinant());
  ASSERT_DOUBLE_EQ(det_2, matrix_2.Determinant());
  ASSERT_DOUBLE_EQ(det_3, matrix_6.Determinant());

  ASSERT_DOUBLE_EQ(-0.2, matrix_3(0, 0));
  ASSERT_DOUBLE_EQ(0.4, matrix_3(0, 1));
  ASSERT_DOUBLE_EQ(1.0, matrix_3(1, 0));
  ASSERT_DOUBLE_EQ(-1.0, matrix_3(1, 1));

  ASSERT_DOUBLE_EQ(0.125, matrix_7(0, 0));

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(matrix_5(i, j), matrix_4(i, j));
    }
  }
}

TEST(Inverse, InverseMatrix2) {
  S21Matrix matrix_2(2, 2);

  EXPECT_THROW(matrix_2.InverseMatrix(), std::logic_error);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
