#include <check.h>
#include "../3dviewer/parser.h"
#include "../3dviewer/affine_transform.h"

#define EPS 1e-5


void viewer_testing(SRunner **sr);

START_TEST(viewer_open_file_1) {
	int flag = 0;
	struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
  open_file("not_find.obj", &test);

	ck_assert_uint_eq(flag, test.load_result);
}
END_TEST

START_TEST(viewer_open_file_2) {
	int flag = 1;
	struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
  open_file("tests_/cube.obj", &test);


	ck_assert_uint_eq(flag, test.load_result);
  free_matrix(&test);
}
END_TEST

START_TEST(viewer_open_file_3) {
	int flag = 1;
	struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
	open_file("tests_/cilin.obj", &test);

	ck_assert_uint_eq(flag, test.load_result);
  free_matrix(&test);
}
END_TEST


Suite *viewer_open_file_suite(void) {
  Suite *s;
  TCase *tc_viewer_open_file_suite;
  s = suite_create("\n viewer_open_file");
  tc_viewer_open_file_suite = tcase_create("viewer_open_file");
  tcase_add_test(tc_viewer_open_file_suite, viewer_open_file_1);
  tcase_add_test(tc_viewer_open_file_suite, viewer_open_file_2);
  tcase_add_test(tc_viewer_open_file_suite, viewer_open_file_3);
  suite_add_tcase(s, tc_viewer_open_file_suite);
  return s;
}

START_TEST(viewer_numbers_v_f_1) {
  int flag = 1;
  struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
  open_file("tests_/cube.obj", &test);
  int number_of_vertex_result = 8 * 3;
  int number_of_faces_all_result = 4 * 6;
  
  ck_assert_uint_eq(flag, 1);
  ck_assert_uint_eq(test.number_of_vertex * 3, number_of_vertex_result);
  ck_assert_uint_eq(test.number_of_faces_all, number_of_faces_all_result);
  free_matrix(&test);
}
END_TEST

START_TEST(viewer_numbers_v_f_2) {
  int flag = 1;
  struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
  open_file("tests_/cilin.obj", &test);
  int number_of_vertex_result = 64 * 3;
  int number_of_faces_all_result = 192;
  
  ck_assert_uint_eq(flag, 1);
  ck_assert_uint_eq(test.number_of_vertex * 3, number_of_vertex_result);
  ck_assert_uint_eq(test.number_of_faces_all, number_of_faces_all_result);
  free_matrix(&test);
}
END_TEST

Suite *viewer_numbers_v_f_suite(void) {
  Suite *s;
  TCase *tc_viewer_numbers_v_f;
  s = suite_create("viewer_numbers_v_f");
  tc_viewer_numbers_v_f = tcase_create("viewer_numbers_v_f");
  tcase_add_test(tc_viewer_numbers_v_f, viewer_numbers_v_f_1);
  tcase_add_test(tc_viewer_numbers_v_f, viewer_numbers_v_f_2);
  suite_add_tcase(s, tc_viewer_numbers_v_f);
  return s;
}

START_TEST(viewer_eq_ver_ind_1) {
  int flag = 1;
  struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
  open_file("tests_/cube.obj", &test);
  float test_vertex[24] = {-0.438186, -0.406016, 0.453849,
                          -0.438186, 0.406016, 0.453849,
                          -0.438186, -0.406016, -0.453849, 
                          -0.438186, 0.406016, -0.453849,
                          0.438186, -0.406016, 0.453849,
                          0.438186, 0.406016, 0.453849,
                          0.438186, -0.406016, -0.453849,
                          0.438186, 0.406016, -0.453849};
  unsigned int test_ind[48] = {0, 1, 1, 3, 
                              3, 2, 2, 0,
                              2, 3, 3, 7,
                              7, 6, 6, 2,
                              6, 7, 7, 5,
                              5, 4, 4, 6,
                              4, 5, 5, 1,
                              1, 0, 0, 4,
                              2, 6, 6, 4,
                              4, 0, 0, 2,
                              7, 3, 3, 1,
                              1, 5, 5, 7};
  
  for (int i = 0; i < test.number_of_vertex * 3; i++) {
      int flag_eq = 0;
      if (fabs(test.matrix_of_vertex_origin[i] - test_vertex[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  for (int i = 0; i < test.number_of_faces_all * 2; i++) {
    ck_assert_uint_eq(test.matrix_of_index[i], test_ind[i]);
  }
  ck_assert_uint_eq(flag, 1);
  free_matrix(&test);
}
END_TEST

START_TEST(viewer_eq_ver_ind_2) {
  int flag = 1;
  struct info_figure test = {0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, false, NULL};
  open_file("tests_/cilin.obj", &test);
  float test_vertex[192] = {0.000000, -0.670000, -0.790000,
                          0.000000, 0.670000, -0.790000,
                          0.091692, -0.670000, -0.774820,
                          0.091692, 0.670000, -0.774820,
                          0.179861, -0.670000, -0.729865,
                          0.179861, 0.670000, -0.729865,
                          0.261118, -0.670000, -0.656861,
                          0.261118, 0.670000, -0.656861,
                          0.332340, -0.670000, -0.558614,
                          0.332340, 0.670000, -0.558614,
                          0.390791, -0.670000, -0.438901,
                          0.390791, 0.670000, -0.438901,
                          0.434223, -0.670000, -0.302320,
                          0.434223, 0.670000, -0.302320,
                          0.460969, -0.670000, -0.154121,
                          0.460969, 0.670000, -0.154121,
                          0.470000, -0.670000, 0.000000,
                          0.470000, 0.670000, 0.000000,
                          0.460969, -0.670000, 0.154121,
                          0.460969, 0.670000, 0.154121,
                          0.434223, -0.670000, 0.302320,
                          0.434223, 0.670000, 0.302320,
                          0.390791, -0.670000, 0.438900,
                          0.390791, 0.670000, 0.438900,
                          0.332340, -0.670000, 0.558614,
                          0.332340, 0.670000, 0.558614,
                          0.261118, -0.670000, 0.656861,
                          0.261118, 0.670000, 0.656861,
                          0.179861, -0.670000, 0.729865,
                          0.179861, 0.670000, 0.729865,
                          0.091692, -0.670000, 0.774820,
                          0.091692, 0.670000, 0.774820,
                          -0.000000, -0.670000, 0.790000,
                          -0.000000, 0.670000, 0.790000,
                          -0.091692, -0.670000, 0.774820,
                          -0.091692, 0.670000, 0.774820,
                          -0.179861, -0.670000, 0.729865,
                          -0.179861, 0.670000, 0.729865,
                          -0.261118, -0.670000, 0.656861,
                          -0.261118, 0.670000, 0.656861,
                          -0.332340, -0.670000, 0.558614,
                          -0.332340, 0.670000, 0.558614,
                          -0.390791, -0.670000, 0.438901,
                          -0.390791, 0.670000, 0.438901,
                          -0.434223, -0.670000, 0.302320,
                          -0.434223, 0.670000, 0.302320,
                          -0.460969, -0.670000, 0.154121,
                          -0.460969, 0.670000, 0.154121,
                          -0.470000, -0.670000, -0.000000,
                          -0.470000, 0.670000, -0.000000,
                          -0.460969, -0.670000, -0.154121,
                          -0.460969, 0.670000, -0.154121,
                          -0.434223, -0.670000, -0.302320,
                          -0.434223, 0.670000, -0.302320,
                          -0.390791, -0.670000, -0.438900,
                          -0.390791, 0.670000, -0.438900,
                          -0.332340, -0.670000, -0.558614,
                          -0.332340, 0.670000, -0.558614,
                          -0.261118, -0.670000, -0.656861,
                          -0.261118, 0.670000, -0.656861,
                          -0.179861, -0.670000, -0.729865,
                          -0.179861, 0.670000, -0.729865,
                          -0.091692, -0.670000, -0.774820,
                          -0.091692, 0.670000, -0.774820};
  unsigned int test_ind[384] = {0, 1, 1, 3, 
                              3, 2, 2, 0,
                              2, 3, 3, 5,
                              5, 4, 4, 2,
                              4, 5, 5, 7,
                              7, 6, 6, 4,
                              6, 7, 7, 9,
                              9, 8, 8, 6,
                              8, 9, 9, 11,
                              11, 10, 10, 8,
                              10, 11, 11, 13,
                              13, 12, 12, 10,
                              12, 13, 13, 15,
                              15, 14, 14, 12,
                              14, 15, 15, 17,
                              17, 16, 16, 14,
                              16, 17, 17, 19,
                              19, 18, 18, 16,
                              18, 19, 19, 21,
                              21, 20, 20, 18,
                              20, 21, 21, 23,
                              23, 22, 22, 20,
                              22, 23, 23, 25,
                              25, 24, 24, 22,
                              24, 25, 25, 27,
                              27, 26, 26, 24,
                              26, 27, 27, 29,
                              29, 28, 28, 26,
                              28, 29, 29, 31,
                              31, 30, 30, 28,
                              30, 31, 31, 33,
                              33, 32, 32, 30,
                              32, 33, 33, 35,
                              35, 34, 34, 32,
                              34, 35, 35, 37,
                              37, 36, 36, 34,
                              36, 37, 37, 39,
                              39, 38, 38, 36,
                              38, 39, 39, 41,
                              41, 40, 40, 38,
                              40, 41, 41, 43,
                              43, 42, 42, 40,
                              42, 43, 43, 45,
                              45, 44, 44, 42,
                              44, 45, 45, 47,
                              47, 46, 46, 44,
                              46, 47, 47, 49,
                              49, 48, 48, 46,
                              48, 49, 49, 51,
                              51, 50, 50, 48,
                              50, 51, 51, 53,
                              53, 52, 52, 50,
                              52, 53, 53, 55,
                              55, 54, 54, 52,
                              54, 55, 55, 57,
                              57, 56, 56, 54,
                              56, 57, 57, 59,
                              59, 58, 58, 56,
                              58, 59, 59, 61,
                              61, 60, 60, 58,
                              3, 1, 1, 63,
                              63, 61, 61, 59,
                              59, 57, 57, 55,
                              55, 53, 53, 51,
                              51, 49, 49, 47,
                              47, 45, 45, 43,
                              43, 41, 41, 39,
                              39, 37, 37, 35,
                              35, 33, 33, 31,
                              31, 29, 29, 27,
                              27, 25, 25, 23,
                              23, 21, 21, 19,
                              19, 17, 17, 15,
                              15, 13, 13, 11,
                              11, 9, 9, 7,
                              7, 5, 5, 3,
                              60, 61, 61, 63,
                              63, 62, 62, 60,
                              62, 63, 63, 1,
                              1, 0, 0, 62,
                              0, 2, 2, 4,
                              4, 6, 6, 8,
                              8, 10, 10, 12,
                              12, 14, 14, 16,
                              16, 18, 18, 20,
                              20, 22, 22, 24,
                              24, 26, 26, 28,
                              28, 30, 30, 32,
                              32, 34, 34, 36,
                              36, 38, 38, 40,
                              40, 42, 42, 44,
                              44, 46, 46, 48,
                              48, 50, 50, 52,
                              52, 54, 54, 56,
                              56, 58, 58, 60,
                              60, 62, 62};
  
  for (int i = 0; i < test.number_of_vertex * 3; i++) {
      int flag_eq = 0;
      if (fabs(test.matrix_of_vertex_origin[i] - test_vertex[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  for (int i = 0; i < test.number_of_faces_all * 2; i++) {
    ck_assert_uint_eq(test.matrix_of_index[i], test_ind[i]);
  }
  ck_assert_uint_eq(flag, 1);
  free_matrix(&test);
}
END_TEST

Suite *viewer_eq_ver_ind(void) {
  Suite *s;
  TCase *tc_viewer_eq_ver_ind;
  s = suite_create("viewer_eq_ver_ind");
  tc_viewer_eq_ver_ind = tcase_create("viewer_eq_ver_ind_");
  tcase_add_test(tc_viewer_eq_ver_ind, viewer_eq_ver_ind_1);
  tcase_add_test(tc_viewer_eq_ver_ind, viewer_eq_ver_ind_2);
  suite_add_tcase(s, tc_viewer_eq_ver_ind);
  return s;
}

START_TEST(viewer_affine_move_model_1) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1;
  matrix_vertex_test[1] = 2;
  matrix_vertex_test[2] = 4.5;

  matrix_vertex_test[3] = 5.6;
  matrix_vertex_test[4] = -4.3;
  matrix_vertex_test[5] = 7.3;

  matrix_vertex_test[6] = 7;
  matrix_vertex_test[7] = 0;
  matrix_vertex_test[8] = 10.23;

  move_model(matrix_vertex_test, 0, 9, 4.5);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  matrix_vertex_test_result[0] = 5.5;
  matrix_vertex_test_result[1] = 2;
  matrix_vertex_test_result[2] = 4.5;

  matrix_vertex_test_result[3] = 10.1;
  matrix_vertex_test_result[4] = -4.3;
  matrix_vertex_test_result[5] = 7.3;

  matrix_vertex_test_result[6] = 11.5;
  matrix_vertex_test_result[7] = 0;
  matrix_vertex_test_result[8] = 10.23;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);

}
END_TEST

START_TEST(viewer_affine_move_model_2) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1;
  matrix_vertex_test[1] = 2;
  matrix_vertex_test[2] = 4.5;

  matrix_vertex_test[3] = 5.6;
  matrix_vertex_test[4] = -4.3;
  matrix_vertex_test[5] = 7.3;

  matrix_vertex_test[6] = 7;
  matrix_vertex_test[7] = 0;
  matrix_vertex_test[8] = 10.23;

  move_model(matrix_vertex_test, 1, 9, 4.5);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  matrix_vertex_test_result[0] = 1;
  matrix_vertex_test_result[1] = 6.5;
  matrix_vertex_test_result[2] = 4.5;

  matrix_vertex_test_result[3] = 5.6;
  matrix_vertex_test_result[4] = 0.2;
  matrix_vertex_test_result[5] = 7.3;
  matrix_vertex_test_result[6] = 7;

  matrix_vertex_test_result[7] = 4.5;
  matrix_vertex_test_result[8] = 10.23;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);

}
END_TEST

START_TEST(viewer_affine_move_model_3) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1;
  matrix_vertex_test[1] = 2;
  matrix_vertex_test[2] = 4.5;
  
  matrix_vertex_test[3] = 5.6;
  matrix_vertex_test[4] = -4.3;
  matrix_vertex_test[5] = 7.3;

  matrix_vertex_test[6] = 7;
  matrix_vertex_test[7] = 0;
  matrix_vertex_test[8] = 10.23;

  move_model(matrix_vertex_test, 2, 9, 4.5);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  matrix_vertex_test_result[0] = 1;
  matrix_vertex_test_result[1] = 2;
  matrix_vertex_test_result[2] = 9;

  matrix_vertex_test_result[3] = 5.6;
  matrix_vertex_test_result[4] = -4.3;
  matrix_vertex_test_result[5] = 11.8;

  matrix_vertex_test_result[6] = 7;
  matrix_vertex_test_result[7] = 0;
  matrix_vertex_test_result[8] = 14.73;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);

}
END_TEST

START_TEST(viewer_affine_rotation_by_ox) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1;
  matrix_vertex_test[1] = 2;
  matrix_vertex_test[2] = 4.5;

  matrix_vertex_test[3] = 5.6;
  matrix_vertex_test[4] = -4.3;
  matrix_vertex_test[5] = 7.3;

  matrix_vertex_test[6] = 7;
  matrix_vertex_test[7] = 0;
  matrix_vertex_test[8] = 10.23;

  rotation_by_ox(matrix_vertex_test, 3, 11);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  
  matrix_vertex_test_result[0] = 1;
  matrix_vertex_test_result[1] = 4.508807;
  matrix_vertex_test_result[2] = -1.980065;

  matrix_vertex_test_result[3] = 5.6;
  matrix_vertex_test_result[4] = 7.280898;
  matrix_vertex_test_result[5] = 4.332266;

  matrix_vertex_test_result[6] = 7;
  matrix_vertex_test_result[7] = 10.229899;
  matrix_vertex_test_result[8] = 0.045275;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);

}
END_TEST

START_TEST(viewer_affine_rotation_by_oy) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1;
  matrix_vertex_test[1] = 4.508807;
  matrix_vertex_test[2] = -1.980065;

  matrix_vertex_test[3] = 5.6;
  matrix_vertex_test[4] = 7.280898;
  matrix_vertex_test[5] = 4.332266;

  matrix_vertex_test[6] = 7;
  matrix_vertex_test[7] = 10.229899;
  matrix_vertex_test[8] = 0.045275;

  rotation_by_oy(matrix_vertex_test, 3, 17);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  
  matrix_vertex_test_result[0] = 1.628466;
  matrix_vertex_test_result[1] = 4.508807;
  matrix_vertex_test_result[2] = 1.506239;

  matrix_vertex_test_result[3] = -5.705944;
  matrix_vertex_test_result[4] = 7.280898;
  matrix_vertex_test_result[5] = 4.191745;

  matrix_vertex_test_result[6] = -1.969671;
  matrix_vertex_test_result[7] = 10.229899;
  matrix_vertex_test_result[8] = 6.717324;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);

}
END_TEST

START_TEST(viewer_affine_rotation_by_oz) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1.628466;
  matrix_vertex_test[1] = 4.508807;
  matrix_vertex_test[2] = 1.506239;

  matrix_vertex_test[3] = -5.705944;
  matrix_vertex_test[4] = 7.280898;
  matrix_vertex_test[5] = 4.191745;

  matrix_vertex_test[6] = -1.969671;
  matrix_vertex_test[7] = 10.229899;
  matrix_vertex_test[8] = 6.717324;

  rotation_by_oz(matrix_vertex_test, 3, 17);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  
  matrix_vertex_test_result[0] = 3.886662;
  matrix_vertex_test_result[1] = -2.806262;
  matrix_vertex_test_result[2] = 1.506239;

  matrix_vertex_test_result[3] = 8.569904;
  matrix_vertex_test_result[4] = 3.482244;
  matrix_vertex_test_result[5] = 4.191745;

  matrix_vertex_test_result[6] = 10.376981;
  matrix_vertex_test_result[7] = -0.921256;
  matrix_vertex_test_result[8] = 6.717324;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);
}
END_TEST

START_TEST(viewer_affine_scale_1) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1.628466;
  matrix_vertex_test[1] = 4.508807;
  matrix_vertex_test[2] = 1.506239;

  matrix_vertex_test[3] = -5.705944;
  matrix_vertex_test[4] = 7.280898;
  matrix_vertex_test[5] = 4.191745;

  matrix_vertex_test[6] = -1.969671;
  matrix_vertex_test[7] = 10.229899;
  matrix_vertex_test[8] = 6.717324;

  scale_model(matrix_vertex_test, 9, 2.33);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  
  matrix_vertex_test_result[0] = 3.794326;
  matrix_vertex_test_result[1] = 10.505521;
  matrix_vertex_test_result[2] = 3.509537;

  matrix_vertex_test_result[3] = -13.294850;
  matrix_vertex_test_result[4] = 16.964493;
  matrix_vertex_test_result[5] = 9.766765;

  matrix_vertex_test_result[6] = -4.589333;
  matrix_vertex_test_result[7] = 23.835666;
  matrix_vertex_test_result[8] = 15.651364;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);
}
END_TEST

START_TEST(viewer_affine_scale_2) {
  float *matrix_vertex_test = (float *)calloc(9, sizeof(float));
  matrix_vertex_test[0] = 1.628466;
  matrix_vertex_test[1] = 4.508807;
  matrix_vertex_test[2] = 1.506239;

  matrix_vertex_test[3] = -5.705944;
  matrix_vertex_test[4] = 7.280898;
  matrix_vertex_test[5] = 4.191745;

  matrix_vertex_test[6] = -1.969671;
  matrix_vertex_test[7] = 10.229899;
  matrix_vertex_test[8] = 6.717324;

  scale_model(matrix_vertex_test, 9, -0.3);

  float *matrix_vertex_test_result = (float *)calloc(9, sizeof(float));
  
  matrix_vertex_test_result[0] = -0.488540;
  matrix_vertex_test_result[1] = -1.352642;
  matrix_vertex_test_result[2] = -0.451872;

  matrix_vertex_test_result[3] = 1.711783;
  matrix_vertex_test_result[4] = -2.184269;
  matrix_vertex_test_result[5] = -1.257523;

  matrix_vertex_test_result[6] = 0.590901;
  matrix_vertex_test_result[7] = -3.068970;
  matrix_vertex_test_result[8] = -2.015197;


  for (int i = 0; i < 9; i++) {
      int flag_eq = 0;
      if (fabs(matrix_vertex_test[i] - matrix_vertex_test_result[i]) < EPS) 
        flag_eq = 1;
      ck_assert_int_eq(1, flag_eq);
  }
  free(matrix_vertex_test);
  free(matrix_vertex_test_result);
}
END_TEST

Suite *viewer_affine(void) {
  Suite *s;
  TCase *tc_viewer_affine;
  s = suite_create("viewer_affine");
  tc_viewer_affine = tcase_create("viewer_affine");
  tcase_add_test(tc_viewer_affine, viewer_affine_move_model_1);
  tcase_add_test(tc_viewer_affine, viewer_affine_move_model_2);
  tcase_add_test(tc_viewer_affine, viewer_affine_move_model_3);
  tcase_add_test(tc_viewer_affine, viewer_affine_rotation_by_ox);
  tcase_add_test(tc_viewer_affine, viewer_affine_rotation_by_oy);
  tcase_add_test(tc_viewer_affine, viewer_affine_rotation_by_oz);
  tcase_add_test(tc_viewer_affine, viewer_affine_scale_1);
  tcase_add_test(tc_viewer_affine, viewer_affine_scale_2);
  suite_add_tcase(s, tc_viewer_affine);
  return s;
}

void viewer_testing(SRunner **sr) {
  *sr = srunner_create(viewer_open_file_suite());
  srunner_add_suite(*sr, viewer_numbers_v_f_suite());
  srunner_add_suite(*sr, viewer_eq_ver_ind());
  srunner_add_suite(*sr, viewer_affine());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  viewer_testing(&sr);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}