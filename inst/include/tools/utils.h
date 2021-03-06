#ifndef dplyr_tools_utils_H
#define dplyr_tools_utils_H

#include <tools/SymbolVector.h>

void check_valid_colnames(const DataFrame& df, bool warn_only = false);
int check_range_one_based(int x, int max);
void assert_all_allow_list(const DataFrame&);
SEXP shared_SEXP(SEXP x);
SEXP shallow_copy(const List& data);
SEXP pairlist_shallow_copy(SEXP p);
void copy_attributes(SEXP out, SEXP data);
SEXP null_if_empty(SEXP x);

bool is_vector(SEXP x);
bool is_atomic(SEXP x);

SEXP vec_names(SEXP x);
SEXP vec_names_or_empty(SEXP x);
bool is_str_empty(SEXP str);
bool has_name_at(SEXP x, R_len_t i);

SEXP child_env(SEXP parent);

int get_size(SEXP x);


namespace dplyr {

SEXP constant_recycle(SEXP x, int n, const SymbolString& name);
std::string get_single_class(SEXP x);
CharacterVector default_chars(SEXP x, R_xlen_t len);
CharacterVector get_class(SEXP x);
SEXP set_class(SEXP x, const CharacterVector& class_);
void copy_class(SEXP out, SEXP origin);
void copy_names(SEXP out, SEXP origin);
CharacterVector get_levels(SEXP x);
SEXP set_levels(SEXP x, const CharacterVector& levels);
bool same_levels(SEXP left, SEXP right);
bool character_vector_equal(const CharacterVector& x, const CharacterVector& y);

SymbolVector get_vars(SEXP x);

// effectively the same as copy_attributes but without names and dims
inline void copy_most_attributes(SEXP out, SEXP data) {
  Rf_copyMostAttrib(data, out);
}


namespace internal {

// *INDENT-OFF*
struct rlang_api_ptrs_t {
  SEXP (*quo_get_expr)(SEXP quo);
  SEXP (*quo_set_expr)(SEXP quo, SEXP expr);
  SEXP (*quo_get_env)(SEXP quo);
  SEXP (*quo_set_env)(SEXP quo, SEXP env);
  SEXP (*new_quosure)(SEXP expr, SEXP env);
  bool (*is_quosure)(SEXP x);
  SEXP (*as_data_pronoun)(SEXP data);
  SEXP (*as_data_mask)(SEXP data, SEXP parent);
  SEXP (*new_data_mask)(SEXP bottom, SEXP top);

  rlang_api_ptrs_t() {
    quo_get_expr =      (SEXP (*)(SEXP))             R_GetCCallable("rlang", "rlang_quo_get_expr");
    quo_set_expr =      (SEXP (*)(SEXP, SEXP))       R_GetCCallable("rlang", "rlang_quo_set_expr");
    quo_get_env =       (SEXP (*)(SEXP))             R_GetCCallable("rlang", "rlang_quo_get_env");
    quo_set_env =       (SEXP (*)(SEXP, SEXP))       R_GetCCallable("rlang", "rlang_quo_set_env");
    new_quosure =       (SEXP (*)(SEXP, SEXP))       R_GetCCallable("rlang", "rlang_new_quosure");
    is_quosure =        (bool (*)(SEXP))             R_GetCCallable("rlang", "rlang_is_quosure");
    as_data_pronoun =   (SEXP (*)(SEXP))             R_GetCCallable("rlang", "rlang_as_data_pronoun");
    as_data_mask =      (SEXP (*)(SEXP, SEXP))       R_GetCCallable("rlang", "rlang_as_data_mask");
    new_data_mask =     (SEXP (*)(SEXP, SEXP))       R_GetCCallable("rlang", "rlang_new_data_mask_3.0.0");
  }
};
// *INDENT-ON*

const rlang_api_ptrs_t& rlang_api();

} // namespace internal


} // dplyr

namespace rlang {

inline SEXP quo_get_expr(SEXP quo) {
  return dplyr::internal::rlang_api().quo_get_expr(quo);
}

inline SEXP quo_get_env(SEXP quo) {
  return dplyr::internal::rlang_api().quo_get_env(quo);
}

inline bool is_quosure(SEXP x) {
  return dplyr::internal::rlang_api().is_quosure(x);
}

inline SEXP new_data_mask(SEXP bottom, SEXP top) {
  return dplyr::internal::rlang_api().new_data_mask(bottom, top);
}

inline SEXP as_data_pronoun(SEXP data) {
  return dplyr::internal::rlang_api().as_data_pronoun(data);
}

}

#endif // #ifndef dplyr_tools_utils_H
